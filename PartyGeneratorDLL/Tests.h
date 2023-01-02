#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"

class Tests
{
public:
	Generator::State storedState;

	void testSkillFunctions(); // join skill / split skill

	template<typename Player, typename Game>
	void testClassGeneration(Player* player);

	template<typename Player, typename Game>
	void testSkillsGeneration(Player* player);

	void testJson();

	void testGui();
};

template<typename Player, typename Game>
inline void Tests::testClassGeneration(Player* player)
{
	// Game* game = static_cast<Game*>(0);
	// static_assert(SAME(game->party[0], Player))
}

template<typename Player, typename Game>
inline void Tests::testSkillsGeneration(Player* player)
{
	// Game* game = static_cast<Game*>(0);
	// static_assert(SAME(game->party[0], Player))
}
