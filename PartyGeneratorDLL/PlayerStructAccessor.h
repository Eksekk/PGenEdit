#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "Generator.h"
#include "Player.h"

extern const bool MALE, FEMALE;

extern const int PLAYER_ALL, PLAYER_ACTIVE, PLAYER_RANDOM;
extern Generator* generator;

// convenience class for accessing player properties without barrage of ifs scattered all around the code due to three game versions
class PlayerStructAccessor
{
	int currentPlayer = 0;
	PlayerStructAccessor& operator[](int index)
	{
		wxASSERT_MSG(index < CURRENT_PARTY_SIZE || index == PLAYER_ALL || index == PLAYER_ACTIVE || index == PLAYER_RANDOM, wxString::Format("Invalid player index (%d) passed to PlayerStructAccessor.operator[]", index));
		currentPlayer = index;
		return *this;
	}
	PlayerStructAccessor& operator[](void* player)
	{
		bool found = false;
		for (int i = 0; i < CURRENT_PARTY_SIZE; ++i)
		{
			if ((uint32_t)player == (uint32_t)generator->players[i])
			{
				found = true;
				currentPlayer = i;
				break;
			}
		}
		wxASSERT_MSG(found, wxString::Format("Invalid player pointer (%X) passed to PlayerStructAccessor.operator[]", (uint32_t)player));
		return *this;
	}

	virtual int16_t& extraAc() = 0;
	virtual int8_t& extraMaxHp() = 0;
	virtual int8_t& extraMaxSp() = 0;
	virtual int8_t& extraMeleeAttack() = 0;
	virtual int8_t& extraRangedAttack() = 0;
	virtual int8_t& extraMeleeDamage() = 0;
	virtual int8_t& extraRangedDamage() = 0;

	virtual int getStatBase(int stat) = 0;
	virtual void setStatBase(int stat, int value) = 0;

	virtual int getStatBonus(int stat) = 0;
	virtual void setStatBonus(int stat, int value) = 0;

	//virtual int& getValue(); // INSTEAD OF GET/SET

	virtual void updatePlayerPointers(const std::vector<uint32_t>& ptrs) = 0;

	virtual ~PlayerStructAccessor();
};

// ENTER CONFIRMS TEMPLATE FOR INTELLISENSE
template<typename Player>
class TemplatedPlayerStructAccessor : public PlayerStructAccessor
{

};