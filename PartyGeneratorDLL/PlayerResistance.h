#pragma once
#include "pch.h"
#include "main.h"

class PlayerSpell;
class PlayerResistance
{
public:
	int id;
	std::string name;
	bool exclusive; // cannot be acquired ingame without cheating
	PlayerSpell* resistanceSpell;
	PlayerSpell* groupResistanceSpell; // day of protection

	PlayerResistance();
};

