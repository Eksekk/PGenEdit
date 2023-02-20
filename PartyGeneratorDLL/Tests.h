#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerStructAccessor.h"
#include "Generator.h"
#include "Utility.h"
#include "GameData.h"

#define myassert(cond, ...) myasserter(__FUNCTION__, __FILE__, __LINE__, (cond), "Assertion failed! (" #cond ")" __VA_OPT__(,) __VA_ARGS__)

extern Generator* generator;

struct Asserter
{
	std::vector<wxString>& errors;
	bool& failed;
	template<typename... Args>
	bool operator()(const char* func, const char* file, int line, bool cond, const wxString& errorMsg, Args&&... args);

	Asserter(std::vector<wxString>& errors, bool& failed);

	Asserter() = delete;
	Asserter(const Asserter&) = delete;
	Asserter(Asserter&&) = delete;
	Asserter& operator=(const Asserter&) = delete;
};

wxString rep(const wxString& str, int n = 1);

template<typename T>
wxString my_to_string(const T& t)
{
	return wxString().operator<<(t); // sorry for clever code, couldn't help myself!
	// we are calling operator<< (which inserts argument into string) on temporary string,
	// taking advantage that it returns modified string (intended to allow chaining,
	// like str << "x" << "y" << 5)
}

template<typename... Args>
bool Asserter::operator()(const char* func, const char* file, int line, bool cond, const wxString& rawErrorMsg, Args&&... args)
{
	if (!cond)
	{
		std::string file2 = file;
		size_t index = file2.rfind('/');
		if (index != std::string::npos)
		{
			file2 = file2.substr(index + 1);
		}
		static const wxString errorFormat("%s(%s:%d) %s");
		wxString errorMsg = rawErrorMsg;
		if constexpr (sizeof...(args) > 0)
		{
			errorMsg << ("\nExtra data:" + rep("\n%s", sizeof...(args)));
			errorMsg = wxString::Format(errorMsg, my_to_string(args)...);
		}
		errors.push_back(wxString::Format(errorFormat, func, file2, line, errorMsg));
		failed = true;
		return false;
	}
	return true;
}

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
	return mergeVectors({ testMisc<Player, Game>(), testSkillFunctions()/*, testJson()*/, testGui<Player, Game>(), testPlayerStructAccessor<Player, Game>() });
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

// automatically tests single integral field from player struct, provided with pointer to field and accessor get/set functions
// I think good use for pointers to members/member functions, other (ugly) alternative I can see is macros // pointers to functions are obsolete,
// old version used them but I couldn't use std::bind and then pass them
template<typename Player, typename IntegralFieldType, typename IntegralGetSetType = int>
void testSettableField(
	Player* player,
	IntegralFieldType Player::* playerFieldPtr,
	std::function<int()> getFunction, // of accessor
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
		int64_t fieldValueBefore = player->*playerFieldPtr, getterValueBefore = getFunction();
		setFunction(test);
		int64_t fieldValueAfter = player->*playerFieldPtr, getterValueAfter = getFunction();
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

		player->*playerFieldPtr = fieldValueBefore;
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