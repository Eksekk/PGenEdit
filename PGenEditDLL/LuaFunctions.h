#pragma once
#include "pch.h"
#include "main.h"

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
// just found out there's lua_typename() function, oh well
std::string luaTypeToString(lua_State* L, int idx);
std::string buildWantedLuaTypeString(std::initializer_list<int> list);
std::string getLuaTypeMismatchString(std::initializer_list<int> wanted, int provided, int stackIndex);
std::string getLuaTypeMismatchString(int wanted, int provided, int stackIndex);