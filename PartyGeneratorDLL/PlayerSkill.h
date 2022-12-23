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
	SkillType type;
	std::vector<Mastery> maxMasteryByClass;
	std::vector<double> affinityByPlayerType;
};
