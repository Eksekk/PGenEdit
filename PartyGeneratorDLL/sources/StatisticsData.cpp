#include "pch.h"
#include "main.h"
#include "StatisticsData.h"

StatisticsData::StatisticsData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}