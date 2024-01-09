#include "pch.h"
#include "LuaWrapper.h"
#include "Utility.h"
#include "LuaFunctions.h"
#include <wx/stackwalk.h>

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
    checkStackIndex(pos);
    lua_pushvalue(L, pos);
    return *this;
}

LuaWrapper& LuaWrapper::getfield(int idx, const char* key)
{
    checkStackIndex(idx);
    lua_getfield(L, idx, key);
    return *this;
}

LuaWrapper& LuaWrapper::setfield(int idx, const char* key)
{
    checkStackIndex(idx);
    lua_setfield(L, idx, key);
    return *this;
}

LuaWrapper& LuaWrapper::gettable(int idx)
{
    checkStackIndex(idx);
    lua_gettable(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::settable(int idx)
{
	checkStackIndex(idx);
	lua_settable(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::rawget(int idx)
{
	checkStackIndex(idx);
	lua_rawget(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::rawset(int idx)
{
	checkStackIndex(idx);
	lua_rawset(L, idx);
    return *this;
}

LuaWrapper& LuaWrapper::getglobal(const char* name)
{
    lua_getglobal(L, name);
    return *this;
}

LuaWrapper& LuaWrapper::setglobal(const char* name)
{
    lua_setglobal(L, name);
    return *this;
}

LuaWrapper& LuaWrapper::settop(int index)
{
    lua_settop(L, index);
    return *this;
}

int LuaWrapper::gettop()
{
    return lua_gettop(L);
}

bool LuaWrapper::getPath(const std::string& path, int firstElemIndex, bool lastMustBeTable, bool create)
{
    auto parts = stringSplit(path, ".");
    return getPath(parts,firstElemIndex, lastMustBeTable, create);
}

bool LuaWrapper::getPath(const std::vector<std::string>& parts, int firstElemIndex, bool lastMustBeTable /*= false*/, bool create /*= false*/)
{
    checkStackIndex(firstElemIndex);
    firstElemIndex = makeAbsoluteStackIndex(firstElemIndex);
    if (create)
    {
        lua_getglobal(L, "tget");
        lua_pushvalue(L, firstElemIndex);
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
    int n = 0;
    static const wxString format = "[index %d, key %s] couldn't get proper value (got '%s', expected '%s')";
    for (size_t i = 0; i < parts.size(); ++i)
    {
        const auto& part = parts[i];
        int idx = i == 0 ? firstElemIndex : -1;
        lua_getfield(L, idx, part.c_str());
        ++n;
        if ((lastMustBeTable || i != parts.size() - 1) && lua_type(L, -1) != LUA_TTABLE) // last part can be any value
        {
            wxLogError(format, n - 1, part, lua::utils::luaTypeToString(L, -1), "table");
            lua_pop(L, n);
            return false;
        }
    }
    // set first added stack value to result and pop all others
    if (n > 1) // lua_replace with -1 only pops top element, so don't do it if there's only one element
	{
		lua_replace(L, -n);
    }
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

LuaWrapper& LuaWrapper::pushcfunction(lua_CFunction func)
{
    lua_pushcfunction(L, func);
    return *this;
}

LuaWrapper& LuaWrapper::pushlightuserdata(void* p)
{
    lua_pushlightuserdata(L, p);
    return *this;
}

void* LuaWrapper::newuserdata(size_t size)
{
    return lua_newuserdata(L, size);
}

std::string LuaWrapper::tostring(int index)
{
	checkStackIndex(index);
	size_t s;
    const char* p = lua_tolstring(L, index, &s);
    return std::string(p, s);
}

lua_Number LuaWrapper::tonumber(int index)
{
    checkStackIndex(index);
    return lua_tonumber(L, index);
}

bool LuaWrapper::toboolean(int index)
{
	checkStackIndex(index);
    return lua_toboolean(L, index);
}

void* LuaWrapper::touserdata(int index)
{
	checkStackIndex(index);
	return lua_touserdata(L, index);
}

lua_CFunction LuaWrapper::tocfunction(int index)
{
	checkStackIndex(index);
	return lua_tocfunction(L, index);
}

int LuaWrapper::checkstack(int extra)
{
    lua_checkstack(L, extra);
    return 0;
}

LuaWrapper& LuaWrapper::concat(int n)
{
    checkStackIndex(-n);
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
    if (errfunc)
    {
		checkStackIndex(errfunc);
    }
    checkStackIndex(-nargs - 1); // args + function
    return lua_pcall(L, nargs, nresults, errfunc);
}

LuaWrapper& LuaWrapper::call(int nargs, int nresults)
{
    checkStackIndex(-nargs - 1); // args + function
    lua_call(L, nargs, nresults);
    return *this;
}

int LuaWrapper::type(int index)
{
	checkStackIndex(index);
    return lua_type(L, index);
}

bool LuaWrapper::isNil(int index)
{
	checkStackIndex(index);
	return lua_isnil(L, index);
}

bool LuaWrapper::isNumber(int index)
{
	checkStackIndex(index);
	return lua_isnumber(L, index);
}

bool LuaWrapper::isString(int index)
{
	checkStackIndex(index);
	return lua_isstring(L, index);
}

bool LuaWrapper::isBoolean(int index)
{
	checkStackIndex(index);
	return lua_isboolean(L, index);
}

bool LuaWrapper::isTable(int index)
{
	checkStackIndex(index);
	return lua_istable(L, index);
}

bool LuaWrapper::isFunction(int index)
{
	checkStackIndex(index);
	return lua_isfunction(L, index);
}

bool LuaWrapper::isThread(int index)
{
	checkStackIndex(index);
	return lua_isthread(L, index);
}

bool LuaWrapper::isUserdata(int index)
{
	checkStackIndex(index);
	return lua_isuserdata(L, index);
}

bool LuaWrapper::isLightuserdata(int index)
{
	checkStackIndex(index);
	return lua_islightuserdata(L, index);
}

bool LuaWrapper::setPath(const std::string& path, int valueIndex, int firstElemIndex, bool create)
{
    checkStackIndex(valueIndex);
    checkStackIndex(firstElemIndex);
    auto parts = stringSplit(path, ".");
    valueIndex = makeAbsoluteStackIndex(valueIndex);
    firstElemIndex = makeAbsoluteStackIndex(firstElemIndex);
    if (parts.size() == 1)
    {
        pushstring(path.data());
        pushvalue(valueIndex);
        lua_settable(L, firstElemIndex);
    }
    else
    {
        auto firstParts = std::vector<std::string>(parts.begin(), parts.end() - 1);
        if (!getPath(firstParts, firstElemIndex, true, create))
        {
            return false;
        }
        lua_pushstring(L, parts.back().data());
        pushvalue(valueIndex);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return true;
}

int LuaWrapper::makeAbsoluteStackIndex(int index)
{
    // in case it gets changed in the future
    static_assert(lua_upvalueindex(2) < lua_upvalueindex(1), "lua_upvalueindex(2) must be less than lua_upvalueindex(1)");
    // don't break special indices
    if (index == LUA_GLOBALSINDEX || index == LUA_REGISTRYINDEX || index == LUA_ENVIRONINDEX || index <= lua_upvalueindex(1))
    {
		return index;
	}
    return index >= 0 ? index : lua_gettop(L) + index + 1;
}

int LuaWrapper::loadstring(const std::string& str)
{
    return luaL_loadstring(L, str.c_str());
}

int LuaWrapper::dostring(const std::string& str)
{
    return luaL_dostring(L, str.c_str());
}

LuaTable LuaWrapper::totable(int index)
{
    checkStackIndex(index);
    return LuaTable(L, index);
}

std::string LuaWrapper::typename_(int index)
{
    checkStackIndex(index);
    return lua_typename(L, index);
}

LuaWrapper& LuaWrapper::unsetGlobal(const char* name)
{
    pushnil();
	setglobal(name);
	return *this;
}

LuaWrapper& LuaWrapper::unsetGlobals(std::initializer_list<std::string> names, bool needToExist)
{
    LuaStackAutoRestore restore(L);
    for (const auto& name : names)
    {
        if (needToExist)
        {
            getglobal(name.c_str());
            if (isNil(-1))
			{
				lua::utils::luaError("Global '{}' doesn't exist", name);
			}
		}
		unsetGlobal(name.c_str());
	}
    return *this;
}

LuaWrapper& LuaWrapper::getmetatable(int index)
{
    checkStackIndex(index);
    lua_getmetatable(L, index);
    return *this;
}

LuaWrapper& LuaWrapper::setmetatable(int index)
{
	checkStackIndex(index);
	lua_setmetatable(L, index);
    return *this;
}

LuaWrapper& LuaWrapper::replace(int pos)
{
	checkStackIndex(pos);
	lua_replace(L, pos);
    return *this;
}

std::string LuaWrapper::dumpStack(int max, lua_State* L)
{
    if (!L)
    {
        L = this->L;
    }
    std::string result;
	int top = lua_gettop(L); // it's important to use raw lua api function here, because it allows to pass a different lua_State
    for (int i = top; i >= 1 && i > top - max; --i)
    {
		result += wxString::Format("%d: %s\n", i, lua::utils::luaTypeAndValueToString(L, i));
	}
    if (IsDebuggerPresent())
	{
        // correctly render newlines in debugger
        OutputDebugStringA(wxString::Format("Lua stack dump:\n%s", result));
        // don't output multiline "array view" of returned string
        return "";
	}
	return result;
}

class MyStackWalker : public wxStackWalker
{
    std::string result;
    bool skip = false;
    virtual void OnStackFrame(const wxStackFrame& frame) override
    {
        static const std::array luaModuleNames{ "lua51.dll", "lua5.1.dll", "lua5.1", "lua51" };
		// any module above must be loaded
		static bool tested = false;
        if (!tested) // only test once
        {
			tested = true;
			bool found = false;
			for (auto&& name : luaModuleNames)
			{
				if (GetModuleHandleA(name))
				{
					found = true;
					break;
				}
			}
			wxASSERT_MSG(found, "Lua module not found - is file version updated, but in-code name not updated?");
        }
		std::string mod = frame.GetModule().ToStdString();
        if (skip || util::container::existsInContainer(luaModuleNames, mod))
        {
            skip = true; // skip lua call and all before it
			return;
		}
        std::string loc;
        if (frame.HasSourceLocation())
        {
		    loc = std::format("[{}] {}({}:{}):", frame.GetModule(), frame.GetName(), frame.GetFileName(), frame.GetLine());
		}
        else
        {
            loc = std::format("[{}] {}:", frame.GetModule(), frame.GetName());
        }
		result += std::format("{} ({:p}):\t{}\n", frame.GetLevel(), frame.GetAddress(), loc);
	}
public:
    std::string getOutput()
    {
        Walk();
        skip = false;
        std::string r;
        r.swap(result);
        return r;
    }
};

std::string LuaWrapper::cppStackTrace()
{
    MyStackWalker walker;
    return walker.getOutput();
}

std::string LuaWrapper::luaStackTrace()
{
    LuaStackAutoRestore restore(L);
    wxASSERT(getPath("debug.traceback", LUA_GLOBALSINDEX));
    call(0, 1);
    return tostring(-1);
}

void LuaWrapper::checkStackIndex(int index)
{
    int abs = makeAbsoluteStackIndex(index);
    static_assert(lua_upvalueindex(2) < lua_upvalueindex(1), "lua_upvalueindex(2) must be less than lua_upvalueindex(1)");
    if (abs != LUA_REGISTRYINDEX && abs != LUA_GLOBALSINDEX && abs != LUA_ENVIRONINDEX && abs > lua_upvalueindex(1) && abs < 1)
    {
        lua::utils::luaError("Invalid stack index {}", index);
    }
    else if (abs > gettop())
	{
		lua::utils::luaError("Stack index {} is out of bounds for stack size {}", index, gettop());
	}
}

void LuaWrapper::checkAndTransformIndexes(std::vector<std::reference_wrapper<int>>& indexes)
{
    for (auto&& ref : indexes)
    {
        checkStackIndex(ref);
		ref.get() = makeAbsoluteStackIndex(ref);
    }
}

int LuaWrapper::getmetafield(int objIndex, const char* key)
{
    checkStackIndex(objIndex);
    return luaL_getmetafield(L, objIndex, key);
}

std::pair<bool, std::vector<LuaTypeInCpp>> LuaWrapper::varargPcall(int funcIndex, int resultsNum, const std::vector<LuaTypeInCpp>& args)
{
	LuaStackAutoRestore stackAutoRestore(L);
    checkStackIndexAndMakeAbsolute(funcIndex);
	wxASSERT(lua::pushErrorHandlerFunction(L));
    int errorFuncIndex = gettop();
    wxASSERT(errorFuncIndex > 0);
	// assume function is on the stack
	varargCallSetup(L, funcIndex, args);
	// call function
	if (pcall(args.size(), resultsNum, errorFuncIndex) != LUA_OK)
	{
		// error occurred
		return std::make_pair(false, varargCallGetResults(L, 1));
	}
	// get results
	return std::make_pair(true, varargCallGetResults(L, resultsNum));
}

std::vector<LuaTypeInCpp> LuaWrapper::varargCall(int funcIndex, int resultsNum, const std::vector<LuaTypeInCpp>& args)
{
	LuaStackAutoRestore stackAutoRestore(L);
	// assume function is on the stack
	varargCallSetup(L, funcIndex, args);
	// call function
	call(args.size(), resultsNum);
	// get results
	return varargCallGetResults(L, resultsNum);
}

LuaWrapper& LuaWrapper::remove(int index)
{
    checkStackIndex(index);
	lua_remove(L, index);
	return *this;
}

void LuaWrapper::checkStackIndexAndMakeAbsolute(int& index)
{
	checkStackIndex(index);
	index = makeAbsoluteStackIndex(index);
}

LuaStackAutoRestore::LuaStackAutoRestore(lua_State* L)
{
    this->L = L;
	top = lua_gettop(L);
}

LuaStackAutoRestore::~LuaStackAutoRestore()
{
	lua_settop(L, top);
}

LuaStackTopBackup::LuaStackTopBackup(lua_State* L)
{
	this->L = L;
	top = lua_gettop(L);
}

void LuaStackTopBackup::restore()
{
	lua_settop(L, top);
}
