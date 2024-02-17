#pragma once
#include "main.h"
#include "LuaTable.h"
#include "LuaFunctions.h"
#include "LuaValue.h"

class LuaWrapper;
extern LuaWrapper luaWrapper; // wrapper for global lua state (the one Grayface uses to setup his hooking system)

// RAII class for restoring stack position
class LuaStackAutoRestore
{
	lua_State* L;
	int top;
public:
	explicit LuaStackAutoRestore(lua_State* L);
    explicit LuaStackAutoRestore(const LuaWrapper& w);
	~LuaStackAutoRestore();

	int getTop() const { return top; }
};

// a class that captures stack position in constructor and restores it only when requested
class LuaStackTopBackup
{
	lua_State* L;
	int top;
public:
	explicit LuaStackTopBackup(lua_State* L);
    explicit LuaStackTopBackup(const LuaWrapper& w);
	void restore();

	int getTop() const { return top; }
};

class LuaWrapper // doesn't take ownership of the state, just makes access to it more convenient
{
    lua_State* L;
public:

    explicit LuaWrapper();
    explicit LuaWrapper(lua_State* L);

    int makeAbsoluteStackIndex(int index);
    void checkStackIndexAndMakeAbsolute(int& index);

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
    LuaWrapper& setmetatableArg(int index, const LuaTable& metatable);
    int getmetafield(int objIndex, const char* key);

    LuaWrapper& settop(int index);
    int gettop();
    LuaWrapper& remove(int index);

    bool equal(int idx1, int idx2);
    bool rawequal(int idx1, int idx2);

    // internally uses pushlstring
    LuaWrapper& pushstring(const std::string& str);
    LuaWrapper& pushnumber(lua_Number num);
    LuaWrapper& pushboolean(int b);
    LuaWrapper& pushnil();
    LuaWrapper& pushcfunction(lua_CFunction func);
    LuaWrapper& pushlightuserdata(void* p);

    void* newuserdata(size_t size);

    // allocates new userdata, creates an object there via placement new, and leaves the userdata on stack, returning object pointer
    // WARNING: don't call delete on returned memory, because it is managed by lua. Call destructor manually instead.
    template<typename T, typename... Args>
    T* newObjectAllocateNewUserdata(Args&&... args)
    {
        void* p = newuserdata(sizeof(T));
		return new(p) T(std::forward<Args>(args)...);
	}

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
    // returns error codes used by lua_load (in particular, for successfull load it returns LUA_OK)
    int loadstring(const std::string& str);
    // returns error codes used by lua_load (in particular, for successfull load it returns LUA_OK)
    int dostring(const std::string& str);

    // dumps lua stack
    // second parameter is to allow using it while debugging, because MSVS doesn't support implicit constructor calls
    std::string dumpStack(int max = 20, lua_State* L = nullptr);
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
    bool setPath(const std::string& path, int valueIndex, int firstElemIndex = LUA_GLOBALSINDEX, bool create = true);
	bool setPath(const std::vector<std::string>& parts, int valueIndex, int firstElemIndex = LUA_GLOBALSINDEX, bool create = true);

private:
    void checkAndTransformIndexes(std::vector<std::reference_wrapper<int>>& indexes);
    void varargCallSetup(lua_State* L, int funcIndex, const std::vector<LuaTypeInCpp>& args)
    {
		checkStackIndex(funcIndex);
		funcIndex = makeAbsoluteStackIndex(funcIndex);
        // function needs to be just before arguments
		if (funcIndex != gettop())
		{
			pushvalue(funcIndex); // push function reference to top
		}
		// push arguments
		int top = gettop();
		LuaTable::fromRange(args).pushArrayPartToLuaStack(L);
		wxASSERT_MSG(gettop() - top == args.size(), "Number of arguments pushed to stack doesn't match number of arguments provided");
    }

    std::vector<LuaTypeInCpp> varargCallGetResults(lua_State* L, int resultsNum)
    {
		std::vector<LuaTypeInCpp> results;
		for (int i = 0; i < resultsNum; ++i)
		{
			results.push_back(lua::utils::convertStackIndexToLuaTypeInCpp(L, -resultsNum + i));
		}
        return results;
    }
public:
    // leaves function unchanged on stack, even if it's top element
    // returns true if function was called successfully and results inside vector, otherwise returns false and first (and only) vector element contains error message/object (like pcall)
    std::pair<bool, std::vector<LuaTypeInCpp>> varargPcall(int funcIndex, int resultsNum, const std::vector<LuaTypeInCpp>& args);

    // leaves function unchanged on stack, even if it's top element
    // returns vector of function results
    std::vector<LuaTypeInCpp> varargCall(int funcIndex, int resultsNum, const std::vector<LuaTypeInCpp>& args);

    // checks validity of stack index, throws error (exception) if it's invalid
    void checkStackIndex(int index);

    lua_State* getLuaState() const { return L; }
    void setLuaState(lua_State* val) { L = val; }

    // operator() which takes lua_State* as argument is used to return a new wrapper, which uses that state
    // it's needed for debugging, because MSVS doesn't support implicit constructor calls
    [[maybe_unused]] LuaWrapper operator()(lua_State* L) const { return LuaWrapper(L); }

    // ugly hack to force code generation for operator()
private:
    static constexpr auto addr = &operator();
};
