#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "Utility.h" // BaseBonus

extern const bool MALE, FEMALE;

extern const int PLAYER_ACTIVE, PLAYER_RANDOM;
extern void** players;

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
	void* playerOverride; // mainly for testing - if it's not null, will always be used instead of index
public:
	inline void setPlayerOverride(void* ptr);
	inline void clearPlayerOverride();

	PlayerStructAccessor();

	// because indexes are used until they are changed, passing PLAYER_RANDOM to forPlayer() will make every call use random player
	// this function simply randomizes player index if it's PLAYER_RANDOM, so each call will affect random, but same player (across each call)
	void unrandomizeRandomPlayer();
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
	[[nodiscard]] virtual BaseBonus getStatBaseBonus(int stat);

	[[nodiscard]] virtual int getSkillPoints() = 0;
	virtual void setSkillPoints(int value) = 0;
	[[nodiscard]] virtual int getSpentSkillPoints() = 0;
	[[nodiscard]] virtual int getSpentSkillPointsForGivenSkills(const std::vector<PlayerSkillValue>& skillsAndValues);

	[[nodiscard]] virtual int64_t getExperience() = 0;
	[[nodiscard]] virtual int64_t getMinimumExperienceForLevel(int level);
	/// affectLevel = true reduces level to maximum possible if value is reduced
	virtual void setExperience(int64_t value, bool affectLevel = true) = 0;

	[[nodiscard]] static int getMinimumLevelForExperience(int64_t experience);

	[[nodiscard]] virtual int getLevel() = 0;
	[[nodiscard]] virtual int getTrainableLevel();
	/// affectExperience = true increases experience to minimum possible if level is increased
	virtual void setLevel(int value, bool affectExperience = true) = 0;

	[[nodiscard]] virtual std::string getName() = 0;
	[[nodiscard]] virtual int getNameMaxUsableLength() = 0;

	[[nodiscard]] virtual std::string getBiography() = 0;
	[[nodiscard]] virtual int getBiographyMaxUsableLength() = 0;

	virtual void setName(const std::string& name) = 0;
	virtual void setBiography(const std::string& biography) = 0;

	enum ClassConstraint
	{
		CLASS_CONSTRAINT_NONE = 0,
		CLASS_CONSTRAINT_CURRENT_CLASS,
		CLASS_CONSTRAINT_ANY_PROMOTION_CLASS
	};
	struct SkillOptions
	{
		bool affectSkillpoints, allowNegativeSkillpoints, affectGold, allowNegativeGold;
		ClassConstraint classConstraint;
		std::vector<SkillCategory> batchSetAffectWhichSkillCategories; // only affects setting multiple skills at once

		SkillOptions() : affectSkillpoints(false), allowNegativeSkillpoints(false), affectGold(false), allowNegativeGold(false),
			classConstraint(CLASS_CONSTRAINT_NONE), batchSetAffectWhichSkillCategories({ SKILLCAT_WEAPON, SKILLCAT_ARMOR, SKILLCAT_MAGIC, SKILLCAT_MISC }) {}
	};

	[[nodiscard]] virtual std::vector<PlayerSkillValue> getSkills() = 0;
	[[nodiscard]] virtual SkillValue getSkill(int skillId) = 0;
	[[nodiscard]] virtual SkillValue getSkill(PlayerSkill* skill) = 0;
	virtual bool setSkills(const std::vector<PlayerSkillValue>& values, const SkillOptions& options = SkillOptions()) = 0;
	virtual bool setSkill(PlayerSkill* skill, SkillValue value, const SkillOptions& options = SkillOptions()) = 0;
	virtual bool setSkill(int skillId, SkillValue value, const SkillOptions& options = SkillOptions()) = 0;
	[[nodiscard]] virtual Mastery getSkillMaxMastery(PlayerSkill* skill, const SkillOptions& options = SkillOptions()) = 0;
	[[nodiscard]] virtual std::unordered_map<PlayerSkill*, Mastery> getSkillMaxMasteries(const std::vector<PlayerSkill*>& skills, const SkillOptions& options = SkillOptions()) = 0;
	virtual void applyClassConstraints(const SkillOptions& options) = 0;

	// common stats
	// TODO get full/current/bonus
	[[nodiscard]] virtual int getHp();
	[[nodiscard]] virtual void setHp(int value);
	[[nodiscard]] virtual int getSp();
	[[nodiscard]] virtual void setSp(int value);

	[[nodiscard]] virtual int getClass() = 0;
	[[nodiscard]] virtual PlayerClass* getClassPtr() = 0;

	[[nodiscard]] virtual std::vector<wxString> getPlayerNames() = 0;
	[[nodiscard]] virtual wxString getNameOrDefault(int overridePlayerIndex) = 0;

	[[nodiscard]] virtual int getSkillBonus(PlayerSkill* skill) = 0;
	[[nodiscard]] virtual int getSkillBonus(int skillId) = 0;

	[[nodiscard]] virtual bool isBlackPotionUsed(int statId) = 0;
	[[nodiscard]] virtual void setBlackPotionUsed(int statId, bool used) = 0;

	[[nodiscard]] virtual int getConditionEffectOnStat(int statId) = 0;
	[[nodiscard]] virtual int getResistanceSpellEffect(int resId) = 0;
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
	Player** getPlayers();
	Player* getPlayerToAffect();

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

public:
	TemplatedPlayerStructAccessor();
	virtual ~TemplatedPlayerStructAccessor() noexcept;

	// C++ limitation, no static initializers for template classes (almost sure)
	static void _initMaps();;

	int getStatBase(int stat) override;

	void setStatBase(int stat, int value) override;

	int getStatBonus(int stat) override;

	void setStatBonus(int stat, int value) override;

	int getSkillPoints() override;

	void setSkillPoints(int value) override;

	int getSpentSkillPoints() override;

	int getNameMaxUsableLength() override;

	int getBiographyMaxUsableLength() override;

	std::vector<PlayerSkillValue> getSkills() override;

private:
	// returns false if skill points requirements cannot be met, otherwise subtracts cost and returns true (need to set skillpoints manually at the end!)
	bool trySubtractSkillpoints(SkillValue newSkillValue, SkillValue oldSkillValue, bool affectSkillpoints, bool allowNegativeSkillpoints, int& sp);

	// like before, but for gold
	bool trySubtractGold(PlayerSkill* skill, SkillValue newSkillValue, SkillValue oldSkillValue, bool affectGold, bool allowNegativeGold, int& gold);
public:

	// this function and two below return true if all skills could be set (due to affectSkillpoints parameter)
	bool setSkills(const std::vector<PlayerSkillValue>& values, const SkillOptions& options = SkillOptions()) override;

	bool setSkill(PlayerSkill* skill, SkillValue value, const SkillOptions& options = SkillOptions()) override;

	bool setSkill(int skillId, SkillValue value, const SkillOptions& options = SkillOptions()) override;

	int64_t getExperience() override;

	void setExperience(int64_t value, bool affectLevel = true) override;

	int getLevel() override;

	void setLevel(int value, bool affectExperience = true) override;

	std::string getName() override;

	std::string getBiography() override;

	void setName(const std::string& name) override;

	void setBiography(const std::string& biography) override;

	SkillValue getSkill(int skillId) override;

	SkillValue getSkill(PlayerSkill* skill) override;

	int getClass() override;

	PlayerClass* getClassPtr() override;

	std::vector<wxString> getPlayerNames() override;

	wxString getNameOrDefault(int overridePlayerIndex) override;

	virtual Mastery getSkillMaxMastery(PlayerSkill* skill, const SkillOptions& options) override;

	virtual std::unordered_map<PlayerSkill*, Mastery> getSkillMaxMasteries(const std::vector<PlayerSkill*>& skills, const SkillOptions& options) override;

	void applyClassConstraints(const SkillOptions& options);

	// Inherited via PlayerStructAccessor
	virtual int getSkillBonus(PlayerSkill* skill) override;

	virtual int getSkillBonus(int skillId) override;

	bool isBlackPotionUsed(int statId) override;

	void setBlackPotionUsed(int statId, bool used) override;

	// Inherited via PlayerStructAccessor
	virtual int getConditionEffectOnStat(int statId) override;

	int getResistanceSpellEffect(int resId) override;
};

using PlayerStructAccessor_6 = TemplatedPlayerStructAccessor<mm6::Player>;
using PlayerStructAccessor_7 = TemplatedPlayerStructAccessor<mm7::Player>;
using PlayerStructAccessor_8 = TemplatedPlayerStructAccessor<mm8::Player>;