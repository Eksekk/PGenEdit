#include "pch.h"
#include "PlayerSpell.h"

extern const int INVALID_ID;
PlayerSpell::PlayerSpell() : id(INVALID_ID), powerWithinSchool(1), schoolSkill(nullptr), minimumMasteryToLearn(MASTERY_NOVICE)
{
	for (int i = 0; i < 5; ++i)
	{
		manaCostByMastery[i] = 1;
		damageAddByMastery[i] = 0;
		averageDamagePerSkillByMastery[i] = 0;
	}
}

/*powerWithinSchool; // power from 1 to 11 (from novice to gm ranked by mana cost)
	std::string name, shortName, description;
	std::array<int, 5> manaCostByMastery, damageAddByMastery;
	std::array<double, 5> averageDamagePerSkillByMastery;
	std::vector<int> damageTypes; // TODO: enum/map
	PlayerSkill* schoolSkill;
	Mastery minimumMasteryToLearn;
	std::vector<SpellType> types;*/