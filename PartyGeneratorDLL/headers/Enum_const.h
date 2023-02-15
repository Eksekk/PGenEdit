#pragma once
#include "pch.h"
#include "main.h"

extern int MAX_PLAYERS; // auto
extern int CURRENT_PARTY_SIZE; // in mm8
extern bool IS_ELEMENTAL_MOD; // changes some game structures, different parsing needed
extern bool IS_MERGE; // ditto, todo: merge versions !!!!! structs.Player.Attrs support

extern int NUM_CLASSES;

enum SkillCombineMode
{
	BIT_PER_MASTERY, // first x bits mean skill, then each bit after indicates next mastery (if it's set); mm7+
	PACKED // first x bits mean skill, then next two bits mean mastery (00 novice or none, 01 expert, 10 master, 11 (potentially) GM); mm6
};

enum Mastery
{
	NONE = 0,
	NOVICE = 1,
	EXPERT = 2,
	MASTER = 3,
	GM = 4,
	GRAND_MASTER = 4,
};

extern Mastery MAX_MASTERY; // 3 in mm6, 4 in mm7+
extern SkillCombineMode SKILL_COMBINE_MODE;
extern int SKILL_BITS;
extern std::array<int, 5> MASTERY_BITS;

extern const double MINIMUM_AFFINITY; // multiplied by weights
extern const double MAXIMUM_AFFINITY; // ditto

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
	ITEM_TYPE_MISC,
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
	PARTY_GENERIC = 0, // means basically "anything can generate", thus everything has affinity 1 in it and probably won't change
	PARTY_CASTER,
	PARTY_MELEE,
	PARTY_RANGED,
	PARTY_DEFENSIVE,
	PARTY_TYPE_COUNT
};

enum PlayerType
{
	PLAYER_GENERIC = 0, // see above
	PLAYER_CASTER,
	PLAYER_MELEE,
	PLAYER_RANGED,
	PLAYER_DEFENSIVE,
	PLAYER_UTILITY, // mainly for misc skills
	PLAYER_TYPE_COUNT
};

extern const std::unordered_map<std::string, int> plTypeEnumStringToId;
extern const std::unordered_map<int, std::string> plTypeEnumIdToString;

enum SkillType
{
	SKILL_GENERIC = 0, // see above
	SKILL_MELEE,
	SKILL_RANGED,
	SKILL_DEFENSIVE,
	SKILL_MAGIC,
	SKILL_UTILITY,
	SKILL_TYPE_COUNT
};

extern const std::unordered_map<std::string, int> skillTypeEnumStringToId;
extern const std::unordered_map<int, std::string> skillTypeEnumIdToString;

enum SkillSpecial // don't make hundreds of skill types, instead associate additional property with certain skills
{
	SKSPC_NONE = 0,
	SKSPC_BLASTER,
	SKSPC_SHIELD,
	SKSPC_ELEMENTAL,
	SKSPC_SELF,
	SKSPC_MAGIC_EXCLUSIVE,
	SKSPC_MEDITATION,
	SKSPC_RACE_SKILL
};

extern const std::unordered_map<std::string, int> skillSpecialEnumStringToId;
extern const std::unordered_map<int, std::string> skillSpecialEnumIdToString;

enum Alignment
{
	ALIGNMENT_ANY = 0,
	ALIGNMENT_NEUTRAL,
	ALIGNMENT_LIGHT, // mm7 and merge
	ALIGNMENT_DARK, // mm7 and merge
};

extern const std::unordered_map<std::string, int> alignmentStringToId;
extern const std::unordered_map<int, std::string> alignmentIdToString;

enum CharacterStrengthIndicator
{
	AVERAGE_LEVEL = 0,
	CHARACTER_GENERATED_LEVEL
};

enum SpellType
{
	ANY = 0,
	DAMAGE_SINGLE_TARGET,
	DAMAGE_MULTI_TARGET,
	DEBUFF,
	DECURSE,
	BUFF_MELEE,
	BUFF_RANGED,
	BUFF_PROTECTION,
	BUFF_UTILITY_QOL,
	HEALING_SINGLE,
	HEALING_GROUP,
	RACIAL,
	SPELL_TYPE_MISC
};

void setFieldSizes_6();
void setFieldSizes_7();
void setFieldSizes_8();

// GAME ENUMS
// decided to use dynamically set ints - reason: I don't like million ifs due to using templates
// type safety will be okayish, because I intend to only use PlayerStructAccessor and the like to actually use the "enums",
// and since all accesses will be in one place, it's easy to add checks for invalid values
// could be better (static checking), but like I said I don't like template verbosity

extern int
STAT_MIGHT,
STAT_INTELLECT,
STAT_PERSONALITY,
STAT_ENDURANCE,
STAT_ACCURACY,
STAT_SPEED,
STAT_LUCK,
STAT_HIT_POINTS,
STAT_SPELL_POINTS,
STAT_ARMOR_CLASS,
STAT_FIRE_RESISTANCE,
STAT_ELEC_RESISTANCE,
STAT_COLD_RESISTANCE,
STAT_POISON_RESISTANCE,
STAT_LEVEL,
STAT_MELEE_ATTACK,
STAT_MELEE_DAMAGE_BASE,
STAT_MELEE_DAMAGE_MIN,
STAT_MELEE_DAMAGE_MAX,
STAT_RANGED_ATTACK,
STAT_RANGED_DAMAGE_BASE,
STAT_RANGED_DAMAGE_MIN,
STAT_RANGED_DAMAGE_MAX,
STAT_MAGIC_RESISTANCE,
STAT_AIR_RESISTANCE,
STAT_WATER_RESISTANCE,
STAT_EARTH_RESISTANCE,
STAT_MIND_RESISTANCE,
STAT_BODY_RESISTANCE,
STAT_ALCHEMY,
STAT_STEALING,
STAT_DISARM_TRAPS,
STAT_IDENTIFY_ITEM,
STAT_IDENTIFY_MONSTER,
STAT_ARMSMASTER,
STAT_DODGING,
STAT_UNARMED,
STAT_SPIRIT_RESISTANCE,
STAT_FIRE_MAGIC,
STAT_AIR_MAGIC,
STAT_WATER_MAGIC,
STAT_EARTH_MAGIC,
STAT_SPIRIT_MAGIC,
STAT_MIND_MAGIC,
STAT_BODY_MAGIC,
STAT_LIGHT_MAGIC,
STAT_DARK_MAGIC,
STAT_MEDITATION,
STAT_BOW,
STAT_SHIELD,
STAT_LEARNING,
STAT_DARK_ELF,
STAT_VAMPIRE,
STAT_DRAGON;
// MY ADDITIONS
extern int
STAT_LIGHT_RESISTANCE,
STAT_DARK_RESISTANCE,
STAT_RANGED_ATTACK_BONUS,
STAT_RANGED_DAMAGE_BONUS,
STAT_MELEE_ATTACK_BONUS,
STAT_MELEE_DAMAGE_BONUS,
STAT_HIT_POINTS_BONUS,
STAT_SPELL_POINTS_BONUS,
STAT_AGE;

// ~~MY ADDITIONS~~

extern void makeEnumStats_6();
extern void makeEnumStats_7();
extern void makeEnumStats_8();
extern void makeEnums();

extern std::vector<int> STATS_PRIMARY;
extern std::vector<int> STATS_RESISTANCES;
extern std::vector<int> STATS_MELEE_RANGED;
extern std::vector<int> STATS_MM67_BONUSES;
extern std::vector<int> STATS_SKILLS;
extern std::vector<int> STATS_OTHER;
extern std::vector<int> STATS_ALL;

extern int
DMG_PHYS,
DMG_MAGIC,
DMG_FIRE,
DMG_ELEC,
DMG_COLD,
DMG_POISON,
DMG_ENERGY,
DMG_AIR,
DMG_WATER,
DMG_EARTH,
DMG_SPIRIT,
DMG_MIND,
DMG_BODY,
DMG_LIGHT,
DMG_DARK,
DMG_DRAGON;

extern void makeEnumDamage_6();
extern void makeEnumDamage_7();
extern void makeEnumDamage_8();

extern std::vector<int> DAMAGE_ALL_TYPES;

inline void checkStatValidity(int stat);
inline void checkDamageTypeValidity(int dmg);