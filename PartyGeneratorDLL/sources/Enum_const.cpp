#include "pch.h"
#include "main.h"
#include "Enum_const.h"

int MAX_PLAYERS = 0;
bool IS_ELEMENTAL_MOD = false;
bool IS_MERGE = false;

Mastery MAX_MASTERY = Mastery::GM; // 3 in mm6, 4 in mm7+
SkillCombineMode SKILL_COMBINE_MODE = BIT_PER_MASTERY;
int SKILL_BITS = 6;
int MASTERY_BITS[4] = { 8, 7, 6, 5 };

const double MINIMUM_AFFINITY = 0.0;
const double MAXIMUM_AFFINITY = 1.0;

int NUM_CLASSES = 30;

const std::unordered_map<std::string, int> plTypeEnumStringToId = { {"caster", PLAYER_CASTER}, {"melee", PLAYER_MELEE}, {"defensive", PLAYER_DEFENSIVE}
	, {"utility", PLAYER_UTILITY}, {"ranged", PLAYER_RANGED} };