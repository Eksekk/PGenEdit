#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "GameData.h"
#include "Utility.h"

extern const int INVALID_ID;

const std::unordered_map<std::string, int> skillTypeEnumStringToId = { {"melee", SKILL_MELEE}, {"ranged", SKILL_RANGED }, {"defensive", SKILL_DEFENSIVE},
	{"magic", SKILL_MAGIC}, {"utility", SKILL_UTILITY} };

const std::unordered_map<std::string, int> skillSpecialEnumStringToId = { {"blaster", SKSPC_BLASTER}, {"meditation", SKSPC_MEDITATION}, {"elemental", SKSPC_ELEMENTAL},
	{"self", SKSPC_SELF}, {"magicExclusive", SKSPC_MAGIC_EXCLUSIVE}, {"shield", SKSPC_SHIELD}, {"raceSkill", SKSPC_RACE_SKILL} };

const std::unordered_map<std::string, int> skillCategoryEnumStringToId = { { "weapon", SKILLCAT_WEAPON}, { "armor", SKILLCAT_ARMOR}, { "magic", SKILLCAT_MAGIC}, {"misc", SKILLCAT_MISC} };

const std::unordered_map<int, std::string> skillTypeEnumIdToString = invertMap(skillTypeEnumStringToId);
const std::unordered_map<int, std::string> skillSpecialEnumIdToString = invertMap(skillSpecialEnumStringToId);
const std::unordered_map<int, std::string> skillCategoryEnumIdToString = invertMap(skillCategoryEnumStringToId);

bool SkillValue::operator==(const SkillValue& other) const
{
	// treat novice (1) and none (0) as equal
	bool masteriesEqual = (!mastery && other.mastery == 1) || (mastery == 1 && !other.mastery) || mastery == other.mastery;
	return (level == other.level && masteriesEqual) && (isZero() == other.isZero());
}
bool SkillValue::operator!=(const SkillValue& other) const
{
	return !operator==(other);
}

bool SkillValue::isZero() const
{
	return level == 0;
}

std::string SkillValue::toString() const
{
	return "{" + std::to_string(level) + ", " + std::to_string(mastery) + "}";
}

SkillValue::operator std::string() const
{
	return toString();
}
SkillValue::operator wxString() const
{
	return toString();
}

wxString& operator<<(wxString& str, const SkillValue& val)
{
	return str << val.toString();
}

SkillValue splitSkill(int skill)
{
	if (skill == 0)
	{
		return SkillValue{ 0, 0 };
	}
	int mask = (1 << SKILL_BITS) - 1;
	int lev = skill & mask;
	if (SKILL_COMBINE_MODE == BIT_PER_MASTERY)
	{
		for (int i = MAX_MASTERY; i > MASTERY_NOVICE; --i)
		{
			if (skill & (1 << MASTERY_BITS[i]))
			{
				return SkillValue{ lev, i };
			}
		}
		return SkillValue{ lev, lev == 0 ? 0 : 1 };
	}
	else if (SKILL_COMBINE_MODE == PACKED)
	{
		return SkillValue{ lev, lev == 0 ? 0 : (skill >> SKILL_BITS) + 1 };
	}
	else
	{
		throw std::runtime_error("Invalid skill combining mode!");
	}
}

int joinSkill(SkillValue skill)
{
	if (skill.isZero())
	{
		return 0;
	}
	int result = skill.level;
	if (SKILL_COMBINE_MODE == BIT_PER_MASTERY)
	{
		return result | (skill.mastery > MASTERY_NOVICE ? (1 << MASTERY_BITS[skill.mastery]) : 0);
	}
	else if (SKILL_COMBINE_MODE == PACKED)
	{
		return result | (std::max(skill.mastery - 1, 0) << SKILL_BITS);
	}
	else
	{
		throw std::runtime_error("Invalid skill combining mode!");
	}
}

[[nodiscard]] int skillpointsSpentForSkill(SkillValue sv)
{
	return std::max(0, sv.level * (sv.level + 1) / 2 - 1);
}

int MAX_SKILL_LEVEL = 0;
void setMaxSkillLevel()
{
	MAX_SKILL_LEVEL = (1 << SKILL_BITS) - 1;
}

int PlayerSkill::getFullTrainCostForMastery(Mastery m)
{
	int cost = 0;
	for (int i = 0; i < (int)m; ++i)
	{
		cost += trainCost[i];
	}
	return cost;
}

int PlayerSkill::getFullTrainCostForMastery(SkillValue sv)
{
	return getFullTrainCostForMastery((Mastery)sv.mastery);
}

int PlayerSkill::getFullTrainCostForMastery(int m)
{
	wxASSERT(m >= 0 && m <= MAX_MASTERY);
	return getFullTrainCostForMastery((Mastery)m);
}

PlayerSkill::PlayerSkill()
{
	id = INVALID_ID;
	for (int i = 0; i < PLAYER_TYPE_COUNT; ++i)
	{
		affinityByPlayerType.emplace(i, 1);
	}
	doNotGenerate = false;
	special = SKSPC_NONE;
	category = SKILLCAT_WEAPON;
	memset(trainCost.data(), 0, trainCost.size() * sizeof(std::decay_t<decltype(trainCost[0])>));
}