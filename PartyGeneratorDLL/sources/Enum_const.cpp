#include "pch.h"
#include "main.h"
#include "Enum_const.h"

int MAX_PLAYERS = 0;
bool IS_ELEMENTAL_MOD = false;
bool IS_MERGE = false;

Mastery MAX_MASTERY = Mastery::GM; // 3 in mm6, 4 in mm7+
SkillCombineMode SKILL_COMBINE_MODE = BIT_PER_MASTERY;
int SKILL_BITS = 6;
std::array<int, 5> MASTERY_BITS = {-1, -1, 6, 7, 8};

const double MINIMUM_AFFINITY = 0.0;
const double MAXIMUM_AFFINITY = 1.0;

int NUM_CLASSES = 30;

const std::unordered_map<std::string, int> plTypeEnumStringToId = { {"caster", PLAYER_CASTER}, {"melee", PLAYER_MELEE}, {"defensive", PLAYER_DEFENSIVE}
	, {"utility", PLAYER_UTILITY}, {"ranged", PLAYER_RANGED} };

const std::unordered_map<std::string, int> skillTypeEnumStringToId = { {"melee", SKILL_MELEE}, {"ranged", SKILL_RANGED }, {"defensive", SKILL_DEFENSIVE},
	{"magic", SKILL_MAGIC}, {"utility", SKILL_UTILITY} };

const std::unordered_map<std::string, int> skillSpecialEnumStringToId = { {"blaster", SKSPC_BLASTER}, {"meditation", SKSPC_MEDITATION}, {"elemental", SKSPC_ELEMENTAL},
	{"self", SKSPC_SELF}, {"magicExclusive", SKSPC_MAGIC_EXCLUSIVE}, {"shield", SKSPC_SHIELD}, {"raceSkill", SKSPC_RACE_SKILL} };

const std::unordered_map<std::string, int> alignmentStringToId = { {"neutral", ALIGNMENT_NEUTRAL}, {"light", ALIGNMENT_LIGHT}, {"dark", ALIGNMENT_DARK} };