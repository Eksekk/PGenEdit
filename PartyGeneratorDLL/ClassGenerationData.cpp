#include "pch.h"
#include "main.h"
#include "ClassGenerationData.h"
#include "GameData.h"

ClassGenerationData::ClassGenerationData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}

void ClassGenerationSettings::setDefaults()
{
	weight = 1;
	for (int& i : tierWeights)
	{
		i = 1;
	}
	alignment = ALIGNMENT_NEUTRAL;
	disabled = false;
	equalChances = false;
}

ClassGenerationSettings::ClassGenerationSettings()
{
	setDefaults();
}

bool ClassGenerationData::readFromJson(const Json& json)
{
	return false;
}

bool ClassGenerationData::writeToJson(Json& json)
{
	return false;
}

void ClassGenerationData::setDefaults()
{
	for (auto& [i, classGenerationSettings] : settings)
	{
		classGenerationSettings.setDefaults();
	}
	possibleAlignment = ALIGNMENT_ANY;
}

void ClassGenerationData::randomize()
{
}

void ClassGenerationData::copyFrom(const GeneratorDataBase& source)
{
}

void ClassGenerationData::createSettings()
{
	for (int i = 0; i < GameData::classes.size(); ++i)
	{
		settings.emplace(GameData::classes[i].id, ClassGenerationSettings());
	}
}

template<typename Player>
bool ClassGenerationData::generate(Player* player/*, Generator::State state*/)
{
	return false;
}