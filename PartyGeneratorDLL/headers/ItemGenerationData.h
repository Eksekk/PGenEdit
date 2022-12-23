#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include <type_traits>
#include "GeneratorDataBase.h"

class ItemGenerationData : public GeneratorDataBase
{
public:
	// remove_extent_t turns array type into its element type
	// array of player's items
	// std::remove_extent_t<decltype(Player::items)>* items;

	ItemGenerationData();
	bool keepCurrentItems;
	bool guaranteeMeleeWeapon;
	bool guaranteeArmor;
	bool guaranteeRangedWeapon;

	std::vector<int> itemTypeWeights;

	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override
	{
		return false;
	}
	virtual bool writeToJson(Json& json) override
	{
		return false;
	}
	template<typename Player>
	bool generate(Player* player)
	{
		return false;
	}
	virtual void setDefaults() override
	{
	}
};

