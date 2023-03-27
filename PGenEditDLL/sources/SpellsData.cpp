#include "pch.h"
#include "main.h"
#include "SpellsData.h"

SpellsData::SpellsData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}

void SpellsData::randomize()
{
}

void SpellsData::copyFrom(const GeneratorDataBase& source)
{
}

SpellsData& SpellsData::operator=(const SpellsData& other)
{
	// TODO: insert return statement here
	return *this;
}

bool SpellsData::operator==(const SpellsData& other) const
{
	return false;
}

bool SpellsData::operator!=(const SpellsData& other) const
{
	return false;
}
