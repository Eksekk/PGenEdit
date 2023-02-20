#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "Generator.h"
#include "Player.h"
#include "Utility.h"
#include "PlayerSkill.h"
#include "GameData.h"
#include "LowLevel.h"

extern const bool MALE, FEMALE;

extern const int PLAYER_ACTIVE, PLAYER_RANDOM;
extern Generator* generator;

class PlayerStructAccessor;
extern PlayerStructAccessor* playerAccessor;
class PlayerClass;

extern void setFieldSizes_6();
extern void setFieldSizes_7();
extern void setFieldSizes_8();

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
	// NOT WORKING - accesses next "instance" of accessor instead of setting player
	/*PlayerStructAccessor& operator[](int index);
	PlayerStructAccessor& operator[](void* player);*/

	// note that these functions set player for all future accesses! I think it's more comfortable this way
	PlayerStructAccessor* forPlayer(int index);
	PlayerStructAccessor* forPlayer(void* player);

	[[nodiscard]] virtual int getStatBase(int stat) = 0;
	virtual void setStatBase(int stat, int value) = 0;

	[[nodiscard]] virtual int getStatBonus(int stat) = 0;
	virtual void setStatBonus(int stat, int value) = 0;

	virtual void setStatBaseBonus(int stat, const BaseBonus& value);
	virtual BaseBonus getStatBaseBonus(int stat);

	[[nodiscard]] static int spentPerSkill(SkillValue sv);

	[[nodiscard]] virtual int getSkillPoints() = 0;
	virtual void setSkillPoints(int value) = 0;
	[[nodiscard]] virtual int getSpentSkillPoints() = 0;
	[[nodiscard]] virtual int getSpentSkillPointsForGivenSkills(const std::vector<PlayerSkillValue>& skillsAndValues);

	virtual int64_t getExperience() = 0;
	virtual int64_t getMinimumExperienceForLevel(int level);
	/// affectLevel = true reduces level to maximum possible if value is reduced
	virtual void setExperience(int64_t value, bool affectLevel = true) = 0;

	[[nodiscard]] static int getMinimumLevelForExperience(int64_t experience);

	[[nodiscard]] virtual int getLevel() = 0;
	[[nodiscard]] virtual int getTrainableLevel();
	/// affectExperience = true increases experience to minimum possible if level is increased
	virtual void setLevel(int value, bool affectExperience = true) = 0;

	[[nodiscard]] virtual std::string getName() = 0;
	[[nodiscard]] virtual int getNameMaxUsableLength() = 0;

	virtual std::string getBiography() = 0;
	virtual int getBiographyMaxUsableLength() = 0;

	virtual void setName(const std::string& name) = 0;
	virtual void setBiography(const std::string& biography) = 0;

	[[nodiscard]] virtual std::vector<PlayerSkillValue> getSkills() = 0;
	[[nodiscard]] virtual SkillValue getSkillValue(int skillId) = 0;
	[[nodiscard]] virtual SkillValue getSkillValue(PlayerSkill* skill) = 0;
	virtual void setSkills(const std::vector<PlayerSkillValue>& values) = 0;
	virtual void setSkill(PlayerSkill* skill, SkillValue value) = 0;
	virtual void setSkill(int skillId, SkillValue value) = 0;

	// common stats
	// TODO get full/current/bonus
	[[nodiscard]] virtual int getHp();
	[[nodiscard]] virtual void setHp(int value);
	[[nodiscard]] virtual int getSp();
	[[nodiscard]] virtual void setSp(int value);

	[[nodiscard]] virtual PlayerClass* getClass() = 0;

	[[nodiscard]] virtual std::vector<wxString> getPlayerNames() = 0;
	[[nodiscard]] virtual wxString getNameOrDefault(int overridePlayerIndex) = 0;
	// LATER
	// virtual void setClass(PlayerClass* clas, bool affectSkills = false, bool affectSpells = false, bool removeInvalidEquippedItems = false,
	//     bool affectAwards = false, bool tryToKeepTierAndAlignment = false) = 0;

	/*
	TODO:
	- hp/sp
	- armor class
	- skill "stats"?
	- items
	- etc.
	*/

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
		static int name; // 16/16/32
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
				(void)forPlayer(i); // switch player
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
				(void)forPlayer(i);
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
	struct BaseOrBonusFieldPointer
	{
		FieldType Player::* base;
		FieldType Player::* bonus;
	};

	template<typename FieldType>
	static std::unordered_map<int, BaseOrBonusFieldPointer<FieldType>> baseBonusFieldToStatMap;
	template<typename FieldType>
	static std::unordered_map<int, FieldType Player::*> singleTypeFieldToStatMap; // either base or bonus, this includes hp/sp because "base" is 4 byte, while bonus 1

	// C++ limitation, no static initializers for template classes (almost sure)
public:
	static void _initMaps()
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
			baseBonusFieldToStatMap<int16_t>[STAT_FIRE_RESISTANCE] = { &Player::fireResistanceBase, &Player::fireResistanceBonus };
			baseBonusFieldToStatMap<int16_t>[STAT_ELEC_RESISTANCE] = { &Player::elecResistanceBase, &Player::elecResistanceBase };
			baseBonusFieldToStatMap<int16_t>[STAT_COLD_RESISTANCE] = { &Player::coldResistanceBase, &Player::coldResistanceBase };
			baseBonusFieldToStatMap<int16_t>[STAT_POISON_RESISTANCE] = { &Player::poisonResistanceBase, &Player::poisonResistanceBase };
			baseBonusFieldToStatMap<int16_t>[STAT_MAGIC_RESISTANCE] = { &Player::magicResistanceBase, &Player::magicResistanceBase };
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

		// hp, sp

		singleTypeFieldToStatMap<int32_t>[STAT_HIT_POINTS] = &Player::HP;
		singleTypeFieldToStatMap<int32_t>[STAT_SPELL_POINTS] = &Player::SP;

		// mm6/7 bonuses
		if constexpr (!SAME(Player, mm8::Player))
		{
			singleTypeFieldToStatMap<int8_t>[STAT_MELEE_ATTACK_BONUS] = &Player::meleeAttackBonus;
			singleTypeFieldToStatMap<int8_t>[STAT_MELEE_DAMAGE_BONUS] = &Player::meleeDamageBonus;
			singleTypeFieldToStatMap<int8_t>[STAT_RANGED_ATTACK_BONUS] = &Player::rangedAttackBonus;
			singleTypeFieldToStatMap<int8_t>[STAT_RANGED_DAMAGE_BONUS] = &Player::rangedDamageBonus;
			singleTypeFieldToStatMap<int8_t>[STAT_HIT_POINTS_BONUS] = &Player::fullHPBonus;
			singleTypeFieldToStatMap<int8_t>[STAT_SPELL_POINTS_BONUS] = &Player::fullSPBonus;
		}

		// other
		baseBonusFieldToStatMap<int16_t>[STAT_LEVEL] = { &Player::levelBase, &Player::levelBonus };
		singleTypeFieldToStatMap<int16_t>[STAT_ARMOR_CLASS] = { &Player::armorClassBonus };

		singleTypeFieldToStatMap<int16_t>[STAT_AGE] = &Player::ageBonus;
	};

	int getStatBase(int stat) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		// TODO why these getBaseAccuracy() etc. methods exist?
		if (existsInVector(STATS_PRIMARY, stat) || existsInVector(STATS_RESISTANCES, stat) || stat == STAT_LEVEL)
		{
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).base;
			return pl->*field;
		}
		// OTHER
		else if (stat == STAT_ARMOR_CLASS)
		{
			return callMemoryAddress<int>(mmv(0x482700, 0x48E687, 0x48DAF2), 1, pl);
		}
		else if (stat == STAT_HIT_POINTS || stat == STAT_SPELL_POINTS)
		{
			auto field = singleTypeFieldToStatMap<int32_t>.at(stat);
			return pl->*field;
		}
		wxASSERT_MSG(false, wxString::Format("Invalid stat %d", stat));
		return 0;
	}

	void setStatBase(int stat, int value) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		if (existsInVector(STATS_PRIMARY, stat) || existsInVector(STATS_RESISTANCES, stat) || stat == STAT_LEVEL)
		{
			boundsCheck(value, boundsByType<int16_t>);
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).base;
			pl->*field = value;
			return;
		}
		else if (stat == STAT_HIT_POINTS || stat == STAT_SPELL_POINTS)
		{
			boundsCheck(value, boundsByType<int32_t>);
			auto field = singleTypeFieldToStatMap<int32_t>.at(stat);
			pl->*field = value;
			return;
		}
		wxASSERT_MSG(false, wxString::Format("Invalid stat %d", stat));
	}

	int getStatBonus(int stat) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		if constexpr (!SAME(Player, mm8::Player))
		{
			if (existsInVector(STATS_MM67_BONUSES, stat))
			{
				auto field = singleTypeFieldToStatMap<int8_t>.at(stat);
				return pl->*field;
			}
		}
		if (existsInVector(STATS_PRIMARY, stat) || existsInVector(STATS_RESISTANCES, stat) || stat == STAT_LEVEL)
		{
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).bonus;
			return pl->*field;
		}
		else if (stat == STAT_ARMOR_CLASS)
		{
			auto field = singleTypeFieldToStatMap<int16_t>.at(STAT_ARMOR_CLASS);
			return pl->*field;
		}
		else if (stat == STAT_HIT_POINTS_BONUS || stat == STAT_SPELL_POINTS_BONUS)
		{
			auto field = singleTypeFieldToStatMap<int8_t>.at(stat);
			return pl->*field;
		}
		wxASSERT_MSG(false, wxString::Format("Invalid stat %d", stat));
		return 0;
	}

	void setStatBonus(int stat, int value) override
	{
		checkStatValidity(stat);
		Player* pl = getPlayers()[getPlayerIndex()];
		if constexpr (!SAME(Player, mm8::Player))
		{
			if (existsInVector(STATS_MM67_BONUSES, stat))
			{
				boundsCheck(value, boundsByType<int8_t>);
				auto field = singleTypeFieldToStatMap<int8_t>.at(stat);
				pl->*field = value;
				return;
			}
		}
		if (existsInVector(STATS_PRIMARY, stat) || existsInVector(STATS_RESISTANCES, stat) || stat == STAT_LEVEL)
		{
			boundsCheck(value, boundsByType<int16_t>);
			auto field = baseBonusFieldToStatMap<int16_t>.at(stat).bonus;
			pl->*field = value;
			return;
		}
		else if (stat == STAT_ARMOR_CLASS)
		{
			boundsCheck(value, boundsByType<int16_t>);
			auto field = singleTypeFieldToStatMap<int16_t>.at(STAT_ARMOR_CLASS);
			pl->*field = value;
			return;
		}
		else if (stat == STAT_HIT_POINTS_BONUS || stat == STAT_SPELL_POINTS_BONUS)
		{
			boundsCheck(value, boundsByType<int8_t>);
			auto field = singleTypeFieldToStatMap<int8_t>.at(stat);
			pl->*field = value;
			return;
		}
		wxASSERT_MSG(false, wxString::Format("Invalid stat %d", stat));
	}

	int getSkillPoints() override
	{
		return getPlayers()[getPlayerIndex()]->skillPoints;
	}

	void setSkillPoints(int value) override
	{
		// int is i4, but let's add check anyway
		boundsCheck(value, -4);
		getPlayers()[getPlayerIndex()]->skillPoints = value;
	}

	int getSpentSkillPoints() override
	{
		std::vector<PlayerSkillValue> skills = getSkills();
		int result = 0;
		for (auto& [skillPtr, skillValue] : skills)
		{
			result += std::max(0, spentPerSkill(skillValue));
		}
		return result;
	}

	int getNameMaxUsableLength() override
	{
		return FIELD_SIZES.name;
	}

	int getBiographyMaxUsableLength() override
	{
		return FIELD_SIZES.biography;
	}

	std::vector<PlayerSkillValue> getSkills() override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		std::vector<PlayerSkillValue> ret;
		ret.reserve(GameData::skills.size());
		for (int i = 0; i < pl->skills.size(); ++i)
		{
			SkillValue val = splitSkill(pl->skills[i]);
			auto itr = GameData::skills.find(i);
			wxASSERT_MSG(itr != GameData::skills.end(), wxString::Format("Skill %d not found in game data", i));
			ret.push_back({ &(itr->second), val });
		}
		return ret;
	}

	void setSkills(const std::vector<PlayerSkillValue>& values) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		for (auto& [skillPtr, skillValue] : values)
		{
			pl->skills.at(skillPtr->id) = joinSkill(skillValue);
		}
	}

	void setSkill(PlayerSkill* skill, SkillValue value) override
	{
		wxASSERT(skill != nullptr);
		if (skill == nullptr)
		{
			return;
		}
		Player* pl = getPlayers()[getPlayerIndex()];
		pl->skills.at(skill->id) = joinSkill(value);
	}

	void setSkill(int skillId, SkillValue value) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		pl->skills.at(skillId) = joinSkill(value);
	}

	int64_t getExperience() override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		return pl->experience;
	}

	void setExperience(int64_t value, bool affectLevel = true) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		int64_t old = pl->experience;
		pl->experience = value;
		if (affectLevel && value < old)
		{
			pl->levelBase = std::max(1, getMinimumLevelForExperience(value));
		}
	}

	int getLevel() override
	{
		return getStatBase(STAT_LEVEL);
	}

	void setLevel(int value, bool affectExperience = true) override
	{
		int old = getStatBase(STAT_LEVEL);
		setStatBase(STAT_LEVEL, value);
		if (affectExperience && value > old)
		{
			setExperience(std::max(getExperience(), getMinimumExperienceForLevel(value)));
		}
	}

	std::string getName() override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		return std::string(pl->name.data());
	}

	std::string getBiography() override
	{
		wxASSERT_MSG(MMVER == 8, "This function is for MM8 only");
		Player* pl = getPlayers()[getPlayerIndex()];
		if constexpr (SAME(Player, mm8::Player))
		{
			return std::string(pl->biography.data());
		}
		else
		{
			return "";
		}
	}

	void setName(const std::string& name) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		size_t max = getNameMaxUsableLength();
		std::string nameToSet = name;
		if (name.size() > max)
		{
			nameToSet = name.substr(0, max);
			wxLogError("Too big name length (%d). Truncated to %d", name.size(), max);
			wxLog::FlushActive();
		}
		memcpy(pl->name.data(), nameToSet.data(), nameToSet.size());
		pl->name[nameToSet.size()] = 0;
	}

	void setBiography(const std::string& biography) override
	{
		wxASSERT_MSG(MMVER == 8, "This function is for MM8 only");
		Player* pl = getPlayers()[getPlayerIndex()];
		if constexpr (SAME(Player, mm8::Player))
		{
			size_t max = getBiographyMaxUsableLength();
			std::string biographyToSet = biography;
			if (biography.size() > max)
			{
				biographyToSet = biographyToSet.substr(0, max);
				wxLogError("Too big biography length (%d). Truncated to %d", biography.size(), max);
				wxLog::FlushActive();
			}
			memcpy(pl->biography.data(), biographyToSet.data(), biographyToSet.size());
			pl->biography[biographyToSet.size()] = 0;
		}
	}

	SkillValue getSkillValue(int skillId) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		return splitSkill(pl->skills.at(skillId));
	}

	SkillValue getSkillValue(PlayerSkill* skill) override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		return splitSkill(pl->skills.at(skill->id));
	}

	PlayerClass* getClass() override
	{
		Player* pl = getPlayers()[getPlayerIndex()];
		return &(GameData::classes.at(pl->clas));
	}

	std::vector<wxString> getPlayerNames() override
	{
		std::vector<wxString> ret;
		for (int i = 0; i < MAX_PLAYERS; ++i)
		{
			ret.push_back(getNameOrDefault(i));
		}
		return ret;
	}

	wxString getNameOrDefault(int overridePlayerIndex) override
	{
		if (overridePlayerIndex == INVALID_ID)
		{
			return getName();
		}
		else if (overridePlayerIndex < CURRENT_PARTY_SIZE)
		{
			int old = playerIndex;
			auto name = forPlayer(overridePlayerIndex)->getName();
			forPlayer(old);
			return name;
		}
		else
		{
			return wxString::Format("Player %d", overridePlayerIndex + 1);
		}
	}

};

template<typename Player>
TemplatedPlayerStructAccessor<Player>::~TemplatedPlayerStructAccessor() noexcept
{

}

template<typename Player>
template<typename FieldType>
std::unordered_map<int, typename TemplatedPlayerStructAccessor<Player>::template BaseOrBonusFieldPointer<FieldType>> TemplatedPlayerStructAccessor<Player>::baseBonusFieldToStatMap;

template<typename Player>
template<typename FieldType>
std::unordered_map<int, FieldType Player::*> TemplatedPlayerStructAccessor<Player>::singleTypeFieldToStatMap;

using PlayerStructAccessor_6 = TemplatedPlayerStructAccessor<mm6::Player>;
using PlayerStructAccessor_7 = TemplatedPlayerStructAccessor<mm7::Player>;
using PlayerStructAccessor_8 = TemplatedPlayerStructAccessor<mm8::Player>;