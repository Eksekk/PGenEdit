#include "pch.h"
#include "LuaFunction.h"
#include "LuaWrapper.h"

void luaFunctionInit()
{
	constexpr auto&& w = luaWrapper;

	LuaStackAutoRestore sr(w.getLuaState());
	w.getPath("pgenedit.functions", LUA_REGISTRYINDEX, true, true);

	// need weak values for functions table to not prevent garbage collection of functions
	w.createtable(0, 0);
	w.pushstring("v");
	w.setfield(-2, "__mode");
	w.setmetatable(-2);
}
