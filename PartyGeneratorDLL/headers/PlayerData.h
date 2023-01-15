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
	int index; // player left to right, starting at 0
	// INVALID_ID MEANS DEFAULT DATA

	CharacterStrengthIndicator strengthIndicator; // TODO: add reference to player data to member classes?
	bool generationEnabled;

	PlayerData(int index);
	PlayerData() = delete;
	virtual ~PlayerData();

	// Inherited via GeneratorDataBase
	// TODO: optional zero out player bits
	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	virtual void setDefaults() override;
	template<typename Player>
	bool generate(Player* player);
};
