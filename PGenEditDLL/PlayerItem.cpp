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

std::string PlayerItem::getCategoryName() const
{
	int itemType = itemAccessor->forItemTxtIndexDo(id - 1, [](auto ptr) -> int { return ptr->equipStat; });

}