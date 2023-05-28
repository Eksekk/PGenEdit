#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "Enum_const.h"
#include "ItemGenerationData.h"

class PlayerItem // holds generic item data, one entry per each item id
{
public:
	int number;
	std::string name;
	PlayerSkill* skill;
	ItemType type;
	double power; // relative
	int cost; // how much should this reduce amount/quality of remaining items to generate
	bool isArtifact;
	std::vector<double> affinityByClass;
	std::vector<double> affinityByPlayerType;
	wxBitmap* image;
	int inventoryWidth, inventoryHeight;

	PlayerItem();

	void loadAndConvertBitmap(const wxString& name);
};
