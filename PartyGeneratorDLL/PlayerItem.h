#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "Enum_const.h"
class PlayerItem
{
	// TODO: handle possibly resetting artifact found bits (custom behavior required for Merge)
	int number;
	std::string name;
	PlayerSkill skill;
	ItemType type;
	double power;
	bool isArtifact;
	std::vector<double> affinityByClass;
	std::vector<double> affinityByPlayerType;
};

