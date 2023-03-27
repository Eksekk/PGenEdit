#pragma once
#include "pch.h"
#include "main.h"
#include "GeneratorDataBase.h"

class PlayerData;

class SpellsData : public GeneratorDataBase
{
public:
	int index;
	bool generationEnabled;
	PlayerData& playerData;
	SpellsData(int index, PlayerData& playerData);
	SpellsData() = delete;
	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override
	{
		return false;
	}
	virtual bool writeToJson(Json& json) override
	{
		return false;
	}
	virtual void setDefaults() override
	{
		generationEnabled = true;
	}
	template<typename Player>
	bool generate(Player* player)
	{
		return false;
	}


	// Inherited via GeneratorDataBase
	virtual void randomize() override;

	virtual void copyFrom(const GeneratorDataBase& source) override;

	SpellsData& operator=(const SpellsData& other);

	bool operator==(const SpellsData& other) const;
	bool operator!=(const SpellsData& other) const;

	// clear beacons if removed lloyd's beacon spell
	// zero out fire spike casts, divine intervention casts and armageddon casts if spell removed
	// reset quick spell, attack spell, spell book page
	// handle removing fly spell - fall damage
};