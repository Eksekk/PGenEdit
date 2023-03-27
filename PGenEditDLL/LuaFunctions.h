#pragma once
#include "pch.h"
#include "main.h"

extern "C"
{
	extern lua_State* Lua;

	int runScript(const char* str);
	static int runScript2(lua_State* L); // need to be static to work correctly, otherwise lua calls into invalid address
	void luaInit();
	bool checkIsInGame();
}

void fillGameStaticPointersAndSizes();