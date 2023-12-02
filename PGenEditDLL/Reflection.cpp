#include "pch.h"
#include "Reflection.h"
#include "LuaWrapper.h"

using type = rttr::type;
using type_id = type::type_id;
const type_id Reflection::TYPE_ID_CHAR = type::get<char>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_CHAR = type::get<unsigned char>().get_id();
const type_id Reflection::TYPE_ID_SHORT = type::get<short>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_SHORT = type::get<unsigned short>().get_id();
const type_id Reflection::TYPE_ID_INT = type::get<int>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_INT = type::get<unsigned int>().get_id();
const type_id Reflection::TYPE_ID_LONG = type::get<long>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_LONG = type::get<unsigned long>().get_id();
const type_id Reflection::TYPE_ID_LONG_LONG = type::get<long long>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_LONG_LONG = type::get<unsigned long long>().get_id();
const type_id Reflection::TYPE_ID_FLOAT = type::get<float>().get_id();
const type_id Reflection::TYPE_ID_DOUBLE = type::get<double>().get_id();
const type_id Reflection::TYPE_ID_LONG_DOUBLE = type::get<long double>().get_id();
const type_id Reflection::TYPE_ID_BOOL = type::get<bool>().get_id();
const type_id Reflection::TYPE_ID_STRING_VIEW = type::get<std::string_view>().get_id();
const type_id Reflection::TYPE_ID_STRING = type::get<std::string>().get_id();
const type_id Reflection::TYPE_ID_VOID_PTR = type::get<void*>().get_id();
const type_id Reflection::TYPE_ID_LUA_TABLE = type::get<LuaTable>().get_id();
const type_id Reflection::TYPE_ID_NIL = type::get<_Nil>().get_id();

const std::vector<type_id> Reflection::TYPE_IDS_INTEGERS{ TYPE_ID_CHAR, TYPE_ID_UNSIGNED_CHAR, TYPE_ID_SHORT, TYPE_ID_UNSIGNED_SHORT, TYPE_ID_INT, TYPE_ID_UNSIGNED_INT, TYPE_ID_LONG, TYPE_ID_UNSIGNED_LONG, TYPE_ID_LONG_LONG, TYPE_ID_UNSIGNED_LONG_LONG };
const std::vector<type_id> Reflection::TYPE_IDS_FLOATS{ TYPE_ID_FLOAT, TYPE_ID_DOUBLE, TYPE_ID_LONG_DOUBLE };
const std::vector<type_id> Reflection::TYPE_IDS_STRINGS{ TYPE_ID_STRING_VIEW, TYPE_ID_STRING };
const std::vector<type_id> Reflection::TYPE_IDS_NUMBERS{ compileTimeMergeVectors({TYPE_IDS_INTEGERS, TYPE_IDS_FLOATS }) };
// this one doesn't use "pointer" vector to merge, because strings already contain char pointers
const std::vector<type_id> Reflection::TYPE_IDS_ALL_TYPES{ compileTimeMergeVectors({TYPE_IDS_NUMBERS, TYPE_IDS_STRINGS, {TYPE_ID_BOOL, TYPE_ID_VOID_PTR, TYPE_ID_NIL} }) };

// creates "safe" lua error, that is not skipping C++ destructors
template<typename... Args>
[[noreturn]] void luaError(const std::string& msg, Args&&... args)
{
    throw LuaErrorException(std::format(msg, std::forward<Args>(args)...));
}

// a function like below, but returning boolean if value is of given type and doesn't throw
template<typename T>
bool isLuaType(lua_State* L, int index)
{
    if constexpr (std::is_same_v<T, bool>)
    {
        return lua_isboolean(L, index);
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        return lua_isinteger(L, index);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        return lua_isnumber(L, index);
    }
    else if constexpr (std::is_same_v<T, std::string_view>)
    {
        return lua_isstring(L, index);
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        return lua_isstring(L, index);
    }
    else if constexpr (std::is_same_v<T, LuaTable>)
    {
        return lua_istable(L, index);
    }
    else if constexpr (std::is_same_v<T, void*>)
    {
        return lua_isuserdata(L, index);
    }
    else if constexpr (std::is_same_v<T, _Nil>)
    {
        return lua_isnil(L, index);
    }
    else
    {
        COMPILE_TIME_CONSTEXPR_IF_ERROR();
        return false; // dummy return
    }
}

template<typename T>
T getLuaTypeOrError(lua_State* L, int index)
{
    if constexpr (std::is_same_v<T, bool>)
    {
        if (!lua_isboolean(L, index))
        {
            luaError("Expected boolean at index {}, got {}", index, lua_typename(L, index));
        }
        return lua_toboolean(L, index);
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        if (!lua_isinteger(L, index))
        {
            luaError("Expected integer at index {}, got {}", index, lua_typename(L, index));
        }
        return lua_tointeger(L, index);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        if (!lua_isnumber(L, index))
        {
            luaError("Expected number at index {}, got {}", index, lua_typename(L, index));
        }
        return lua_tonumber(L, index);
    }
    else if constexpr (std::is_same_v<T, std::string_view>)
    {
        if (!lua_isstring(L, index))
        {
            luaError("Expected string at index {}, got {}", index, lua_typename(L, index));
        }
        return lua_tostring(L, index);
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        if (!lua_isstring(L, index))
        {
            luaError("Expected string at index {}, got {}", index, lua_typename(L, index));
        }
        return std::string(lua_tostring(L, index));
    }
    else if constexpr (std::is_same_v<T, LuaTable>)
    {
        if (!lua_istable(L, index))
        {
            luaError("Expected table at index {}, got {}", index, lua_typename(L, index));
        }
        return LuaTable(L, index);
    }
    else if constexpr (std::is_same_v<T, void*>)
    {
        if (!lua_isuserdata(L, index))
        {
            luaError("Expected userdata (object) at index {}, got {}", index, lua_typename(L, index));
        }
        return lua_touserdata(L, index);
    }
    else if constexpr (std::is_same_v<T, _Nil>)
    {
        if (!lua_isnil(L, index))
        {
            luaError("Expected nil at index {}, got {}", index, lua_typename(L, index));
        }
        return _Nil();
    }
    else
    {
        COMPILE_TIME_CONSTEXPR_IF_ERROR();
        return T(); // dummy return
    }
}

bool luaTableHasMetafield(int index, const std::string& name)
{
    lua_getmetatable(Lua, index);
    if (lua_isnil(Lua, -1))
    {
        lua_pop(Lua, 1);
        return false;
    }
    lua_getfield(Lua, -1, name.c_str());
    if (lua_isnil(Lua, -1))
    {
        lua_pop(Lua, 2);
        return false;
    }
    lua_pop(Lua, 2);
    return true;
}

template<typename T>
T getLuaTableMetafieldOrError(int index, const std::string& name)
{
    lua_getmetatable(Lua, index);
    if (lua_isnil(Lua, -1))
    {
        lua_pop(Lua, 1);
        luaError("Couldn't get metafield '{}' - table doesn't have a metatable", name);
    }
    lua_getfield(Lua, -1, name.c_str());
    if (lua_isnil(Lua, -1))
    {
        lua_pop(Lua, 2);
        luaError("Couldn't get metafield '{}' - table doesn't have such metafield", name);
    }
    T ret = getLuaTypeOrError<T>(Lua, -1);
    lua_pop(Lua, 2);
    return ret;
}

void luaExpectStackSize(int expected)
{
    int stackSize = lua_gettop(Lua);
    if (stackSize != expected)
    {
        luaError("Expected {} arguments, got {}", expected, stackSize);
    }
}

// returns variant containing pointer to object of given type, or invalid variant if failed
static rttr::variant convertToObjectPointer(void* ptr, const std::string& typeName)
{
    rttr::type t = rttr::type::get_by_name(typeName);
    rttr::type ptrT = rttr::type::get_by_name(typeName + "*"); // pointer to object
    if (!t.is_valid())
    {
        luaError("Couldn't get type '{}'", typeName);
        return rttr::variant();
    }
    else if (!t.is_class())
    {
        luaError("Couldn't get type '{}' - it's not a class", typeName);
        return rttr::variant();
    }
    else if (!ptrT.is_valid())
    {
        luaError("Couldn't get type '{}'", typeName + "*");
        return rttr::variant();
    }
    else if (!ptrT.is_pointer())
    {
        luaError("Couldn't get type '{}' - it's not a pointer", typeName + "*");
        return rttr::variant();
    }
    else if (ptrT.get_raw_type() != t)
    {
        luaError("Couldn't get type '{}' - it's not a pointer to '{}'", typeName + "*", typeName);
        return rttr::variant();
    }
    else
    {
        rttr::variant var(ptr);
        if (!var.convert(static_cast<const rttr::type&>(ptrT))) // static_cast used to choose correct overload
        {
            luaError("Couldn't convert void* pointer {:p} to type '{}'", ptr, typeName + "*");
            return rttr::variant();
        }
        else
        {
            return var;
        }
    }
}

// receives class name as string
int luaDebug::classExists(lua_State* L)
{
    LuaWrapper w(L);
    if (w.gettop() != 1)
    {
        w.pushboolean(false);
        return 1;
    }
    std::string s = getLuaTypeOrError<std::string>(L, 1);
    rttr::type t = rttr::type::get_by_name(s);
    w.pushboolean(t.is_class());
    return 1;
}

// handles both userdata and table
static void* luaGetObjectPtr(lua_State* L, int index)
{
    void* ptr = nullptr;
    if (lua_isuserdata(L, index))
    {
        ptr = lua_touserdata(L, index);
        if (!ptr)
        {
            luaError("Couldn't get object - userdata is null");
        }
        //className = getLuaTableMetafieldOrError<std::string>(index, "className");
    }
    else if (lua_istable(L, index))
    {
        lua_getfield(L, index, "?ptr"); // class object table field
        if (!lua_isnumber(L, -1))
        {
            lua_pop(L, 1);
            luaError("Couldn't get object - table doesn't have a pointer");
        }
        return (void*)(dword_t)lua_tonumber(L, -1);
        lua_pop(L, 1);
        //className = getLuaTableMetafieldOrError<std::string>(index, "className");
    }
    else
    {
        luaError("Couldn't get object - first argument is neither userdata nor table");
    }
}

// receives object pointer (userdata) of address equal to pointer to object
int luaDebug::copyObject(lua_State* L)
{
    LuaWrapper w(L);
    luaExpectStackSize(1);
    void* ptr = luaGetObjectPtr(L, 1);
    if (!ptr)
    {
        luaError("Couldn't copy object - pointer is null");
        return 0;
    }
    rttr::variant var = convertToObjectPointer(ptr, getLuaTableMetafieldOrError<std::string>(1, "className"));
    if (!var.is_valid())
    {
        luaError("Couldn't copy object - couldn't convert to object pointer");
        return 0;
    }
    rttr::variant obj = Reflection::findAndInvokeConstructorWithCppArgs(var.get_type(), { var });
    if (!obj.is_valid())
    {
        luaError("Couldn't copy object - couldn't find ctor");
        return 0;
    }
    else
    {
        if (!obj.convert(rttr::type::get<void*>()))
        {
            luaError("Couldn't copy object - couldn't convert to void pointer");
            return 0;
        }
        else
        {
            void* objPtr = obj.get_value<void*>();
            void* ud = lua_newuserdata(L, sizeof(rttr::variant)); // automatically pushed to stack
            new(ud) rttr::variant(objPtr);
            // TODO: set __gc here?
            return 1;
        }
    }
    //...
}

// receives class name as string, number of arguments and optionally, arguments
int luaDebug::createObject(lua_State* L)
{
    LuaWrapper w(L);
    auto name = getLuaTypeOrError<std::string>(L, 1);
    int nargs;
    if (w.gettop() == 1) // assume no arguments
    {
        nargs = 0;
    }
    else
    {
        nargs = getLuaTypeOrError<int>(L, 2);
        int realArgCount = w.gettop() - 2;
        if (realArgCount != nargs)
        {
            luaError("Expected {} arguments, got {}", nargs, realArgCount);
            return 0;
        }
    }
    auto t = rttr::type::get_by_name(name);
    if (!t.is_valid())
    {
        luaError("Couldn't get class '{}'", name);
        return 0;
    }
    else if (!t.is_class())
    {
        luaError("Couldn't create object of type '{}', it's not a class", name);
        return 0;
    }
    else
    {
        rttr::variant obj = Reflection::findAndInvokeConstructorWithLuaArgs(t, nargs);
        if (!obj.is_valid())
        {
            luaError("Couldn't create object of type '{}'", name);
            return 0;
        }
        else
        {
            if (!obj.convert(rttr::type::get<void*>()))
            {
                luaError("Couldn't create object of type '{}' - couldn't convert to void pointer", name);
                return 0;
            }
            else
            {
                void* objPtr = obj.get_value<void*>();
                void* ud = lua_newuserdata(L, sizeof(rttr::variant)); // automatically pushed to stack
                new(ud) rttr::variant(objPtr);
                return 1;
            }
        }
    }
}

int luaDebug::destroyObject(lua_State* L)
{
    LuaWrapper w(L);
    luaExpectStackSize(1);
    if (w.isTable(1))
    {
        luaError("Couldn't destroy object - first argument is a table (C++ owned object), not userdata");
        return 0;
    }
    void* ptr = luaGetObjectPtr(L, 1);
    if (!ptr)
    {
        luaError("Couldn't destroy object - pointer is null");
        return 0;
    }
    rttr::variant var = convertToObjectPointer(ptr, getLuaTableMetafieldOrError<std::string>(1, "className"));
    if (!var.is_valid())
    {
        luaError("Couldn't destroy object - couldn't convert to object pointer");
        return 0;
    }
    var.get_type().destroy(var);
    // FIXME: will this work with pointers too, and delete pointed-to object, not 4-byte pointer primitive?
    return 0;
}

LuaTable getBasicTypeDataTable(const rttr::type& type)
{
    LuaTable typeInfo;
    const rttr::type::type_id typeId = type.get_id();
    typeInfo["name"] = type.get_name().to_string();
    typeInfo["isConst"] = TypeIds::isTypeAnyConst(typeId);
    typeInfo["isReference"] = TypeIds::isTypeAnyReference(typeId);
    typeInfo["isPointer"] = TypeIds::isTypeAnyPointer(typeId);
    typeInfo["isClass"] = type.is_class();
    typeInfo["isEnum"] = type.is_enumeration();
    rttr::type rawType = type.get_raw_type();
    if (typeId != rawType.get_id()) // avoid infinite recursion
    {
        typeInfo["raw"] = getBasicTypeDataTable(rawType);
    }
    return typeInfo;
}

LuaTable getCallableParamInfo(const rttr::parameter_info& param)
{
    LuaTable paramInfo;
    paramInfo["type"] = getBasicTypeDataTable(param.get_type());
    paramInfo["hasDefaultValue"] = param.has_default_value();
    paramInfo["defaultValue"] = param.get_default_value().to_string(); // FIXME: this is not a string, but a variant
    return paramInfo;
}

LuaTable getCallableParamsTable(const rttr::array_range<rttr::parameter_info>& params)
{
    LuaTable paramsTable;
    int i = 1;
    for (auto& param : params)
    {
        paramsTable[i++] = getCallableParamInfo(param);
    }
    return paramsTable;
}

// receives: class name
int luaDebug::getClassInfo(lua_State* L)
{
    luaExpectStackSize(1);
    std::string name = getLuaTypeOrError<std::string>(L, 1);
    rttr::type t{ type::get_by_name(name) };
    if (!t.is_valid())
    {
        luaError("Couldn't get class '{}'", name);
        return 0;
    }
    else if (!t.is_class())
    {
        luaError("Couldn't get class '{}', it's not a class", name);
        return 0;
    }
    /*
    -- name, type, isConst, isReference, isPointer, isClass, isEnum, isStatic, isField, isMethod, isCallable
    -- isCallable (for example std::function, functions as fields)
    -- if isCallable, then also returnType, params [array of basic properties above + two extra fields: hasDefaultValue, defaultValue]
    */
    LuaTable info;
    for (auto& prop : t.get_properties())
    {
        LuaTable propInfo;
        //fillInBasicTypeData(propInfo, prop.get_type());
        propInfo["name"] = prop.get_name().to_string();
        propInfo["type"] = getBasicTypeDataTable(prop.get_type());
        propInfo["isStatic"] = prop.is_static();
        propInfo["isField"] = true;
        propInfo["isMethod"] = false;
        propInfo["isCallable"] = t.is_function_pointer() || t.is_member_function_pointer(); // FIXME: somehow handle std::function
        // FIXME: no method-specific info is added for std::function

        info.getTableFieldOrCreate("fields")[prop.get_name().to_string()] = propInfo;
    }

    for (auto& method : t.get_methods())
    {
        LuaTable propInfo;
        //fillInBasicTypeData(propInfo, method.get_return_type());
        propInfo["name"] = method.get_name().to_string();
        propInfo["returnType"] = getBasicTypeDataTable(method.get_return_type());
        propInfo["isStatic"] = method.is_static();
        propInfo["isField"] = false;
        propInfo["isMethod"] = true;
        propInfo["isCallable"] = true;

        propInfo["params"] = getCallableParamsTable(method.get_parameter_infos());
        propInfo["signature"] = method.get_signature().to_string();

        info.getTableFieldOrCreate("methods")[method.get_name().to_string()] = propInfo;
    }

    for (auto& ctor : t.get_constructors())
    {
        LuaTable propInfo;
        //fillInBasicTypeData(propInfo, ctor.get_return_type());
        propInfo["returnType"] = getBasicTypeDataTable(ctor.get_declaring_type()); // always same return value
        propInfo["isField"] = false;
        propInfo["isMethod"] = true;
        propInfo["isCallable"] = true;

        propInfo["params"] = getCallableParamsTable(ctor.get_parameter_infos());
        propInfo["signature"] = ctor.get_signature().to_string();

        info.getTableFieldOrCreate("constructors").arrayInsert(propInfo);
    }

    // bases, derived
    LuaTable bases;
    for (auto& base : t.get_base_classes())
    {
        bases.arrayInsert(base.get_name().to_string());
    }
    info["bases"] = bases;
    LuaTable derived;
    for (auto& derivedClass : t.get_derived_classes())
    {
        derived.arrayInsert(derivedClass.get_name().to_string());
    }
    info["derived"] = derived;

    info.pushToLuaStack();
    return 1;
}

// receives: [class name, field name, object] or [field name] (global)
int getFieldCommon(lua_State* L)
{
    LuaWrapper w(L);
    if (w.gettop() == 1) // get global
    {
        // get global
        std::string name = w.tostring(2);
        auto t = rttr::type::get_by_name(name);
        if (!t.is_valid())
        {
            luaError("Couldn't get global '" + w.tostring(2) + "'");
            return 0;
        }
        else if (t.is_class())
        {
            luaError("Couldn't get global '" + w.tostring(2) + "' - it's a class");
            return 0;
        }
        else
        {
            Reflection::getGlobalVariableToLuaStack(name);
            return 1;
        }
    }
    else // get class field
    {
        rttr::type t = rttr::type::get_by_name(w.tostring(1));
        if (!t.is_valid())
        {
            luaError("Couldn't get class '" + w.tostring(1) + "'");
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't get class '" + w.tostring(1) + "' - it's not a class");
            return 0;
        }
        else
        {
            rttr::variant var = convertToObjectPointer(luaGetObjectPtr(L, 3), w.tostring(1));
            if (!var.is_valid())
            {
                luaError("Couldn't get class '" + w.tostring(1) + "' - couldn't convert to object pointer");
                return 0;
            }
            else
            {
                rttr::property prop = t.get_property(w.tostring(2));
                if (!prop.is_valid())
                {
                    luaError("Couldn't get property '" + w.tostring(2) + "' of class '" + w.tostring(1) + "'");
                    return 0;
                }
                else
                {
                    Reflection::getPropertyToLuaStack(var, w.tostring(2));
                }
            }
        }
        rttr::property p = .get_property(w.tostring(2));
    }
}

int luaDebug::getClassObjectField(lua_State* L)
{
    
}

int luaDebug::getGlobalField(lua_State* L)
{
    return 0;
}

int luaDebug::setGlobalField(lua_State* L)
{
    return 0;
}

int luaDebug::invokeClassMethod(lua_State* L)
{
    return 0;
}

int luaDebug::invokeFunctionOrCallableObject(lua_State* L)
{
    return 0;
}

int luaDebug::invokeCallable(lua_State* L)
{
    return 0;
}

int luaDebug::setClassObjectField(lua_State* L)
{
    return 0;
}
