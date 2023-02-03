#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"
#include "Utility.h"

#define myassert(cond, ...) myasserter(__FUNCTION__, __FILE__, __LINE__, (cond), wxString("Assertion failed! (" #cond ")")__VA_OPT__(,) __VA_ARGS__)

extern Generator* generator;

struct Asserter
{
	std::vector<wxString>& errors;
	bool& failed;
	template<typename... Args>
	bool operator()(const char* func, const char* file, int line, bool cond, wxString errorMsg, const Args&... args);

	Asserter(std::vector<wxString>& errors, bool& failed);

	Asserter() = delete;
	Asserter(const Asserter&) = delete;
	Asserter(Asserter&&) = delete;
	Asserter& operator=(const Asserter&) = delete;
};

class Tests
{
public:
	static Generator::State storedState;

	static std::vector<wxString> testSkillFunctions(); // join skill / split skill

	static std::vector<wxString> testAlignmentRadioBox();
	template<typename Player, typename Game>
	static std::vector<wxString> testClassGeneration(Player* player);

	template<typename Player, typename Game>
	static std::vector<wxString> testSkillsGeneration(Player* player);

	static std::vector<wxString> testJson();
	static std::vector<wxString> testGui();

	template<typename Player, typename Game>
	static std::vector<wxString> run();

	template<typename Player, typename Game>
	static std::vector<wxString> testMisc();
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
std::vector<wxString> Tests::testMisc()
{
	std::vector<wxString> errors;
	bool failed;
	Asserter myasserter(errors, failed);
	Player** players = (Player**)generator->players;
	for (int i = 0; i < MAX_PLAYERS; ++i) // TODO: player count can be different in mm8
	{

	}
	return errors;
}

template<typename Player, typename Game>
std::vector<wxString> Tests::run()
{
	return mergeVectors(testMisc<Player, Game>(), testSkillFunctions(), testJson(), testGui());
}