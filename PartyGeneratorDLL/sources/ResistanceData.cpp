#include "pch.h"
#include "main.h"
#include "ResistanceData.h"
#include "globals.h"

template<typename Player>
bool ResistanceData::generate(Player* player)
{
	return false;
}

bool ResistanceData::writeToJson(Json& json)
{
	return false;
}

bool ResistanceData::readFromJson(const Json& json)
{
	return false;
}

void ResistanceData::setDefaults()
{
	playerResistancePoints = 0;
	disabled = false;
	for (auto& line : lines)
	{
		line.setDefaults();
	}
}

ResistanceDataInner::ResistanceDataInner()
{
	setDefaults();
}

void ResistanceDataInner::setDefaults()
{
	disabled = false;
	// TODO: isExclusive
	resistanceId = INVALID_ID;
	useExact = allowMoreThanResistancePoints = useRange = false;
	subtractFromResistancePoints = scaleByLevel = true;
	rangeVal = std::make_pair(0, 0);
	priority = exactVal = 0;
	weight = 1;
}