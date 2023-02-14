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

	virtual ~PlayerStructAccessor() noexcept;

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

	// return void if function returns void, otherwise vector of results
	// trailing return type required?
	// invoke_result_t needs to have Args expanded
	// rvalue reference is automatically added by invoke_result_t
	template<typename Function, typename... Args>
	auto forAllPlayersApply(Function f, Args&&... args) ->
	std::conditional_t<
		std::is_same_v<std::invoke_result_t<Function, Args...>, void>,
		void,
		std::vector<std::invoke_result_t<Function, Args...>>
	>
	{
		int old = playerIndex;
		using ReturnType = std::invoke_result_t<Function, Args...>;
		if constexpr (SAME(ReturnType, void))
		{
			for (int i = 0; i < CURRENT_PARTY_SIZE; ++i)
			{
				(void)operator[](i);
				f(std::forward<Args>(args)...);
			}
			playerIndex = old;
		}
		else
		{
			//static_assert(std::is_copy_assignable_v<ReturnType>, "Return type is not copy assignable");
			std::vector<ReturnType> ret;
			ret.reserve(CURRENT_PARTY_SIZE);
			for (int i = 0; i < CURRENT_PARTY_SIZE; ++i)
			{
				(void)operator[](i);
				ret.push_back(f(std::forward<Args>(args)...));
			}
			playerIndex = old;
			return ret;
		}
	}
};

// ENTER CONFIRMS TEMPLATE FOR INTELLISENSE
template<typename Player>
class TemplatedPlayerStructAccessor : public PlayerStructAccessor
{
	virtual ~TemplatedPlayerStructAccessor() noexcept;

	inline Player** getPlayers()
	{
		return (Player**)generator->players;
	}

	template<typename FieldType>
	struct BaseOrBonusPointer
	{
		FieldType Player::* base;
		FieldType Player::* bonus;
	};

	template<typename FieldType>
	static std::unordered_map<int, BaseOrBonusPointer<FieldType>> baseBonusFieldToStatMap;
	template<typename FieldType>
	static std::unordered_map<int, FieldType Player::*> singleTypeFieldToStatMap;

	static class InitMaps // IF PROBLEMS ARISE, MOVE INITIALIZATION TO FUNCTION AND CALL WHEN NEEDED
	{
		InitMaps()
		{
			// primary stats
			baseBonusFieldToStatMap<int16_t>[STAT_MIGHT] = { &Player::mightBase, &Player::mightBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_INTELLECT] = { &Player::intellectBase, &Player::intellectBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_PERSONALITY] = { &Player::personalityBase, &Player::personalityBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_ENDURANCE] = { &Player::enduranceBase, &Player::enduranceBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_ACCURACY] = { &Player::accuracyBase, &Player::accuracyBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_SPEED] = { &Player::speedBase, &Player::speedBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_LUCK] = { &Player::luckBase, &Player::luckBonus };

			// resistances
			if constexpr (SAME(Player, mm6::Player))
			{
				// TODO
				//fieldToStatMap<int16_t>[STAT_FIRE_RESISTANCE] = Player::
			}
			else
			{
				baseBonusFieldToStatMap<int16_t>[STAT_FIRE_RESISTANCE] = { &Player::fireResistanceBase, &Player::fireResistanceBonus };
				baseBonusFieldToStatMap<int16_t>[STAT_WATER_RESISTANCE] = { &Player::waterResistanceBase, &Player::waterResistanceBonus };
				baseBonusFieldToStatMap<int16_t>[STAT_AIR_RESISTANCE] = { &Player::airResistanceBase, &Player::airResistanceBonus };
				baseBonusFieldToStatMap<int16_t>[STAT_EARTH_RESISTANCE] = { &Player::earthResistanceBase, &Player::earthResistanceBonus };

				baseBonusFieldToStatMap<int16_t>[STAT_MIND_RESISTANCE] = { &Player::mindResistanceBase, &Player::mindResistanceBonus };
				baseBonusFieldToStatMap<int16_t>[STAT_SPIRIT_RESISTANCE] = { &Player::spiritResistanceBase, &Player::spiritResistanceBonus };
				baseBonusFieldToStatMap<int16_t>[STAT_BODY_RESISTANCE] = { &Player::bodyResistanceBase, &Player::bodyResistanceBonus };

				baseBonusFieldToStatMap<int16_t>[STAT_LIGHT_RESISTANCE] = { &Player::lightResistanceBase, &Player::lightResistanceBonus };
				baseBonusFieldToStatMap<int16_t>[STAT_DARK_RESISTANCE] = { &Player::darkResistanceBase, &Player::darkResistanceBonus };
			}

			

			// mm6/7 extras
			if constexpr (SAME(Player, mm6::Player) || SAME(Player, mm7::Player))
			{
				singleTypeFieldToStatMap<int8_t>[STAT_MELEE_ATTACK_BONUS] = &Player::meleeAttackBonus;
				singleTypeFieldToStatMap<int8_t>[STAT_MELEE_DAMAGE_BONUS] = &Player::meleeDamageBonus;
				singleTypeFieldToStatMap<int8_t>[STAT_RANGED_ATTACK_BONUS] = &Player::meleeAttackBonus;
				singleTypeFieldToStatMap<int8_t>[STAT_RANGED_DAMAGE_BONUS] = &Player::meleeDamageBonus;
			}

			// hp, sp
			if constexpr (SAME(Player, mm8::Player))
			{
				// TODO
			}
			else
			{
				singleTypeFieldToStatMap<int32_t>[STAT_HIT_POINTS] = &Player::HP;
				singleTypeFieldToStatMap<int32_t>[STAT_SPELL_POINTS] = &Player::SP;

				singleTypeFieldToStatMap<int8_t>[STAT_MELEE_ATTACK_BONUS] = &Player::meleeAttackBonus;
				singleTypeFieldToStatMap<int8_t>[STAT_MELEE_DAMAGE_BONUS] = &Player::meleeDamageBonus;
				singleTypeFieldToStatMap<int8_t>[STAT_RANGED_ATTACK_BONUS] = &Player::rangedAttackBonus;
				singleTypeFieldToStatMap<int8_t>[STAT_RANGED_DAMAGE_BONUS] = &Player::rangedDamageBonus;
			}
		}
	} _initMaps;

	int getAcBonus() override
	{
		// works!!!
		if (false)
		{
			forAllPlayersApply(std::function<void(int)>(std::bind(&TemplatedPlayerStructAccessor<Player>::setAcBonus, this, std::placeholders::_1)), 5);
			auto x = forAllPlayersApply(std::function<int()>(std::bind(&TemplatedPlayerStructAccessor<Player>::getAcBonus, this)));
		}
		
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
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		// PRIMARY
		// TODO why these getBaseAccuracy() etc. methods exist?
		if (existsInVector(STATS_PRIMARY, stat))
		{
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).base;
			return pl->*field;
		}
		// OTHER
		else if (stat == STAT_ARMOR_CLASS)
		{
			typedef int(__thiscall *getArmorClassPtr)(Player*);
			return reinterpret_cast<getArmorClassPtr>(mmv(0x482700, 0x48E687, 0x48DAF2))(pl);
		}
		else
		{
			//static_assert(false); // TODO
			return 5;
		}
	}

	void setStatBase(int stat, int value) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		if (existsInVector(STATS_PRIMARY, stat))
		{
			boundsCheck(value, boundsByType<int16_t>);
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).base;
			pl->*field = value;
		}
	}

	int getStatBonus(int stat) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		if (existsInVector(STATS_PRIMARY, stat))
		{
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).bonus;
			return pl->*field;
		}
	}

	void setStatBonus(int stat, int value) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		if (existsInVector(STATS_PRIMARY, stat))
		{
			boundsCheck(value, boundsByType<int16_t>);
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).base;
			pl->*field = value;
		}
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

template<typename Player>
TemplatedPlayerStructAccessor<Player>::~TemplatedPlayerStructAccessor() noexcept
{

}

template<typename Player>
template<typename FieldType>
std::unordered_map<int, typename TemplatedPlayerStructAccessor<Player>::template BaseOrBonusPointer<FieldType>> TemplatedPlayerStructAccessor<Player>::baseBonusFieldToStatMap;

template<typename Player>
template<typename FieldType>
std::unordered_map<int, FieldType Player::*> TemplatedPlayerStructAccessor<Player>::singleTypeFieldToStatMap;

//template class TemplatedPlayerStructAccessor<mm6::Player>;
template class TemplatedPlayerStructAccessor<mm7::Player>;
//template class TemplatedPlayerStructAccessor<mm8::Player>;

using PlayerStructAccessor_6 = TemplatedPlayerStructAccessor<mm6::Player>;
using PlayerStructAccessor_7 = TemplatedPlayerStructAccessor<mm7::Player>;
using PlayerStructAccessor_8 = TemplatedPlayerStructAccessor<mm8::Player>;