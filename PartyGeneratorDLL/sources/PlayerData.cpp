#include "pch.h"
#include "main.h"
#include "PlayerData.h"
#include "Generator.h"

PlayerData::PlayerData()
{
	skills = new SkillsData;
	spells = new SpellsData;
	items = new ItemGenerationData;
	stats = new StatisticsData;
	resists = new ResistanceData;
	setDefaults();
}

PlayerData::~PlayerData()
{
	if (skills) delete skills;
	if (spells) delete spells;
	if (items) delete items;
	if (stats) delete stats;
	if (resists) delete resists;
}

bool PlayerData::readFromJson(const Json& json)
{
	return false;
}

bool PlayerData::writeToJson(Json& json)
{
	return false;
}

template<typename Player>
bool PlayerData::generate(Player* player)
{
	return false;
}

void PlayerData::setDefaults()
{
	skills->setDefaults();
	spells->setDefaults();
	items->setDefaults();
	stats->setDefaults();
	resists->setDefaults();
	classes.setDefaults();
	playerType = PLAYER_GENERIC;
	strengthIndicator = CHARACTER_GENERATED_LEVEL;
	generationEnabled = true;
}