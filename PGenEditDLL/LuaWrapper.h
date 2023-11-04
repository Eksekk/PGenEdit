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

    int makeAbsoluteStackIndex(int index);

    LuaWrapper& pop(int n);
    LuaWrapper& pushvalue(int pos);

    LuaWrapper& getfield(int idx, const char* key);
    LuaWrapper& setfield(int idx, const char* key);
    LuaWrapper& gettable(int idx);
    LuaWrapper& settable(int idx);
    LuaWrapper& rawget(int idx);
    LuaWrapper& rawset(int idx);

    // internally uses pushlstring
    LuaWrapper& pushstring(const std::string& str);
    LuaWrapper& pushnumber(lua_Number num);
    LuaWrapper& pushboolean(int b);
    LuaWrapper& pushnil();

    // internally uses tolstring
    std::string tostring(int index);
    int checkstack(int extra);
    LuaWrapper& concat(int n);
    LuaWrapper& createtable(int narr, int nrec);
    LuaWrapper& newtable();
    int pcall(int nargs, int nresults, int errfunc);
    LuaWrapper& call(int nargs, int nresults);

    int type(int index);
    bool isNil(int index);
    bool isNumber(int index);
    bool isString(int index);
    bool isBoolean(int index);
    bool isTable(int index);
    bool isFunction(int index);
    bool isThread(int index);
    bool isUserdata(int index);
    bool isLightuserdata(int index);

    // tries to get sequence of tables corresponding to given path separated with dots, uses global environment for first part
    // returns true if successful and only adds to the stack requested object, otherwise returns false and stack is fully restored
    // if "create" is true, acts like "tget" function
    bool getPath(const std::string& path, bool lastMustBeTable = false, bool create = false);

    bool getPath(const std::vector<std::string>& parts, bool lastMustBeTable = false, bool create = false);

    // gets the path (without last element) with getPath and then sets last element to value at provided stack index
    bool setPath(const std::string& path, int index);
    


    lua_State* getLuaState() const { return L; }
    void setLuaState(lua_State* val) { L = val; }
};

