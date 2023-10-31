#pragma once
#include "pch.h"
#include "main.h"
#include "LuaFunctions.h"
#include "Utility.h"

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

template<int stackIndexFirst, int count, int current = 0, template<typename...> typename Tuple, typename... Args>
static void processSingleLuaArgRecursive(Tuple<Args...>& tuple)
{
    if constexpr (current < count)
    {
        using ElemType = std::tuple_element_t<current, Tuple<Args...>>;
        std::get<current>(tuple) = convertSingleLuaStackArg<ElemType>(stackIndexFirst + current);
        processSingleLuaArgRecursive<stackIndexFirst, count, current + 1, Tuple, Args...>(tuple);
    }
}

// NEEDS TO RETURN EventArg type!
template<int stackIndexFirst, typename... Args>
std::tuple<Args...> convertLuaToCpp()
{
    try 
    {
        std::tuple<Args...> tup;
        processSingleLuaArgRecursive<stackIndexFirst, sizeof...(Args)>(tup);
        return tup;
    }
    catch (const std::exception& ex)
    {
    	
    }
}

auto x = convertLuaToCpp<1, int, char, bool>();

template<int current, typename... Args>
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
    pushSingleCppArgRecursive<0, Args...>(args);
}

static void ff()
{
    std::tuple<int, std::string, bool> tup(5, "aaa", false);
    pushCppArgs(tup);
}

template<typename... Args>
using HandlerFuncType = std::function<void(Args&... args)>;

template<typename... Args>
HandlerFuncType<Args...> getEventActivator(const std::string& eventName, HandlerFuncType<Args...> handler, Args&&... args)
{
    return [=](Args&... args)
        {

        };
}