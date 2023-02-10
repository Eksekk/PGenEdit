#include "pch.h"
#include "main.h"
#include "PlayerItem.h"
#include "Generator.h"

PlayerItem::PlayerItem() : number(INVALID_ID), power(1), cost(1), isArtifact(false), image(nullptr), inventoryWidth(1), inventoryHeight(1)
{
	
}

void PlayerItem::loadAndConvertBitmap(const wxString& name)
{

}
