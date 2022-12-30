#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include "GeneratorDataBase.h"
#include "ResistanceData.h"
#include "SkillsData.h"
#include "SpellsData.h"
#include "StatisticsData.h"
#include "ItemGenerationData.h"
#include "Enum_const.h"
#include "ClassGenerationData.h"

class PlayerData : GeneratorDataBase
{
public:
	ItemGenerationData* items;
	ResistanceData* resists;
	SkillsData* skills;
	SpellsData* spells;
	StatisticsData* stats;
	ClassGenerationData classes;
	PlayerType playerType;

	PlayerData();
	virtual ~PlayerData();

	// Inherited via GeneratorDataBase
	// TODO: optional zero out player bits
	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	virtual void setDefaults() override;
	template<typename Player>
	bool generate(Player* player);
};
