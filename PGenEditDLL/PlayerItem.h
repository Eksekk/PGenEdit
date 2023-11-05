#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
#include "Enum_const.h"
#include "ItemGenerationData.h"
#include "ItemStructAccessor.h"

struct PlayerItemModifierData
{
    int mod1DiceCount, mod1DiceSides, mod2;
};

struct ItemImageRelatedData
{
    std::string bitmapName;
    int inventoryWidth, inventoryHeight;
    std::unique_ptr<wxBitmap> image; // wxBitmap is refcounted, using unique_ptr, because raw pointer wouldn't call destructor (decrement refcount)
};

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

    std::string getSkillString() const;
    std::string getStatsString() const; // weapons have "damage: 2d5+4", armor has "AC: +15" etc.
    static std::optional<std::string> getEnchantmentsString(const mm7::Item& item);
    PlayerItemModifierData getModifierData() const;
	void loadAndConvertBitmap(const wxString& name);
	std::string getItemTypeName() const;
	template<typename Function>
	auto forItemTxtDo(Function&& func) const
	{
		return itemAccessor->forItemTxtIndexDo(id, std::forward<Function>(func));
    }

    // executes only if item has std bonus
    template<AnyItemStruct Item, typename Function>
    static auto forStdItemTxtDoOptional(const Item& item, const Function&& func)
    {
        return item.bonus
            ? itemAccessor->forStdItemTxtIndexDo(item.bonus - 1, std::forward<Function>(func))
            : decltype(itemAccessor->forStdItemTxtIndexDo(item.bonus - 1, std::forward<Function>(func)))(); // default-constructed instance of return type
    }

    // executes only if item has spc bonus
    template<AnyItemStruct Item, typename Function>
    static auto forSpcItemTxtDoOptional(const Item& item, const Function&& func)
    {
        return item.bonus2
            ? itemAccessor->forSpcItemTxtIndexDo(item.bonus2 - 1, std::forward<Function>(func))
            : decltype(itemAccessor->forSpcItemTxtIndexDo(item.bonus2 - 1, std::forward<Function>(func)))(); // default-constructed instance of return type
    }
};

