#pragma once
#include "main.h"

class PlayerPrimaryStat
{
public:
	const int id;
	const std::string name;
	const int blackPotionId;

	PlayerPrimaryStat() = delete;
	PlayerPrimaryStat(int id, std::string name, int blackPotionId);
};

