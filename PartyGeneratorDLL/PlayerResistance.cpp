#include "pch.h"
#include "PlayerResistance.h"

extern const int INVALID_ID;

PlayerResistance::PlayerResistance(int id, const std::string& name, bool exclusive, PlayerSpell* resistanceSpell, PlayerSpell* groupResistanceSpell)
	: id(id), name(name), exclusive(exclusive), resistanceSpell(resistanceSpell), groupResistanceSpell(groupResistanceSpell)
{
}
