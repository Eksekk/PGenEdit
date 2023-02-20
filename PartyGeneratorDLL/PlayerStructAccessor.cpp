#include "pch.h"
#include "main.h"
#include "PlayerStructAccessor.h"
#include "LowLevel.h"

const bool MALE = true, FEMALE = false; // TODO: check
const int PLAYER_ACTIVE = 6, PLAYER_RANDOM = 7;

PlayerStructAccessor* playerAccessor = nullptr;
//PlayerStructAccessor::FieldSizes PlayerStructAccessor::FIELD_SIZES;
int PlayerStructAccessor::FieldSizes::biography = 0; // 0/0/256, set in dllApi.cpp
int PlayerStructAccessor::FieldSizes::skill = -2; // 1/-2/-2
int PlayerStructAccessor::FieldSizes::name = 15;

void setFieldSizes_6()
{
	PlayerStructAccessor::FieldSizes::skill = 1;
}
void setFieldSizes_7()
{

}
void setFieldSizes_8()
{
	PlayerStructAccessor::FieldSizes::biography = 255; // exact size unknown, according to Grayface
	PlayerStructAccessor::FieldSizes::name = 31;
}


PlayerStructAccessor* PlayerStructAccessor::forPlayer(int index)
{
	wxASSERT_MSG(index < CURRENT_PARTY_SIZE || index == PLAYER_ACTIVE || index == PLAYER_RANDOM, wxString::Format("Invalid player index (%d) passed to PlayerStructAccessor.operator[]", index));
	playerIndex = index;
	return this;
}

PlayerStructAccessor* PlayerStructAccessor::forPlayer(void* player)
{
	bool found = false;
	for (int i = 0; i < CURRENT_PARTY_SIZE; ++i)
	{
		if ((uint32_t)player == (uint32_t)generator->players[i])
		{
			found = true;
			playerIndex = i;
			break;
		}
	}
	wxASSERT_MSG(found, wxString::Format("Invalid player pointer (%X) passed to PlayerStructAccessor.operator[]", (uint32_t)player));
	return this;
}

void PlayerStructAccessor::setStatBaseBonus(int stat, const BaseBonus& value)
{
	setStatBase(stat, value.base);
	setStatBonus(stat, value.bonus);
}

BaseBonus PlayerStructAccessor::getStatBaseBonus(int stat)
{
	BaseBonus bb;
	bb.base = getStatBase(stat);
	bb.bonus = getStatBonus(stat);
	return bb;
}

int PlayerStructAccessor::spentPerSkill(SkillValue sv)
{
	return sv.level * (sv.level + 1) / 2 - 1;
}

int PlayerStructAccessor::getSpentSkillPointsForGivenSkills(const std::vector<PlayerSkillValue>& skillsAndValues)
{
	int result = 0;
	for (auto& [skillPtr, value] : skillsAndValues)
	{
		result += spentPerSkill(value);
	}
	return result;
}

int64_t PlayerStructAccessor::getMinimumExperienceForLevel(int level)
{
	return (int64_t)level * (level - 1) * 500;
}

int PlayerStructAccessor::getMinimumLevelForExperience(int64_t experience)
{
	// formula is 500 * (level - 1) * level
	// so for level 10 it would require 500 * 9 * 10 = 45000
	
	int64_t levelsMultiplied = experience / 500;
	// level^2 + level = levelsMultiplied
	int64_t delta = 1 + 4 * levelsMultiplied;
	if (delta >= 0)
	{
		int64_t solution = (-1 + std::sqrt(delta)) / 2 + 1;
		return solution;
	}
	return 0;
}

int PlayerStructAccessor::getTrainableLevel()
{
	return getMinimumLevelForExperience(getExperience());
}

PlayerStructAccessor::~PlayerStructAccessor() noexcept {}

int PlayerStructAccessor::getPlayerIndex()
{
	static std::mt19937 gen(std::random_device{}());
	if (playerIndex == PLAYER_RANDOM)
	{
		return std::uniform_int_distribution(0, CURRENT_PARTY_SIZE - 1)(gen);
	}
	else if (playerIndex == PLAYER_ACTIVE)
	{
		int index = std::max(0, (int32_t)dword(mmv(0x4D50E8, 0x507A6C, 0x519350)) - 1);
		return index;
	}
	else
	{
		wxASSERT_MSG(playerIndex < CURRENT_PARTY_SIZE, wxString::Format("Invalid player index %d", playerIndex));
		return std::clamp(playerIndex, 0, CURRENT_PARTY_SIZE - 1);
	}
}

int PlayerStructAccessor::getHp()
{
	return getStatBase(STAT_HIT_POINTS);
}

void PlayerStructAccessor::setHp(int value)
{
	setStatBase(STAT_HIT_POINTS, value);
}

int PlayerStructAccessor::getSp()
{
	return getStatBase(STAT_SPELL_POINTS);
}

void PlayerStructAccessor::setSp(int value)
{
	setStatBase(STAT_SPELL_POINTS, value);
}

template class TemplatedPlayerStructAccessor<mm6::Player>;
template class TemplatedPlayerStructAccessor<mm7::Player>;
template class TemplatedPlayerStructAccessor<mm8::Player>;