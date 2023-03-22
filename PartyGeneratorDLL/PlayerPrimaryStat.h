#pragma once
#include "pch.h"
#include "main.h"

class PlayerPrimaryStat
{
public:
	const int id;
	const std::string name;
	const int blackPotionId;

	int getConditionEffect(int cond) const;
	PlayerPrimaryStat() = delete;
	PlayerPrimaryStat(int id, std::string name, int blackPotionId);
};

