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
static void* luaGetObjectPtr(lua_State* L, int index, void*& ptr)
{
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
        lua_getfield(L, index, "?ptr");
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
    rttr::variant obj = Reflection::findAndInvokeConstructorWithCppArgs(var.get_type(), { var });
    if (!obj.is_valid())
    {
        luaError("Couldn't copy object - couldn't find constructor");
        return 0;
    }
    else
    {
        if (!obj.convert(rttr::type::get<void*>()))
        {
            luaError("Couldn't copy object - couldn't convert to original type");
            return 0;
        }
        else
        {
            void* objPtr = obj.get_value<void*>();
            w.newtable().pushnumber((dword_t)objPtr).setfield(-1, "?ptr");
            return 1;
        }
    }
    //...
}

int luaDebug::createObject(lua_State* L)
{
    LuaWrapper w(L);
    void* ptr = 
}

int luaDebug::destroyObject(lua_State* L)
{
    return 0;
}

int luaDebug::getClassFields(lua_State* L)
{
    return 0;
}

int luaDebug::getClassInfo(lua_State* L)
{
    return 0;
}

int luaDebug::getField(lua_State* L)
{
    LuaWrapper w(L);
    if (w.isNil(1))
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
    else
    {
        void* ptr;
        if (luaWrapper.isUserdata(1))
        {
            ptr = luaWrapper.touserdata(1);
            if (!ptr)
            {
                luaError("Couldn't get field '" + w.tostring(2) + "' - userdata is null");
                return 0;
            }
        }
        else if (luaWrapper.isTable(1))
        {
            lua_getfield(L, 1, "?ptr");
            if (!lua_isnumber(L, 3))
            {
                lua_pop(L, 1);
                luaError("Couldn't get field '" + w.tostring(2) + "' - table doesn't have a pointer");
                return 0;
            }
        }
        else
        {
            luaError("Couldn't get field '" + w.tostring(2) + "' - first argument is neither userdata nor table");
            return 0;
        }
    }
}

int luaDebug::invokeCallable(lua_State* L)
{
    return 0;
}

int luaDebug::setField(lua_State* L)
{
    return 0;
}
