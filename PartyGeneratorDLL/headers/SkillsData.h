#pragma once
#include "pch.h"
#include "main.h"
#include "GeneratorDataBase.h"
#include "Enum_const.h"

class SkillsData : public GeneratorDataBase
{
public:
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
	}
	template<typename Player>
	bool generate(Player* player)
	{
		return false;
	}
};