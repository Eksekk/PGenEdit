#include "pch.h"
#include "LuaFunctions.h"

extern "C"
{
	lua_State* Lua = nullptr;

	int runScript(const char* str)
	{
		bool error = luaL_loadstring(Lua, str);
		if (!error)
		{
			error = lua_pcall(Lua, 0, 0, 0);
		}
		if (error)
		{
			const char* msg = lua_tostring(Lua, -1);
			lua_pop(Lua, 1);
			luaL_error(Lua, msg);
			return 0;
		}
		lua_pushboolean(Lua, true);
		return 1;
	}

	// need to be static to work correctly, otherwise lua calls into invalid address
	static int runScript2(lua_State* L)
	{
		// like in asm, if gettop is 2, there are 2 parameters on the stack and stack points at last parameter (not at next free one)
		if (lua_gettop(L) == 0)
		{
			luaL_error(L, "Source code parameter missing");
			return 0;
		}
		if (lua_type(L, -1) != LUA_TSTRING)
		{
			luaL_error(L, "String parameter required");
			return 0;
		}
		const char* str = lua_tostring(L, -1);
		lua_pop(L, 1);
		return runScript(str);
	}

	const luaL_Reg lib[] =
	{
		{"runScript", runScript2},
		{0, 0}
	};

	void luaInit()
	{
		lua_getglobal(Lua, "pgen");
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			luaL_openlib(Lua, "pgen", lib, 0);
			lua_pop(Lua, 2);
		}
		else
		{
			lua_pop(Lua, 1);
		}
		/*lua_getglobal(Lua, "pgen");
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			lua_createtable(Lua, 0, 0);
			lua_pushcfunction(Lua, runScript2);
			lua_setfield(L, -1, )
		}
		else
		{
			lua_pop(Lua, 1);
		}*/
	}

	bool checkIsInGame()
	{
		lua_pushstring(Lua, "InGame");
		lua_rawget(Lua, LUA_REGISTRYINDEX);
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			lua_settop(Lua, 0);
			return false;
		}
		else
		{
			bool ret = lua_toboolean(Lua, -1);
			lua_settop(Lua, 0);
			return ret;
		}
	}
}

