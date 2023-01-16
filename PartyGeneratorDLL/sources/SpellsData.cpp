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
