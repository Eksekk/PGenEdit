#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerClass.h"
#include "PlayerSkill.h"
#include "PlayerPrimaryStat.h"
#include "PlayerResistance.h"
#include "PlayerItem.h"

extern bool inMM;

class GameData
{
public:
	// first int is id (ingame, not index)
	static std::unordered_map<int, PlayerClass> classes; // lua + game structure parsing
	static std::unordered_map<int, PlayerSkill> skills; // lua + game structure parsing
	static std::map<int, std::unique_ptr<PlayerPrimaryStat>> primaryStats; // ordinary map to allow iterating in order
	static std::map<int, std::unique_ptr<PlayerResistance>> resistances;
	static std::map<int, std::unique_ptr<PlayerItem>> items;

	static bool processClassDataJson(const char* str);
	static bool processSkillDataJson(const char* str);
	static bool processMiscDataJson(const char* str);
	void fillInItemImages();
	static bool processItemDataJson(const char* str);

	static const int DATA_TYPE_COUNT = 3;

	static Json classDataJson, skillDataJson, miscDataJson, itemDataJson;

	static bool allDataReceived; // from lua, like class info
	static void postProcess();
	static void updateIsInGameAndPartySize();

	// TODO functions to parse data from lua and to parse game structures

	// pass templated game pointer, not stditemstxt etc.
};

