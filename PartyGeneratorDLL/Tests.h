#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerStructAccessor.h"
#include "Generator.h"
#include "Utility.h"
#include "Asserter.h"

extern Generator* generator;

class Tests
{
public:
	static Generator::State storedState;
	static bool testingNow; // to make game data not zero out party size when showing log message (modal, has own event loop)

	static std::vector<wxString> testSkillFunctions(); // join skill / split skill

	static std::vector<wxString> testAlignmentRadioBox();
	template<typename Player, typename Game>
	static std::vector<wxString> testClassGeneration(Player* player);

	template<typename Player, typename Game>
	static std::vector<wxString> testSkillsGeneration(Player* player);

	static std::vector<wxString> testJson();
	template<typename Player, typename Game>
	static std::vector<wxString> testGui();
	template<typename Player, typename Game>
	static std::vector<wxString> testPlayerStructAccessor();

	template<typename Player, typename Game>
	static std::vector<wxString> run();

	template<typename Player, typename Game>
	static std::vector<wxString> testMisc();
};

template<typename Player, typename Game>
std::vector<wxString> Tests::run()
{
	testingNow = true;
	auto ret = mergeVectors({ testMisc<Player, Game>(), testSkillFunctions()/*, testJson()*//*, testGui<Player, Game>()*/, testPlayerStructAccessor<Player, Game>() });
	testingNow = false;
	return ret;
}

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

// automatically tests single integral field from game struct, provided with pointer to field and accessor get/set functions
// I think good use for pointers to members/member functions, other (ugly) alternative I can see is macros
// pointers to functions are obsolete,
// old version used them but I couldn't use std::bind and then pass them
template<typename Struct, typename IntegralFieldType, typename IntegralGetSetType = int>
void testSettableStructField(
	Struct* stru,
	IntegralFieldType Struct::* structFieldPtr,
	std::function<IntegralGetSetType()> getFunction, // of accessor
	std::function<void(IntegralGetSetType)> setFunction, // of accessor
	Bounds bounds,
	Asserter& myasserter,
	const wxString& logId
)
{
	static_assert(std::is_integral_v<IntegralFieldType>);
	static_assert(std::is_integral_v<IntegralGetSetType>);
	
	//wxLogNull noLog;

	auto [low, high] = bounds;
	myassert(low <= high, wxString::Format("[%s] bounds [%lld, %lld] too wide", logId, low, high));
	int64_t range = high - low + 1;
	int64_t unit = range / 100;
	std::array<int64_t, 24> tests{ low, low + 1, low + 3, low + 10, low + 50, low + unit, low + unit * 4, low + unit * 20, low + unit * 37, low + unit * 45, low + unit * 50,
		0, 1, 4, 10, 22, high - unit * 42, high - unit * 22, high - unit * 5, high - unit, high - 20, high - 3, high - 1, high };

	int oldErrorsNum = myasserter.errors.size();
	for (int i = 0; i < tests.size(); ++i)
	{
		int64_t test = tests[i];
		wxString failMsg = wxString::Format("[%s] Test #%d (value: %lld) failed", logId, i, test);
		int64_t fieldValueBefore = stru->*structFieldPtr, getterValueBefore = getFunction();
		setFunction(test);
		int64_t fieldValueAfter = stru->*structFieldPtr, getterValueAfter = getFunction();
		if (fieldValueBefore != fieldValueAfter) // only perform checks if test value wasn't the original value
		{
			myassert(fieldValueBefore != getterValueAfter, wxString::Format(failMsg + " field before: %lld, getter after: %lld", fieldValueBefore, getterValueAfter));
			myassert(getterValueBefore != getterValueAfter, wxString::Format(failMsg + " getter before: %lld, getter after: %lld", getterValueBefore, getterValueAfter));
			myassert(getterValueBefore != fieldValueAfter, wxString::Format(failMsg + " getter before: %lld, field after: %lld", getterValueBefore, fieldValueAfter));
		}
		else
		{
			myassert(getterValueBefore == getterValueAfter, wxString::Format(failMsg + " getter before: %lld, getter after: %lld", getterValueBefore, getterValueAfter));
		}

		stru->*structFieldPtr = fieldValueBefore;
		myassert((int64_t)getFunction() == fieldValueBefore, wxString::Format(failMsg + " [member pointer assign] getter: %lld, field: %lld", (int64_t)getFunction(), fieldValueBefore));
	}
	
	if (oldErrorsNum != myasserter.errors.size())
	{
		std::vector<wxString> parts;
		parts.reserve(tests.size());
		std::transform(tests.begin(), tests.end(), std::back_inserter(parts), [](uint64_t test) -> wxString { return wxString::Format("%lld", test); });
		wxLogWarning("Test data: %s", concatWxStrings(parts, ", "));
	}

	// for [getStat/setStat]-settable stats, either make new function similar to this one, but less templates and member pointers
	// or experiment with std::bind (wxwidgets says, I think, that you can bind free function to member function pointer - see Bind())
	
	// for resistances, iterate over each "enum" value, check if it's present in data from lua, and if yes, then test it
	// this takes care of elemental mod

	// LET'S GOOOOO
}