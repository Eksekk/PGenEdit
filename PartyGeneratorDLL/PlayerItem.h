#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "Enum_const.h"
#include "ItemGenerationData.h"
class PlayerItem
{
	int number;
	std::string name;
	PlayerSkill skill;
	ItemType type;
	double power; // relative
	int cost; // how much should this reduce amount/quality of remaining items to generate
	bool isArtifact;
	std::vector<double> affinityByClass;
	std::vector<double> affinityByPlayerType;

	static int getItemCount(ItemGenerationData* genData);
	static int getSpecificItemCount(ItemGenerationData* genData);
	static int getItemTypeCount(ItemGenerationData* genData);
	static int getItemTypeValue(ItemGenerationData* genData);
};

