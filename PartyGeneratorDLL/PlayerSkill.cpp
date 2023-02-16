#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "GameData.h"

extern const int INVALID_ID;

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
	if (skill.isZero())
	{
		return 0;
	}
	int result = skill.level;
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