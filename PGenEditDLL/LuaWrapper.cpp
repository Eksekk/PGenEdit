#include "pch.h"
#include "LuaWrapper.h"
#include "Utility.h"
#include "LuaFunctions.h"

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

LuaWrapper& LuaWrapper::setfield(int idx, const char* key)
{
    lua_setfield(L, idx, key);
    return *this;
}

LuaWrapper& LuaWrapper::gettable(int idx)
{
    lua_gettable(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::settable(int idx)
{
    lua_settable(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::rawget(int idx)
{
    lua_rawget(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::rawset(int idx)
{
    lua_rawset(L, idx);
    return *this;
}

bool LuaWrapper::getPath(const std::string& path, bool lastMustBeTable, bool create)
{
    auto parts = stringSplit(path, ".");
    return getPath(parts, lastMustBeTable, create);
}

bool LuaWrapper::getPath(const std::vector<std::string>& parts, bool lastMustBeTable /*= false*/, bool create /*= false*/)
{
    if (create)
    {
        lua_getglobal(L, "tget");
        lua_pushvalue(L, LUA_GLOBALSINDEX);
        for (const auto& part : parts)
        {
            pushstring(part);
        }
        int error = pcall(parts.size() + 1, 1, 0);
        if (error)
        {
            wxLogError("Couldn't tget() path '%s': '%s'", stringConcat(parts, "."), lua_tostring(L, -1));
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
        wxLogError(format, 0, parts.at(0), luaTypeToString(L, -1), "table");
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
            wxLogError(format, n - 1, part, luaTypeToString(L, -1), "table");
            lua_pop(L, n);
            return false;
        }
    }
    // set first added stack value to result and pop all others
    lua_replace(L, -n);
    lua_pop(L, std::max(0, n - 2));
    return true;
}

LuaWrapper& LuaWrapper::pushstring(const std::string& str)
{
    lua_pushlstring(L, str.c_str(), str.size());
    return *this;
}

LuaWrapper& LuaWrapper::pushnumber(lua_Number num)
{
    lua_pushnumber(L, num);
    return *this;
}

LuaWrapper& LuaWrapper::pushboolean(int b)
{
    lua_pushboolean(L, b);
    return *this;
}

LuaWrapper& LuaWrapper::pushnil()
{
    lua_pushnil(L);
    return *this;
}

std::string LuaWrapper::tostring(int index)
{
    size_t s;
    const char* p = lua_tolstring(L, index, &s);
    return std::string(p, s);
}

int LuaWrapper::checkstack(int extra)
{
    lua_checkstack(L, extra);
    return 0;
}

LuaWrapper& LuaWrapper::concat(int n)
{
    lua_concat(L, n);
    return *this;
}

LuaWrapper& LuaWrapper::createtable(int narr, int nrec)
{
    lua_createtable(L, narr, nrec);
    return *this;
}

LuaWrapper& LuaWrapper::newtable()
{
    lua_newtable(L);
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

int LuaWrapper::type(int index)
{
    return lua_type(L, index);
}

bool LuaWrapper::isNil(int index)
{
    return lua_isnil(L, index);
}

bool LuaWrapper::isNumber(int index)
{
    return lua_isnumber(L, index);
}

bool LuaWrapper::isString(int index)
{
    return lua_isstring(L, index);
}

bool LuaWrapper::isBoolean(int index)
{
    return lua_isboolean(L, index);
}

bool LuaWrapper::isTable(int index)
{
    return lua_istable(L, index);
}

bool LuaWrapper::isFunction(int index)
{
    return lua_isfunction(L, index);
}

bool LuaWrapper::isThread(int index)
{
    return lua_isthread(L, index);
}

bool LuaWrapper::isUserdata(int index)
{
    return lua_isuserdata(L, index);
}

bool LuaWrapper::isLightuserdata(int index)
{
    return lua_islightuserdata(L, index);
}

bool LuaWrapper::setPath(const std::string& path, int index)
{
    auto parts = stringSplit(path, ".");
    index = makeAbsoluteStackIndex(index);
    if (parts.size() == 1)
    {
        pushstring(path.data());
        pushvalue(index);
        lua_settable(L, LUA_GLOBALSINDEX);
    }
    else
    {
        auto firstParts = std::vector<std::string>(parts.begin(), parts.end() - 1);
        if (!getPath(firstParts))
        {
            return false;
        }
        lua_pushstring(L, parts.back().data());
        pushvalue(index);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return true;
}

int LuaWrapper::makeAbsoluteStackIndex(int index)
{
    return index >= 0 ? index : lua_gettop(L) + index + 1;
}