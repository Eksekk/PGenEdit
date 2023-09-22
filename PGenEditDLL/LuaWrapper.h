#pragma once
#include "pch.h"
#include "main.h"

class LuaWrapper;
extern LuaWrapper luaWrapper;

class LuaWrapper // doesn't take ownership of the state, just makes access to it more convenient
{
    lua_State* L;
public:

    LuaWrapper();
    LuaWrapper(lua_State* L);

    LuaWrapper& pop(int n);
    LuaWrapper& pushvalue(int pos);
    LuaWrapper& getfield(int idx, const char* key);
    // tries to get sequence of tables corresponding to given path separated with dots, uses global environment for first part
    // returns true if successful and only adds to the stack requested object, otherwise returns false and stack is fully restored
    bool getPath(const std::string& path);
    


    lua_State* getLuaState() const { return L; }
    void setLuaState(lua_State* val) { L = val; }
};

