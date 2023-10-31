#pragma once
#include "pch.h"
#include "main.h"
#include "LuaFunctions.h"
#include "Utility.h"
#include "LuaWrapper.h"

namespace
{
    template <typename T>
    using Ref = std::reference_wrapper<T>;
    using _EventArgKeyValue = std::variant<
        Ref<qword_t>, Ref<sqword_t>,
        Ref<dword_t>, Ref<sdword_t>,
        Ref<word_t>, Ref<sword_t>,
        Ref<byte_t>, Ref<sbyte_t>,
        Ref<float>, Ref<double>, Ref<long double>,
        Ref<std::string>, Ref<void*>, Ref<bool>
    >;

}
using EventArgKeyValue = std::variant<
    Ref<qword_t>, Ref<sqword_t>,
    Ref<dword_t>, Ref<sdword_t>,
    Ref<word_t>, Ref<sword_t>,
    Ref<byte_t>, Ref<sbyte_t>,
    Ref<float>, Ref<double>, Ref<long double>,
    Ref<std::string>, Ref<void*>, Ref<bool>/*,
    Ref<_EventArgKeyValue>*/ // no subtables for now
>;

using EventArgsMap = std::unordered_map<EventArgKeyValue, EventArgKeyValue>;

using EventArg = std::variant<EventArgKeyValue, EventArgsMap>;

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
}

// auto will work here, because there will be one template instantion per possible type
template<typename ArgType>
auto convertSingleLuaStackArg(int stackIndex)
{
    int type = lua_type(Lua, stackIndex);
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
            throw std::logic_error(getLuaTypeMismatchString({LUA_TNUMBER, LUA_TBOOLEAN}, type, stackIndex));
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
}

// we know types of destination args, still have to return it as variants (containing passed type), or tuple of specific args, or throw exception
// pass stack index and take next args from incrementing it

template<int current = 0, template<typename...> typename Tuple, typename... Args>
static void processSingleLuaArgRecursive(int stackIndexFirst, Tuple<Args...>& tuple)
{
    if constexpr (current < sizeof...(Args))
    {
        using ElemType = std::tuple_element_t<current, Tuple<Args...>>;
        std::get<current>(tuple) = convertSingleLuaStackArg<ElemType>(stackIndexFirst + current);
        processSingleLuaArgRecursive<current + 1, Tuple, Args...>(stackIndexFirst, tuple);
    }
}

// NEEDS TO RETURN EventArg type!
template<typename... Args>
std::tuple<Args...> convertLuaToCpp(int stackIndexFirst)
{
    // this can throw
    std::tuple<Args...> tup;
    processSingleLuaArgRecursive<sizeof...(Args)>(stackIndexFirst, tup);
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
    auto x = convertLuaToCpp<int, char, bool>(1);
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

template<typename... Args, typename... ReturnArgs>
ReturnFuncType<std::tuple<ReturnArgs...>, Args...> getEventActivator(const std::string& eventName, const std::tuple<ReturnArgs...>&) // dummy tuple to allow second parameter pack
{
    constexpr const int count = sizeof...(Args);
    return [=](Args... args) -> std::tuple<int, std::tuple<ReturnArgs...>>
    {
        int stackPos = lua_gettop(Lua);
        // TODO: a version which receives keys as separate arguments, converts them and gets path
        luaWrapper.getPath("pgenedit.events");
        lua_pushlstring(Lua, eventName.data(), eventName.size());
        lua_gettable(Lua, -2);
        lua_replace(Lua, -2); // replaces table
        lua_getfield(Lua, -1, "call");
        lua_replace(Lua, -2); // replaces events subtable
        pushCppArgs(std::make_tuple(args...));
        if (!lua_pcall(Lua, count, 0/*!!!!!!!*/, 0))
        {
            wxLogError("Event handler for '%s' pgenedit event caused error: %s", eventName, lua_tostring(Lua, -1));
            lua_settop(Lua, stackPos);
            return make_tuple(0, std::tuple<ReturnArgs...>());
        }
        // FIXME: clean Lua error (somehow deal with longjmp) instead of hard crash
        wxASSERT_MSG(lua_gettop(Lua) - stackPos >= sizeof...(ReturnArgs), wxString::Format("Expected at least %d stack args, current number of stack args is %d", sizeof...(Args), lua_gettop(Lua)));
        // can have not all args returned
        // args can have different types!
        std::tuple<ReturnArgs...> returnTuple = convertLuaToCpp<ReturnArgs...>(lua_gettop(Lua) - sizeof...(ReturnArgs) + 1);
        lua_settop(Lua, stackPos);
        return make_tuple(1, returnTuple);
    };
}