#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"

class Tests
{
public:
	static Generator::State storedState;

	static std::vector<wxString> testSkillFunctions(); // join skill / split skill

	template<typename Player, typename Game>
	static std::vector<wxString> testClassGeneration(Player* player);

	template<typename Player, typename Game>
	static std::vector<wxString> testSkillsGeneration(Player* player);

	static std::vector<wxString> testJson();
	static std::vector<wxString> testGui();

	template<typename Player, typename Game>
	static std::vector<wxString> run();
};

template<typename Player, typename Game>
inline std::vector<wxString> Tests::testClassGeneration(Player* player)
{
	// Game* game = static_cast<Game*>(0);
	// static_assert(SAME(game->party[0], Player))
}

template<typename Player, typename Game>
inline std::vector<wxString> Tests::testSkillsGeneration(Player* player)
{
	// Game* game = static_cast<Game*>(0);
	// static_assert(SAME(game->party[0], Player))
}

template<typename Player, typename Game>
std::vector<wxString> Tests::run()
{
	return testSkillFunctions();
}
