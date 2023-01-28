#include "pch.h"
#include "main.h"
#include "StatisticsData.h"

StatisticsData::StatisticsData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
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
