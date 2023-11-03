#include "pch.h"
#include "LuaTable.h"
#include "LuaFunctions.h"
#include "LuaWrapper.h"

_Nil Nil;

// converts value to lua value and pushes it on the stack
void luaTypeInCppToStack(const LuaTypeInCpp& val)
{
    if (const _Nil* nil = std::get_if<_Nil>(&val))
    {
        luaWrapper.pushnil();
    }
    else if (const sqword_t* num = std::get_if<sqword_t>(&val))
    {
        luaWrapper.pushnumber(*num);
    }
    else if (const lua_Number* num = std::get_if<lua_Number>(&val))
    {
        luaWrapper.pushnumber(*num);
    }
    else if (const std::string* str = std::get_if<std::string>(&val))
    {
        luaWrapper.pushstring(*str);
    }
    else if (const bool* b = std::get_if<bool>(&val))
    {
        luaWrapper.pushboolean(*b);
    }
    else if (const LuaTable* tbl = std::get_if<LuaTable>(&val))
    {
        tbl->toLuaTable();
    }
}

void LuaTable::toLuaTable() const
{
    luaWrapper.newtable();
    for (const auto& [key, value] : values)
    {
        luaTypeInCppToStack(key);
        luaTypeInCppToStack(value);
        luaWrapper.settable(-3);
    }
}

void argError(const std::string& expected, const std::string& actual)
{
    wxLogError("Expected type '%s', got '%s'", expected, actual);
}

void LuaTable::luaConvertTypeCommon(LuaTypeInCpp& val, int stack)
{
    stack = luaWrapper.makeAbsoluteStackIndex(stack);
    switch (lua_type(Lua, stack))
    {
    case LUA_TNIL:
        val = Nil;
        break;
    case LUA_TTABLE:
        val = LuaTable::fromLuaTable(stack);
        break;
    case LUA_TNUMBER:
    {
        lua_Number num = lua_tonumber(Lua, stack);
        lua_Number asInteger = (lua_Number)static_cast<sqword_t>(num);
        if (asInteger == num)
        {
            val = static_cast<sqword_t>(num);
        }
        else
        {
            val = num;
        }
    }
    break;
    case LUA_TBOOLEAN:
        val = (bool)lua_toboolean(Lua, stack);
        break;
    case LUA_TSTRING:
    {
        const char* p;
        size_t s;
        p = lua_tolstring(Lua, stack, &s);
        val = std::string(p, s);
    }
    break;
    }
}

LuaTable LuaTable::fromLuaTable(int index)
{
    wxASSERT_MSG(luaWrapper.isTable(index), wxString::Format("Value at index #%d is not a table", index));
    static sqword_t dword_max = std::numeric_limits<dword_t>::max(), sdword_min = std::numeric_limits<sdword_t>::min(), sdword_max = std::numeric_limits<sdword_t>::max();
    index = luaWrapper.makeAbsoluteStackIndex(index);
    int prevStack = lua_gettop(Lua);
    LuaTable t;
    lua_pushnil(Lua);
    while (lua_next(Lua, index) != 0)
    {
        LuaTypeInCpp key;
        LuaTypeInCpp value;
        switch (lua_type(Lua, -2)) // key
        {
        case LUA_TNIL:
        case LUA_TTABLE:
        case LUA_TNUMBER:
        case LUA_TBOOLEAN:
        case LUA_TSTRING:
            LuaTable::luaConvertTypeCommon(key, -2);
            break;
            // those below are unsupported
        case LUA_TFUNCTION:
            argError("function", luaTypeToString(Lua, -2));
            break;
        case LUA_TTHREAD:
            argError("thread", luaTypeToString(Lua, -2));
            break;
        case LUA_TUSERDATA:
            argError("userdata", luaTypeToString(Lua, -2));
            break;
        case LUA_TLIGHTUSERDATA:
            argError("light userdata", luaTypeToString(Lua, -2));
            break;
        }

        switch (lua_type(Lua, -1)) // value
        {
        case LUA_TNIL:
        case LUA_TTABLE:
        case LUA_TNUMBER:
        case LUA_TBOOLEAN:
        case LUA_TSTRING:
            LuaTable::luaConvertTypeCommon(value, -1);
            break;
            // those below are unsupported
        case LUA_TFUNCTION:
            argError("function", luaTypeToString(Lua, -1));
            break;
        case LUA_TTHREAD:
            argError("thread", luaTypeToString(Lua, -1));
            break;
        case LUA_TUSERDATA:
            argError("userdata", luaTypeToString(Lua, -1));
            break;
        case LUA_TLIGHTUSERDATA:
            argError("light userdata", luaTypeToString(Lua, -1));
            break;
        }
        t.emplace(std::move(key), std::move(value));
        lua_pop(Lua, 1); // pop value, leave key
    }
    lua_settop(Lua, prevStack);
    return t;
}

LuaTableValues::iterator LuaTable::begin()
{
    return values.begin();
}

LuaTableValues::iterator LuaTable::end()
{
    return values.end();
}

LuaTableValues::const_iterator LuaTable::begin() const
{
    return values.begin();
}

LuaTableValues::const_iterator LuaTable::end() const
{
    return values.end();
}

LuaTable::LuaTable(const LuaTableValues& values) : values(values)
{
}

LuaTable::LuaTable(LuaTableValues&& values) : values(std::move(values))
{
}

void LuaTable::emplace(LuaTypeInCpp&& key, LuaTypeInCpp&& value)
{
    values.emplace(std::forward<LuaTypeInCpp>(key), std::forward<LuaTypeInCpp>(value));
}

const LuaTypeInCpp& LuaTable::at(const LuaTypeInCpp& type) const
{
    return values.at(type);
}

LuaTypeInCpp& LuaTable::at(const LuaTypeInCpp& type)
{
    return values.at(type);
}

bool LuaTable::contains(const LuaTypeInCpp& type) const
{
    return values.contains(type);
}

bool operator==(const LuaTypeInCpp& a, const LuaTypeInCpp& b)
{
    // only way is to reimplement default behavior as on cppreference and sometimes use custom compare?

    // cannot have two variable initializers of different types inside if, and auto must deduce to same type
    // that's why variables are declared
    const lua_Number* num, * num2;
    const sqword_t* integer;
    if (num = std::get_if<lua_Number>(&a), integer = std::get_if<sqword_t>(&b); num && integer)
    {
        if (*num == *integer)
        {
            return true;
        }
    }
    else if (integer = std::get_if<sqword_t>(&a), num = std::get_if<lua_Number>(&b); integer && num)
    {
        if (*num == *integer)
        {
            return true;
        }
    }
    else if (num = std::get_if<lua_Number>(&a), num2 = std::get_if<lua_Number>(&b); num && num2)
    {
        return essentiallyEqualFloats(*num, *num2);
    }
    return operator==(a, b);
}

bool operator!=(const LuaTypeInCpp& a, const LuaTypeInCpp& b)
{
    return false;
}
