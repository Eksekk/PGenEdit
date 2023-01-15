#pragma once
#include "pch.h"
#include "main.h"
#include "GeneratorDataBase.h"
#include "Enum_const.h"

class PlayerData;

class SkillsData : public GeneratorDataBase
{
public:
	int index;
	bool generationEnabled;
	PlayerData& playerData;
	SkillsData(int index, PlayerData& playerData);
	SkillsData() = delete;

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