#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "Enum_const.h"
#include "ItemGenerationData.h"
#include "ItemStructAccessor.h"

class PlayerItem // holds generic item data, one entry per each item id
{
public:
    // these are plucked from game data directly
    union
    {
        int id;
        int number;
    };
    std::unique_ptr<wxBitmap> image;
    // width in cells is ceil(width / 45), same for height
    int inventoryWidth, inventoryHeight;
    std::string name;
    std::string pictureName;
    dword_t value;
    int itemTypeActual;
    PlayerSkill* skill;
    bool isArtifact;

	// from JSON
	ItemType itemTypeGenerator;
	double power; // relative
	int cost; // how much should this reduce amount/quality of remaining items to generate
	std::vector<double> affinityByClass;
	std::vector<double> affinityByPlayerType;

	PlayerItem();

	void loadAndConvertBitmap(const wxString& name);
	std::string getItemTypeName() const;
	std::string getItemModString() const; // weapons have "damage: 2d5+4", armor has "AC: +15" etc.
	template<typename Function>
	auto forItemTxtDo(Function&& func) const
	{
		return itemAccessor->forItemTxtIndexDo(id, std::forward<Function>(func));
	}
};

