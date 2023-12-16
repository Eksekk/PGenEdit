#pragma once
#include "main.h"
#include "LuaTable.h"
#include "Utility.h"

extern "C"
{
	extern lua_State* Lua;

	int runScript(const char* str);
	static int runScript2(lua_State* L); // need to be static to work correctly, otherwise lua calls into invalid address
	void luaInit();
	void luaDeInit();
	bool checkIsInGame();
	void setupGameSaveHandler();
	void removeGameSaveHandler();
}

bool detectIfIsMerge();
void fillGameStaticPointersAndSizes();

// custom exception, which will be thrown as part one of generating lua error from C++
// using this, because it properly invokes destructors of objects
// this exception should be caught by C++ function directly called by lua, and it should execute its own stack objects' destructors and generate lua error
class LuaErrorException : public std::runtime_error
{
    // TODO: have more fields (like what type of error it is, and what are error parameters, so for type mismatch we can show expected type and actual type) to facilitate unit testing
public:
    LuaErrorException(const std::string& msg) : std::runtime_error(msg) {}

    ~LuaErrorException()
    {
        //wxMessageBox(wxString::Format("Lua error: %s", what()), "Lua error", wxICON_ERROR | wxOK);
    }
};

namespace lua::utils
{
    // creates "safe" lua error, that is not skipping C++ destructors
    // still need to write try-catch block **in first function on call stack called by lua** which calls luaL_error
    // note: exception object is automatically destroyed, even though lua might skip C++ code by using longjmp to signal error
    // [[noreturn]] doesn't need to be here BTW, exception object is still destroyed
    template<typename... Args>
    [[noreturn]] void luaError(const std::string& msg, Args&&... args)
    {
        throw LuaErrorException(std::vformat(msg, std::make_format_args(std::forward<Args>(args)...)));
    }

	// throws error if condition is false
	template<typename... Args>
	void luaAssert(bool condition, const std::string& msg, Args&&... args)
	{
		if (!condition)
		{
			luaError(msg, std::forward<Args>(args)...);
		}
	}

    // just found out there's lua_typename() function, oh well
    std::string luaTypeToString(lua_State* L, int idx);
    std::string buildWantedLuaTypeString(lua_State* L, std::initializer_list<int> list);
    std::string getLuaTypeMismatchString(lua_State* L, std::initializer_list<int> wanted, int provided, int stackIndex);
    std::string getLuaTypeMismatchString(lua_State* L, int wanted, int provided, int stackIndex);

	// a function like below, but returning boolean if value is of given type and doesn't throw
	template<typename T>
	bool isLuaType(lua_State* L, int index)
	{
	    if constexpr (std::is_same_v<T, bool>)
	    {
	        return lua_isboolean(L, index);
	    }
	    else if constexpr (std::is_same_v<T, int>)
	    {
	        return lua_isnumber(L, index); // conscious choice to truncate values like 1.5 to 1, because otherwise 2 might be treated as integer, but 2.00000001, which is essentially equal to 2, will be treated as noninteger
	    }
	    else if constexpr (std::is_same_v<T, double>)
	    {
	        return lua_isnumber(L, index);              
	    }
	    else if constexpr (std::is_same_v<T, std::string_view>)
	    {
	        return lua_isstring(L, index);
	    }
	    else if constexpr (std::is_same_v<T, std::string>)
	    {
	        return lua_isstring(L, index);
	    }
	    else if constexpr (std::is_same_v<T, LuaTable>)
	    {
	        return lua_istable(L, index);
	    }
	    else if constexpr (std::is_same_v<T, void*>)
	    {
	        return lua_isuserdata(L, index);
	    }
	    else if constexpr (std::is_same_v<T, _Nil>)
	    {
	        return lua_isnil(L, index);
	    }
	    else
	    {
	        COMPILE_TIME_CONSTEXPR_IF_ERROR();
	        return false; // dummy return
	    }
	}
	
	template<typename T>
	T getLuaTypeOrError(lua_State* L, int index)
	{
	    if constexpr (std::is_same_v<T, bool>)
	    {
	        if (!lua_isboolean(L, index))
	        {
	            luaError("Bad argument #{}: expected boolean, got {}", index, lua_typename(L, index));
	        }
	        return lua_toboolean(L, index);
	    }
	    else if constexpr (std::is_same_v<T, int>)
	    {
	        if (!lua_isnumber(L, index))
	        {
	            luaError("Bad argument #{}: expected number, got {}", index, lua_typename(L, index));
	        }
	        else
	        {
	            lua_Number num = lua_tonumber(L, index);
	            if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min())
	            {
	                luaError("Bad argument #{}: number is out of range of int", index, lua_typename(L, index));
	            }
	            else if (!essentiallyEqualFloats(num, (lua_Number)(sqword_t)num))
	            {
	                luaError("Bad argument #{}: number is not integer", index, lua_typename(L, index));
	            }
	        }
	        return lua_tointeger(L, index);
	    }
	    else if constexpr (std::is_same_v<T, double>)
	    {
	        if (!lua_isnumber(L, index))
	        {
	            luaError("Bad argument #{}: expected number, got {}", index, lua_typename(L, index));
	        }
	        return lua_tonumber(L, index);
	    }
	    else if constexpr (std::is_same_v<T, std::string_view>)
	    {
	        if (!lua_isstring(L, index))
	        {
	            luaError("Bad argument #{}: expected string, got {}", index, lua_typename(L, index));
	        }
	        return lua_tostring(L, index);
	    }
	    else if constexpr (std::is_same_v<T, std::string>)
	    {
	        if (!lua_isstring(L, index))
	        {
	            luaError("Bad argument #{}: expected string, got {}", index, lua_typename(L, index));
	        }
	        return std::string(lua_tostring(L, index));
	    }
	    else if constexpr (std::is_same_v<T, LuaTable>)
	    {
	        if (!lua_istable(L, index))
	        {
	            luaError("Bad argument #{}: expected table, got {}", index, lua_typename(L, index));
	        }
	        return LuaTable(L, index);
	    }
	    else if constexpr (std::is_same_v<T, void*>)
	    {
	        if (!lua_isuserdata(L, index))
	        {
	            luaError("Bad argument #{}: expected object (userdata), got {}", index, lua_typename(L, index));
	        }
	        return lua_touserdata(L, index);
	    }
	    else if constexpr (std::is_same_v<T, _Nil>)
	    {
	        if (!lua_isnil(L, index))
	        {
	            luaError("Bad argument #{}: expected nil, got {}", index, lua_typename(L, index));
	        }
	        return _Nil();
	    }
	    else
	    {
	        COMPILE_TIME_CONSTEXPR_IF_ERROR();
	        return T(); // dummy return
	    }
	}
	
	bool luaTableHasMetafield(lua_State* L, int index, const std::string& name);
	
	template<typename T>
	T getLuaTableMetafieldOrError(lua_State* L, int index, const std::string& name)
	{
	    lua_getmetatable(L, index);
	    if (lua_isnil(L, -1))
	    {
	        lua_pop(L, 1);
	        luaError("Couldn't get metafield '{}' - table doesn't have a metatable", name);
	    }
	    lua_getfield(L, -1, name.c_str());
	    if (lua_isnil(L, -1))
	    {
	        lua_pop(L, 2);
	        luaError("Couldn't get metafield '{}' - table doesn't have such metafield", name);
	    }
	    T ret = getLuaTypeOrError<T>(L, -1);
	    lua_pop(L, 2);
	    return ret;
	}
	
	void luaExpectStackSize(lua_State* L, int expected);
}