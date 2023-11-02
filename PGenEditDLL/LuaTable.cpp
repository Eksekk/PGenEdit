#include "pch.h"
#include "LuaTable.h"
#include "LuaFunctions.h"
#include "LuaWrapper.h"

_Nil Nil;

LuaTable LuaTable::fromLuaTable(int index)
{
    wxASSERT_MSG(luaWrapper.isTable(index), wxString::Format("Value at index #%d is not a table", index));
    LuaTable t = processSingleTableContents(index);
    return t;
}

void LuaTable::toLuaTable()
{
    wxFAIL;
}

void argError(const std::string& expected, const std::string& actual)
{
    wxLogError("Expected type '%s', got '%s'", expected, actual);
}

void LuaTable::luaConvertTypeCommon(LuaTypesInCpp& val, int stack)
{
    stack = luaWrapper.makeAbsoluteStackIndex(stack);
    switch (lua_type(Lua, stack))
    {
    case LUA_TNIL:
        val = Nil;
        break;
    case LUA_TTABLE:
        val = LuaTable::processSingleTableContents(stack);
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

LuaTable LuaTable::processSingleTableContents(int index)
{
    static sqword_t dword_max = std::numeric_limits<dword_t>::max(), sdword_min = std::numeric_limits<sdword_t>::min(), sdword_max = std::numeric_limits<sdword_t>::max();
    index = luaWrapper.makeAbsoluteStackIndex(index);
    int prevStack = lua_gettop(Lua);
    LuaTable t;
    lua_pushnil(Lua);
    while (lua_next(Lua, index) != 0)
    {
        LuaTypesInCpp key;
        LuaTypesInCpp value;
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
    }
    lua_settop(Lua, prevStack);
    return t;
}

LuaTableValues::iterator LuaTable::begin()
{
    return values->begin();
}

LuaTableValues::iterator LuaTable::end()
{
    return values->end();
}

LuaTableValues::const_iterator LuaTable::begin() const
{
    return values->begin();
}

LuaTableValues::const_iterator LuaTable::end() const
{
    return values->end();
}

void LuaTable::emplace(LuaTypesInCpp&& key, LuaTypesInCpp&& value)
{
    values->emplace(std::forward<LuaTypesInCpp>(key), std::forward<LuaTypesInCpp>(value));
}

const LuaTypesInCpp& LuaTable::at(const LuaTypesInCpp& type) const
{
    return values->at(type);
}

LuaTypesInCpp& LuaTable::at(const LuaTypesInCpp& type)
{
    return values->at(type);
}

bool LuaTable::contains(const LuaTypesInCpp& type) const
{
    return values->contains(type);
}

LuaTable::LuaTable()
{
    values = std::make_unique<LuaTableValues>();
}