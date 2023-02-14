#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"
#include "Utility.h"
#include "PlayerStructAccessor.h"
#include "GameData.h"

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
	static std::vector<wxString> testPlayerStructAccessor();

	template<typename Player, typename Game>
	static std::vector<wxString> run();

	template<typename Player, typename Game>
	static std::vector<wxString> testMisc();
};

template<typename Player, typename Game>
std::vector<wxString> Tests::run()
{
	return mergeVectors(testMisc<Player, Game>(), testSkillFunctions(), testJson(), testGui(), testPlayerStructAccessor<Player, Game>());
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

	// test clamping
	int x = 145;
	int x2 = 145;
	boundsCheck(x2, -1);
	myassert(x != x2);

	return errors;
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
	
	wxLogNull noLog;

	auto [low, high] = bounds;
	myassert(low <= high, wxString::Format("[%s] bounds [%d, %d] too wide", logId, low, high));
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
			myassert(fieldValueBefore != getterValueAfter, failMsg);
			myassert(getterValueBefore != getterValueAfter, failMsg);
			myassert(getterValueBefore != fieldValueAfter, failMsg);
		}
		else
		{
			myassert(getterValueBefore == getterValueAfter, failMsg);
		}

		player->*playerFieldPtr = fieldValueBefore;
		myassert(getFunction() == fieldValueBefore, failMsg);
	}
	
	if (oldErrorsNum != myasserter.errors.size())
	{
		std::vector<wxString> parts;
		parts.reserve(tests.size());
		std::transform(tests.begin(), tests.end(), std::back_inserter(parts), [](uint64_t test) -> wxString { return wxString::Format("%lld", test); });
		myassert(false, wxString::Format("Test data: %s", concatWxStrings(parts, ", ")));
	}

	// for [getStat/setStat]-settable stats, either make new function similar to this one, but less templates and member pointers
	// or experiment with std::bind (wxwidgets says, I think, that you can bind free function to member function pointer - see Bind())
	
	// for resistances, iterate over each "enum" value, check if it's present in data from lua, and if yes, then test it
	// this takes care of elemental mod

	// LET'S GOOOOO
}

template<typename Player, typename Game>
std::vector<wxString> Tests::testPlayerStructAccessor()
{
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);

	static_assert(SAME(Player, mm7::Player), "Tests for other games not implemented yet");

	Player* pl = new Player;
	memset(pl, 0, sizeof(Player));

	wxLogNull noLog;

	void* oldPlayerZero = generator->players[0];
	generator->players[0] = pl;
	(void)playerAccessor[0]; // switch to player 0
	// full hp bonus, full sp bonus, ranged/melee attack/damage bonus
	if constexpr (SAME(Player, mm6::Player) || SAME(Player, mm7::Player))
	{
		pl->fullHPBonus = 50;
		pl->fullSPBonus = 122;
		myassert(playerAccessor->getFullHpBonus() == pl->fullHPBonus);
		myassert(playerAccessor->getFullSpBonus() == pl->fullSPBonus);

		playerAccessor->setFullHpBonus(100);
		playerAccessor->setFullSpBonus(44);
		myassert(playerAccessor->getFullHpBonus() == pl->fullHPBonus && pl->fullHPBonus == 100);
		myassert(playerAccessor->getFullSpBonus() == pl->fullSPBonus && pl->fullSPBonus == 44);

		myassert(playerAccessor->getMeleeAttackBonus() == 0);
		pl->meleeAttackBonus = 12;
		pl->meleeDamageBonus = 43;
		myassert(playerAccessor->getMeleeAttackBonus() == 12);
		myassert(playerAccessor->getMeleeDamageBonus() == 43);
		playerAccessor->setMeleeAttackBonus(playerAccessor->getMeleeAttackBonus() + 34);
		myassert(playerAccessor->getMeleeAttackBonus() == 12 + 34 && pl->meleeAttackBonus == 12 + 34);
		playerAccessor->setMeleeAttackBonus(-5);
		myassert(playerAccessor->getMeleeAttackBonus() == -5 && pl->meleeAttackBonus == -5);

		pl->rangedAttackBonus = -22;
		pl->rangedDamageBonus = 55;
		myassert(playerAccessor->getRangedAttackBonus() == -22);
		myassert(playerAccessor->getRangedDamageBonus() == 55);
		playerAccessor->setRangedDamageBonus(115);
		myassert(playerAccessor->getRangedDamageBonus() == 115 && pl->rangedDamageBonus == 115);
		playerAccessor->setRangedAttackBonus(playerAccessor->getRangedAttackBonus() + 55);
		myassert(playerAccessor->getRangedAttackBonus() == -22 + 55 && pl->rangedAttackBonus == -22 + 55);
		playerAccessor->setRangedDamageBonus(playerAccessor->getRangedDamageBonus() + 3);
		myassert(playerAccessor->getRangedDamageBonus() == 115 + 3 && pl->rangedDamageBonus == 115 + 3);
	}

	// hp
	pl->HP = 24342;
	myassert(playerAccessor->getHp() == 23242);
	pl->HP = -5555555;
	myassert(playerAccessor->getHp() == -5555555);
	playerAccessor->setHp(543543);
	myassert(playerAccessor->getHp() == 543543 && pl->HP == 543543);
	playerAccessor->setHp(0);
	myassert(playerAccessor->getHp() == 0 && pl->HP == 0);
	
	// sp
	pl->SP = 24342;
	myassert(playerAccessor->getSp() == 23242);
	pl->SP = -5555555;
	myassert(playerAccessor->getSp() == -5555555);
	playerAccessor->setSp(543543);
	myassert(playerAccessor->getSp() == 543543 && pl->SP == 543543);
	playerAccessor->setSp(0);
	myassert(playerAccessor->getSp() == 0 && pl->SP == 0);

	// ac bonus
	myassert(playerAccessor->getAcBonus() == 0);
	pl->armorClassBonus = 55;
	myassert(playerAccessor->getAcBonus() == 55);
	playerAccessor->setAcBonus(24);
	myassert(playerAccessor->getAcBonus() == 24 && pl->armorClassBonus == 24);

	// NEW CODE FOR EASIER TESTING (keeping old just in case new breaks)
	using namespace std::placeholders;

	// helper function (less typing!) which binds placeholders they receive to [get/set]StatBase method, so you can ultimately do:
	// testPrimaryStatBase(STAT_MIGHT, &Player::mightBase, "Might base");

	auto testStatBase = [&pl, &myasserter] (int statId, auto Player::*baseField, const wxString& logId) -> void
	{
		// tried making lambda passing placeholder (argument) to bind (two level indirection; see below), didn't work
		std::function<int(void)> boundBaseGet{ std::bind(&PlayerStructAccessor::getStatBase, playerAccessor, statId) };
		std::function<void(int)> boundBaseSet{ std::bind(&PlayerStructAccessor::setStatBase, playerAccessor, statId, _1) };

		// without decay won't work
		
		// small explanation for future myself:
		// pl->*baseField gets value from pointer "pl" with pointer-to-member value
		// decltype() returns declaration type (doesn't actually execute, only returns a type, kinda like assembly "lea" versus "mov")
		// std::decay_t<> strips all "decorations" from a type such as const, volatile, pointer, reference, array etc., making it suitable for comparisons
		using IntegerType = std::decay_t<decltype(pl->*baseField)>;
		static_assert(std::is_integral_v<IntegerType> && sizeof(IntegerType) <= 4, "Field type must be integer <= 4 bytes");
		testSettableField<Player, IntegerType>(pl, baseField, boundBaseGet, boundBaseSet, boundsByType<IntegerType>, myasserter, logId);
	};
	auto testStatBonus = [&pl, &myasserter] (int statId, auto Player::*bonusField, const wxString& logId) -> void
	{
		std::function<int(void)> boundBonusGet{ std::bind(&PlayerStructAccessor::getStatBonus, playerAccessor, statId) };
		std::function<void(int)> boundBonusSet{ std::bind(&PlayerStructAccessor::setStatBonus, playerAccessor, statId, _1) };

		using IntegerType = std::decay_t<decltype(pl->*bonusField)>;
		static_assert(std::is_integral_v<IntegerType> && sizeof(IntegerType) <= 4, "Field type must be integer <= 4 bytes");
		testSettableField<Player, IntegerType>(pl, bonusField, boundBonusGet, boundBonusSet, boundsByType<IntegerType>, myasserter, logId);
	};

	auto testStatBaseBonus = [&pl, &myasserter, &testStatBase, &testStatBonus](int statId, auto Player::* baseField, auto Player::* bonusField, const wxString& logId)
	{
		static_assert(std::is_same_v<std::decay_t<decltype(pl->*baseField)>, std::decay_t<decltype(pl->*bonusField)>>, "Integer types for base and bonus fields are different");
		testStatBase(statId, baseField, logId + " base");
		testStatBonus(statId, bonusField, logId + " bonus");
	};
	// NOT WORKING
	// auto bindGetBase = [](auto placeholderStatId) { return std::bind(&PlayerStructAccessor::getStatBase, playerAccessor, placeholderStatId); };
	// auto bindSetBase = [](auto placeholderStatId) { return std::bind(std::mem_fn(&PlayerStructAccessor::setStatBase), playerAccessor, placeholderStatId); };
	// std::function<void(int statId, int16_t Player::* field, const wxString& logId)> testPrimaryStatBase = std::bind(testSettableField<Player, int16_t>, pl, _2, bindGetBase(_1), bindSetBase(_1), getBounds(-2), myasserter, _3);
	
	testStatBaseBonus(STAT_MIGHT, &Player::mightBase, &Player::mightBonus, "Might");
	testStatBaseBonus(STAT_INTELLECT, &Player::intellectBase, &Player::intellectBase, "Intellect");
	testStatBaseBonus(STAT_PERSONALITY, &Player::personalityBase, &Player::personalityBonus, "Personality");
	testStatBaseBonus(STAT_ENDURANCE, &Player::enduranceBase, &Player::enduranceBonus, "Endurance");
	testStatBaseBonus(STAT_ACCURACY, &Player::accuracyBase, &Player::accuracyBonus, "Accuracy");
	testStatBaseBonus(STAT_SPEED, &Player::speedBase, &Player::speedBonus, "Speed");
	testStatBaseBonus(STAT_LUCK, &Player::luckBase, &Player::luckBonus, "Luck");

	// skills
	auto& skillsMap = GameData::skills;
	myassert(skillsMap.size() > 10);
	// try 5 first, 5 last, every 3th and every 2th
	std::vector<PlayerSkill*> skillsVector;
	skillsVector.reserve(skillsMap.size());
	std::transform(skillsMap.begin(), skillsMap.end(), std::back_inserter(skillsVector), [](auto& pair) -> PlayerSkill* { return &pair.second; });
	static auto randomSkillValue = []() -> SkillValue
	{
		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution mDist(0, (int)MAX_MASTERY), sDist(0, (1 << SKILL_BITS) - 1);
		assert(mDist.b() >= MASTER && sDist.b() >= 63);
		return SkillValue{ sDist(gen), mDist(gen) };
	};
	auto testSpecifiedSkillsByIndex = [&myasserter, &skillsMap, &skillsVector, pl](const std::vector<int>& indexes) -> void
	{
		std::vector<PlayerSkillValue> skillsToSet;
		for (int i : indexes)
		{
			skillsToSet.push_back(PlayerSkillValue{ skillsVector[i], randomSkillValue() });
		}
		auto oldSkills = playerAccessor->getSkills();
		playerAccessor->setSkills(skillsToSet);
		auto newSkills = playerAccessor->getSkills();
		for (int i = 0; i < skillsVector.size(); ++i)
		{
			const wxString iterationStr = wxString::Format("Iteration %d", i);
			// skills map must contain key with value of i (I'm too lazy to use map here)

			myassert(skillsMap.contains(i), iterationStr);

			// if skill was intended to change:
			//	1. old value must not be equal to new value from accessor
			//	2. as above, but raw new value (access player struct)
			//	3. new value from accessor must be equal to raw value
			// else:
			//	4. old == new (accessor)
			//	5. old == new (raw)
			//	6. see point 3

			// IMPLEMENT EQUALITY OPERATOR MYSELF?

			if (existsInVector(indexes, i)) // 1, 2, 3
			{
				// need to have explicitly defined operator !=, even if == is defined, otherwise there are ambiguity errors
				myassert(oldSkills[i].value != newSkills[i].value, iterationStr); // 1
				myassert(oldSkills[i].value != splitSkill(pl->skills[i]), iterationStr); // 2
				myassert(newSkills[i].value == splitSkill(pl->skills[i]), iterationStr); // 3
			}
			else // 4, 5, 6
			{
				myassert(oldSkills[i].value == newSkills[i].value, iterationStr); // 4
				myassert(oldSkills[i].value == splitSkill(pl->skills[i]), iterationStr); // 5
				myassert(newSkills[i].value != splitSkill(pl->skills[i]), iterationStr); // 6
			}
		}
	};
	
	int s = skillsMap.size();
	std::vector<int> first5({0, 1, 2, 3, 4}), last5({s - 5, s - 4, s - 3, s - 2, s - 1});
	std::vector<int> every2th, every3th;
	every2th.resize((ceil(skillsVector.size() / 2.0)));
	every3th.resize((ceil(skillsVector.size() / 3.0)));
	int val = -2;
	std::ranges::generate(every2th, [&] { return val += 2; });
	val = -3;
	std::ranges::generate(every3th, [&] { return val += 3; });

	testSpecifiedSkillsByIndex(first5);
	testSpecifiedSkillsByIndex(last5);
	testSpecifiedSkillsByIndex(every2th);
	testSpecifiedSkillsByIndex(every3th);

	generator->players[0] = oldPlayerZero;
	delete pl;
	return errors;
}