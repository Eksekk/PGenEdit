#pragma once
#include "pch.h"
#include "main.h"

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

template<typename... Args>
using HandlerFuncType = std::function<void(Args&... args)>;

template<typename... Args>
HandlerFuncType<Args...> getEventActivator(const std::string& eventName, HandlerFuncType<Args...> handler, Args&&... args)
{
    return [=]()
        {

        };
}