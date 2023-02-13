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

class PlayerStructAccessor;
extern PlayerStructAccessor* playerAccessor;

// convenience class for accessing player properties without barrage of ifs scattered all around the code due to three game versions
// not included in player structs because I'd have to duplicate most code three times, and idk if that wouldn't break the POD status
// I require
// having all accesses in one place simplifies preconditions checking and error handling
// for now they display all errors directly for ease of development, later on I'll make them quieter ("There has been a problem about last operation." + 
// "Check message window for details") or convert to exceptions
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

	// common stats
	virtual int getHp() = 0;
	virtual void setHp(int value) = 0;
	virtual int getSp() = 0;
	virtual void setSp(int value) = 0;

	virtual ~PlayerStructAccessor();

	// FIELD SIZES
	// only those sizes that are used in the ui???
	
	struct FieldSizes
	{
		static constexpr int
			experience = -8,
			condition = -8,
			primaryStatistic = -2,
			armorClassBonus = -2,
			acBonus = -2,
			level = -2,
			ageBonus = -2,
			resistance = -2,
			recoveryDelay = -2,
			skillPoints = -4,
			hp = -4,
			birthYear = -4,
			meleeDamageBonus = -1,
			meleeAttackBonus = -1,
			meleeDamageBonus = -1,
			rangedAttackBonus = -1,
			rangedDamageBonus = -1,
			fullHPBonus = -1,
			fullSPBonus = -1;

		// THESE BELOW ARE DEFINED IN CPP FILE
		// doesn't matter that they're not constexpr because I don't know game version until dll is loaded
		// could have done conditional compilation and produce dll for each game, but I chose the other approach
		static int biography; // 0/0/256, set in dllApi.cpp
		static int skill; // 1/-2/-2
	};
	static FieldSizes FIELD_SIZES;
};

// ENTER CONFIRMS TEMPLATE FOR INTELLISENSE
template<typename Player>
class TemplatedPlayerStructAccessor : public PlayerStructAccessor
{
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
		boundsCheck(value, FIELD_SIZES.acBonus);
		getPlayers()[getPlayerIndex()]->armorClassBonus = value;
	}

	int getFullHpBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->fullHPBonus;
	}


	void setFullHpBonus(int value) override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		boundsCheck(value, FIELD_SIZES.fullHPBonus);
		getPlayers()[getPlayerIndex()]->fullHPBonus = value;
	}


	int getFullSpBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->fullSPBonus;
	}


	void setFullSpBonus(int value) override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		boundsCheck(value, FIELD_SIZES.fullSPBonus);
		getPlayers()[getPlayerIndex()]->fullSPBonus = value;
	}


	int getMeleeAttackBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->meleeAttackBonus;
	}


	void setMeleeAttackBonus(int value) override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		boundsCheck(value, FIELD_SIZES.meleeAttackBonus);
		getPlayers()[getPlayerIndex()]->meleeAttackBonus = value;
	}


	int getRangedAttackBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->rangedAttackBonus;
	}


	void setRangedAttackBonus(int value) override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		boundsCheck(value, FIELD_SIZES.rangedAttackBonus);
		getPlayers()[getPlayerIndex()]->rangedAttackBonus = value;
	}


	int getMeleeDamageBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->meleeDamageBonus;
	}


	void setMeleeDamageBonus(int value) override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		boundsCheck(value, FIELD_SIZES.meleeDamageBonus);
		getPlayers()[getPlayerIndex()]->meleeDamageBonus = value;
	}


	int getRangedDamageBonus() override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		return getPlayers()[getPlayerIndex()]->rangedDamageBonus;
	}


	void setRangedDamageBonus(int value) override
	{
		static_assert(SAME(Player, mm6::Player) || SAME(Player, mm7::Player));
		boundsCheck(value, FIELD_SIZES.rangedDamageBonus);
		getPlayers()[getPlayerIndex()]->rangedDamageBonus = value;
	}


	int getStatBase(int stat) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		// PRIMARY
		if (stat == STAT_MIGHT)
		{
			return pl->mightBase;
		}
		else if (stat == STAT_PERSONALITY)
		{
			return pl->personalityBase;
		}
		else if (stat == STAT_INTELLECT)
		{
			return pl->intellectBase;
		}
		else if (stat == STAT_ENDURANCE)
		{
			return pl->enduranceBase;
		}
		else if (stat == STAT_SPEED)
		{
			return pl->speedBase;
		}
		else if (stat == STAT_ACCURACY)
		{
			return pl->accuracyBase;
		}
		else if (stat == STAT_PERSONALITY)
		{
			return pl->luckBase;
		}
		// OTHER
		else if (stat == STAT_ARMOR_CLASS)
		{
			typedef int(__thiscall *getArmorClassPtr)(void*);
			return reinterpret_cast<getArmorClassPtr>(mmv(0x482700, 0x48E687, 0x48DAF2))(pl);
		}
		else
		{
			static_assert(false); // TODO
		}
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

public:
	int getHp() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setHp(int value) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	int getSp() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void setSp(int value) override
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