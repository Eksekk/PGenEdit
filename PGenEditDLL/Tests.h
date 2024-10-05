#pragma once
#include "main.h"
#include "PlayerStructAccessor.h"
#include "Generator.h"
#include "Utility.h"
#include "Asserter.h"
#include "GUI_tests.h"
#include "HookTests.h"
#include "LuaTests.h"
#include "ReflectionTests.h"
#include "UtilityFunctionTests.h"

extern Generator* generator;

class Tests
{
public:
	static Generator::State storedState;
	static bool testingNow; // to make game data not zero out party size when showing log message (modal, has own event loop)

	static std::vector<wxString> testSkillFunctions(); // join skill / split skill
	template<typename Player, typename Game>
	static std::vector<wxString> testClassGeneration(Player* player);

	template<typename Player, typename Game>
	static std::vector<wxString> testSkillsGeneration(Player* player);

	static std::vector<wxString> testJson();
	template<typename Player, typename Game>
	static std::vector<wxString> testPlayerStructAccessor();

	template<typename Player, typename Game>
	static std::vector<wxString> run();

	static std::vector<wxString> testMisc();

	static std::vector<wxString> runNonGameTests();
};

template<typename Player, typename Game>
std::vector<wxString> Tests::run()
{
	testingNow = true;
	auto ret = mergeVectors({ testMisc(), UtilityFunctionTests::run(), testSkillFunctions()/*, testJson()*/, GUI_tests::testGui<Player, Game>()
		, testPlayerStructAccessor<Player, Game>(), HookTests::run<Player, Game>(), LuaTests::run(), ReflectionTests::run()
	});
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
	for (size_t i = 0; i < tests.size(); ++i)
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
		wxLogWarning("Test data: %s", stringConcat(parts, ", "));
	}

	// for [getStat/setStat]-settable stats, either make new function similar to this one, but less templates and member pointers
	// or experiment with std::bind (wxwidgets says, I think, that you can bind free function to member function pointer - see Bind())
	
	// for resistances, iterate over each "enum" value, check if it's present in data from lua, and if yes, then test it
	// this takes care of elemental mod

	// LET'S GOOOOO
}

/*
Stuff generated by GPT-4 Turbo for testing with google test:

To create unit tests for the `getClassObjectPtrField` function, we need to consider the different scenarios that the function is expected to handle.We should test both the successful path where the property is found and the error cases where the property is not found or the instance is not a pointer.

	Here's an example of how you might write unit tests for this function using a hypothetical unit testing framework (e.g., Google Test for C++):

	```cpp
#include <gtest/gtest.h>
#include <rttr/registration>

	// Mock function to simulate luaError behavior
	void luaError(const std::string & message, const std::string & propertyName, const std::string & typeName)
{
	throw std::runtime_error(message);
}

// Mock function to simulate objectDoesNotHavePropertyLuaError behavior
void objectDoesNotHavePropertyLuaError(const std::string& typeName, const std::string& propertyName)
{
	throw std::runtime_error("Object of type '" + typeName + "' does not have property '" + propertyName + "'");
}

// Example class to use in tests
class MyClass
{
public:
	int myField;
};

// Register the class and its property with RTTR
RTTR_REGISTRATION{
	rttr::registration::class_<MyClass>("MyClass")
		.property("myField", &MyClass::myField);
}

	// Test fixture for setting up test environment
	class GetClassObjectPtrFieldTest : public ::testing::Test
{
protected:
	MyClass myObject;
	MyClass* myObjectPtr;
	rttr::variant instance;

	virtual void SetUp()
	{
		myObjectPtr = &myObject;
		instance = myObjectPtr;
	}
};

// Test case for successful retrieval of a property
TEST_F(GetClassObjectPtrFieldTest, GetValidProperty)
{
	rttr::property prop = getClassObjectPtrField(instance, "myField");
	ASSERT_TRUE(prop.is_valid());
	ASSERT_EQ(prop.get_name(), "myField");
}

// Test case for invalid property name
TEST_F(GetClassObjectPtrFieldTest, GetInvalidProperty)
{
	EXPECT_THROW({
		getClassObjectPtrField(instance, "nonExistentField");
		}, std::runtime_error);
}

// Test case for non-pointer instance
TEST_F(GetClassObjectPtrFieldTest, NonPointerInstance)
{
	rttr::variant nonPointerInstance = myObject;
	EXPECT_THROW({
		getClassObjectPtrField(nonPointerInstance, "myField");
		}, std::runtime_error);
}

// Main function to run all tests
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
```

	In this example, we use Google Test as the unit testing framework.We define a test fixture `GetClassObjectPtrFieldTest` to set up the common environment for each test case.We then write three test cases :

1. `GetValidProperty`: Tests that a valid property is successfully retrieved.
	2. `GetInvalidProperty`: Tests that an exception is thrown when an invalid property name is provided.
	3. `NonPointerInstance`: Tests that an exception is thrown when the instance is not a pointer.

	Please note that the `luaError` and `objectDoesNotHavePropertyLuaError` functions are mocked to throw exceptions instead of integrating with a Lua environment, as the actual implementation details are not provided.You would need to adjust these mocks to match the behavior of your actual error handling functions.
*/





