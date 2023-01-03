#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerClass.h"
#include "PlayerSkill.h"
#include <vector>

class GameData
{
public:
	// first int is id (ingame, not index)
	static std::unordered_map<int, PlayerClass> classes; // lua + game structure parsing
	static std::unordered_map<int, PlayerSkill> skills; // lua + game structure parsing

	static bool processClassDataJson(const char* str);
	static bool processSkillDataJson(const char* str);

	static bool allDataReceived; // from lua, like class info
	static void postProcess();

	// TODO functions to parse data from lua and to parse game structures

	// pass templated game pointer, not stditemstxt etc.
};

