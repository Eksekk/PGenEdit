#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerClass.h"
#include "PlayerSkill.h"
#include "PlayerPrimaryStat.h"

extern bool inMM;

class GameData
{
public:
	// first int is id (ingame, not index)
	static std::unordered_map<int, PlayerClass> classes; // lua + game structure parsing
	static std::unordered_map<int, PlayerSkill> skills; // lua + game structure parsing
	static std::map<int, PlayerPrimaryStat> primaryStats; // ordinary map to allow iterating in order

	static bool processClassDataJson(const char* str);
	static bool processSkillDataJson(const char* str);
	static bool processMiscDataJson(const char* str);
	static const int DATA_TYPE_COUNT = 3;

	static Json classDataJson, skillDataJson, miscDataJson;

	static bool allDataReceived; // from lua, like class info
	static void postProcess();
	static void reparse(const char* data[DATA_TYPE_COUNT]);
	static void updateIsInGameAndPartySize();

	// TODO functions to parse data from lua and to parse game structures

	// pass templated game pointer, not stditemstxt etc.
};

