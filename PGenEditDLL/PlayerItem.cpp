#include "pch.h"
#include "main.h"
#include "PlayerItem.h"
#include "Generator.h"
#include "ItemStructAccessor.h"
#include "Utility.h"

PlayerItem::PlayerItem() : number(INVALID_ID), power(1), cost(1), isArtifact(false), image(nullptr), inventoryWidth(1), inventoryHeight(1),
    itemTypeActual(0), itemTypeGenerator(ItemType::OTHER_EQUIPPABLE), skill(nullptr), value(0)
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
    const std::array<int64_t, 10> armors{ ITEM_TYPE_ARMOR, ITEM_TYPE_SHIELD, ITEM_TYPE_GAUNTLETS, ITEM_TYPE_BELT, ITEM_TYPE_CLOAK, ITEM_TYPE_BOOTS, ITEM_TYPE_RING };
    if (existsInContainer(armors, itemTypeActual))
    {
        // TODO: is this the right AC calculation?
        return wxString::Format(formatArmor, d.mod1DiceCount + d.mod1DiceSides + d.mod2).ToStdString();
    }
    else
    {
        const std::array<int64_t, 7> weaponTypes{ ITEM_TYPE_SWORD, ITEM_TYPE_AXE, ITEM_TYPE_BOW, ITEM_TYPE_CLUB, ITEM_TYPE_DAGGER, ITEM_TYPE_SPEAR, ITEM_TYPE_STAFF };
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
    return "None";
}

std::optional<std::string> PlayerItem::getEnchantmentsString(const mm7::Item& item)
{
    static const wxString stdBonusFormat("%s: +%d");
    if (item.bonus)
    {
        return std::make_optional(std::move(wxString::Format(stdBonusFormat,
            itemAccessor->forStdItemTxtIndexDo(item.bonus - 1, [](AnyStdItemsTxtItemStruct auto* s) { return s->nameAdd; }), item.bonusStrength
        ).ToStdString()));
    }
    else if (item.bonus2)
    {
        return std::make_optional(itemAccessor->forSpcItemTxtIndexDo(item.bonus2 - 1, [](AnySpcItemsTxtItemStruct auto* s) { return s->nameAdd; }));
    }
    else
    {
        return "";
    }
}

PlayerItemModifierData PlayerItem::getModifierData() const
{
    PlayerItemModifierData d;
    itemAccessor->forItemTxtIndexDo(id, [&](AnyItemsTxtItemStruct auto* entry)
        {
            d.mod1DiceCount = entry->mod1DiceCount;
            d.mod1DiceSides = entry->mod1DiceSides;
            d.mod2 = entry->mod2;
        }
    );
    return d;
}