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
std::string PlayerItem::getItemModString() const
{
    // TODO
    return "";
}