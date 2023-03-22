#include "pch.h"
#include "PlayerPrimaryStat.h"

int PlayerPrimaryStat::getConditionEffect(int cond) const
{
	wxFAIL;
	return 0;
}

PlayerPrimaryStat::PlayerPrimaryStat(int id, std::string name, int blackPotionId) : id(id), name(name), blackPotionId(blackPotionId)
{
}