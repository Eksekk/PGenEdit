#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"
#include "Utility.h"

#define myassert(cond, ...) myasserter(__FUNCTION__, __FILE__, __LINE__, (cond), "Assertion failed! (" #cond ")" __VA_OPT__(,) __VA_ARGS__)

extern Generator* generator;

struct Asserter
{
	std::vector<wxString>& errors;
	bool& failed;
	template<typename... Args>
	bool operator()(const char* func, const char* file, int line, bool cond, const wxString& errorMsg, const Args&... args);

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

	// bounds check
	wxLogNull noLog;

	// uint8_t
	myassert(boundsCheck(0, 1));
	myassert(boundsCheck(3, 1));
	myassert(boundsCheck(58, 1));
	myassert(boundsCheck(222, 1));
	myassert(boundsCheck(255, 1));
	// not
	myassert(!boundsCheck(-55, 1));
	myassert(!boundsCheck(-1, 1));
	myassert(!boundsCheck(256, 1));
	myassert(!boundsCheck(500, 1));
	myassert(!boundsCheck(222500, 1));

	// int8_t
	myassert(boundsCheck(-128, -1));
	myassert(boundsCheck(-15, -1));
	myassert(boundsCheck(0, -1));
	myassert(boundsCheck(111, -1));
	myassert(boundsCheck(127, -1));
	// not
	myassert(!boundsCheck(-129, -1));
	myassert(!boundsCheck(-5555, -1));
	myassert(!boundsCheck(128, -1));
	myassert(!boundsCheck(4325342, -1));

	// uint16_t
	int u16_max = std::numeric_limits<uint16_t>::max();
	myassert(boundsCheck(0, 2));
	myassert(boundsCheck(15, 2));
	myassert(boundsCheck(2222, 2));
	myassert(boundsCheck(u16_max - 555, 2));
	myassert(boundsCheck(u16_max, 2));
	// not
	myassert(!boundsCheck(-5555555, 2));
	myassert(!boundsCheck(-5435, 2));
	myassert(!boundsCheck(-1, 2));
	myassert(!boundsCheck(u16_max + 1, 2));
	myassert(!boundsCheck(u16_max + 5555, 2));
	myassert(!boundsCheck(-u16_max, 2));

	// int16_t
	int i16_min = std::numeric_limits<int16_t>::min(), i16_max = std::numeric_limits<int16_t>::max();

	myassert(boundsCheck(i16_min, -2));
	myassert(boundsCheck(i16_min + 1, -2));
	myassert(boundsCheck(i16_min + 2222, -2));
	myassert(boundsCheck(0, -2));
	myassert(boundsCheck(5436, -2));
	myassert(boundsCheck(i16_max - 23549, -2));
	myassert(boundsCheck(i16_max, -2));
	// not
	myassert(!boundsCheck(i16_min - 55555, -2));
	myassert(!boundsCheck(i16_min - 54, -2));
	myassert(!boundsCheck(i16_min - 1, -2));
	myassert(!boundsCheck(i16_min + 4538738, -2));
	myassert(!boundsCheck(-u16_max, -2));
	myassert(!boundsCheck(i16_max + 1, -2));
	myassert(!boundsCheck(i16_max + 2325435, -2));
	myassert(!boundsCheck(i16_max - 4387432, -2));

	// uint32_t
	int64_t u32_max = std::numeric_limits<uint32_t>::max();

	myassert(boundsCheck(i16_max, 4));
	myassert(boundsCheck(u16_max, 4));
	myassert(boundsCheck(0, 4));
	myassert(boundsCheck(5465434, 4));
	myassert(boundsCheck(u32_max - 4395, 4));
	myassert(boundsCheck(u32_max, 4));
	// not
	myassert(!boundsCheck(-32485, 4));
	myassert(!boundsCheck(-1, 4));
	myassert(!boundsCheck(u32_max + 1, 4));
	myassert(!boundsCheck(u32_max + 122222, 4));

	// int32_t
	int64_t i32_min = std::numeric_limits<int32_t>::min(), i32_max = std::numeric_limits<int32_t>::max();

	myassert(boundsCheck(i32_min, -4));
	myassert(boundsCheck(i32_min + 5555, -4));
	myassert(boundsCheck(0, -4));
	myassert(boundsCheck(i32_max - 3847853, -4));
	myassert(boundsCheck(i32_max, -4));
	// not
	myassert(!boundsCheck(i32_min - 55555666, -4));
	myassert(!boundsCheck(i32_min - 444, -4));
	myassert(!boundsCheck(i32_min - 1, -4));
	myassert(!boundsCheck(i32_max + 1, -4));
	myassert(!boundsCheck(i32_max + 34252432, -4));

	return errors;
}

template<typename Player, typename Game>
std::vector<wxString> Tests::run()
{
	return mergeVectors(testMisc<Player, Game>(), testSkillFunctions(), testJson(), testGui());
}