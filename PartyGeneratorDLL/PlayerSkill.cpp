#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "GameData.h"

Skill splitSkill(int skill)
{
	int mask = (1 << (SKILL_BITS)) - 1;
	int lev = skill & mask;
	if (SKILL_COMBINE_MODE == BIT_PER_MASTERY)
	{
		for (int i = 3; i >= NOVICE; --i)
		{
			if (skill & (1 << MASTERY_BITS[i]))
			{
				return Skill{ lev, i };
			}
		}
		return Skill{ lev, 0 };
	}
	else if (SKILL_COMBINE_MODE == PACKED)
	{
		return Skill{ lev, skill >> SKILL_BITS };
	}
	else
	{
		throw std::runtime_error("Invalid skill combining mode!");
	}
}

int joinSkill(Skill skill)
{
	int mask = (1 << (SKILL_BITS)) - 1;
	int result = skill.level;
	if (SKILL_COMBINE_MODE == BIT_PER_MASTERY)
	{
		return result | (1 << MASTERY_BITS[skill.mastery]);
	}
	else if (SKILL_COMBINE_MODE == PACKED)
	{
		return result | (skill.mastery << SKILL_BITS);
	}
	else
	{
		throw std::runtime_error("Invalid skill combining mode!");
	}
}