#pragma once
#include "main.h"

extern int MAX_PLAYERS; // auto
extern int CURRENT_PARTY_SIZE; // in mm8
extern bool IS_ELEMENTAL_MOD; // changes some game structures, different parsing needed
extern bool IS_MERGE; // ditto, todo: merge versions !!!!! structs.Player.Attrs support

const int INVENTORY_WIDTH_PLAYER = 14, INVENTORY_HEIGHT_PLAYER = 9;

extern int NUM_CLASSES;

enum SkillCombineMode
{
	BIT_PER_MASTERY, // first x bits mean skill, then each bit after indicates next mastery (if it's set); mm7+
	PACKED // first x bits mean skill, then next two bits mean mastery (00 novice or none, 01 expert, 10 master, 11 (potentially) GM); mm6
};

enum Mastery
{
	MASTERY_NONE = 0,
	MASTERY_NOVICE = 1,
	MASTERY_EXPERT = 2,
	MASTERY_MASTER = 3,
	MASTERY_GM = 4,
	MASTERY_GRAND_MASTER = 4,
};

enum StartingSkills6
{
	START_SKILL_NOT_AVAILABLE = 0,
	START_SKILL_GIVEN_ON_START_6 = 1,
	START_SKILL_CAN_CHOOSE_6 = 2,
	START_SKILL_CAN_LEARN = 3,
};

enum StartingSkills78
{
    START_SKILL_CANNOT_CHOOSE = 0,
    START_SKILL_CAN_CHOOSE_78 = 1,
    START_SKILL_GIVEN_ON_START_78 = 2,
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

// callbacks that allow to do additional processing after generated code runs (for example, to add custom values)
void callbackStatsInitialize();
void callbackSkillsInitialize();
void callbackDamageInitialize();
void callbackItemTypeInitialize();
void callbackItemSlotInitialize();
void callbackPlayerBuffInitialize();
void callbackPartyBuffInitialize();
void callbackMonsterBitsInitialize();
void callbackMonsterBuffInitialize();
void callbackMonsterBonusInitialize();
void callbackMonsterKindInitialize();
void callbackHouseTypeInitialize();
void callbackHouseScreensInitialize();
void callbackFacetBitsInitialize();
void callbackFaceAnimationInitialize();
void callbackConditionInitialize();
void callbackChestBitsInitialize();
void callbackAIStateInitialize();
void callbackSpellsInitialize();

enum class CallbackCheckResult
{
	VALID, // value is valid
	INVALID, // value is invalid
	NO_CHANGE // depends on default processing, whether value is valid or not
};

// callbacks that allow additional processing while checking if certain value is valid for current game version
CallbackCheckResult callbackCheckStatsValidity(int64_t stat);
CallbackCheckResult callbackCheckSkillsValidity(int64_t skill);
CallbackCheckResult callbackCheckDamageValidity(int64_t dmg);
CallbackCheckResult callbackCheckItemTypeValidity(int64_t type);
CallbackCheckResult callbackCheckItemSlotValidity(int64_t slot);
CallbackCheckResult callbackCheckPlayerBuffValidity(int64_t buff);
CallbackCheckResult callbackCheckPartyBuffValidity(int64_t buff);
CallbackCheckResult callbackCheckMonsterBitsValidity(int64_t bits);
CallbackCheckResult callbackCheckMonsterBuffValidity(int64_t buff);
CallbackCheckResult callbackCheckMonsterBonusValidity(int64_t bonus);
CallbackCheckResult callbackCheckMonsterKindValidity(int64_t kind);
CallbackCheckResult callbackCheckHouseTypeValidity(int64_t type);
CallbackCheckResult callbackCheckHouseScreensValidity(int64_t screen);
CallbackCheckResult callbackCheckFacetBitsValidity(int64_t bits);
CallbackCheckResult callbackCheckFaceAnimationValidity(int64_t anim);
CallbackCheckResult callbackCheckConditionValidity(int64_t cond);
CallbackCheckResult callbackCheckChestBitsValidity(int64_t bits);
CallbackCheckResult callbackCheckAIStateValidity(int64_t state);
CallbackCheckResult callbackCheckSpellsValidity(int64_t spell);

using CheckValueCallback = CallbackCheckResult(*)(int64_t);
bool checkValidValue(const std::vector<int64_t>& values, uint64_t value, CheckValueCallback callback);


// MY ADDITIONS
extern int64_t
STAT_LIGHT_RESISTANCE,
STAT_DARK_RESISTANCE,
STAT_RANGED_ATTACK_BONUS,
STAT_RANGED_DAMAGE_BONUS,
STAT_MELEE_ATTACK_BONUS,
STAT_MELEE_DAMAGE_BONUS,
STAT_HIT_POINTS_BONUS,
STAT_SPELL_POINTS_BONUS,
STAT_AGE;


extern std::vector<int64_t> STATS_PRIMARY;
extern std::vector<int64_t> STATS_RESISTANCES;
extern std::vector<int64_t> STATS_MELEE_RANGED;
extern std::vector<int64_t> STATS_SKILLS;
extern std::vector<int64_t> STATS_MM67_BONUSES;
extern std::vector<int64_t> STATS_OTHER;

// ~~MY ADDITIONS~~

// THIS CODE IS AUTOMATICALLY GENERATED, unless marked otherwise

#include "constDefinitionsAutoGenerated.h"