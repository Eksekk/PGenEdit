#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "Generator.h"
#include "Player.h"
#include "Utility.h"
#include "PlayerSkill.h"

extern const bool MALE, FEMALE;

extern const int PLAYER_ACTIVE, PLAYER_RANDOM;
extern Generator* generator;

// convenience class for accessing player properties without barrage of ifs scattered all around the code due to three game versions
class PlayerStructAccessor
{
protected:
	int playerIndex = 0;
	int getPlayerIndex();
public:
	PlayerStructAccessor& operator[](int index)
	{
		wxASSERT_MSG(index < CURRENT_PARTY_SIZE || index == PLAYER_ACTIVE || index == PLAYER_RANDOM, wxString::Format("Invalid player index (%d) passed to PlayerStructAccessor.operator[]", index));
		playerIndex = index;
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
				playerIndex = i;
				break;
			}
		}
		wxASSERT_MSG(found, wxString::Format("Invalid player pointer (%X) passed to PlayerStructAccessor.operator[]", (uint32_t)player));
		return *this;
	}

	virtual int getAcBonus() = 0;
	virtual void setAcBonus(int value) = 0;
	virtual int getFullHpBonus() = 0;
	virtual void setFullHpBonus(int value) = 0;
	virtual int getFullSpBonus() = 0;
	virtual void setFullSpBonus(int value) = 0;
	virtual int getMeleeAttackBonus() = 0;
	virtual void setMeleeAttackBonus(int value) = 0;
	virtual int getRangedAttackBonus() = 0;
	virtual void setRangedAttackBonus(int value) = 0;
	virtual int getMeleeDamageBonus() = 0;
	virtual void setMeleeDamageBonus(int value) = 0;
	virtual int getRangedDamageBonus() = 0;
	virtual void setRangedDamageBonus(int value) = 0;

	virtual int getStatBase(int stat) = 0;
	virtual void setStatBase(int stat, int value) = 0;

	virtual int getStatBonus(int stat) = 0;
	virtual void setStatBonus(int stat, int value) = 0;

	virtual int getSkillPoints() = 0;
	virtual void setSkillPoints(int value) = 0;
	virtual int getSpentSkillPoints() = 0;

	virtual char* getOrSetName() = 0;
	virtual int getNameMaxLength() = 0;

	virtual char* getOrSetBiography() = 0;
	virtual int getBiographyMaxLength() = 0;

	virtual std::vector<PlayerSkillValue> getSkills() = 0;
	virtual void setSkills(const std::vector<PlayerSkillValue>& values) = 0;
	virtual void setSkill(PlayerSkill* skill, SkillValue value) = 0;
	virtual void setSkill(int skillId, SkillValue value) = 0;

	virtual ~PlayerStructAccessor();
};

// ENTER CONFIRMS TEMPLATE FOR INTELLISENSE
template<typename Player>
class TemplatedPlayerStructAccessor : public PlayerStructAccessor
{
	// visual studio complains "type name is not allowed"
	inline Player** getPlayers()
	{
		return (Player**)generator->players;
	}

	int getAcBonus() override
	{
		return getPlayers()[getPlayerIndex()]->armorClassBonus;
	}


	void setAcBonus(int value) override
	{
		boundsCheck(value, -2);
		getPlayers()[getPlayerIndex()]->armorClassBonus = value;
	}

	int getFullHpBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->fullHPBonus;
	}


	void setFullHpBonus(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getFullSpBonus() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setFullSpBonus(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getMeleeAttackBonus() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setMeleeAttackBonus(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getRangedAttackBonus() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setRangedAttackBonus(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getMeleeDamageBonus() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setMeleeDamageBonus(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getRangedDamageBonus() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setRangedDamageBonus(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getStatBase(int stat) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setStatBase(int stat, int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getStatBonus(int stat) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setStatBonus(int stat, int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getSkillPoints() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setSkillPoints(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getSpentSkillPoints() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	char* getOrSetName() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getNameMaxLength() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	char* getOrSetBiography() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getBiographyMaxLength() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	std::vector<PlayerSkillValue> getSkills() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setSkills(const std::vector<PlayerSkillValue>& values) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setSkill(PlayerSkill* skill, SkillValue value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setSkill(int skillId, SkillValue value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};


//template class TemplatedPlayerStructAccessor<mm6::Player>;
template class TemplatedPlayerStructAccessor<mm7::Player>;
//template class TemplatedPlayerStructAccessor<mm8::Player>;

using PlayerStructAccessor_6 = TemplatedPlayerStructAccessor<mm6::Player>;
using PlayerStructAccessor_7 = TemplatedPlayerStructAccessor<mm7::Player>;
using PlayerStructAccessor_8 = TemplatedPlayerStructAccessor<mm8::Player>;