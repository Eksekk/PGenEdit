#pragma once
#include "pch.h"
#include "main.h"

extern int MAX_PLAYERS; // auto
extern bool IS_ELEMENTAL_MOD; // auto
extern bool IS_MERGE; // lua

extern int NUM_CLASSES;

enum SkillCombineMode
{
	BIT_PER_MASTERY, // first x bits mean skill, then each bit after indicates next mastery (if it's set); mm7+
	PACKED // first x bits mean skill, then next two bits mean mastery (increasing order: 00, 01, 10, 11); mm6
};

enum Mastery
{
	NOVICE = 1,
	EXPERT = 2,
	MASTER = 3,
	GM = 4,
	GRAND_MASTER = 4,
};

extern Mastery MAX_MASTERY; // 3 in mm6, 4 in mm7+
extern SkillCombineMode SKILL_COMBINE_MODE;
extern int SKILL_BITS;
extern int MASTERY_BITS[4];

extern const double MINIMUM_AFFINITY;
extern const double MAXIMUM_AFFINITY;

enum ItemType // for generator purposes
{
	MELEE_WEAPON = 0,
	RANGED_WEAPON,
	BLASTER,
	BODY_ARMOR,
	SHIELD,
	OTHER_EQUIPPABLE,
	POTION,
	SCROLL,
	MISC,
	ITEM_TYPE_COUNT,
};

enum ItemSubtype // only some items get this
{
	WEAPON_1H = 0,
	WEAPON_2H,
	BOW,
	CROSSBOW,
	// leather chain plate can be taken from skill
	POTION_HP, // gives hp
	POTION_SP, // gives sp
	POTION_BUFF, // buffs player
	POTION_EFFECT, // other type of effect
	SCROLL_DAMAGE, // usually useless, thus explicitly mentioned
	SCROLL_DECURSE,
	SCROLL_PROTECT, // prot from magic and resistances (preservation could be too but is not included)
	SCROLL_BUFF,
	SCROLL_DEBUFF_MONSTER,
	SCROLL_OTHER,
	ITEM_SUBTYPE_COUNT,
};

enum PartyType
{
	PARTY_GENERIC = 0,
	PARTY_CASTER,
	PARTY_MELEE,
	PARTY_RANGED,
	PARTY_DEFENSIVE,
	PARTY_TYPE_COUNT
};

enum PlayerType
{
	PLAYER_GENERIC = 0,
	PLAYER_CASTER,
	PLAYER_MELEE,
	PLAYER_RANGED,
	PLAYER_DEFENSIVE,
	PLAYER_UTILITY, // mainly for misc skills
	PLAYER_TYPE_COUNT
};

extern const std::unordered_map<std::string, int> plTypeEnumStringToId;

enum SkillType
{
	SKILL_GENERIC,
	SKILL_MELEE,
	SKILL_RANGED,
	SKILL_MAGIC,
	SKILL_UTILITY,
	SKILL_TYPE_COUNT
};

enum Alignment
{
	ALIGNMENT_NEUTRAL,
	ALIGNMENT_LIGHT, // mm7 and Merge
	ALIGNMENT_DARK, // mm7 and Merge
};

namespace mm6
{
	struct consts
	{

	};

	struct enums
	{

	};
}

namespace mm7
{
	struct consts
	{

	};

	struct enums
	{

	};
}

namespace mm8
{
	struct consts
	{

	};

	struct enums
	{

	};
}