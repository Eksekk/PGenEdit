#include "pch.h"
#include "LuaWrapper.h"
#include "Utility.h"

LuaWrapper luaWrapper;

LuaWrapper::LuaWrapper() : L(nullptr)
{
}

LuaWrapper::LuaWrapper(lua_State* L) : L(L)
{
}

LuaWrapper& LuaWrapper::pop(int n)
{
    lua_pop(L, n);
    return *this;
}

LuaWrapper& LuaWrapper::pushvalue(int pos)
{
    lua_pushvalue(L, pos);
    return *this;
}

LuaWrapper& LuaWrapper::getfield(int idx, const char* key)
{
    lua_getfield(L, idx, key);
    return *this;
}

std::string luaTypeToStr(lua_State* L, int idx)
{
    switch (lua_type(L, idx))
    {
    case LUA_TNIL:
        return "nil";
    case LUA_TBOOLEAN:
        return "boolean";
    case LUA_TSTRING:
        return "string";
    case LUA_TNUMBER:
        return "number";
    case LUA_TTABLE:
        return "table";
    case LUA_TTHREAD:
        return "thread";
    case LUA_TUSERDATA:
        return "userdata";
    }
    return "";
}

bool LuaWrapper::getPath(const std::string& path, bool lastMustBeTable, bool create)
{
    auto parts = splitString(path, ".");
    if (create)
    {
        lua_getglobal(L, "tget");
        lua_pushvalue(L, LUA_GLOBALSINDEX);
        for (const auto& part : parts)
        {
            pushString(part);
        }
        int error = pcall(parts.size() + 1, 1, 0);
        if (error)
        {
            wxLogError("Couldn't tget() path '%s': '%s'", path, lua_tostring(L, -1));
            pop(1);
            wxLog::FlushActive();
            return false;
        }
        return true;
    }
    lua_getglobal(L, parts.at(0).c_str());
    int n = 1;
    static const wxString format = "[index %d, key %s] couldn't get proper value (got '%s', expected '%s')";
    if (lua_type(L, -1) != LUA_TTABLE)
    {
        wxLogError(format, 0, parts.at(0), luaTypeToStr(L, -1), "table");
        lua_pop(L, n);
        return false;
    }
    for (size_t i = 1; i < parts.size(); ++i)
    {
        const auto& part = parts[i];
        lua_getfield(L, -1, part.c_str());
        ++n;
        if ((lastMustBeTable || i != parts.size() - 1) && lua_type(L, -1) != LUA_TTABLE) // last part can be any value
        {
            wxLogError(format, n - 1, part, luaTypeToStr(L, -1), "table");
            lua_pop(L, n);
            return false;
        }
    }
    // set first added stack value to result and pop all others
    lua_replace(L, -n);
    lua_pop(L, std::max(0, n - 2));
    return true;
}

LuaWrapper& LuaWrapper::pushString(const std::string& str)
{
    lua_pushstring(L, str.c_str());
    return *this;
}

int LuaWrapper::pcall(int nargs, int nresults, int errfunc)
{
    return lua_pcall(L, nargs, nresults, errfunc);
}

LuaWrapper& LuaWrapper::call(int nargs, int nresults)
{
    lua_call(L, nargs, nresults);
    return *this;
}
