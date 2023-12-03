#pragma once
#include "main.h"
#include "CallEvents.h"
#include "LuaWrapper.h"
#include "Utility.h"

template<typename T>
concept IsCvUnqualifiedTopLevel = !(std::is_const_v<std::remove_reference_t<T>> || std::is_volatile_v<std::remove_reference_t<T>>);

// custom exception, which will be thrown as part one of generating lua error from C++
// using this, because it properly invokes destructors of objects
// this exception should be caught by C++ function directly called by lua, and it should execute its own stack objects' destructors and generate lua error
class LuaErrorException : public std::runtime_error
{
    // TODO: have more fields (like what type of error it is, and what are error parameters, so for type mismatch we can show expected type and actual type) to facilitate unit testing
    public:
        LuaErrorException(const std::string& msg) : std::runtime_error(msg) {}
};

// creates "safe" lua error, that is not skipping C++ destructors
template<typename... Args>
[[noreturn]] void luaError(const std::string& msg, Args&&... args)
{
    throw LuaErrorException(std::vformat(msg, std::make_format_args(std::forward<Args>(args)...)));
}

template<typename... Args>
void callDestructors(Args&&... args)
{
    (args.~Args(), ...);
}

// lua debug api
namespace luaDebug
{
    // TODO: I removed static from these functions, because I want to use them in LuaFunctions.cpp (to register them in lua), but I'm not sure if it's correct
    extern "C"
    {
        int classExists(lua_State* L);
        int copyObject(lua_State* L);
        int createObject(lua_State* L);
        int destroyObject(lua_State* L);
        int getClassObjectField(lua_State* L);
        int getClassField(lua_State* L);
        int getGlobalField(lua_State* L);
        int setClassObjectField(lua_State* L);
        int setClassField(lua_State* L);
        int setGlobalField(lua_State* L);
        int invokeClassMethod(lua_State* L);
        int invokeClassObjectMethod(lua_State* L);
        int invokeGlobalMethod(lua_State* L);
        int getClassInfo(lua_State* L);
        int getGlobalEnvironmentInfo(lua_State* L);
    }
}
// member methods, static methods, global methods, global callables, member callables, static callables
// those that are object properties: member methods, member callables
// those that are class properties: static methods, static callables
// those that are global properties: global methods, global callables

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

private:

    template<typename T>
    static rttr::variant tryConvertNumberToType(T val, type_id typeId, bool allowCrossTypeConversions = false)
    {
        if (typeId == TYPE_ID_CHAR)
        {
            return static_cast<char>(val);
        }
        else if (typeId == TYPE_ID_UNSIGNED_CHAR)
        {
            return static_cast<unsigned char>(val);
        }
        else if (typeId == TYPE_ID_SHORT)
        {
            return static_cast<short>(val);
        }
        else if (typeId == TYPE_ID_UNSIGNED_SHORT)
        {
            return static_cast<unsigned short>(val);
        }
        else if (typeId == TYPE_ID_INT)
        {
            return static_cast<int>(val);
        }
        else if (typeId == TYPE_ID_UNSIGNED_INT)
        {
            return static_cast<unsigned int>(val);
        }
        else if (typeId == TYPE_ID_LONG)
        {
            return static_cast<long>(val);
        }
        else if (typeId == TYPE_ID_UNSIGNED_LONG)
        {
            return static_cast<unsigned long>(val);
        }
        else if (typeId == TYPE_ID_LONG_LONG)
        {
            return static_cast<long long>(val);
        }
        else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
        {
            return static_cast<unsigned long long>(val);
        }
        else if (typeId == TYPE_ID_FLOAT)
        {
            return static_cast<float>(val);
        }
        else if (typeId == TYPE_ID_DOUBLE)
        {
            return static_cast<double>(val);
        }
        else if (typeId == TYPE_ID_LONG_DOUBLE)
        {
            return static_cast<long double>(val);
        }
        else if (allowCrossTypeConversions)
        {
            if (typeId == TYPE_ID_BOOL)
            {
                return static_cast<bool>((long long)val); // second cast is for doubles, which can't be cast to bool directly
            }
            // strings
            else if (typeId == TYPE_ID_STRING)
            {
                return std::to_string(val);
            }
            else if (typeId == TYPE_ID_STRING_VIEW)
            {
                return std::string_view(std::to_string(val));
            }
        }
        return rttr::variant();
    }
    public:
    // converts lua parameter from stack to given type (using RTTR type_id)
    // allowCrossTypeCategoryConversions allows to convert lua types to C++ types, which are not exactly matching, but are compatible (like number to boolean)
    static rttr::variant convertStackIndexToType(lua_State* L, int stackIndex, const rttr::type& typ, bool allowCrossTypeCategoryConversions = false)
    {
        LuaWrapper wrapper(L);
        type_id typeId = typ.get_id();
        stackIndex = wrapper.makeAbsoluteStackIndex(stackIndex);
        switch (lua_type(Lua, stackIndex))
        {
        case LUA_TNUMBER:
        {
            lua_Number num = lua_tonumber(Lua, stackIndex);
            return tryConvertNumberToType(num, typeId, allowCrossTypeCategoryConversions);
        }
        case LUA_TSTRING:
        {
            size_t s;
            const char* str = lua_tolstring(Lua, stackIndex, &s);
            if (existsInVector(TYPE_IDS_STRINGS, typeId))
            {
                if (typeId == TYPE_ID_STRING)
                {
                    return std::string(str, s);
                }
                else if (typeId == TYPE_ID_STRING_VIEW)
                {
                    return std::string_view(str, s);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && typeId == TYPE_ID_BOOL)
            {
                // TODO: decide how I would want string to bool conversion to work
                return static_cast<bool>(str);
            }
            break;
        }
        case LUA_TBOOLEAN:
            if (typeId == TYPE_ID_BOOL)
            {
                return static_cast<bool>(lua_toboolean(Lua, stackIndex));
            }
            else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_INTEGERS, typeId))
            {
                int b = lua_toboolean(Lua, stackIndex);
                if (typeId == TYPE_ID_CHAR)
                {
                    return static_cast<char>(b);
                }
                else if (typeId == TYPE_ID_UNSIGNED_CHAR)
                {
                    return static_cast<unsigned char>(b);
                }
                else if (typeId == TYPE_ID_SHORT)
                {
                    return static_cast<short>(b);
                }
                else if (typeId == TYPE_ID_UNSIGNED_SHORT)
                {
                    return static_cast<unsigned short>(b);
                }
                else if (typeId == TYPE_ID_INT)
                {
                    return static_cast<int>(b);
                }
                else if (typeId == TYPE_ID_UNSIGNED_INT)
                {
                    return static_cast<unsigned int>(b);
                }
                else if (typeId == TYPE_ID_LONG)
                {
                    return static_cast<long>(b);
                }
                else if (typeId == TYPE_ID_UNSIGNED_LONG)
                {
                    return static_cast<unsigned long>(b);
                }
                else if (typeId == TYPE_ID_LONG_LONG)
                {
                    return static_cast<long long>(b);
                }
                else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
                {
                    return static_cast<unsigned long long>(b);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_FLOATS, typeId))
            {
                int b = lua_toboolean(Lua, stackIndex);
                if (typeId == TYPE_ID_FLOAT)
                {
                    return static_cast<float>(b);
                }
                else if (typeId == TYPE_ID_DOUBLE)
                {
                    return static_cast<double>(b);
                }
                else if (typeId == TYPE_ID_LONG_DOUBLE)
                {
                    return static_cast<long double>(b);
                }
                else
                {
                    return rttr::variant();
                }
            }
            else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_STRINGS, typeId))
            {
                // TODO: decide how I would want bool to string conversion to work
                int b = lua_toboolean(Lua, stackIndex);
                if (typeId == TYPE_ID_STRING)
                {
                    return std::string(b ? "true" : "false");
                }
                else if (typeId == TYPE_ID_STRING_VIEW)
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
            if (typeId == TYPE_ID_LUA_TABLE)
            {
                return LuaTable::fromLuaTable(L, stackIndex);
            }
            else if (typ.is_sequential_container())
            {
                // have to extract information from lua table into rttr::variant containing desired container
                rttr::type wrappedType = typ.get_wrapped_type();
                rttr::variant var = typ.create();
                rttr::variant_sequential_view seqView = var.create_sequential_view();
                LuaTable t = LuaTable::fromLuaTable(L, stackIndex);
                auto arr = t.getArrayPart();
                seqView.set_size(arr.size());
                for (int i = 0; const LuaTypeInCpp& val : arr)
                {
                    seqView.set_value(i++, val);
                }
                return var;
            }
            else if (typ.is_associative_container())
            {
                // have to extract information from lua table into rttr::variant containing desired container
                rttr::type wrappedType = typ.get_wrapped_type();
                rttr::variant var = typ.create();
                rttr::variant_associative_view assocView = var.create_associative_view();
                LuaTable t = LuaTable::fromLuaTable(L, stackIndex);
                for (auto&& [key, value] : t)
                {
                    assocView.insert(key, value);
                }
                return var;
            }
            else if (allowCrossTypeCategoryConversions && typeId == TYPE_ID_BOOL)
            {
                return true;
            }
            else
            {
                return rttr::variant();
            }
            break;
        case LUA_TNIL:
            if (typeId == TYPE_ID_NIL)
            {
                return Nil;
            }
            else if (allowCrossTypeCategoryConversions && typeId == TYPE_ID_BOOL)
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
    // takes constituent types of LuaTypeInCpp and converts them to lua types
    template<typename T>
    static void convertToLuaTypeOnStack(lua_State* L, const T& val)
    {
        LuaWrapper wrapper(L);
        using BaseType = std::remove_cvref_t<T>;
        rttr::type typ = rttr::type::get<BaseType>();
        if constexpr (SAME(BaseType, _Nil))
        {
            wrapper.pushnil();
        }
        else if constexpr (SAME(BaseType, LuaTable))
        {
            val->pushToLuaStack();
        }
        else if constexpr (SAME(BaseType, bool))
        {
            wrapper.pushboolean(val);
        }
        else if constexpr (std::is_integral_v<BaseType> || std::is_floating_point_v<BaseType>) // number
        {
            wrapper.pushnumber(static_cast<lua_Number>(val));
        }
        else if constexpr (SAME(BaseType, std::string) || SAME(BaseType, std::string_view))
        {
            wrapper.pushstring(val.c_str());
        }
        else if constexpr (SAME(BaseType, char*))
        {
            wrapper.pushstring(val);
        }
        else if constexpr (SAME(BaseType, void*))
        {
            wrapper.pushlightuserdata(val);
        }
        else
        {
            showDeducedType(val);
            COMPILE_TIME_CONSTEXPR_IF_ERROR();
        }
    }

    static LuaTypeInCpp convertVariantToLuaTypeInCpp(const rttr::variant& var)
    {
        type_id typ = var.get_type().get_id();
        if (var.is_sequential_container())
        {
            // create table from sequential container
            rttr::variant_sequential_view seqView = var.create_sequential_view();
            LuaTable t;
            for (int i = 0; auto& value : seqView)
            {
                t[i++] = convertVariantToLuaTypeInCpp(value);
            }
            return t;
        }
        else if (var.is_associative_container())
        {
            // create table from associative container
            rttr::variant_associative_view assocView = var.create_associative_view();
            LuaTable t;
            for (auto&& [key, value] : assocView)
            {
                t[convertVariantToLuaTypeInCpp(key)] = convertVariantToLuaTypeInCpp(value);
            }
            return t;
        }
        else if (typ == TYPE_ID_NIL)
        {
            return Nil;
        }
        else if (typ == TYPE_ID_LUA_TABLE)
        {
            return var.get_value<LuaTable>();
        }
        else if (typ == TYPE_ID_BOOL)
        {
            return var.get_value<bool>();
        }
        else if (typ == TYPE_ID_CHAR)
        {
            return var.get_value<char>();
        }
        else if (typ == TYPE_ID_UNSIGNED_CHAR)
        {
            return var.get_value<unsigned char>();
        }
        else if (typ == TYPE_ID_SHORT)
        {
            return var.get_value<short>();
        }
        else if (typ == TYPE_ID_UNSIGNED_SHORT)
        {
            return var.get_value<unsigned short>();
        }
        else if (typ == TYPE_ID_INT)
        {
            return var.get_value<int>();
        }
        else if (typ == TYPE_ID_UNSIGNED_INT)
        {
            return var.get_value<unsigned int>();
        }
        else if (typ == TYPE_ID_LONG)
        {
            return var.get_value<long>();
        }
        else if (typ == TYPE_ID_UNSIGNED_LONG)
        {
            return var.get_value<unsigned long>();
        }
        else if (typ == TYPE_ID_LONG_LONG)
        {
            return var.get_value<long long>();
        }
        else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
        {
            return static_cast<sqword_t>(var.get_value<unsigned long long>());
        }
        else if (typ == TYPE_ID_FLOAT)
        {
            return var.get_value<float>();
        }
        else if (typ == TYPE_ID_DOUBLE)
        {
            return var.get_value<double>();
        }
        else if (typ == TYPE_ID_LONG_DOUBLE)
        {
            return static_cast<double>(var.get_value<long double>());
        }
        else if (typ == TYPE_ID_STRING)
        {
            return var.get_value<std::string>();
        }
        else if (typ == TYPE_ID_STRING_VIEW)
        {
            return (std::string)var.get_value<std::string_view>();
        }
        else if (typ == TYPE_ID_VOID_PTR)
        {
            return (dword_t)var.get_value<void*>();
        }
        else
        {
            luaError("Unsupported type '%s' in convertVariantToLuaTypeInCpp", var.get_type().get_name().to_string());
            return 0; // dummy return
        }
    }

    static rttr::variant convertLuaTypeInCppToVariantByTypeId(const LuaTypeInCpp& var, const type_id& typeId, bool allowCrossTypeConversions = false)
    {
        // let's assume integers can be converted to floats and vice versa, even if allowCrossTypeConversions is false
        if (const sqword_t* val = std::get_if<sqword_t>(&var))
        {
            return tryConvertNumberToType(*val, typeId, allowCrossTypeConversions);
        }
        else if (const lua_Number* val = std::get_if<lua_Number>(&var))
        {
            return tryConvertNumberToType(*val, typeId, allowCrossTypeConversions);
        }
        else if (const std::string* val = std::get_if<std::string>(&var))
        {
            if (typeId == TYPE_ID_STRING)
            {
                return *val;
            }
            else if (typeId == TYPE_ID_STRING_VIEW)
            {
                return std::string_view(*val);
            }
            else if (allowCrossTypeConversions)
            {
                if (typeId == TYPE_ID_BOOL)
                {
                     return !val->empty();
                }

                try
                {
                    return tryConvertNumberToType(std::stod(*val), typeId, allowCrossTypeConversions);
                }
                catch (const std::exception&)
                {
                    // ignore
                }

                try 
                {
                    return tryConvertNumberToType(std::stoll(*val), typeId, allowCrossTypeConversions);
                }
                catch (const std::exception&)
                {
                    // ignore
                }
            }
        }
        else if (const bool* val = std::get_if<bool>(&var))
        {
            if (typeId == TYPE_ID_BOOL)
            {
                return *val;
            }
            else if (allowCrossTypeConversions)
            {
                if (typeId == TYPE_ID_CHAR)
                {
                    return static_cast<char>(*val);
                }
                else if (typeId == TYPE_ID_UNSIGNED_CHAR)
                {
                    return static_cast<unsigned char>(*val);
                }
                else if (typeId == TYPE_ID_SHORT)
                {
                    return static_cast<short>(*val);
                }
                else if (typeId == TYPE_ID_UNSIGNED_SHORT)
                {
                    return static_cast<unsigned short>(*val);
                }
                else if (typeId == TYPE_ID_INT)
                {
                    return static_cast<int>(*val);
                }
                else if (typeId == TYPE_ID_UNSIGNED_INT)
                {
                    return static_cast<unsigned int>(*val);
                }
                else if (typeId == TYPE_ID_LONG)
                {
                    return static_cast<long>(*val);
                }
                else if (typeId == TYPE_ID_UNSIGNED_LONG)
                {
                    return static_cast<unsigned long>(*val);
                }
                else if (typeId == TYPE_ID_LONG_LONG)
                {
                    return static_cast<long long>(*val);
                }
                else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
                {
                    return static_cast<unsigned long long>(*val);
                }
                else if (typeId == TYPE_ID_FLOAT)
                {
                    return static_cast<float>(*val);
                }
                else if (typeId == TYPE_ID_DOUBLE)
                {
                    return static_cast<double>(*val);
                }
                else if (typeId == TYPE_ID_LONG_DOUBLE)
                {
                    return static_cast<long double>(*val);
                }
                else if (typeId == TYPE_ID_STRING)
                {
                    return std::string(*val ? "true" : "false");
                }
                else if (typeId == TYPE_ID_STRING_VIEW)
                {
                    return std::string_view(*val ? "true" : "false");
                }
            }
        }
        else if (const LuaTable* val = std::get_if<LuaTable>(&var))
        {
            if (typeId == TYPE_ID_LUA_TABLE)
            {
                return *val;
            }
            else if (allowCrossTypeConversions && typeId == TYPE_ID_BOOL)
            {
                return true;
            }
        }
        return rttr::variant();
    }

    // now similar function to above, but using runtime type_id of rttr::variant perform the conversions
    static bool convertToLuaTypeOnStackByTypeId(lua_State* L, const rttr::variant& val)
    {
        LuaWrapper wrapper(L);
        type_id typ = val.get_type().get_id();
        if (val.is_sequential_container())
        {
            // create table from sequential container
            rttr::type wrappedType = val.get_type().get_wrapped_type();
            rttr::variant_sequential_view seqView = val.create_sequential_view();
            LuaTable t;
            for (int i = 0; auto& value : seqView)
            {
                if (value.get_type().get_id() != wrappedType.get_id())
                {
                    throw std::runtime_error("Can't convert sequential container to lua table, because it contains elements of different types");
                }
                t[i++] = convertVariantToLuaTypeInCpp(value);
            }
            t.pushToLuaStack(L);
        }
        else if (val.is_associative_container())
        {
            // create table from associative container
            rttr::type wrappedType = val.get_type().get_wrapped_type();
            rttr::variant_associative_view assocView = val.create_associative_view();
            LuaTable t;
            for (auto&& [key, value] : assocView)
            {
                t[convertVariantToLuaTypeInCpp(key)] = convertVariantToLuaTypeInCpp(value);
            }
            t.pushToLuaStack(L);
        }
        else if (typ == TYPE_ID_NIL)
        {
            wrapper.pushnil();
        }
        else if (typ == TYPE_ID_LUA_TABLE)
        {
            val.get_value<LuaTable>().pushToLuaStack(L);
        }
        else if (typ == TYPE_ID_BOOL)
        {
            wrapper.pushboolean(val.get_value<bool>());
        }
        else if (typ == TYPE_ID_CHAR)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<char>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_CHAR)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned char>()));
        }
        else if (typ == TYPE_ID_SHORT)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<short>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_SHORT)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned short>()));
        }
        else if (typ == TYPE_ID_INT)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<int>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_INT)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned int>()));
        }
        else if (typ == TYPE_ID_LONG)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<long>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_LONG)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long>()));
        }
        else if (typ == TYPE_ID_LONG_LONG)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<long long>()));
        }
        else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long long>()));
        }
        else if (typ == TYPE_ID_FLOAT)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<float>()));
        }
        else if (typ == TYPE_ID_DOUBLE)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<double>()));
        }
        else if (typ == TYPE_ID_LONG_DOUBLE)
        {
            wrapper.pushnumber(static_cast<lua_Number>(val.get_value<long double>()));
        }
        else if (typ == TYPE_ID_STRING)
        {
            wrapper.pushstring(val.get_value<std::string>());
        }
        else if (typ == TYPE_ID_STRING_VIEW)
        {
            wrapper.pushstring(std::string(val.get_value<std::string_view>()));
        }
        else if (typ == TYPE_ID_VOID_PTR)
        {
            wrapper.pushlightuserdata(val.get_value<void*>());
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
    // by default pops converted parameters from lua stack, but can be disabled
    // nArgs is intended to be set by lua side to show how many arguments were passed to the function (to allow to use default values)
    static std::vector<rttr::variant> convertLuaParametersToCppForReflection(lua_State* L, const std::vector<rttr::parameter_info>& requiredParameters, int nArgs, bool pop = true)
    {
        LuaWrapper wrapper(L);
        std::vector<wxString> errorParts;
        if (nArgs == -1)
        {
            nArgs = requiredParameters.size();
        }
        else if (nArgs > (int)requiredParameters.size())
        {
            errorParts.push_back(wxString::Format("Too many parameters passed by lua function (expected %d, got %d)", requiredParameters.size(), nArgs));
        }
        else if (nArgs < (int)requiredParameters.size())
        {
            bool haveDefault = true;
            for (int i = nArgs; i < (int)requiredParameters.size(); ++i)
            {
                if (!requiredParameters[i].has_default_value())
                {
                    haveDefault = false;
                    break;
                }
            }
            if (!haveDefault)
            {
                errorParts.push_back(wxString::Format("Not enough parameters passed by lua function (expected %d, got %d), can't recover using default values", requiredParameters.size(), nArgs));
            }
        }
        int defaultCount = requiredParameters.size() - nArgs;
        wxASSERT_MSG(wrapper.gettop() >= nArgs, "Not enough parameters on lua stack to convert to C++ types");
        std::vector<rttr::variant> result(requiredParameters.size());
        int stackTop = wrapper.gettop();
        int firstStackIndex = stackTop - nArgs + 1; // have to go to the top of the stack for proper argument order
        for (int i = 0; i < (int)requiredParameters.size(); ++i)
        {
            if (i < nArgs) // use passed parameter
            {
                int currentStackIndex = firstStackIndex + i;
                auto&& param = requiredParameters[i];
                result[i] = convertStackIndexToType(L, currentStackIndex, param.get_type(), true);
                // failsafe to check that lua stack top has not changed (shouldn't happen, but just in case)
                if (wrapper.gettop() != stackTop)
                {
                    int top = wrapper.gettop();
                    if (pop) // restore stack to original state
                    {
                        wrapper.settop(stackTop - nArgs);
                    }
                    throw std::runtime_error(wxString::Format("Lua stack top changed during conversion of lua parameters to C++ types (from %d to %d)", stackTop, top));
                }
                if (!result[i].is_valid()) // got invalid (not supported) type
                {
                    errorParts.push_back(wxString::Format("Parameter %d (stack index %d, name '%s') of lua type '%s' to C++ type '%s'", i + 1, currentStackIndex, param.get_name().data(), lua_typename(Lua, currentStackIndex), param.get_type().get_name().data()));
                }
            }
            else // use default value
            {
                result[i] = requiredParameters[i].get_default_value();
            }
        }
        if (pop)
        {
            wrapper.settop(stackTop - nArgs);
        }
        if (!errorParts.empty())
        {
            throw std::runtime_error("Failed to convert some parameters. Exact failures:\n" + stringConcat(errorParts, "\n"));
        }
        return result;
    }

   private:


    // not using convertLuaParametersToCppForReflection here, because it throws exception on failure, and we want to return false instead

    static bool canConvertLuaParameter(lua_State* L, int stackIndex, const rttr::parameter_info& required)
    {
        LuaWrapper wrapper(L);
        // check validity of stack index
        if (stackIndex < 1 || stackIndex > wrapper.gettop())
        {
            wxFAIL_MSG(wxString::Format("Invalid stack index %d (current size is %d)", stackIndex, wrapper.gettop()));
            return false;
        }
        rttr::variant val = convertStackIndexToType(L, stackIndex, required.get_type());
        return val.is_valid();
    }

    static bool canConvertLuaParameters(lua_State* L, const std::vector<rttr::parameter_info>& required, int nArgs = -1)
    {
        LuaWrapper wrapper(L);
        if (nArgs == -1)
        {
            nArgs = required.size();
        }
        else if (nArgs > (int)required.size())
        {
            return false;
        }
        else if (nArgs < (int)required.size())
        {
            bool haveDefault = true;
            for (int i = nArgs; i < (int)required.size(); ++i)
            {
                if (!required[i].has_default_value())
                {
                    haveDefault = false;
                    break;
                }
            }
            if (!haveDefault)
            {
                return false;
            }
        }
        for (int i = 0; i < nArgs; ++i)
        {
            int stackIndex = wrapper.makeAbsoluteStackIndex(wrapper.gettop() - nArgs + i + 1);
            if (!canConvertLuaParameter(L, stackIndex, required[i]))
            {
                return false;
            }
        }
        return true;
    }

    static rttr::variant callWithLuaParamsCommon(lua_State* L, const rttr::method& meth, rttr::instance inst, int nArgs)
    {
        if (!meth.is_valid())
        {
            return rttr::variant();
        }
        auto paramsArray = meth.get_parameter_infos();
        std::vector<rttr::parameter_info> params(paramsArray.begin(), paramsArray.end());
        if (!canConvertLuaParameters(L, params, nArgs))
        {
            return rttr::variant();
        }
        std::vector<rttr::variant> variants = convertLuaParametersToCppForReflection(L, params, nArgs);
        std::vector<rttr::argument> args;
        for (rttr::variant& arg : variants)
        {
            args.push_back(arg);
        }
        rttr::variant result = meth.invoke_variadic(inst.is_valid() ? inst : rttr::instance(), args);
        return result;
    }

    template<typename T>
    static rttr::variant callWithLuaParamsCommonTemplated(const std::string& name, T* instancePtr, int nArgs = -1)
    {
        bool isMemberFunc = instancePtr != nullptr;
        rttr::method meth = isMemberFunc ? rttr::type::get<T>().get_method(name) : rttr::type::get_global_method(name);
        return callWithLuaParamsCommon(meth, isMemberFunc ? rttr::instance(instancePtr) : rttr::instance(), nArgs);
    }

    // to allow calling above function with nullptr (in reality it's not a pointer type, so can't bind to T*, we need to overload it)
    static rttr::variant callWithLuaParamsCommonTemplated(const std::string& name, std::nullptr_t instancePtr, int nArgs = -1)
    {
        return callWithLuaParamsCommonTemplated(name, static_cast<void*>(nullptr), nArgs);
    }

    static int defaultArgumentCount(const std::vector<rttr::parameter_info>& paramInfo)
    {
        int result = 0;
        int i = 0;
        for (auto itr = paramInfo.rbegin(); itr != paramInfo.rend(); ++itr, ++i)
        {
            if (!itr->has_default_value())
            {
                return i;
            }
        }
        // all default
        return paramInfo.size();
    }

public:
    /// property getters

    // generic templated function to get variable, either global or instance
//     template<typename Class>
//     static rttr::variant getVariableTemplatedCommon(const std::string& name, Class* instancePtr)
//     {
//         bool isMemberFunc = instancePtr != nullptr;
//         rttr::property prop = isMemberFunc ? rttr::type::get<Class>().get_property(name) : rttr::type::get_global_property(name);
//         if (!prop.is_valid())
//         {
//             return false;
//         }
//         return prop.get_value(isMemberFunc ? instancePtr : rttr::instance());
//     }
//     
//     // nullptr_t version
//     static rttr::variant getVariableTemplatedCommon(const std::string& name, std::nullptr_t instancePtr)
//     {
//         return getVariableTemplatedCommon(name, static_cast<void*>(nullptr));
//     }

    // get property into lua stack, templated
//     template<typename Class>
//     static bool getClassObjectFieldToLuaStackTemplated(Class* instance, const std::string& propertyName)
//     {
//         return convertToLuaTypeOnStackByTypeId(getVariableTemplatedCommon(propertyName, instance));
//     }

    // gets static field of class to lua stack
    static bool getClassFieldToLuaStack(lua_State* L, const std::string& className, const std::string& fieldName)
    {
        rttr::type type = rttr::type::get_by_name(className);
        if (!type.is_valid())
        {
            return false;
        }
        rttr::property prop = type.get_property(fieldName);
        if (!prop.is_valid())
        {
            return false;
        }
        return convertToLuaTypeOnStackByTypeId(L, prop.get_value(rttr::instance()));
    }

    // variant must contain pointer to real object type, not void*
    static bool getClassObjectFieldToLuaStack(lua_State* L, const std::string& className, const std::string& fieldName, const rttr::variant& instance)
    {
        rttr::type type = rttr::type::get_by_name(className);
        if (!type.is_valid())
        {
            return false;
        }
        rttr::property prop = type.get_property(fieldName);
        if (!prop.is_valid())
        {
            return false;
        }
        return convertToLuaTypeOnStackByTypeId(L, prop.get_value(instance));
    }

    static bool getGlobalVariableToLuaStack(lua_State* L, const std::string& fieldName)
    {
        rttr::property prop = rttr::type::get_global_property(fieldName);
        if (!prop.is_valid())
        {
            return false;
        }
        return convertToLuaTypeOnStackByTypeId(L, prop.get_value(rttr::instance()));
    }

    /// property setters

    // uses variants
    static bool setClassObjectFieldFromLuaStack(lua_State* L, const rttr::variant& instance, const std::string& propertyName, int stackIndex = -1)
    {
        rttr::property prop = instance.get_type().get_raw_type().get_property(propertyName);
        if (!prop.is_valid())
        {
            return false;
        }
        rttr::variant value = convertStackIndexToType(L, stackIndex, prop.get_type());
        if (!value.is_valid())
        {
            return false;
        }
        return prop.set_value(instance, value);
    }

    static bool setClassFieldFromLuaStack(lua_State* L, const std::string& className, const std::string& propertyName, int stackIndex = -1)
    {
        rttr::type type = rttr::type::get_by_name(className);
        if (!type.is_valid())
        {
            return false;
        }
        rttr::property prop = type.get_property(propertyName);
        if (!prop.is_valid())
        {
            return false;
        }
        else if (!prop.is_static()) // not class field
        {
            return false;
        }
        rttr::variant value = convertStackIndexToType(L, stackIndex, prop.get_type());
        if (!value.is_valid())
        {
            return false;
        }
        return prop.set_value(rttr::instance(), value);
    }

    static bool setGlobalVariableFromLuaStack(lua_State* L, const std::string& variableName, int stackIndex = -1)
    {
        rttr::property prop = rttr::type::get_global_property(variableName);
        if (!prop.is_valid())
        {
            return false;
        }
        rttr::variant value = convertStackIndexToType(L, stackIndex, prop.get_type());
        if (!value.is_valid())
        {
            return false;
        }
        return prop.set_value(rttr::instance(), value);
    }

    // generic function to set variable, either global or instance, templated
//     template<typename Class>
//     static bool setVariableFromLuaStackCommonTemplated(lua_State* L, const std::string& name, Class* instancePtr, int stackIndex = -1)
//     {
//         LuaWrapper wrapper(L);
//         stackIndex = wrapper.makeAbsoluteStackIndex(stackIndex);
//         bool isMemberFunc = instancePtr != nullptr;
//         rttr::property prop = isMemberFunc ? rttr::type::get<Class>().get_property(name) : rttr::type::get_global_property(name);
//         if (!prop.is_valid())
//         {
//             return false;
//         }
//         rttr::variant value = convertStackIndexToType(stackIndex, prop.get_type());
//         if (!value.is_valid())
//         {
//             return false;
//         }
//         prop.set_value(isMemberFunc ? instancePtr : rttr::instance(), value);
//     }
// 
//     // nullptr_t version
//     static bool setVariableFromLuaStackCommonTemplated(lua_State* L, const std::string& name, std::nullptr_t instancePtr, int stackIndex = -1)
//     {
//         return setVariableFromLuaStackCommonTemplated(L, name, static_cast<void*>(nullptr), stackIndex);
//     }

    // set global variable from lua stack
    // returns if operation was successful, in case of failure, lua stack is not modified
//     static bool setGlobalVariableFromLuaStack(lua_State* L, const std::string& variableName, int stackIndex = -1)
//     {
//         return setVariableFromLuaStackCommonTemplated(L, variableName, nullptr, stackIndex);
//     }
// 
//     // set property from lua stack
//     template<typename Class>
//     static bool setClassObjectFieldFromLuaStackTemplated(lua_State* L, Class* instance, const std::string& propertyName, int stackIndex = -1)
//     {
//         return setVariableFromLuaStackCommonTemplated(L, propertyName, instance, stackIndex);
//     }
// 
//     // set class property from lua stack
//     template<typename Class>
//     static bool setClassFieldFromLuaStackTemplated(lua_State* L, const std::string& className, const std::string& propertyName, int stackIndex = -1)
//     {
//         return setVariableFromLuaStackCommonTemplated(L, propertyName, nullptr, stackIndex);
//     }

    static rttr::variant callGlobalFunctionWithLuaParams(lua_State* L, const std::string& name, int nArgs = -1)
    {
        rttr::method meth = rttr::type::get_global_method(name);

        return callWithLuaParamsCommon(L, meth, rttr::instance(), nArgs);
    }

    static rttr::variant callClassObjectMethodWithLuaParams(lua_State* L, rttr::variant instance, const std::string& methodName, int nArgs = -1)
    {
        rttr::type t = instance.get_type().get_raw_type();
        if (!t.is_class())
        {
            return rttr::variant();
        }
        else if (!instance.get_type().is_pointer())
        {
            return rttr::variant();
        }
        rttr::method meth = t.get_method(methodName);

        return callWithLuaParamsCommon(L, meth, instance, nArgs);
    }

    static rttr::variant callClassMethodWithLuaParams(lua_State* L, const std::string& className, const std::string& methodName, int nArgs = -1)
    {
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_class())
        {
            return rttr::variant();
        }
        rttr::method meth = t.get_method(methodName);

        return callWithLuaParamsCommon(L, meth, rttr::instance(), nArgs);
    }

    // so, I need to be able to put object, variant containing object or something like that into userdata allocated by lua
    // idk if rttr variants are moveable (if there is a way to avoid copying), but I will assume they are not
    // possible options:
    // 1) pass a pointer to variant containing [object or pointer to object] to lua, and then create userdata of it
    // 2) pass variant containing [object or pointer to object] to lua, and then create userdata of it - probably will be hard to avoid unnecessary copying
    // we can't use raw pointers to class, because I don't know, which type it is, and I don't want to use void* (because it's not type safe)
    // for now I will use variant passed by copy, which contains a pointer to object (userdata will contain variant class)

    // also takes a nArgs parameter, which specifies, how many arguments from lua stack should be passed to constructor (if -1, then any number of arguments is allowed). It needs to be greater or equal to the number of non-default parameters
    // returns variant containing pointer to created object, or invalid variant if no matching constructor was found
    static rttr::variant findAndInvokeConstructorWithLuaArgs(lua_State* L, const rttr::type& type, int nArgs = -1)
    {
        for (rttr::constructor ctor : type.get_constructors())
        {
            auto info = ctor.get_parameter_infos();

            std::vector<rttr::parameter_info> vec(info.begin(), info.end());
            if (canConvertLuaParameters(L, vec, nArgs))
            {
                std::vector<rttr::variant> variants = convertLuaParametersToCppForReflection(L, vec, nArgs);
                std::vector<rttr::argument> params;
                for (rttr::variant& arg : variants)
                {
                    params.push_back(arg);
                }
                rttr::variant result = ctor.invoke_variadic(params);
                // object is std::shared_ptr<Class>, so we need to extract it
                result.get_type().get_method("release").invoke(result); // release ownership of object
                return result.extract_wrapped_value();
            }
        }
        return rttr::variant();
    }

public:
    // returns variant containing pointer to created object, or invalid variant if no matching constructor was found
    static rttr::variant findAndInvokeConstructorWithCppArgs(const rttr::type& type, const std::vector<rttr::variant>& args)
    {
        for (rttr::constructor ctor : type.get_constructors())
        {
            auto info = ctor.get_parameter_infos();

            std::vector<rttr::parameter_info> vec(info.begin(), info.end());
            int defCount = defaultArgumentCount(vec);
            if (args.size() >= info.size() - defCount && args.size() <= vec.size()) // have to check that we have enough arguments, but not too many
            {
                bool canConvert = true;
                for (int i = 0; i < (int)vec.size(); ++i)
                {
                    if (args[i].get_type().get_id() != vec[i].get_type().get_id())
                    {
                        wxLogError("Can't convert argument %d from type '%s' to type '%s'", i + 1, args[i].get_type().get_name().data(), vec[i].get_type().get_name().data());
                        wxLog::FlushActive();
                        canConvert = false;
                        break;
                    }
                }
                if (canConvert)
                {
                    auto r = args | std::views::transform([](const rttr::variant& var) { return static_cast<rttr::argument>(var); });
                    std::vector<rttr::argument> params(r.begin(), r.end());
                    rttr::variant result = ctor.invoke_variadic(params);
                    result.get_type().get_method("release").invoke(result); // release ownership of object
                    return result.extract_wrapped_value();
                }
            }
        }
        return rttr::variant();
    }

    // creates instance of given class by calling constructor with matching parameters
    // returns shared_ptr to created instance, or nullptr if no matching constructor was found
    // this one returns shared_ptr, because it's provided with a class type, so it can have nicer form of usage
    template<typename Class>
    static std::shared_ptr<Class> createInstanceByConstructorFromLuaStack(lua_State* L, int nArgs = -1)
    {
        auto result = findAndInvokeConstructorWithLuaArgs(rttr::type::get<Class>(), nArgs);
        // we need to do copy construction, because there are three options for constructor policies regarding object creation:
        // 1) create a new object with automatic storage duration
        // 2) create a new object and return std::shared_ptr<Class> (default)
        // 3) create a new object with dynamic storage duration (Class*), which needs to be properly .destroy()-ed later
        // third option is best for this use case IMO, but it requires explicitly changing policy in each class constructor registration, and I would obviously forget about it many times, ~~so I will just create a dynamic copy of automatic storage object~~ (decided to use shared_ptr's instead)
        static_assert(std::is_copy_constructible_v<Class>, "Class must be copy constructible (for now)");

        // TODO: require that "dynamic creation" policy is set if class is not copy constructible
        return result.is_valid() ? result.get_value<std::shared_ptr<Class>>() : nullptr;
    }

    // creates instance of given class by calling constructor with matching parameters
    // returns a variant with std::shared_ptr to dynamically-allocated variant containing instance. Variant is invalid if no matching constructor was found
    // returns variant containing pointer to created object, or invalid variant if no matching constructor was found
    static rttr::variant createInstanceByConstructorFromLuaStack(lua_State* L, const std::string& className, int nArgs = -1)
    {
        rttr::type type = rttr::type::get_by_name(className);
        if (!type.is_valid())
        {
            return nullptr;
        }
        auto result = findAndInvokeConstructorWithLuaArgs(L, type, nArgs);
        // now hopefully has shared_ptr inside, pointing to new instance of class
        // can methods be invoked reflectively on raw pointers to class?
        return result;
    }

//     static std::string toString(const rttr::variant& var)
//     {
//         for (const auto& prop : var.get_type().get_properties())
//         {
//             prop.get_name();
//             prop.
//         }
//     }

    // store reflectively created class instances as userdata/light userdata inside lua? (so that we can get them back later)
};