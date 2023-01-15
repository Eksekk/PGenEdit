#pragma once
#include "pch.h"
#include "main.h"
#include "GeneratorDataBase.h"

class PlayerData;

class StatisticsData : public GeneratorDataBase
{
public:
	int index;
	bool generationEnabled;
	PlayerData& playerData;
	StatisticsData(int index, PlayerData& playerData);
	StatisticsData() = delete;
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
};

