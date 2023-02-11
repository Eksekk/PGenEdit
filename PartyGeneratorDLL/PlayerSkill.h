#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"

struct SkillValue
{
	int level, mastery;

	bool operator==(const SkillValue& other);
};

SkillValue splitSkill(int skill);
int joinSkill(SkillValue skill);

class PlayerSkill;
struct PlayerSkillValue
{
	PlayerSkill* skill;
	SkillValue value;
};

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
