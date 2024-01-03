#pragma once
#include "main.h"
#include "LuaTable.h"

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
    LuaWrapper& replace(int pos);

    LuaWrapper& getfield(int idx, const char* key);
    LuaWrapper& setfield(int idx, const char* key);
    LuaWrapper& gettable(int idx);
    LuaWrapper& settable(int idx);
    LuaWrapper& rawget(int idx);
    LuaWrapper& rawset(int idx);
    LuaWrapper& getglobal(const char* name);
    LuaWrapper& setglobal(const char* name);
    LuaWrapper& unsetGlobal(const char* name);
    // unsets several globals at once, if needToExist is true, throws error if any of them doesn't exist
    LuaWrapper& unsetGlobals(std::initializer_list<std::string> names, bool needToExist = false);
    LuaWrapper& getmetatable(int index);
    LuaWrapper& setmetatable(int index);

    LuaWrapper& settop(int index);
    int gettop();

    // internally uses pushlstring
    LuaWrapper& pushstring(const std::string& str);
    LuaWrapper& pushnumber(lua_Number num);
    LuaWrapper& pushboolean(int b);
    LuaWrapper& pushnil();
    LuaWrapper& pushcfunction(lua_CFunction func);
    LuaWrapper& pushlightuserdata(void* p);

    // internally uses tolstring
    std::string tostring(int index);
    lua_Number tonumber(int index);
    bool toboolean(int index);
    void* touserdata(int index);
    lua_CFunction tocfunction(int index);
    LuaTable totable(int index);

    int checkstack(int extra);
    LuaWrapper& concat(int n);
    LuaWrapper& createtable(int narr, int nrec);
    LuaWrapper& newtable();
    int pcall(int nargs, int nresults, int errfunc);
    LuaWrapper& call(int nargs, int nresults);

    int type(int index);
    std::string typename_(int index);
    bool isNil(int index);
    bool isNumber(int index);
    bool isString(int index);
    bool isBoolean(int index);
    bool isTable(int index);
    bool isFunction(int index);
    bool isThread(int index);
    bool isUserdata(int index);
    bool isLightuserdata(int index);
    // return boolean if error occurred, error code, results?
    bool loadstring(const std::string& str);
    bool dostring(const std::string& str);

    // dumps lua stack
    std::string dumpStack();
    // calls debug.traceback()
    std::string luaStackTrace();

    // uses wxStackWalker to add C++ stack trace to lua stack trace
    std::string cppStackTrace();

    // tries to get sequence of tables corresponding to given path separated with dots, uses provided table or global environment, if it's not provided or LUA_GLOBALSINDEX, for first part
    // returns true if successful and only adds to the stack requested object, otherwise returns false and stack is fully restored
    // if "create" is true, acts like "tget" function
    bool getPath(const std::string& path, int firstElemIndex = LUA_GLOBALSINDEX, bool lastMustBeTable = false, bool create = false);

    bool getPath(const std::vector<std::string>& parts, int firstElemIndex = LUA_GLOBALSINDEX, bool lastMustBeTable = false, bool create = false);

    // gets the path (without last element) with getPath and then sets last element to value at provided stack index
    bool setPath(const std::string& path, int valueIndex, int firstElemIndex = LUA_GLOBALSINDEX);

    lua_State* getLuaState() const { return L; }
    void setLuaState(lua_State* val) { L = val; }
};

// RAII class for restoring stack position
class LuaStackAutoRestore
{
    lua_State* L;
    int top;
public:
    LuaStackAutoRestore(lua_State* L);
	~LuaStackAutoRestore();

    int getTop() const { return top; }
};

// a class that captures stack position in constructor and restores it only when requested
class LuaStackTopBackup
{
	lua_State* L;
	int top;
public:
	LuaStackTopBackup(lua_State* L);
	void restore();

    int getTop() const { return top; }
};
