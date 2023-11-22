#pragma once
#include "main.h"
#include "CallEvents.h"
#include "LuaWrapper.h"

template<typename T>
concept IsCvUnqualifiedTopLevel = !(std::is_const_v<std::remove_reference_t<T>> || std::is_volatile_v<std::remove_reference_t<T>>);

// will contain utils for dealing with RTTR reflection system, like a template method for calling any method by name, converting lua types to required C++ types etc.
class Reflection
{
    // so, I need to be able to call any method by name, and I need to be able to convert lua types to C++ types
    // however, we don't know the exact signature (types) of the method, and converting lua types to
    // **exactly matching** C++ types (RTTR requires it) is not trivial
    // (for example, there are two types for numbers: integer and float, and lua (5.1) doesn't distinguish between them, so 7 could be just 7 or 7.0 [double])
    // so I will store the type_id of those types, they will change with each different game launch, but will be the same, once I set them dynamically in .cpp file of this class
    // this allows to "get exact type" of method parameter, still will require a ton of ifs, but should work
    // NOTE: when creating those ifs, we need to strip any const or volatile qualifiers
public:
    using type = rttr::type;
    using type_id = type::type_id;
    static const type_id TYPE_ID_CHAR;
    static const type_id TYPE_ID_UNSIGNED_CHAR;
    static const type_id TYPE_ID_SHORT;
    static const type_id TYPE_ID_UNSIGNED_SHORT;
    static const type_id TYPE_ID_INT;
    static const type_id TYPE_ID_UNSIGNED_INT;
    static const type_id TYPE_ID_LONG;
    static const type_id TYPE_ID_UNSIGNED_LONG;
    static const type_id TYPE_ID_LONG_LONG;
    static const type_id TYPE_ID_UNSIGNED_LONG_LONG;
    static const type_id TYPE_ID_FLOAT;
    static const type_id TYPE_ID_DOUBLE;
    static const type_id TYPE_ID_LONG_DOUBLE;
    static const type_id TYPE_ID_BOOL;
    static const type_id TYPE_ID_STRING;
    static const type_id TYPE_ID_STRING_VIEW;
    static const type_id TYPE_ID_VOID_PTR;
    static const type_id TYPE_ID_LUA_TABLE;
    static const type_id TYPE_ID_NIL;

    // combinations of individual types
    static const std::vector<type_id> TYPE_IDS_INTEGERS; // excludes floating-point types
    static const std::vector<type_id> TYPE_IDS_NUMBERS; // includes floating-point types
    static const std::vector<type_id> TYPE_IDS_FLOATS;
    static const std::vector<type_id> TYPE_IDS_STRINGS;
    static const std::vector<type_id> TYPE_IDS_POINTERS;
    static const std::vector<type_id> TYPE_IDS_ALL_TYPES;

    // FIXME: make a method checking compatibility of two types, so that we can check if we can convert lua type to C++ type, which is parameter of the method
    // if any parameter doesn't match (remember about cv!), we can't call the method with this overload
    // remember about special handling for types in lua, which natively are not in C++ (like nil, table, function, userdata, thread)
    // and remember about integer/float distinction required in lua -> cpp conversion

    // lua can be converted to cpp like this [these brackets mean the conversion needs to be explicitly requested]:
    // number -> char, short, int, long, long long, float, double, long double, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long, [bool]
    // string -> std::string, std::string_view, char*, [bool]
    // boolean -> bool, [all integer formats like int]
    // table -> LuaTable, [bool]
    // nil -> _Nil, [bool]
    // function -> none
    // thread -> none
    // userdata -> void*
    // lightuserdata -> void*
    // any lua type representable in cpp -> LuaTypeInCpp, rttr::variant

    // converts lua parameter from stack to given type (using RTTR type_id)
    // allowCrossTypeCategoryConversions allows to convert lua types to C++ types, which are not exactly matching, but are compatible (like number to boolean)
    static rttr::variant convertStackIndexToTypeById(int stackIndex, const type_id& typ, bool allowCrossTypeCategoryConversions = false)
    {
        stackIndex = luaWrapper.makeAbsoluteStackIndex(stackIndex);
        switch (lua_type(Lua, stackIndex))
        {
        case LUA_TNUMBER:
        {
            lua_Number num = lua_tonumber(Lua, stackIndex);
            if (existsInVector(TYPE_IDS_NUMBERS, typ))
            {
                if (typ == TYPE_ID_CHAR)
                {
                    return static_cast<char>(num);
                }
                else if (typ == TYPE_ID_UNSIGNED_CHAR)
                {
                    return static_cast<unsigned char>(num);
                }
                else if (typ == TYPE_ID_SHORT)
                {
                    return static_cast<short>(num);
                }
                else if (typ == TYPE_ID_UNSIGNED_SHORT)
                {
                    return static_cast<unsigned short>(num);
                }
                else if (typ == TYPE_ID_INT)
                {
                    return static_cast<int>(num);
                }
                else if (typ == TYPE_ID_UNSIGNED_INT)
                {
                    return static_cast<unsigned int>(num);
                }
                else if (typ == TYPE_ID_LONG)
                {
                    return static_cast<long>(num);
                }
                else if (typ == TYPE_ID_UNSIGNED_LONG)
                {
                    return static_cast<unsigned long>(num);
                }
                else if (typ == TYPE_ID_LONG_LONG)
                {
                    return static_cast<long long>(num);
                }
                else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
                {
                    return static_cast<unsigned long long>(num);
                }
                else if (typ == TYPE_ID_FLOAT)
                {
                    return static_cast<float>(num);
                }
                else if (typ == TYPE_ID_DOUBLE)
                {
                    return static_cast<double>(num);
                }
                else if (typ == TYPE_ID_LONG_DOUBLE)
                {
                    return static_cast<long double>(num);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && typ == TYPE_ID_BOOL)
            {
                return static_cast<bool>(num);
            }
            break;
        }
        case LUA_TSTRING:
            size_t s;
            const char* str = lua_tolstring(Lua, stackIndex, &s);
            if (existsInVector(TYPE_IDS_STRINGS, typ))
            {
                if (typ == TYPE_ID_STRING)
                {
                    return std::string(str, s);
                }
                else if (typ == TYPE_ID_STRING_VIEW)
                {
                    return std::string_view(str, s);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && typ == TYPE_ID_BOOL)
            {
                // TODO: decide how I would want string to bool conversion to work
                return static_cast<bool>(str);
            }
            break;
        case LUA_TBOOLEAN:
            if (typ == TYPE_ID_BOOL)
            {
                return static_cast<bool>(lua_toboolean(Lua, stackIndex));
            }
            else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_INTEGERS, typ))
            {
                int b = lua_toboolean(Lua, stackIndex);
                if (typ == TYPE_ID_CHAR)
                {
                    return static_cast<char>(b);
                }
                else if (typ == TYPE_ID_UNSIGNED_CHAR)
                {
                    return static_cast<unsigned char>(b);
                }
                else if (typ == TYPE_ID_SHORT)
                {
                    return static_cast<short>(b);
                }
                else if (typ == TYPE_ID_UNSIGNED_SHORT)
                {
                    return static_cast<unsigned short>(b);
                }
                else if (typ == TYPE_ID_INT)
                {
                    return static_cast<int>(b);
                }
                else if (typ == TYPE_ID_UNSIGNED_INT)
                {
                    return static_cast<unsigned int>(b);
                }
                else if (typ == TYPE_ID_LONG)
                {
                    return static_cast<long>(b);
                }
                else if (typ == TYPE_ID_UNSIGNED_LONG)
                {
                    return static_cast<unsigned long>(b);
                }
                else if (typ == TYPE_ID_LONG_LONG)
                {
                    return static_cast<long long>(b);
                }
                else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
                {
                    return static_cast<unsigned long long>(b);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_FLOATS, typ))
            {
                int b = lua_toboolean(Lua, stackIndex);
                if (typ == TYPE_ID_FLOAT)
                {
                    return static_cast<float>(b);
                }
                else if (typ == TYPE_ID_DOUBLE)
                {
                    return static_cast<double>(b);
                }
                else if (typ == TYPE_ID_LONG_DOUBLE)
                {
                    return static_cast<long double>(b);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_STRINGS, typ))
            {
                // TODO: decide how I would want bool to string conversion to work
                int b = lua_toboolean(Lua, stackIndex);
                if (typ == TYPE_ID_STRING)
                {
                    return std::string(b ? "true" : "false");
                }
                else if (typ == TYPE_ID_STRING_VIEW)
                {
                    return std::string_view(b ? "true" : "false");
                }
                else
                {
                    return rttr::variant();
                }
            }
            break;
        case LUA_TTABLE:
            if (typ == TYPE_ID_LUA_TABLE)
            {
                return LuaTable::fromLuaTable(stackIndex);
            }
            else if (allowCrossTypeCategoryConversions && typ == TYPE_ID_BOOL)
            {
                return true;
            }
            else
            {
                return rttr::variant();
            }
            break;
        case LUA_TNIL:
            if (typ == TYPE_ID_NIL)
            {
                return Nil;
            }
            else if (allowCrossTypeCategoryConversions && typ == TYPE_ID_BOOL)
            {
                return false;
            }
            else
            {
                return rttr::variant();
            }
            break;
        default:
            // TODO: return nil?
            wxFAIL_MSG(wxString::Format("Unsupported lua type '%s'", lua_typename(Lua, stackIndex)));
        }
        return rttr::variant();
    }

    // will be used to allow reflected methods to return values in lua
    template<typename T>
    static void convertToLuaTypeOnStack(const T& val)
    {
        using BaseType = std::remove_cvref_t<T>;
        rttr::type typ = rttr::type::get<BaseType>();
        if constexpr (SAME(BaseType, _Nil))
        {
            luaWrapper.pushnil();
        }
        else if constexpr (SAME(BaseType, LuaTable))
        {
            val->pushToLuaStack();
        }
        else if constexpr (SAME(BaseType, bool))
        {
            luaWrapper.pushboolean(val);
        }
        else if constexpr (std::is_integral_v<BaseType> || std::is_floating_point_v<BaseType>) // number
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val));
        }
        else if constexpr (SAME(BaseType, std::string) || SAME(BaseType, std::string_view))
        {
            luaWrapper.pushstring(val.c_str());
        }
        else if constexpr (SAME(BaseType, char*))
        {
            luaWrapper.pushstring(val);
        }
        else if constexpr (SAME(BaseType, void*))
        {
            luaWrapper.pushlightuserdata(val);
        }
        else
        {
            showDeducedType(val);
            COMPILE_TIME_CONSTEXPR_IF_ERROR();
        }
    }

    // now similar function to above, but using runtime type_id of rttr::variant perform the conversions
    static bool convertToLuaTypeOnStackByTypeId(const rttr::variant& val)
    {
        type_id typ = val.get_type().get_id();
        if (typ == TYPE_ID_NIL)
        {
            luaWrapper.pushnil();
        }
        else if (typ == TYPE_ID_LUA_TABLE)
        {
            val.get_value<LuaTable>().pushToLuaStack();
        }
        else if (typ == TYPE_ID_BOOL)
        {
            luaWrapper.pushboolean(val.get_value<bool>());
        }
        else if (typ == TYPE_ID_CHAR)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<char>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_CHAR)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned char>()));
        }
        else if (typ == TYPE_ID_SHORT)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<short>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_SHORT)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned short>()));
        }
        else if (typ == TYPE_ID_INT)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<int>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_INT)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned int>()));
        }
        else if (typ == TYPE_ID_LONG)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<long>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_LONG)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long>()));
        }
        else if (typ == TYPE_ID_LONG_LONG)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<long long>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long long>()));
        }
        else if (typ == TYPE_ID_FLOAT)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<float>()));
        }
        else if (typ == TYPE_ID_DOUBLE)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<double>()));
        }
        else if (typ == TYPE_ID_LONG_DOUBLE)
        {
            luaWrapper.pushnumber(static_cast<lua_Number>(val.get_value<long double>()));
        }
        else if (typ == TYPE_ID_STRING)
        {
            luaWrapper.pushstring(val.get_value<std::string>());
        }
        else if (typ == TYPE_ID_STRING_VIEW)
        {
            luaWrapper.pushstring(std::string(val.get_value<std::string_view>()));
        }
        else if (typ == TYPE_ID_VOID_PTR)
        {
            luaWrapper.pushlightuserdata(val.get_value<void*>());
        }
        else
        {
            return false;
            //wxFAIL_MSG(wxString::Format("Can't convert type '%s' to matching lua type", val.get_type().get_name().data()));
        }
        return true;
    }

    // receives a vector of required types, and converts lua parameters to C++ types, which are required by the method
    // throws exception with additional info if conversion of any parameter fails
    static std::vector<rttr::variant> convertLuaParametersToCppForReflection(const std::vector<rttr::type>& requiredTypes)
    {
        wxASSERT_MSG(luaWrapper.gettop() >= requiredTypes.size(), "Not enough parameters on lua stack to convert to C++ types");
        std::vector<rttr::variant> result(requiredTypes.size());
        int stackTop = luaWrapper.gettop();
        int firstStackIndex = stackTop - requiredTypes.size() + 1; // have to go to the top of the stack for proper argument order
        std::vector<wxString> errorParts;
        for (int i = 0; i < requiredTypes.size(); ++i)
        {
            int currentStackIndex = firstStackIndex + i;
            auto&& type = requiredTypes[i];
            result[i] = convertStackIndexToTypeById(currentStackIndex, type.get_id(), true);
            // failsafe to check that lua stack top has not changed (shouldn't happen, but just in case)
            if (luaWrapper.gettop() != stackTop)
            {
                throw std::runtime_error(wxString::Format("Lua stack top changed during conversion of lua parameters to C++ types (from %d to %d)", stackTop, luaWrapper.gettop()));
            }
            if (!result[i].is_valid()) // got invalid (not supported) type
            {
                errorParts.push_back(wxString::Format("Parameter %d (stack index %d) of lua type '%s' to C++ type '%s'", i + 1, currentStackIndex, lua_typename(Lua, currentStackIndex), type.get_name().data()));
            }
        }
        if (!errorParts.empty())
        {
            throw std::runtime_error("Failed to convert some parameters. Exact failures:\n" + stringConcat(errorParts, "\n"));
        }
        return result;
    }

public:

    template<typename T>
    static rttr::variant callWithLuaParamsCommon(const std::string& name, T* instancePtr)
    {
        bool isMemberFunc = instancePtr != nullptr;
        rttr::method meth = isMemberFunc ? instancePtr->get_type().get_method(name) : rttr::type::get_global_method(name);
        if (!meth.is_valid())
        {
            return false;
        }
        auto paramsArray = meth.get_parameter_infos();
        std::vector<rttr::type> types;
        for (rttr::parameter_info param : paramsArray)
        {
            types.push_back(param.get_type());
        }
        std::vector<rttr::variant> variants = convertLuaParametersToCppForReflection(types);
        std::vector<rttr::argument> params;
        for (rttr::variant& arg : variants)
        {
            params.push_back(arg);
        }
        rttr::variant result = meth.invoke_variadic(isMemberFunc ? instancePtr : {}, params);
        return result;
    }

    // to allow calling above function with nullptr (in reality it's not a pointer type, so can't bind to T*, we need to overload it)
    static rttr::variant callWithLuaParamsCommon(const std::string& name, std::nullptr_t instancePtr)
    {
        return callWithLuaParamsCommon(name, static_cast<void*>(nullptr));
    }

    // generic function to get variable, either global or instance
    template<typename Class>
    static rttr::variant getVariableToLuaStackCommon(const std::string& name, Class* instancePtr)
    {
        bool isMemberFunc = instancePtr != nullptr;
        rttr::property prop = isMemberFunc ? instancePtr->get_type().get_property(name) : rttr::type::get_global_property(name);
        if (!prop.is_valid())
        {
            return false;
        }
        return prop.get_value(isMemberFunc ? instancePtr : {});
    }

    // nullptr_t version
    static rttr::variant getVariableToLuaStackCommon(const std::string& name, std::nullptr_t instancePtr)
    {
        return getVariableToLuaStackCommon(name, static_cast<void*>(nullptr));
    }

    // generic function to set variable, either global or instance
    template<typename Class>
    static bool setVariableFromLuaStackCommon(const std::string& name, Class* instancePtr, int stackIndex = -1)
    {
        stackIndex = luaWrapper.makeAbsoluteStackIndex(stackIndex);
        bool isMemberFunc = instancePtr != nullptr;
        rttr::property prop = isMemberFunc ? instancePtr->get_type().get_property(name) : rttr::type::get_global_property(name);
        if (!prop.is_valid())
        {
            return false;
        }
        rttr::variant value = convertStackIndexToTypeById(stackIndex, prop.get_type().get_id());
        if (!value.is_valid())
        {
            return false;
        }
        prop.set_value(isMemberFunc ? instancePtr : {}, value);
        return true;
    }

    // nullptr_t version
    static bool setVariableFromLuaStackCommon(const std::string& name, std::nullptr_t instancePtr, int stackIndex = -1)
    {
        return setVariableFromLuaStackCommon(name, static_cast<void*>(nullptr), stackIndex);
    }

    static rttr::variant callFreeFunctionWithLuaParams(const std::string& name)
    {
        return callWithLuaParamsCommon(name, nullptr);
    }

    // get global variable to lua stack
    // returns if operation was successful, in case of failure, lua stack is not modified
    static bool getGlobalVariableToLuaStack(const std::string& variableName, int stackIndex = -1)
    {
        getVariableToLuaStackCommon(variableName, nullptr);
    }

    // set global variable from lua stack
    // returns if operation was successful, in case of failure, lua stack is not modified
    static bool setGlobalVariableFromLuaStack(const std::string& variableName, int stackIndex = -1)
    {
        setVariableFromLuaStackCommon(variableName, nullptr, stackIndex);
    }

    template<typename Class>
    static rttr::variant callInstanceMethodWithLuaParams(Class* instance, const std::string& methodName)
    {
        return callWithLuaParamsCommon(methodName, instance);
    }

    // get property into lua stack
    template<typename Class>
    static void getPropertyToLuaStack(Class* instance, const std::string& propertyName)
    {
        getVariableToLuaStackCommon(propertyName, instance);
    }

    // set property from lua stack
    template<typename Class>
    static bool setPropertyFromLuaStack(Class* instance, const std::string& propertyName, int stackIndex = -1)
    {
        return setPropertyFromLuaStackCommon(propertyName, instance, stackIndex);
    }

    // not using convertLuaParametersToCppForReflection here, because it throws exception on failure, and we want to return false instead

    bool canConvertLuaParameter(int stackIndex, const rttr::parameter_info& required)
    {
        // check validity of stack index
        if (stackIndex < 1 || stackIndex > luaWrapper.gettop())
        {
            wxFAIL_MSG(wxString::Format("Invalid stack index %d (current size is %d)", stackIndex, luaWrapper.gettop()));
            return false;
        }
        rttr::variant val = convertStackIndexToTypeById(stackIndex, required.get_type().get_id());
        return val.is_valid();
    }

    bool canConvertLuaParameters(const std::vector<rttr::parameter_info>& required)
    {
        for (int i = 0; i < required.size(); ++i)
        {
            int stackIndex = luaWrapper.makeAbsoluteStackIndex(luaWrapper.gettop() - required.size() + i + 1);
            if (!canConvertLuaParameter(stackIndex, required[i]))
            {
                return false;
            }
        }
        return true;
    }

    // creates instance of given class by calling constructor with matching parameters
    // returns pointer to created instance, or nullptr if no matching constructor was found
    template<typename Class>
    static Class* createInstanceByConstructorFromLuaStack()
    {
        for (rttr::constructor ctor : rttr::type::get<Class>().get_constructors())
        {
            auto info = ctor.get_parameter_infos();
            std::vector<parameter_info> vec(info.begin(), info.end());
            if (canConvertLuaParameters(vec))
            {
                std::vector<rttr::variant> variants = convertLuaParametersToCppForReflection(vec);
                std::vector<rttr::argument> params;
                for (rttr::variant& arg : variants)
                {
                    params.push_back(arg);
                }
                rttr::variant result = ctor.invoke_variadic(params);
                return result.get_value<Class*>();
            }
        }
        return nullptr;
    }
};