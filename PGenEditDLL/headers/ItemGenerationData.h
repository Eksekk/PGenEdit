#pragma once
#include "main.h"
#include "Player.h"
#include "GeneratorDataBase.h"
#include "Enum_const.h"
#include "Player.h"

class PlayerItem;

class PlayerData;

struct GuaranteedItem
{
	mm7::Item details;

};

class ItemGenerationData : public GeneratorDataBase
{
public:
	// remove_extent_t turns array type into its element type
	// array of player's items
	// std::remove_extent_t<decltype(Player::items)>* items;

	bool keepCurrentItems;
	bool guaranteeMeleeWeapon;
	bool guaranteeArmor;
	bool guaranteeRangedWeapon;

	int remainingValue;

	int index;
	bool generationEnabled;
	PlayerData& playerData;
	ItemGenerationData(int index, PlayerData& playerData);
	ItemGenerationData() = delete;
	template<typename Player>
	bool generate(Player* player);
	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;

	virtual void setDefaults() override;
	virtual void randomize() override;
	virtual void copyFrom(const GeneratorDataBase& source) override;
	// using a TON of function templates instead of class template because I really
	// hate std::variant syntax (std::visit) and the fact
	// that I'd probably have to use it all over my code

	template <typename Player>
	int getItemCount(Player* player);
	template <typename Player>
	int getSpecificItemCount(PlayerItem* item);
	template <typename Player>
	int getItemTypeCount(ItemType type);
	template <typename Player>
	int getItemTypeValue(ItemType type);

	struct State
	{
		void* items; // allocated inside Generator::generate() to skip template verbosity
					 // (be able to cast instantly into proper item type)
	} state;

	template<typename Player>
	static std::function<bool(void*, int, PlayerItem*, ItemGenerationData*)> shouldItemTypeGenerate[ITEM_TYPE_COUNT];

	ItemGenerationData& operator=(const ItemGenerationData& other);

	bool operator==(const ItemGenerationData& other) const;
	bool operator!=(const ItemGenerationData& other) const;
	
};

