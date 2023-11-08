#pragma once
#include "main.h"
#include "Enum_const.h"

class PlayerSkill;

class PlayerSpell
{
public:
	int id, powerWithinSchool; // power from 1 to 11 (from novice to gm ranked by mana cost)
	std::string name, shortName, description;
	std::array<int, 5> manaCostByMastery, damageAddByMastery, recoveryDelayByMastery;
	std::array<double, 5> averageDamagePerSkillByMastery; // TODO
	std::array<std::string, 5> rankDescriptions;
	std::vector<int> damageTypes; // TODO: enum/map
	PlayerSkill* schoolSkill;
	Mastery minimumMasteryToLearn;
	std::vector<SpellType> types; // TODO

	PlayerSpell();
};

