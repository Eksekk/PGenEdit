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

template<typename Player>
std::function<bool(void*, int remainingValue, PlayerItem*, ItemGenerationData*)> ItemGenerationData::shouldItemTypeGenerate[ITEM_TYPE_COUNT];

template<typename Player>
bool shouldPotionGenerate(void* player, PlayerItem* itemDef, ItemGenerationData* genData)
{
	Player* pl = (Player*)player;

}