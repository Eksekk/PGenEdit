#include "pch.h"
#include "LuaFunction.h"
#include "LuaWrapper.h"

void LuaFunction::fetchFromRegistry()
{
// 	LuaWrapper& w = luaWrapper;
// 	LuaStackAutoRestore ar(w);
// 
// 	w.getPath({ "pgenedit", registrySubtableKeyFunctions }, LUA_REGISTRYINDEX, false, false);
// 
// 	LuaValue v(w.getLuaState(), -1);
// 	if (!v.is)
	throw std::logic_error("Lua functions in C++ are stored only in registry, so this function doesn't need to / can't be called");
}

void LuaFunction::persistInRegistry() const
{
	throw std::logic_error("Lua functions in C++ are stored only in registry, so this function doesn't need to / can't be called");
}
