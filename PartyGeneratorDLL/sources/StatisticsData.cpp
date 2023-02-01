#include "pch.h"
#include "main.h"
#include "StatisticsData.h"

StatisticsData::StatisticsData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}

// Inherited via GeneratorDataBase

bool StatisticsData::readFromJson(const Json& json)
{
	return false;
}

bool StatisticsData::writeToJson(Json& json)
{
	return false;
}

void StatisticsData::setDefaults()
{
	generationEnabled = true;
	efficientUseOfBreakpoints = true;
}

void StatisticsData::randomize()
{
}

void StatisticsData::copyFrom(const GeneratorDataBase& source)
{
}

StatisticsData& StatisticsData::operator=(const StatisticsData& other)
{
	// TODO: insert return statement here
	return *this;
}

bool StatisticsData::operator==(const StatisticsData& other) const
{
	return false;
}

bool StatisticsData::operator!=(const StatisticsData& other) const
{
	return false;
}
