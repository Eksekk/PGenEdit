#include "pch.h"
#include "main.h"
#include "ItemGenerationData.h"
#include "Player.h"

ItemGenerationData::ItemGenerationData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	//items = player->items;
	setDefaults();
}

// Inherited via GeneratorDataBase
bool ItemGenerationData::readFromJson(const Json& json)
{
	return false;
}
bool ItemGenerationData::writeToJson(Json& json)
{
	return false;
}
template<typename Player>
bool ItemGenerationData::generate(Player* player)
{
	return false;
}
void ItemGenerationData::setDefaults()
{
	generationEnabled = true;
	keepCurrentItems = false;
	guaranteeMeleeWeapon = false;
	guaranteeArmor = false;
	guaranteeRangedWeapon = false;
	remainingValue = 0;
}

void ItemGenerationData::randomize()
{
}

void ItemGenerationData::copyFrom(const GeneratorDataBase& source)
{
}

ItemGenerationData& ItemGenerationData::operator=(const ItemGenerationData& other)
{
	return *this;
}

bool ItemGenerationData::operator==(const ItemGenerationData& other) const
{
	return false;
}

bool ItemGenerationData::operator!=(const ItemGenerationData& other) const
{
	return false;
}

template <typename Player>
int ItemGenerationData::getItemCount(Player* player)
{
	
}
template <typename Player>
int ItemGenerationData::getSpecificItemCount(PlayerItem* item)
{
	return 0;
}
template <typename Player>
int ItemGenerationData::getItemTypeCount(ItemType type)
{
	return 0;
}
template <typename Player>
int ItemGenerationData::getItemTypeValue(ItemType type)
{
	return 0;
}

/*template<typename Player>
bool ItemGenerationData::shouldItemGenerate(Player* player, PlayerItem* itemDef);

template<typename Player>
bool ItemGenerationData::shouldPotionGenerate(void* player, int remainingValue, PlayerItem* itemDef)
{
	Player* pl = (Player*)player;

}*/