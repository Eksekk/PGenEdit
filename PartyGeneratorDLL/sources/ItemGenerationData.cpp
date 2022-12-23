#include "pch.h"
#include "main.h"
#include "ItemGenerationData.h"
#include "Player.h"

ItemGenerationData::ItemGenerationData()
{
	//items = player->items;
	keepCurrentItems = false;
	guaranteeMeleeWeapon = false;
	guaranteeArmor = false;
	guaranteeRangedWeapon = false;
}