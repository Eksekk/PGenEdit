#pragma once
#include "pch.h"
#include "main.h"
#include "LuaFunctions.h"
#include "Utility.h"
#include "LuaWrapper.h"
#include "LuaTable.h"

// call this function, must receive eventName, handler function taking args by reference, and args, which should be taken by reference or pointer
// 
// function sets pgenedit.events[eventName] to generated lua-interacting function and returns a lambda, which will call the event,
// receive/modify args, and maybe return values returned by event handler (hard!)
// 
// there needs to be some intermediate lua-interacting function to get args from stack, update values after handler is executed,
// change types between Lua and C++, optionally generate Lua error if there is a problem
//
// for simplicity, handler function will be same type as returned activator function, in future handler might receive any extra args
//
// Args... type needs to support "pseudo-tables" with reference wrappers to represent lua tables and access/modify them (recursive variant type?)
//
// since C++ has static typing, it's probably impossible to do variable arg number templates (or very annoying to use vector of std::any), I'm doing static number of basic args
// additional args (like, not present by default) will be inside table parameter

template<typename ArgType>
auto convertLuaTypeToCpp(ArgType& arg)
{
    if constexpr (SAME(ArgType, bool))
    {
        return arg;
    }
    else if constexpr (std::is_arithmetic_v<ArgType>)
    {
        return static_cast<lua_Number>(arg);
    }
    else if constexpr (SAME(ArgType, std::string))
    {
        return arg;
    }
    else if constexpr (std::is_pointer_v<ArgType>)
    {
        return (lua_Number)(dword_t)arg;
    }
    else if constexpr (SAME(ArgType, LuaTable))
    {
        return arg;
    }
}

// auto will work here, because there will be one template instantion per possible type
template<typename ArgType>
auto convertSingleLuaStackArg(int stackIndex)
{
    int type = lua_type(Lua, stackIndex);
    if (type == LUA_TNIL)
    {
        return ArgType(); // default-constructed
        // TO CONSIDER: using unique_ptr's everywhere might allow for unspecified args to be nullptr
    }
    else
    {

        if constexpr (SAME(ArgType, bool))
        {
            return lua_toboolean(Lua, stackIndex);
        }
        else if constexpr (std::is_arithmetic_v<ArgType>)
        {
            if (type == LUA_TNUMBER)
            {
                return static_cast<ArgType>(lua_tonumber(Lua, stackIndex));
            }
            else if (type == LUA_TBOOLEAN)
            {
                return static_cast<ArgType>(lua_toboolean(Lua, stackIndex));
            }
            else
            {
                // not sure how I want to handle this, using exceptions for now
                throw std::logic_error(getLuaTypeMismatchString({ LUA_TNUMBER, LUA_TBOOLEAN }, type, stackIndex));
            }
        }
        else if constexpr (SAME(ArgType, std::string))
        {
            if (type == LUA_TSTRING)
            {
                size_t len;
                const char* str = lua_tolstring(Lua, stackIndex, &len);
                return std::string(str, len);
            }
            else
            {
                throw std::logic_error(getLuaTypeMismatchString({ LUA_TSTRING }, type, stackIndex));
            }
        }
        else if constexpr (std::is_pointer_v<ArgType>)
        {
            return reinterpret_cast<ArgType>(convertSingleLuaStackArg<dword_t>(stackIndex));
        }
        else if constexpr (SAME(ArgType, LuaTable))
        {
            return LuaTable::fromLuaTable(stackIndex);
        }
    }
}

// we know types of destination args, still have to return it as variants (containing passed type), or tuple of specific args, or throw exception
// pass stack index and take next args from incrementing it

template<int current = 0, typename... Args>
static void processSingleLuaArgRecursive(int stackIndexFirst, std::tuple<Args...>& tuple)
{
    if constexpr (current < sizeof...(Args))
    {
        using ElemType = std::tuple_element_t<current, std::tuple<Args...>>;
        std::get<current>(tuple) = convertSingleLuaStackArg<ElemType>(stackIndexFirst + current);
        processSingleLuaArgRecursive<current + 1>(stackIndexFirst, tuple);
    }
}

template<typename... Args>
std::tuple<Args...> convertLuaToCpp(int stackIndexFirst)
{
    // this can throw
    std::tuple<Args...> tup;
    processSingleLuaArgRecursive<0, Args...>(stackIndexFirst, tup);
    return tup;
}

template<int current = 0, typename... Args>
static void pushSingleCppArgRecursive(const std::tuple<Args...>& tup)
{
    if constexpr (current < sizeof...(Args))
    {
        const auto& val = std::get<current>(tup);
        using T = std::remove_cvref_t<decltype(val)>;
        if constexpr (SAME(T, bool))
        {
            lua_pushboolean(Lua, val);
        }
        else if constexpr (std::is_arithmetic_v<T>) // bool is also arithmetic, but this branch is entered only if it's not bool - see above if
        {
            lua_pushnumber(Lua, val);
        }
        else if constexpr (SAME(T, std::string))
        {
            lua_pushlstring(Lua, val.data(), val.size());
        }
        else if constexpr (std::is_same_v<std::decay_t<decltype(val)>, void*>) // using std decay there, because it keeps pointer
        {
            lua_pushnumber(Lua, reinterpret_cast<dword_t>(val));
            wxFAIL; // static_assert always fails
        }
        else
        {
            wxLogError("Unknown type");
            wxLog::FlushActive();
            showDeducedType(val);
        }
        pushSingleCppArgRecursive<current + 1>(tup);
    }
}

// NEEDS TO RECEIVE EventArg types!
template<typename... Args>
static void pushCppArgs(const std::tuple<Args...>& args)
{
    pushSingleCppArgRecursive(args);
}

static void ff()
{
    std::tuple<int, std::string, bool> tup(5, "aaa", false);
    pushCppArgs(tup);
}

// getEventActivator returns function, which, when called, will call the event with provided args
// receives event name

template<typename... ReturnTypes>
struct CustomReturnCaller
{
    //template<typename... Args>
    //static std::tuple<ReturnTypes> getEventActivator() {}
};

// returns tuple with first argument equal to number of returned args, and second containing parameters
template<typename Ret, typename... Args>
using ReturnFuncType = std::function<std::tuple<int, Ret>(Args...)>;

// GRAYFACE'S EVENTS support returning only one value!
template<typename... Args, typename... ReturnArgs> // "real" parameter pack (specified) must be first
ReturnFuncType<std::tuple<ReturnArgs...>, Args...> getEventActivator(const std::string& eventName, const std::tuple<ReturnArgs...>&) // dummy tuple to allow second parameter pack
{
    static_assert(sizeof...(ReturnArgs) <= 1, "Grayface's events support returning only one value");
    constexpr const int count = sizeof...(Args);
    return [=](Args... args) -> std::tuple<int, std::tuple<ReturnArgs...>>
    {
        int stackPos = lua_gettop(Lua);
        luaWrapper.getPath("pgenedit.events.call");
        lua_pushlstring(Lua, eventName.data(), eventName.size());
        pushCppArgs(std::make_tuple(args...));
        if (lua_pcall(Lua, count + 1, sizeof...(ReturnArgs), 0)) // unspecified return values will be nils
        {
            wxLogError("Event handler for '%s' pgenedit event caused error: %s", eventName, lua_tostring(Lua, -1));
            wxLog::FlushActive();
            lua_settop(Lua, stackPos);
            return make_tuple(0, std::tuple<ReturnArgs...>());
        }
        // FIXME: clean Lua error (somehow deal with longjmp) instead of hard crash
        int providedCount = lua_gettop(Lua) - stackPos;
        //wxASSERT_MSG(lua_gettop(Lua) - stackPos >= sizeof...(ReturnArgs), wxString::Format("Expected at least %d stack args, current number of stack args is %d", sizeof...(ReturnArgs), lua_gettop(Lua)));
        // can have not all args returned
        // args can have different types!
        std::tuple<ReturnArgs...> returnTuple = convertLuaToCpp<ReturnArgs...>(lua_gettop(Lua) - sizeof...(ReturnArgs) + 1);
        lua_settop(Lua, stackPos);
        return make_tuple(1, returnTuple);
    };
}