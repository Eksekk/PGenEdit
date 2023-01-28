#include "pch.h"
#include "main.h"
#include "SkillsData.h"

SkillsData::SkillsData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}

void SkillsData::randomize()
{
}

void SkillsData::copyFrom(const GeneratorDataBase& source)
{
}

SkillsData& SkillsData::operator=(const SkillsData& other)
{
	return *this;
}

bool SkillsData::operator==(const SkillsData& other) const
{
	return false;
}

bool SkillsData::operator!=(const SkillsData& other) const
{
	return false;
}
