#include "pch.h"
#include "main.h"
#include "PlayerItem.h"
#include "Generator.h"
#include "ItemStructAccessor.h"

PlayerItem::PlayerItem() : number(INVALID_ID), power(1), cost(1), isArtifact(false), image(nullptr), inventoryWidth(1), inventoryHeight(1)
{
	
}

void PlayerItem::loadAndConvertBitmap(const wxString& name)
{

}

std::string PlayerItem::getItemTypeName() const
{
    int type = itemAccessor->forItemTxtIndexDo(id, [](auto itemTxt) { return itemTxt->equipStat; }) + 1;
    if (type == 0)
    {
        wxLogError("Invalid item equip stat 0");
        return "invalid";
    }
    return ENUM_TO_STRING_ITEM_SLOT.at(type);
}

std::string PlayerItem::getSkillString() const
{
    if (skill)
    {
        return skill->name;
    }
    else
    {
        return "None";
    }
}

std::string PlayerItem::getStatsString() const
{
    static const wxString formatArmor = "AC: +%d", formatWeapon = "%dd%d + %d";
    PlayerItemModifierData d = getModifierData();
    const std::array<int, 10> armors{ ITEM_TYPE_ARMOR, ITEM_TYPE_SHIELD, ITEM_TYPE_GAUNTLETS, ITEM_TYPE_BELT, ITEM_TYPE_CLOAK, ITEM_TYPE_BOOTS, ITEM_TYPE_RING };
    if (false)
    {
        // TODO: is this the right AC calculation?
        return wxString::Format(formatArmor, d.mod1DiceCount + d.mod1DiceSides + d.mod2).ToStdString();
    }
    else
    {
        const std::array<int, 7> weaponTypes{ ITEM_TYPE_SWORD, ITEM_TYPE_AXE, ITEM_TYPE_BOW, ITEM_TYPE_CLUB, ITEM_TYPE_DAGGER, ITEM_TYPE_SPEAR, ITEM_TYPE_STAFF };
        bool found = false;
        for (int t : weaponTypes)
        {
            if (itemTypeActual == t)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            return wxString::Format(formatWeapon, d.mod1DiceCount, d.mod1DiceSides, d.mod2).ToStdString();
        }
    }
}

std::string PlayerItem::getEnchantmentsString() const
{
    return std::string();
}

PlayerItemModifierData PlayerItem::getModifierData() const
{
    PlayerItemModifierData d;
    itemAccessor->forItemTxtIndexDo(id, [&](AnyItemsTxtItemStruct auto* entry) -> int
        {
            d.mod1DiceCount = entry->mod1DiceCount;
            d.mod1DiceSides = entry->mod1DiceSides;
            d.mod2 = entry->mod2;
        }
    );
    return d;
}