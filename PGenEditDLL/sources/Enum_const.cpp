#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "Utility.h"
#include "PlayerStructAccessor.h"

extern const int INVALID_ID;
extern int MMVER;

int MAX_PLAYERS = 0;

bool IS_ELEMENTAL_MOD = false;
bool IS_MERGE = false;

int CURRENT_PARTY_SIZE = 0;

Mastery MAX_MASTERY = Mastery::MASTERY_GM; // 3 in mm6, 4 in mm7+
SkillCombineMode SKILL_COMBINE_MODE = BIT_PER_MASTERY;
int SKILL_BITS = 6;
std::array<int, 5> MASTERY_BITS = {-1, -1, 6, 7, 8};

const double MINIMUM_AFFINITY = 0.0;
const double MAXIMUM_AFFINITY = 1.0;

int NUM_CLASSES = 30;

const std::unordered_map<std::string, int> plTypeEnumStringToId = { {"caster", PLAYER_CASTER}, {"melee", PLAYER_MELEE}, {"defensive", PLAYER_DEFENSIVE}
	, {"utility", PLAYER_UTILITY}, {"ranged", PLAYER_RANGED} };
const std::unordered_map<std::string, int> alignmentStringToId = { {"neutral", ALIGNMENT_NEUTRAL}, {"light", ALIGNMENT_LIGHT}, {"dark", ALIGNMENT_DARK}, {"any", ALIGNMENT_ANY} };


const std::unordered_map<int, std::string> plTypeEnumIdToString = invertMap(plTypeEnumStringToId);
const std::unordered_map<int, std::string> alignmentIdToString = invertMap(alignmentStringToId);

namespace consts
{
	int64_t
		STAT_LIGHT_RESISTANCE = INVALID_ID,
		STAT_DARK_RESISTANCE = INVALID_ID,
		STAT_RANGED_ATTACK_BONUS = INVALID_ID,
		STAT_RANGED_DAMAGE_BONUS = INVALID_ID,
		STAT_MELEE_ATTACK_BONUS = INVALID_ID,
		STAT_MELEE_DAMAGE_BONUS = INVALID_ID,
		STAT_HIT_POINTS_BONUS = INVALID_ID,
		STAT_SPELL_POINTS_BONUS = INVALID_ID,
		STAT_AGE = INVALID_ID;

	std::vector<int64_t> STATS_PRIMARY;
	std::vector<int64_t> STATS_RESISTANCES;
	std::vector<int64_t> STATS_MELEE_RANGED;
	std::vector<int64_t> STATS_SKILLS;
	std::vector<int64_t> STATS_MM67_BONUSES;
	std::vector<int64_t> STATS_OTHER;

	namespace detail
	{
		void makeEnums()
		{
			typedef void(*Func)();
			Func stats = mmv(makeEnumStats_6, makeEnumStats_7, makeEnumStats_8), skills = mmv(makeEnumSkills_6, makeEnumSkills_7, makeEnumSkills_8),
				damage = mmv(makeEnumDamage_6, makeEnumDamage_7, makeEnumDamage_8),
				itemSlot = mmv(makeEnumItemSlot_6, makeEnumItemSlot_7, makeEnumItemSlot_8), partyBuff = mmv(makeEnumPartyBuff_6, makeEnumPartyBuff_7, makeEnumPartyBuff_8),
				monsterBits = mmv(makeEnumMonsterBits_6, makeEnumMonsterBits_7, makeEnumMonsterBits_8), monsterBuff = mmv(makeEnumMonsterBuff_6, makeEnumMonsterBuff_7, makeEnumMonsterBuff_8),
				monsterBonus = mmv(makeEnumMonsterBonus_6, makeEnumMonsterBonus_7, makeEnumMonsterBonus_8), monsterKind = mmv(makeEnumMonsterKind_6, makeEnumMonsterKind_7, makeEnumMonsterKind_8),
				itemType = mmv(makeEnumItemType_6, makeEnumItemType_7, makeEnumItemType_8), houseType = mmv(makeEnumHouseType_6, makeEnumHouseType_7, makeEnumHouseType_8),
				houseScreens = mmv(makeEnumHouseScreens_6, makeEnumHouseScreens_7, makeEnumHouseScreens_8), facetBits = mmv(makeEnumFacetBits_6, makeEnumFacetBits_7, makeEnumFacetBits_8),
				faceAnimation = mmv(makeEnumFaceAnimation_6, makeEnumFaceAnimation_7, makeEnumFaceAnimation_8), condition = mmv(makeEnumCondition_6, makeEnumCondition_7, makeEnumCondition_8),
				chestBits = mmv(makeEnumChestBits_6, makeEnumChestBits_7, makeEnumChestBits_8), aistate = mmv(makeEnumAIState_6, makeEnumAIState_7, makeEnumAIState_8),
				spells = mmv(makeEnumSpells_6, makeEnumSpells_7, makeEnumSpells_8);

			stats();
			//callbackStatsInitialize();
			skills();
			//callbackSkillsInitialize();
			damage();
			//callbackDamageInitialize();
			itemSlot();
			//callbackItemSlotInitialize();
			partyBuff();
			//callbackPartyBuffInitialize();
			monsterBits();
			//callbackMonsterBitsInitialize();
			monsterBuff();
			//callbackMonsterBuffInitialize();
			monsterBonus();
			//callbackMonsterBonusInitialize();
			monsterKind();
			//callbackMonsterKindInitialize();
			itemType();
			//callbackItemTypeInitialize();
			houseType();
			//callbackHouseTypeInitialize();
			houseScreens();
			//callbackHouseScreensInitialize();
			facetBits();
			//callbackFacetBitsInitialize();
			faceAnimation();
			//callbackFaceAnimationInitialize();
			condition();
			//callbackConditionInitialize();
			chestBits();
			//callbackChestBitsInitialize();
			aistate();
			//callbackAIStateInitialize();
			spells();
			//callbackSpellsInitialize();
		}

		// GAME ENUMS

		int nextFreeCustomId()
		{
			static int id = 100;
			return id++;
		}

		void callbackStatsInitialize()
		{
			if (MMVER == 6)
			{
				STAT_RANGED_ATTACK_BONUS = nextFreeCustomId();
				STAT_RANGED_DAMAGE_BONUS = nextFreeCustomId();
				STAT_MELEE_ATTACK_BONUS = nextFreeCustomId();
				STAT_MELEE_DAMAGE_BONUS = nextFreeCustomId();
				STAT_HIT_POINTS_BONUS = nextFreeCustomId();
				STAT_SPELL_POINTS_BONUS = nextFreeCustomId();
				STAT_AGE = nextFreeCustomId();

				STATS_RESISTANCES.insert(STATS_RESISTANCES.end(), { STAT_FIRE_RESISTANCE, STAT_COLD_RESISTANCE, STAT_ELEC_RESISTANCE, STAT_POISON_RESISTANCE, STAT_MAGIC_RESISTANCE });
			}
			else if (MMVER == 7)
			{
				STAT_LIGHT_RESISTANCE = nextFreeCustomId();
				STAT_DARK_RESISTANCE = nextFreeCustomId();
				STAT_RANGED_ATTACK_BONUS = nextFreeCustomId();
				STAT_RANGED_DAMAGE_BONUS = nextFreeCustomId();
				STAT_MELEE_ATTACK_BONUS = nextFreeCustomId();
				STAT_MELEE_DAMAGE_BONUS = nextFreeCustomId();
				STAT_HIT_POINTS_BONUS = nextFreeCustomId();
				STAT_SPELL_POINTS_BONUS = nextFreeCustomId();
				STAT_AGE = nextFreeCustomId();
			}
			else if (MMVER == 8)
			{
				STAT_LIGHT_RESISTANCE = nextFreeCustomId();
				STAT_DARK_RESISTANCE = nextFreeCustomId();
				STAT_AGE = nextFreeCustomId();
				STATS_SKILLS.insert(STATS_SKILLS.end(), { STAT_DRAGON, STAT_DARK_ELF, STAT_VAMPIRE });
			}
			else
			{
				wxLogFatalError("Unknown MM version (%d)!", MMVER);
			}

			// STATS
			{
				if (MMVER < 8)
				{
					STATS_MM67_BONUSES.insert(STATS_MM67_BONUSES.begin(), { STAT_MELEE_ATTACK_BONUS, STAT_MELEE_DAMAGE_BONUS, STAT_RANGED_ATTACK_BONUS,
						STAT_RANGED_DAMAGE_BONUS, STAT_HIT_POINTS_BONUS, STAT_SPELL_POINTS_BONUS });
				}
				if (MMVER > 6)
				{
					STATS_RESISTANCES.insert(STATS_RESISTANCES.end(), { STAT_FIRE_RESISTANCE, STAT_WATER_RESISTANCE, STAT_AIR_RESISTANCE, STAT_EARTH_RESISTANCE, STAT_BODY_RESISTANCE,
						STAT_SPIRIT_RESISTANCE, STAT_MIND_RESISTANCE, STAT_LIGHT_RESISTANCE, STAT_DARK_RESISTANCE });

					STATS_SKILLS.insert(STATS_SKILLS.end(), { STAT_FIRE_MAGIC, STAT_AIR_MAGIC, STAT_EARTH_MAGIC, STAT_WATER_MAGIC, STAT_BODY_MAGIC, STAT_SPIRIT_MAGIC,
						STAT_MIND_MAGIC, STAT_LIGHT_MAGIC, STAT_DARK_MAGIC, STAT_BOW, STAT_MEDITATION, STAT_SHIELD, STAT_LEARNING, STAT_ARMSMASTER, STAT_ALCHEMY, STAT_DODGING,
						STAT_UNARMED, STAT_IDENTIFY_ITEM, STAT_IDENTIFY_MONSTER, STAT_STEALING });
				}
				STATS_PRIMARY.insert(STATS_PRIMARY.end(), { STAT_MIGHT, STAT_INTELLECT, STAT_PERSONALITY, STAT_ENDURANCE, STAT_ACCURACY, STAT_SPEED, STAT_LUCK });

				STATS_MELEE_RANGED.insert(STATS_MELEE_RANGED.end(), { STAT_MELEE_ATTACK, STAT_MELEE_DAMAGE_BASE, STAT_MELEE_DAMAGE_MAX, STAT_MELEE_DAMAGE_MIN,
					STAT_RANGED_ATTACK, STAT_RANGED_DAMAGE_BASE, STAT_RANGED_DAMAGE_MAX, STAT_RANGED_DAMAGE_MIN });

				STATS_OTHER.insert(STATS_OTHER.end(), { STAT_HIT_POINTS, STAT_SPELL_POINTS, STAT_ARMOR_CLASS, STAT_LEVEL, STAT_AGE });

				// all
				STATS_ALL.insert(STATS_ALL.end(), STATS_PRIMARY.begin(), STATS_PRIMARY.end());
				STATS_ALL.insert(STATS_ALL.end(), STATS_MELEE_RANGED.begin(), STATS_MELEE_RANGED.end());
				STATS_ALL.insert(STATS_ALL.end(), STATS_RESISTANCES.begin(), STATS_RESISTANCES.end());
				STATS_ALL.insert(STATS_ALL.end(), STATS_SKILLS.begin(), STATS_SKILLS.end());
				STATS_ALL.insert(STATS_ALL.end(), STATS_OTHER.begin(), STATS_OTHER.end());
				STATS_ALL.insert(STATS_ALL.end(), STATS_MM67_BONUSES.begin(), STATS_MM67_BONUSES.end());
			}
		}

		void callbackSkillsInitialize()
		{
		}

		void callbackDamageInitialize()
		{
			if (MMVER == 6)
			{
				
			}
		}

		void callbackItemTypeInitialize()
		{
		}

		void callbackItemSlotInitialize()
		{
		}

		void callbackPlayerBuffInitialize()
		{
		}

		void callbackPartyBuffInitialize()
		{
		}

		void callbackMonsterBitsInitialize()
		{
		}

		void callbackMonsterBuffInitialize()
		{
		}

		void callbackMonsterBonusInitialize()
		{
		}

		void callbackMonsterKindInitialize()
		{
		}

		void callbackHouseTypeInitialize()
		{
		}

		void callbackHouseScreensInitialize()
		{
		}

		void callbackFacetBitsInitialize()
		{
		}

		void callbackFaceAnimationInitialize()
		{
		}

		void callbackConditionInitialize()
		{
		}

		void callbackChestBitsInitialize()
		{
		}

		void callbackAIStateInitialize()
		{
		}

		void callbackSpellsInitialize()
		{
		}

		CallbackCheckResult callbackCheckStatsValidity(int64_t stat)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckSkillsValidity(int64_t skill)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckDamageValidity(int64_t dmg)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckItemTypeValidity(int64_t type)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckItemSlotValidity(int64_t slot)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckPlayerBuffValidity(int64_t buff)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckPartyBuffValidity(int64_t buff)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckMonsterBitsValidity(int64_t bits)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckMonsterBuffValidity(int64_t buff)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckMonsterBonusValidity(int64_t bonus)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckMonsterKindValidity(int64_t kind)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckHouseTypeValidity(int64_t type)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckHouseScreensValidity(int64_t screen)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckFacetBitsValidity(int64_t bits)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckFaceAnimationValidity(int64_t anim)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckConditionValidity(int64_t cond)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckChestBitsValidity(int64_t bits)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckAIStateValidity(int64_t state)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		CallbackCheckResult callbackCheckSpellsValidity(int64_t spell)
		{
			return CallbackCheckResult::NO_CHANGE;
		}

		bool checkValidValue(const std::vector<int64_t>&values, uint64_t value, CheckValueCallback callback)
		{
			CallbackCheckResult result = callback(value);
			if (result == CallbackCheckResult::NO_CHANGE)
			{
				return std::find(values.begin(), values.end(), value) != values.end();
			}
			return result == CallbackCheckResult::VALID;
		}
	}
}