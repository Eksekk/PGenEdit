#pragma once
#include "pch.h"
#include "main.h"
#include <string>
#include <vector>
#include "Enum_const.h"

struct Skill
{
	int level, mastery;
};

Skill splitSkill(int skill);
int joinSkill(Skill skill);

class PlayerSkill
{
public:
	int id;
	std::string name;
	std::vector<SkillType> types;
	SkillSpecial special;
	std::unordered_map<int, Mastery> maxMasteryByClass; // <class, mastery>
	std::unordered_map<int, double> affinityByPlayerType;
	bool doNotGenerate; // for skills like diplomacy in mm7 (yes, it exists ingame)

	PlayerSkill();
};
