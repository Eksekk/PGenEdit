#pragma once
#include "pch.h"
#include "main.h"

class PlayerSpell;
class PlayerResistance
{
public:
	const int id;
	const std::string name;
	const bool exclusive; // cannot be acquired ingame without cheating
	PlayerSpell* const resistanceSpell;
	PlayerSpell* const groupResistanceSpell; // day of protection

	PlayerResistance() = delete;
	PlayerResistance(int id, const std::string& name, bool exclusive, PlayerSpell* resistanceSpell, PlayerSpell* groupResistanceSpell);
};