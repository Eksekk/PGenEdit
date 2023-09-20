#include "pch.h"
#include "LuaWrapper.h"

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
