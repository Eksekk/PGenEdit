#pragma once
#include "pch.h"
#include "main.h"

class LuaWrapper // doesn't take ownership of the state, just makes access to it more convenient
{
    lua_State* L;
public:

    LuaWrapper();
    LuaWrapper(lua_State* L);

    LuaWrapper& pop(int n);
    LuaWrapper& pushvalue(int pos);
    LuaWrapper& getfield(int idx, const char* key);


    lua_State* getLuaState() const { return L; }
    void setLuaState(lua_State* val) { L = val; }
};

