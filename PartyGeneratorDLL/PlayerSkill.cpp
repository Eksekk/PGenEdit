#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "GameData.h"

extern const int INVALID_ID;

bool SkillValue::operator==(const SkillValue& other)
{
	return level == other.level && mastery == other.mastery;
}
bool SkillValue::operator!=(const SkillValue& other)
{
	return !operator==(other);
}

SkillValue splitSkill(int skill)
{
	int mask = (1 << SKILL_BITS) - 1;
	int lev = skill & mask;
	if (SKILL_COMBINE_MODE == BIT_PER_MASTERY)
	{
		for (int i = GRAND_MASTER; i > NOVICE; --i)
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
	int result = skill.level;
	if (!result || !skill.mastery)
	{
		return 0;
	}
	if (SKILL_COMBINE_MODE == BIT_PER_MASTERY)
	{
		return result | (skill.mastery > NOVICE ? (1 << MASTERY_BITS[skill.mastery]) : 0);
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

PlayerSkill::PlayerSkill()
{
	id = INVALID_ID;
	for (int i = 0; i < PLAYER_TYPE_COUNT; ++i)
	{
		affinityByPlayerType.emplace(i, 1);
	}
	doNotGenerate = false;
	special = SKSPC_NONE;
}