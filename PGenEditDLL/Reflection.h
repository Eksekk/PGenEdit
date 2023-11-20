#pragma once
#include "main.h"
#include "CallEvents.h"
#include "LuaWrapper.h"

// will contain utils for dealing with RTTR reflection system, like a template method for calling any method by name, converting lua types to required C++ types etc.
class Reflection
{
    template<int index, typename... Args>
    static bool convertLuaParametersToCppInner(std::tuple<Args...>& output)
    {
        std::get<index>(output) = convertSingleLuaStackArg(-1 - index);
        if constexpr (index < sizeof...(Args) - 1)
        {
            return convertLuaParametersToCppInner<index + 1>(output);
        }
        return true;
    }
    public:
    template<typename... Args>
    bool convertLuaParametersToCpp(std::tuple<Args...>& output)
    {
        wxASSERT_MSG(lua_gettop(Lua) >= sizeof...(Args), "Not enough parameters on stack!");
        return convertLuaParametersToCppInner<0, Args...>(output);
        // TODO
    }
public:
    template<typename... CallArgTypes>
    static rttr::variant callFreeFunctionByName(const std::string& functionName, CallArgTypes&&... args)
    {
        auto method = rttr::type::get_global_method(functionName);
        wxASSERT_MSG(method.is_valid(), "Invalid method name!");
        return method.invoke_variadic(std::forward<CallArgTypes>(args)...);
    }

    template<typename Class, typename... CallArgTypes>
    static rttr::variant callInstanceMethodByName(Class* instance, const std::string& methodName, CallArgTypes&&... args)
    {
        auto method = instance->get_type().get_method(methodName);
        wxASSERT_MSG(method.is_valid(), "Invalid method name!");
        return method.invoke_variadic(*instance, std::forward<CallArgTypes>(args)...);
    }

    // get property by name
    template<typename Class>
    static rttr::variant getPropertyByName(Class* instance, const std::string& propertyName)
    {
        auto prop = instance->get_type().get_property(propertyName);
        if (!prop.is_valid())
        {
            return rttr::variant(); // return empty variant to allow caller to check if property was found
            // maybe should use exceptions instead, oh well
        }
        wxASSERT_MSG(prop.is_valid(), "Invalid property name!");
        return prop.get_value(*instance);
    }

    // set property by name
    template<typename Class>
    static bool setPropertyByName(Class* instance, const std::string& propertyName, const rttr::variant& value)
    {
        auto prop = instance->get_type().get_property(propertyName);
        if (!prop.is_valid())
        {
            return false;
        }
        prop.set_value(*instance, value);
        return true;
    }

    // get global variable
    template<typename T>
    static rttr::variant getGlobalVariableByName(const std::string& variableName)
    {
        auto var = rttr::type::get_global_variable(variableName);
        if (!var.is_valid())
        {
            return rttr::variant(); // return empty variant to allow caller to check if global variable was found
        }
        return var.get_value();
    }

    // set global variable
    template<typename T>
    static bool setGlobalVariableByName(const std::string& variableName, const rttr::variant& value)
    {
        auto var = rttr::type::get_global_variable(variableName);
        if (!var.is_valid())
        {
            return false;
        }
        var.set_value(value);
        return true;
    }

    // create instance of the class with given constructor parameters and return raw pointer to it
    template<typename Class, typename... CallArgTypes>
    static Class* createInstanceByConstructorArgs(CallArgTypes&&... args)
    {
        auto ctor = rttr::type::get<Class>().get_constructor<CallArgTypes...>();
        if (!ctor.is_valid())
        {
            return nullptr;
        }
        return ctor.invoke_variadic(std::forward<CallArgTypes>(args)...).get_value<Class*>();
    }
};