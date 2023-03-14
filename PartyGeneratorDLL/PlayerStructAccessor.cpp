#include "pch.h"
#include "main.h"
#include "PlayerStructAccessor.h"
#include "LowLevel.h"
#include "PartyStructAccessor.h"

const bool MALE = true, FEMALE = false; // TODO: check
const int PLAYER_ACTIVE = 6, PLAYER_RANDOM = 7;

template<typename Player>
template<typename FieldType>
std::unordered_map<int, typename TemplatedPlayerStructAccessor<Player>::template BaseOrBonusFieldPointer<FieldType>> TemplatedPlayerStructAccessor<Player>::baseBonusFieldToStatMap;

template<typename Player>
template<typename FieldType>
std::unordered_map<int, FieldType Player::*> TemplatedPlayerStructAccessor<Player>::singleTypeFieldToStatMap;

template<typename Player>
TemplatedPlayerStructAccessor<Player>::~TemplatedPlayerStructAccessor() noexcept
{

}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getSkillBonus(int skillId)
{
	if (MMVER == 6) return 0;
	SkillValue fullValue = splitSkill(callMemoryAddress<int>(mmv(0, 0x48F87A, 0x48EF4F), 1, getPlayerToAffect(), skillId));
	SkillValue baseValue = getSkill(skillId);
	return fullValue.level - baseValue.level;
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getSkillBonus(PlayerSkill* skill)
{
	return getSkillBonus(skill->id);
}

template<typename Player>
Player** TemplatedPlayerStructAccessor<Player>::getPlayers()
{
	return (Player**)players;
}

template<typename Player>
Player* TemplatedPlayerStructAccessor<Player>::getPlayerToAffect()
{
	if (playerOverride)
	{
		return reinterpret_cast<Player*>(playerOverride);
	}
	else
	{
		return getPlayers()[getPlayerIndex()];
	}
}

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::applyClassConstraints(const SkillOptions& options)
{
	std::vector<PlayerSkillValue> skillsToSet;
	std::transform(GameData::skills.begin(), GameData::skills.end(), std::back_inserter(skillsToSet), [this](auto& pair) -> PlayerSkillValue
		{
			return { &pair.second, this->getSkill(&pair.second) }; // gets current skill masteries
		});
	std::vector<PlayerSkill*> skillPtrs;
	std::ranges::transform(skillsToSet, std::back_inserter(skillPtrs), [](PlayerSkillValue& psv) -> PlayerSkill*
		{
			return psv.skill;
		});
	auto masteries = getSkillMaxMasteries(skillPtrs, options);
	for (PlayerSkillValue& psv : skillsToSet)
	{
		psv.value.mastery = std::min(static_cast<Mastery>(psv.value.mastery), masteries.at(psv.skill));
	}
	setSkills(skillsToSet, options);
}

template<typename Player>
std::unordered_map<PlayerSkill*, Mastery>
TemplatedPlayerStructAccessor<Player>::getSkillMaxMasteries(const std::vector<PlayerSkill*>& skills, const SkillOptions& options)
{
	std::unordered_map<PlayerSkill*, Mastery> ret;
	if (options.classConstraint == CLASS_CONSTRAINT_NONE)
	{
		for (const auto skillPtr : skills)
		{
			ret[skillPtr] = MAX_MASTERY;
		}
		return ret;
	}
	else if (options.classConstraint == CLASS_CONSTRAINT_CURRENT_CLASS)
	{
		for (const auto skillPtr : skills)
		{
			ret[skillPtr] = getClassPtr()->maximumSkillMasteries.at(skillPtr->id);
		}
		return ret;
	}
	else //CLASS_CONSTRAINT_ANY_PROMOTION_CLASS
	{
		PlayerClass::TreeOptions opt(false, true, false); // !lower, higher, !equal 
		auto tree = getClassPtr()->getClassTree(opt);
		for (const auto skillPtr : skills)
		{
			for (const auto clsPtr : tree)
			{
				ret[skillPtr] = std::max(ret[skillPtr], clsPtr->maximumSkillMasteries.at(skillPtr->id)); // IMPORTANT: "std::max(ret[skillPtr]", not "std::max(ret.at(skillPtr)"
				// key doesn't exist yet
			}
		}
		return ret;
	}
}

template<typename Player>
Mastery TemplatedPlayerStructAccessor<Player>::getSkillMaxMastery(PlayerSkill* skill, const SkillOptions& options)
{
	if (options.classConstraint == CLASS_CONSTRAINT_NONE)
	{
		return MAX_MASTERY;
	}
	else if (options.classConstraint == CLASS_CONSTRAINT_CURRENT_CLASS)
	{
		return GameData::classes.at(getClass()).maximumSkillMasteries.at(skill->id);
	}
	else //CLASS_CONSTRAINT_ANY_PROMOTION_CLASS
	{
		PlayerClass::TreeOptions opt(false, true, false);
		auto tree = getClassPtr()->getClassTree(opt);
		PlayerClass* max = *(
			std::max_element(tree.begin(), tree.end(), [skill](PlayerClass* const cls1, PlayerClass* const cls2) -> bool
				{
					return cls1->maximumSkillMasteries.at(skill->id) < cls2->maximumSkillMasteries.at(skill->id);
				})
			);
		return max->maximumSkillMasteries.at(skill->id);
	}
}

template<typename Player>
wxString TemplatedPlayerStructAccessor<Player>::getNameOrDefault(int overridePlayerIndex)
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

template<typename Player>
std::vector<wxString>
TemplatedPlayerStructAccessor<Player>::getPlayerNames()
{
	std::vector<wxString> ret;
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		ret.push_back(getNameOrDefault(i));
	}
	return ret;
}

template<typename Player>
PlayerClass* TemplatedPlayerStructAccessor<Player>::getClassPtr()
{
	Player* pl = getPlayerToAffect();
	return &(GameData::classes.at(pl->clas));
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getClass()
{
	Player* pl = getPlayerToAffect();
	return pl->clas;
}

template<typename Player>
SkillValue TemplatedPlayerStructAccessor<Player>::getSkill(PlayerSkill* skill)
{
	Player* pl = getPlayerToAffect();
	return splitSkill(pl->skills.at(skill->id));
}

template<typename Player>
SkillValue TemplatedPlayerStructAccessor<Player>::getSkill(int skillId)
{
	Player* pl = getPlayerToAffect();
	return splitSkill(pl->skills.at(skillId));
}

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setBiography(const std::string& biography)
{
	wxASSERT_MSG(MMVER == 8, "This function is for MM8 only");
	Player* pl = getPlayerToAffect();
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

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setName(const std::string& name)
{
	Player* pl = getPlayerToAffect();
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

template<typename Player>
std::string TemplatedPlayerStructAccessor<Player>::getBiography()
{
	wxASSERT_MSG(MMVER == 8, "This function is for MM8 only");
	Player* pl = getPlayerToAffect();
	if constexpr (SAME(Player, mm8::Player))
	{
		return std::string(pl->biography.data());
	}
	else
	{
		return "";
	}
}

template<typename Player>
std::string TemplatedPlayerStructAccessor<Player>::getName()
{
	Player* pl = getPlayerToAffect();
	return std::string(pl->name.data());
}

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setLevel(int value, bool affectExperience /*= true*/)
{
	int old = getStatBase(STAT_LEVEL);
	setStatBase(STAT_LEVEL, value);
	if (affectExperience && value > old)
	{
		setExperience(std::max(getExperience(), getMinimumExperienceForLevel(value)));
	}
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getLevel()
{
	return getStatBase(STAT_LEVEL);
}

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setExperience(int64_t value, bool affectLevel /*= true*/)
{
	Player* pl = getPlayerToAffect();
	int64_t old = pl->experience;
	pl->experience = value;
	if (affectLevel && value < old)
	{
		pl->levelBase = std::max(1, getMinimumLevelForExperience(value));
	}
}

template<typename Player>
int64_t TemplatedPlayerStructAccessor<Player>::getExperience()
{
	Player* pl = getPlayerToAffect();
	return pl->experience;
}

template<typename Player>
bool TemplatedPlayerStructAccessor<Player>::setSkill(int skillId, SkillValue value, const SkillOptions& options /*= SkillOptions()*/)
{
	return setSkill(&GameData::skills.at(skillId), value, options);
}

template<typename Player>
bool TemplatedPlayerStructAccessor<Player>::setSkill(PlayerSkill* skill, SkillValue value, const SkillOptions& options /*= SkillOptions()*/)
{
	wxASSERT(skill != nullptr);
	if (skill == nullptr)
	{
		return true;
	}

	value.mastery = std::min(value.mastery, (int)getSkillMaxMastery(skill, options));
	if (value.mastery == 0)
	{
		value.level = 0;
	}
	int sp = getSkillPoints();
	if (!trySubtractSkillpoints(value, getSkill(skill), options.affectSkillpoints, options.allowNegativeSkillpoints, sp))
	{
		return false;
	}
	int gold = partyAccessor->getGold();
	if (!trySubtractGold(skill, value, getSkill(skill), options.affectGold, options.allowNegativeGold, gold))
	{
		return false;
	}
	Player* pl = getPlayerToAffect();
	value = value.mastery == MASTERY_NONE ? SkillValue{ 0, 0 } : value; // if user sets mastery to none, unlearn skill
	pl->skills.at(skill->id) = joinSkill(value);
	setSkillPoints(sp);
	partyAccessor->setGold(gold);
	return true;
}

template<typename Player>
bool TemplatedPlayerStructAccessor<Player>::setSkills(const std::vector<PlayerSkillValue>& values, const SkillOptions& options /*= SkillOptions()*/)
{
	Player* pl = getPlayerToAffect();
	int sp = getSkillPoints();
	int gold = partyAccessor->getGold();
	bool ret = true;
	for (auto& [skillPtr, skillValue] : values)
	{
		SkillValue setWhat = skillValue.mastery == MASTERY_NONE ? SkillValue{ 0, 0 } : skillValue;
		setWhat.mastery = std::min(setWhat.mastery, (int)getSkillMaxMastery(skillPtr, options));
		if (setWhat.mastery == 0)
		{
			setWhat.level = 0;
		}
		if (existsInVector(options.batchSetAffectWhichSkillCategories, skillPtr->category))
		{
			int oldGold = gold, oldSp = sp;
			ret = trySubtractSkillpoints(setWhat, getSkill(skillPtr), options.affectSkillpoints, options.allowNegativeSkillpoints, sp)
				&& trySubtractGold(skillPtr, setWhat, getSkill(skillPtr), options.affectGold, options.allowNegativeGold, gold);
			if (!ret)
			{
				sp = oldSp;
				gold = oldGold;
				break;
			}
			pl->skills.at(skillPtr->id) = joinSkill(setWhat);
		}

	}
	setSkillPoints(sp);
	partyAccessor->setGold(gold);
	return ret;
}

template<typename Player>
bool TemplatedPlayerStructAccessor<Player>::trySubtractSkillpoints(SkillValue newSkillValue, SkillValue oldSkillValue, bool affectSkillpoints, bool allowNegativeSkillpoints, int& sp)
{
	if (affectSkillpoints)
	{
		int cost = skillpointsSpentForSkill(newSkillValue) - skillpointsSpentForSkill(oldSkillValue);
		if (cost > sp && !allowNegativeSkillpoints)
		{
			return false;
		}
		sp -= cost;
	}
	return true;
}

template<typename Player>
bool TemplatedPlayerStructAccessor<Player>::trySubtractGold(PlayerSkill* skill, SkillValue newSkillValue, SkillValue oldSkillValue, bool affectGold, bool allowNegativeGold, int& gold)
{
	if (affectGold)
	{
		int cost = skill->trainCost.at(newSkillValue.mastery) - skill->trainCost.at(oldSkillValue.mastery);
		if (cost > gold && !allowNegativeGold)
		{
			return false;
		}
		gold -= cost;
	}
	return true;
}

template<typename Player>
std::vector<PlayerSkillValue>
TemplatedPlayerStructAccessor<Player>::getSkills()
{
	Player* pl = getPlayerToAffect();
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

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getBiographyMaxUsableLength()
{
	return FIELD_SIZES.biography;
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getNameMaxUsableLength()
{
	return FIELD_SIZES.name;
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getSpentSkillPoints()
{
	std::vector<PlayerSkillValue> skills = getSkills();
	int result = 0;
	for (auto& [skillPtr, skillValue] : skills)
	{
		result += std::max(0, skillpointsSpentForSkill(skillValue));
	}
	return result;
}

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setSkillPoints(int value)
{
	// int is i4, but let's add check anyway
	boundsCheck(value, -4);
	getPlayerToAffect()->skillPoints = value;
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getSkillPoints()
{
	return getPlayerToAffect()->skillPoints;
}

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setStatBase(int stat, int value)
{
	checkStatValidity(stat);
	Player* pl = getPlayerToAffect();
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

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getStatBonus(int stat)
{
	checkStatValidity(stat);
	Player* pl = getPlayerToAffect();
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

template<typename Player>
void TemplatedPlayerStructAccessor<Player>::setStatBonus(int stat, int value)
{
	checkStatValidity(stat);
	Player* pl = getPlayerToAffect();
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


template<typename Player>
void TemplatedPlayerStructAccessor<Player>::_initMaps()
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
}

template<typename Player>
int TemplatedPlayerStructAccessor<Player>::getStatBase(int stat)
{
	checkStatValidity(stat);
	Player* pl = getPlayerToAffect();
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
		if ((uint32_t)player == (uint32_t)players[i])
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

int PlayerStructAccessor::getSpentSkillPointsForGivenSkills(const std::vector<PlayerSkillValue>& skillsAndValues)
{
	int result = 0;
	for (auto& [skillPtr, value] : skillsAndValues)
	{
		result += skillpointsSpentForSkill(value);
	}
	return result;
}

int64_t PlayerStructAccessor::getMinimumExperienceForLevel(int level)
{
	return (int64_t)level * ((int64_t)level - 1) * 500;
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

void PlayerStructAccessor::setPlayerOverride(void* ptr)
{
	playerOverride = ptr;
}

void PlayerStructAccessor::clearPlayerOverride()
{
	playerOverride = nullptr;
}

PlayerStructAccessor::PlayerStructAccessor() : playerOverride(nullptr), playerIndex(0)
{

}

void PlayerStructAccessor::unrandomizeRandomPlayer()
{
	static std::mt19937 gen(std::random_device{}());
	static std::array<std::uniform_int_distribution<int>, 5> dists{ std::uniform_int_distribution<int>(0, 0), std::uniform_int_distribution<int>(0, 1),
		std::uniform_int_distribution<int>(0, 2), std::uniform_int_distribution<int>(0, 3), std::uniform_int_distribution<int>(0, 4) };
	if (playerIndex == PLAYER_RANDOM)
	{
		if (CURRENT_PARTY_SIZE < 0 || CURRENT_PARTY_SIZE > 5)
		{
			wxLogError("Invalid current party size (%d)", CURRENT_PARTY_SIZE);
		}
		else
		{
			playerIndex = dists[std::max(0, CURRENT_PARTY_SIZE - 1)](gen);
		}
	}
	else
	{
		wxLogWarning("Random player index expected, but current index is %d", playerIndex);
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