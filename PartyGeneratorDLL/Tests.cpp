#include "pch.h"
#include "main.h"
#include "Tests.h"
#include "PlayerSkill.h"
#include "GuiApplication.h"
#include <wx/notebook.h>
#include "GeneralPanel.h"
#include "DefaultPlayerPanel.h"
#include "PlayerPanel.h"
#include "globals.h"
#include "MainWindow.h"
#include "EditorMainWindow.h"
#include "EditorPlayerWindow.h"

extern Generator* generator;

Asserter::Asserter(std::vector<wxString>& errors, bool& failed) : errors(errors), failed(failed) {}

wxString rep(const wxString& str, int n)
{
	wxString ret = str;
	for (int i = 0; i < n - 1; ++i)
	{
		ret << str;
	}
	return ret;
}

std::vector<wxString> Tests::testAlignmentRadioBox()
{
	// need to pass nullptr!!! otherwise children of frame will be created as top level windows
	// and NtUserCreateWindowEx will fail with code 1406 (0x57E)
	wxFrame* w = new wxFrame(nullptr, wxID_ANY, "testFrame");
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	AlignmentRadioBox* b1 = new AlignmentRadioBox(w, "a"), *b2 = new AlignmentRadioBox(w, "b");
	myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment());
	b1->setSelection(ALIGNMENT_LIGHT);
	myassert(b1->getSelectedAlignment() != b2->getSelectedAlignment());
	b2->setSelection(ALIGNMENT_LIGHT);
	myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment());
	b1->setSelection(ALIGNMENT_ANY);
	b2->setSelection(ALIGNMENT_DARK);
	myassert(b1->getSelectedAlignment() != b2->getSelectedAlignment());

	for (const auto& str : AlignmentRadioBox::texts)
	{
		b1->setSelection(str);
		b2->setSelection(str);
		myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment(), str);
	}

	b1->SetSelection(AlignmentRadioBox::alignmentIndexes.find(ALIGNMENT_DARK)->second);
	b2->setSelection(ALIGNMENT_DARK);
	myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment());
	myassert(b1->GetSelection() == b2->GetSelection());
	w->Destroy();
	//delete b1, b2, w;
	return errors;
}

std::vector<wxString> Tests::testJson()
{
	static const std::string TEST_FILE_NAME = "class data tests.txt", ERROR_FILE_NAME = "class data errors.txt", OLD_ERROR_FILE_NAME = "old class data errors.txt";
	static const int TEST_AMOUNT = 25;
	// std::ios::in fails if file doesn't exist, even if std::ios::out is specified
	std::fstream errorFile(ERROR_FILE_NAME, std::ios::in);
	if (errorFile.is_open())
	{
		std::fstream(OLD_ERROR_FILE_NAME, std::ios::out | std::ios::trunc) << errorFile.rdbuf();
		errorFile.close();
	}
	else
	{
		errorFile.clear(); // remove failed open flags
	}
	errorFile.open(ERROR_FILE_NAME, std::ios::out | std::ios::trunc);
	if (!jsonErrors.empty())
	{
		wxString str = wxString::Format("Time: %s\nEntering %s(), %d old errors still present:\n\n%s\n\n\n", getTimeStr(), __FUNCTION__, jsonErrors.size(), concatWxStrings(jsonErrors, "\n"));
		errorFile << str;
		if (jsonErrors.size() <= 5)
		{
			wxLogError(str);
		}
		else
		{
			wxLogError("%d json errors written to error file", jsonErrors.size());
		}
		wxLog::FlushActive();
	}
	jsonErrors.clear();
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	std::fstream testFile;
	bool existed = true;
	Json testOut = Json::array(), existingJson;
	std::fstream oldTestsFile(TEST_FILE_NAME, std::ios::in);
	if (oldTestsFile.is_open() && std::filesystem::file_size(TEST_FILE_NAME) > 0)
	{
		try
		{
			existingJson = Json::parse(oldTestsFile);
		}
		catch (const nlohmann::json::exception& ex)
		{
			wxLogError("Error reading old tests file, generating new tests\nError description: %s", ex.what());
			wxLog::FlushActive();
			existed = false;
			testFile.open(TEST_FILE_NAME, std::ios::out | std::ios::trunc);
		}
	}
	else
	{
		existed = false;
		testFile.open(TEST_FILE_NAME, std::ios::out | std::ios::trunc);
	}
	unsigned int failedNum = 0;
	try
	{
		const size_t playerJsonSize = existingJson.size();
		for (int pl = 0; pl < MAX_PLAYERS; ++pl)
		{
			if (!existed || playerJsonSize <= pl)
			{
				testOut.push_back(Json::array());
			}
			auto& classes = generator->playerData[pl]->classes;
			Json copy;
			classes.writeToJson(copy);
			const size_t classJsonSize = playerJsonSize > pl ? existingJson[pl].size() : 0;
			for (int i = 0; i < TEST_AMOUNT; ++i)
			{
				Json j;
				if (existed && playerJsonSize > pl && classJsonSize > i)
				{
					classes.readFromJson(existingJson[pl][i]);
				}
				else
				{
					classes.randomize();
				}
				classes.writeToJson(j);
				if (!existed || classJsonSize <= i)
				{
					testOut[pl].push_back(j);
				}
				ClassGenerationData classes2(classes.index, classes.playerData);
				classes2.readFromJson(j);
				if (classes != classes2)
				{
					errorFile << wxString::Format("Test %d (player %d) failed\nResult json:\n%s\n\n", i, pl, j.dump(4) + "\n\n");
					++failedNum;
				}
			}
			classes.readFromJson(copy);
		}
		if (failedNum > 0)
		{
			wxLogInfo(wxString::Format("%d class json tests failed", failedNum));
			wxLog::FlushActive();
		}
		if (!existed)
		{
			testFile << testOut;
		}
	}
	catch (const std::exception& ex)
	{
		wxLogError(ex.what());
		wxLog::FlushActive();
	}
	if (!jsonErrors.empty())
	{
		wxString str = wxString::Format("Time: %s\nLeaving %s(), %d errors occurred:\n\n%s\n\n\n", getTimeStr(), __FUNCTION__, jsonErrors.size(), concatWxStrings(jsonErrors, "\n"));
		errorFile << str;
		if (jsonErrors.size() <= 5)
		{
			wxLogError(str);
		}
		else
		{
			wxLogError("%d json errors written to error file", jsonErrors.size());
		}
		wxLog::FlushActive();
		jsonErrors.clear();
	}
	return errors;
}

template<typename Player, typename Game>
std::vector<wxString> Tests::testGui()
{
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	auto tabs = wxGetApp().mainWindow->tabs;
	myassert(tabs->GetPageCount() == MainWindow::FIRST_PLAYER_PAGE + MAX_PLAYERS);
	myassert(dynamic_cast<GeneralPanel*>(tabs->GetPage(MainWindow::GENERAL_PANEL_PAGE)));
	auto defPanel = dynamic_cast<DefaultPlayerPanel*>(tabs->GetPage(MainWindow::DEFAULT_PLAYER_PAGE));
	if (myassert(defPanel) && defPanel != nullptr)
	{
		myassert(dynamic_cast<PlayerData*>(defPanel->linkedGenerationData));
	}
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		auto playerPanel = dynamic_cast<PlayerPanel*>(tabs->GetPage(i + MainWindow::FIRST_PLAYER_PAGE));
		myassert(playerPanel, wxString::Format("iteration %d", i));
		if (playerPanel)
		{
			myassert(playerPanel->linkedGenerationData, wxString::Format("iteration %d", i));
		}
	}

	// main editor window and player windows

	int oldCURRENT_PARTY_SIZE = CURRENT_PARTY_SIZE;
	CURRENT_PARTY_SIZE = MAX_PLAYERS;

	auto eWindow = wxGetApp().editorMainWindow;
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		eWindow->playerWindows[i]->Freeze();
		myassert(eWindow->playerWindows[i]->playerIndex == i, i, eWindow->playerWindows[i]->playerIndex);
		bool wasVisiblePreviously = eWindow->playerWindows[i]->IsShown();
		eWindow->playerWindows[i]->Hide();
		wxCommandEvent event(wxEVT_BUTTON, eWindow->playerButtonIds[i]);
		event.SetEventObject(eWindow);
		// THE ONLY WAY TO PROCESS EVENTS BOUND TO BUTTONS ETC AND HANDLED IN WINDOW
		// frame's ProcessEvent() doesn't work when event from button is bound to frame
		// and button's method is protected
		eWindow->playerButtons[i]->HandleWindowEvent(event);
		myassert(eWindow->playerWindows[i]->IsShown(), i);
		eWindow->playerWindows[i]->Show(wasVisiblePreviously);
		eWindow->playerWindows[i]->Thaw();
	}

	bool wasVisiblePreviously = eWindow->IsShown();
	eWindow->Show();
	wxCloseEvent event(wxEVT_CLOSE_WINDOW);
	// here process event works, because event is directly bound to frame (calling its Bind() method, not button's), also we friended "Tests" class
	eWindow->ProcessEvent(event);
	myassert(!eWindow->IsShown());
	eWindow->Show(wasVisiblePreviously);

	Player* player = new Player;
	memset(player, 0, sizeof(Player));
	void* oldPlayer = players[1];
	players[1] = player;

	auto oldName = playerAccessor->forPlayer(1)->getName();
	playerAccessor->setName("abcd");
	wxTimerEvent event2(*(eWindow->updateTimer));
	eWindow->ProcessEvent(event2);
	myassert(eWindow->playerButtons[1]->GetLabel() == "abcd", eWindow->playerButtons[1]->GetLabel());
	playerAccessor->setName(oldName);
	CURRENT_PARTY_SIZE = 3;
	eWindow->ProcessEvent(event2);
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		if (i < CURRENT_PARTY_SIZE)
		{
			myassert(eWindow->playerButtons[i]->GetLabel() == playerAccessor->forPlayer(i)->getName(), i, eWindow->playerButtons[i]->GetLabel(), playerAccessor->forPlayer(i)->getName());
		}
		myassert(i < CURRENT_PARTY_SIZE ? eWindow->playerButtons[i]->IsEnabled() : !eWindow->playerButtons[i]->IsEnabled(), i);
	}
	players[1] = oldPlayer;
	CURRENT_PARTY_SIZE = oldCURRENT_PARTY_SIZE;
	eWindow->ProcessEvent(event2);
	delete player;

	return mergeVectors({ errors, testAlignmentRadioBox() });
}

// explicit instantiation
template std::vector<wxString> Tests::testGui<mm6::Player, mm6::Game>();
template std::vector<wxString> Tests::testGui<mm7::Player, mm7::Game>();
template std::vector<wxString> Tests::testGui<mm8::Player, mm8::Game>();

template<typename Player, typename Game>
std::vector<wxString> Tests::testPlayerStructAccessor()
{
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);

	//static_assert(SAME(Player, mm7::Player), "Tests for other games not implemented yet");

	Player* pl = new Player;
	memset(pl, 0, sizeof(Player));
	int oldCURRENT_PARTY_SIZE = CURRENT_PARTY_SIZE;
	CURRENT_PARTY_SIZE = 1;

	//wxLogNull noLog;

	void* oldPlayerZero = players[0];
	players[0] = pl;
	(void)playerAccessor->forPlayer(0); // switch to player 0
	// full hp bonus, full sp bonus, ranged/melee attack/damage bonus
	if constexpr (SAME(Player, mm6::Player) || SAME(Player, mm7::Player))
	{
		pl->fullHPBonus = 50;
		pl->fullSPBonus = 122;
		myassert(playerAccessor->getStatBonus(STAT_HIT_POINTS_BONUS) == pl->fullHPBonus);
		myassert(playerAccessor->getStatBonus(STAT_SPELL_POINTS_BONUS) == pl->fullSPBonus);

		playerAccessor->setStatBonus(STAT_HIT_POINTS_BONUS, 100);
		playerAccessor->setStatBonus(STAT_SPELL_POINTS_BONUS, 44);
		myassert(playerAccessor->getStatBonus(STAT_HIT_POINTS_BONUS) == pl->fullHPBonus && pl->fullHPBonus == 100);
		myassert(playerAccessor->getStatBonus(STAT_SPELL_POINTS_BONUS) == pl->fullSPBonus && pl->fullSPBonus == 44);

		myassert(playerAccessor->getStatBonus(STAT_MELEE_ATTACK_BONUS) == 0);
		pl->meleeAttackBonus = 12;
		pl->meleeDamageBonus = 43;
		myassert(playerAccessor->getStatBonus(STAT_MELEE_ATTACK_BONUS) == 12);
		myassert(playerAccessor->getStatBonus(STAT_MELEE_DAMAGE_BONUS) == 43);
		playerAccessor->setStatBonus(STAT_MELEE_ATTACK_BONUS, playerAccessor->getStatBonus(STAT_MELEE_ATTACK_BONUS) + 34);
		myassert(playerAccessor->getStatBonus(STAT_MELEE_ATTACK_BONUS) == 12 + 34 && pl->meleeAttackBonus == 12 + 34);
		playerAccessor->setStatBonus(STAT_MELEE_ATTACK_BONUS, -5);
		myassert(playerAccessor->getStatBonus(STAT_MELEE_ATTACK_BONUS) == -5 && pl->meleeAttackBonus == -5);

		pl->rangedAttackBonus = -22;
		pl->rangedDamageBonus = 55;
		myassert(playerAccessor->getStatBonus(STAT_RANGED_ATTACK_BONUS) == -22);
		myassert(playerAccessor->getStatBonus(STAT_RANGED_DAMAGE_BONUS) == 55);
		playerAccessor->setStatBonus(STAT_RANGED_DAMAGE_BONUS, 115);
		myassert(playerAccessor->getStatBonus(STAT_RANGED_DAMAGE_BONUS) == 115 && pl->rangedDamageBonus == 115);
		playerAccessor->setStatBonus(STAT_RANGED_ATTACK_BONUS, playerAccessor->getStatBonus(STAT_RANGED_ATTACK_BONUS) + 55);
		myassert(playerAccessor->getStatBonus(STAT_RANGED_ATTACK_BONUS) == -22 + 55 && pl->rangedAttackBonus == -22 + 55);
		playerAccessor->setStatBonus(STAT_RANGED_DAMAGE_BONUS, playerAccessor->getStatBonus(STAT_RANGED_DAMAGE_BONUS) + 3);
		myassert(playerAccessor->getStatBonus(STAT_RANGED_DAMAGE_BONUS) == 115 + 3 && pl->rangedDamageBonus == 115 + 3);
	}

	// hp
	pl->HP = 24342;
	myassert(playerAccessor->getHp() == 24342);
	pl->HP = -5555555;
	myassert(playerAccessor->getHp() == -5555555);
	playerAccessor->setHp(543543);
	myassert(playerAccessor->getHp() == 543543 && pl->HP == 543543);
	playerAccessor->setHp(0);
	myassert(playerAccessor->getHp() == 0 && pl->HP == 0);

	// sp
	pl->SP = 24342;
	myassert(playerAccessor->getSp() == 24342);
	pl->SP = -5555555;
	myassert(playerAccessor->getSp() == -5555555);
	playerAccessor->setSp(543543);
	myassert(playerAccessor->getSp() == 543543 && pl->SP == 543543);
	playerAccessor->setSp(0);
	myassert(playerAccessor->getSp() == 0 && pl->SP == 0);

	// ac bonus
	myassert(playerAccessor->getStatBonus(STAT_ARMOR_CLASS) == 0);
	pl->armorClassBonus = 55;
	myassert(playerAccessor->getStatBonus(STAT_ARMOR_CLASS) == 55);
	playerAccessor->setStatBonus(STAT_ARMOR_CLASS, 24);
	myassert(playerAccessor->getStatBonus(STAT_ARMOR_CLASS) == 24 && pl->armorClassBonus == 24);

	// NEW CODE FOR EASIER TESTING (keeping old just in case new breaks)
	using namespace std::placeholders;

	// helper function (less typing!) which binds placeholders they receive to [get/set]StatBase method, so you can ultimately do:
	// testPrimaryStatBase(STAT_MIGHT, &Player::mightBase, "Might base");

	auto testStatBase = [pl, &myasserter](int statId, auto Player::* baseField, const wxString& logId) -> void
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
	auto testStatBonus = [pl, &myasserter](int statId, auto Player::* bonusField, const wxString& logId) -> void
	{
		std::function<int(void)> boundBonusGet{ std::bind(&PlayerStructAccessor::getStatBonus, playerAccessor, statId) };
		std::function<void(int)> boundBonusSet{ std::bind(&PlayerStructAccessor::setStatBonus, playerAccessor, statId, _1) };

		using IntegerType = std::decay_t<decltype(pl->*bonusField)>;
		static_assert(std::is_integral_v<IntegerType> && sizeof(IntegerType) <= 4, "Field type must be integer <= 4 bytes");
		testSettableField<Player, IntegerType>(pl, bonusField, boundBonusGet, boundBonusSet, boundsByType<IntegerType>, myasserter, logId);
	};

	auto testStatBaseBonus = [pl, &myasserter, &testStatBase, &testStatBonus](int statId, auto Player::* baseField, auto Player::* bonusField, const wxString& logId)
	{
		static_assert(std::is_same_v<std::decay_t<decltype(pl->*baseField)>, std::decay_t<decltype(pl->*bonusField)>>, "Integer types for base and bonus fields are different");
		testStatBase(statId, baseField, logId + " base");
		testStatBonus(statId, bonusField, logId + " bonus");
	};
	// NOT WORKING
	// auto bindGetBase = [](auto placeholderStatId) { return std::bind(&PlayerStructAccessor::getStatBase, playerAccessor, placeholderStatId); };
	// auto bindSetBase = [](auto placeholderStatId) { return std::bind(std::mem_fn(&PlayerStructAccessor::setStatBase), playerAccessor, placeholderStatId); };
	// std::function<void(int statId, int16_t Player::* field, const wxString& logId)> testPrimaryStatBase = std::bind(testSettableField<Player, int16_t>, pl, _2, bindGetBase(_1), bindSetBase(_1), getBounds(-2), myasserter, _3);


	// PRIMARY
	testStatBaseBonus(STAT_MIGHT, &Player::mightBase, &Player::mightBonus, "Might");
	testStatBaseBonus(STAT_INTELLECT, &Player::intellectBase, &Player::intellectBonus, "Intellect");
	testStatBaseBonus(STAT_PERSONALITY, &Player::personalityBase, &Player::personalityBonus, "Personality");
	testStatBaseBonus(STAT_ENDURANCE, &Player::enduranceBase, &Player::enduranceBonus, "Endurance");
	testStatBaseBonus(STAT_ACCURACY, &Player::accuracyBase, &Player::accuracyBonus, "Accuracy");
	testStatBaseBonus(STAT_SPEED, &Player::speedBase, &Player::speedBonus, "Speed");
	testStatBaseBonus(STAT_LUCK, &Player::luckBase, &Player::luckBonus, "Luck");

	// RESISTANCES
	if constexpr (SAME(Player, mm6::Player))
	{
		testStatBaseBonus(STAT_FIRE_RESISTANCE, &Player::fireResistanceBase, &Player::fireResistanceBonus, "Fire resistance");
		testStatBaseBonus(STAT_ELEC_RESISTANCE, &Player::elecResistanceBase, &Player::elecResistanceBonus, "Elec resistance");
		testStatBaseBonus(STAT_COLD_RESISTANCE, &Player::coldResistanceBase, &Player::coldResistanceBonus, "Cold resistance");
		testStatBaseBonus(STAT_POISON_RESISTANCE, &Player::poisonResistanceBase, &Player::poisonResistanceBonus, "Poison resistance");
		testStatBaseBonus(STAT_MAGIC_RESISTANCE, &Player::magicResistanceBase, &Player::magicResistanceBonus, "Magic resistance");
	}
	else
	{
		testStatBaseBonus(STAT_FIRE_RESISTANCE, &Player::fireResistanceBase, &Player::fireResistanceBonus, "Fire resistance");
		testStatBaseBonus(STAT_AIR_RESISTANCE, &Player::airResistanceBase, &Player::airResistanceBonus, "Air resistance");
		testStatBaseBonus(STAT_WATER_RESISTANCE, &Player::waterResistanceBase, &Player::waterResistanceBonus, "Water resistance");
		testStatBaseBonus(STAT_EARTH_RESISTANCE, &Player::earthResistanceBase, &Player::earthResistanceBonus, "Earth resistance");

		testStatBaseBonus(STAT_BODY_RESISTANCE, &Player::bodyResistanceBase, &Player::bodyResistanceBonus, "Body resistance");
		testStatBaseBonus(STAT_MIND_RESISTANCE, &Player::mindResistanceBase, &Player::mindResistanceBonus, "Mind resistance");
		testStatBaseBonus(STAT_SPIRIT_RESISTANCE, &Player::spiritResistanceBase, &Player::spiritResistanceBonus, "Spirit resistance");

		testStatBaseBonus(STAT_LIGHT_RESISTANCE, &Player::lightResistanceBase, &Player::lightResistanceBonus, "Light resistance");
		testStatBaseBonus(STAT_DARK_RESISTANCE, &Player::darkResistanceBase, &Player::darkResistanceBonus, "Dark resistance");
	}

	// mm6/7 bonus
	if constexpr (!SAME(Player, mm8::Player))
	{
		testStatBonus(STAT_MELEE_ATTACK_BONUS, &Player::meleeAttackBonus, "Melee attack bonus");
		testStatBonus(STAT_MELEE_DAMAGE_BONUS, &Player::meleeDamageBonus, "Melee damage bonus");
		testStatBonus(STAT_RANGED_ATTACK_BONUS, &Player::rangedAttackBonus, "Ranged attack bonus");
		testStatBonus(STAT_RANGED_DAMAGE_BONUS, &Player::rangedDamageBonus, "Ranged damage bonus");
		testStatBonus(STAT_HIT_POINTS_BONUS, &Player::fullHPBonus, "Full HP bonus");
		testStatBonus(STAT_SPELL_POINTS_BONUS, &Player::fullSPBonus, "Full SP bonus");
	}

	// other

	testStatBonus(STAT_ARMOR_CLASS, &Player::armorClassBonus, "Armor class bonus");
	testStatBaseBonus(STAT_LEVEL, &Player::levelBase, &Player::levelBonus, "Level");
	testStatBase(STAT_HIT_POINTS, &Player::hitPoints, "Hit points base");
	testStatBase(STAT_SPELL_POINTS, &Player::spellPoints, "Spell points base");

	testSettableField(pl, &Player::skillPoints, std::function<int(void)> { std::bind(&PlayerStructAccessor::getSkillPoints, playerAccessor) },
		std::function<void(int)>{ std::bind(&PlayerStructAccessor::setSkillPoints, playerAccessor, _1) },
		boundsByType<int32_t>, myasserter, "Skill points");

	auto testStringProperty = [pl, &myasserter](auto& array, std::function<std::string(void)> getter, std::function<void(const std::string&)> setter, size_t maxSize) -> void
	{
		static const auto randomString = [](size_t len) -> std::string
		{
			static const std::string keyspace = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
			// can't be const - error
			static std::mt19937 gen(std::random_device{}());
			// can't be const either - another error
			static std::uniform_int_distribution dist(0, (int)keyspace.size() - 1);
			std::string ret(len, '_');
			for (int i = 0; i < len; ++i)
			{
				ret[i] = keyspace[dist(gen)];
			}
			return ret;
		};
		const std::vector<size_t> sizes{ 0, 1, 3, 5, maxSize - 10, maxSize - 5, maxSize - 1, maxSize };
		for (int i = 0; i < sizes.size(); ++i)
		{
			const std::string oldVal{ array.data() };
			const std::string test = randomString(sizes[i]);
			wxASSERT(test.size() < array.size());
			setter(test);
			const std::string newVal = getter();

			const wxString failMsg = wxString::Format("Old: %s, new: %s", oldVal, test);
			if (oldVal != test)
			{
				myassert(oldVal != newVal, failMsg);
				myassert(test == newVal, failMsg);
			}
			else
			{
				myassert(newVal == oldVal, failMsg);
				myassert(test == newVal, failMsg);
			}

			memcpy(array.data(), oldVal.data(), oldVal.size());
			array[oldVal.size()] = 0;
			myassert(getter() == oldVal, failMsg);
		}
	};

	auto nameGetter = std::bind(&PlayerStructAccessor::getName, playerAccessor);
	auto nameSetter = std::bind(&PlayerStructAccessor::setName, playerAccessor, _1);

	testStringProperty(pl->name, nameGetter, nameSetter, playerAccessor->getNameMaxUsableLength());

	if constexpr (SAME(Player, mm8::Player))
	{
		auto biographyGetter = std::bind(&PlayerStructAccessor::getBiography, playerAccessor);
		auto biographySetter = std::bind(&PlayerStructAccessor::setBiography, playerAccessor, _1);

		testStringProperty(pl->biography, biographyGetter, biographySetter, playerAccessor->getBiographyMaxUsableLength());
	}

	auto expTest = [pl, &myasserter](int64_t exp, int level)
	{
		pl->experience = exp;
		auto expLevelMsg = "Exp %lld, level %d";
		myassert(playerAccessor->getMinimumLevelForExperience(exp) == level, wxString::Format(expLevelMsg, exp, playerAccessor->getMinimumLevelForExperience(exp))); // can also call static methods on objects (but they don't get "this" param)
		myassert(playerAccessor->getTrainableLevel() == level);
		playerAccessor->setExperience(0);
		myassert(playerAccessor->getLevel() == 1, wxString::Format("Level %d", playerAccessor->getLevel()));
		myassert(playerAccessor->getStatBase(STAT_LEVEL) == 1, wxString::Format("Level %d", playerAccessor->getLevel()));
		playerAccessor->setLevel(level);
		myassert(playerAccessor->getStatBase(STAT_LEVEL) == level, wxString::Format("Level %d", playerAccessor->getLevel()));
		myassert(playerAccessor->getMinimumLevelForExperience(exp) == level, wxString::Format(expLevelMsg, exp, playerAccessor->getMinimumLevelForExperience(exp)));
		myassert(playerAccessor->getTrainableLevel() == level, wxString::Format("Level %d, trainable %d", playerAccessor->getLevel(), playerAccessor->getTrainableLevel()));
		pl->experience = exp;
		myassert(playerAccessor->getExperience() == exp, wxString::Format("Getter exp %lld, test value %lld", playerAccessor->getExperience(), exp));
	};
	expTest(999, 1);
	expTest(1000, 2);
	expTest(1001, 2);
	expTest(2999, 2);
	expTest(3000, 3);
	expTest(4777, 3);
	expTest(6000, 4);
	expTest(11111, 5);

	// skills (not stat-like ones, but full-fledged)
	auto& skillsMap = GameData::skills;
	myassert(skillsMap.size() > 10);
	// try 5 first, 5 last, every 3th and every 2th
	std::vector<PlayerSkill*> skillsVector;
	skillsVector.reserve(skillsMap.size());
	std::transform(skillsMap.begin(), skillsMap.end(), std::back_inserter(skillsVector), [](auto& pair) -> PlayerSkill* { return &pair.second; });
	std::sort(skillsVector.begin(), skillsVector.end(), [](PlayerSkill* a, PlayerSkill* b) -> bool { return a->id < b->id; });
	myassert(skillsVector[5]->id == 5);
	auto randomSkillValue = [](int id) -> SkillValue
	{
		std::mt19937 gen(id); // seed with id to get consistent values
		std::uniform_int_distribution mDist(0, (int)MAX_MASTERY), sDist(0, (1 << SKILL_BITS) - 1);
		assert(mDist.b() >= MASTERY_MASTER && sDist.b() >= 63);
		return SkillValue{ sDist(gen), mDist(gen) };
	};
	auto testSpecifiedSkillsByIndex = [&randomSkillValue, &myasserter, &skillsMap, &skillsVector, pl](const std::vector<int>& skillIdsToChange) -> void
	{
		std::vector<PlayerSkillValue> skillsToSet;
		std::vector<bool> changed;
		for (int i : skillIdsToChange)
		{
			skillsToSet.push_back(PlayerSkillValue{ skillsVector[i], randomSkillValue(i) });
			changed.push_back(skillsToSet.back().value != playerAccessor->getSkill(i));
		}
		auto oldSkills = playerAccessor->getSkills();
		playerAccessor->setSkills(skillsToSet);
		auto newSkills = playerAccessor->getSkills();
		for (int skillId = 0; skillId < skillsVector.size(); ++skillId)
		{
			const wxString iterationStr = wxString::Format("Iteration %d, skill name: %s, old value: %s, new value: %s", skillId,
				skillsMap.at(skillId).name, oldSkills[skillId].value.toString(), newSkills[skillId].value.toString());

			// if skill was intended to change:
			//	1. old value must not be equal to new value from accessor
			//	2. as above, but raw new value (access player struct)
			//	3. new value from accessor must be equal to raw value
			// else:
			//	4. old == new (accessor)
			//	5. old == new (raw)
			//	6. see point 3

			int index = indexInVector(skillIdsToChange, skillId);
			if (index != -1 && changed[index]) // 1, 2, 3
			{
				// need to have explicitly defined operator !=, even if == is defined, otherwise there are ambiguity errors
				// TODO use map, not vector?
				myassert(oldSkills[skillId].value != newSkills[skillId].value, iterationStr); // 1
				myassert(oldSkills[skillId].value != splitSkill(pl->skills[skillId]), iterationStr); // 2
				myassert(newSkills[skillId].value == splitSkill(pl->skills[skillId]), iterationStr); // 3
			}
			else // 4, 5, 6
			{
				myassert(oldSkills[skillId].value == newSkills[skillId].value, iterationStr); // 4
				myassert(oldSkills[skillId].value == splitSkill(pl->skills[skillId]), iterationStr); // 5
				myassert(newSkills[skillId].value == splitSkill(pl->skills[skillId]), iterationStr); // 6
			}
		}
	};

	int s = skillsMap.size();
	std::vector<int> first5({ 0, 1, 2, 3, 4 }), last5({ s - 5, s - 4, s - 3, s - 2, s - 1 });
	std::vector<int> every2th, every3th;
	every2th.resize((ceil(skillsVector.size() / 2.0)));
	every3th.resize((ceil(skillsVector.size() / 3.0)));
	int val = -2;
	std::ranges::generate(every2th, [&]() mutable { return val += 2; });
	val = -3;
	std::ranges::generate(every3th, [&]() mutable { return val += 3; });

	testSpecifiedSkillsByIndex(first5);
	testSpecifiedSkillsByIndex(last5);
	testSpecifiedSkillsByIndex(every2th);
	testSpecifiedSkillsByIndex(every3th);

	/*
		/*enum ClassConstraint
		{
			CLASS_CONSTRAINT_NONE = 0,
			CLASS_CONSTRAINT_CURRENT_CLASS,
			CLASS_CONSTRAINT_ANY_PROMOTION_CLASS
		};
		struct SkillOptions
		{
			bool affectSkillpoints, allowNegativeSkillpoints, affectGold, allowNegativeGold;
			ClassConstraint classConstraint;
			std::vector<SkillCategory> affectWhichSkillCategories;

			SkillOptions() : affectSkillpoints(false), allowNegativeSkillpoints(false), affectGold(false), allowNegativeGold(false),
				classConstraint(CLASS_CONSTRAINT_NONE), affectWhichSkillCategories({ SKILLCAT_WEAPON, SKILLCAT_ARMOR, SKILLCAT_MAGIC, SKILLCAT_MISC }) {}
		};
		virtual bool setSkills(const std::vector<PlayerSkillValue>& values, const SkillOptions& options = SkillOptions()) = 0;
		virtual bool setSkill(PlayerSkill* skill, SkillValue value, const SkillOptions& options = SkillOptions()) = 0;
		virtual bool setSkill(int skillId, SkillValue value, const SkillOptions& options = SkillOptions()) = 0;
		[[nodiscard]] virtual Mastery getSkillMaxMastery(PlayerSkill* skill, const SkillOptions& options = SkillOptions()) = 0;
		[[nodiscard]] virtual std::unordered_map<PlayerSkill*, Mastery> getSkillMaxMasteries(const std::vector<PlayerSkill*>& skills, const SkillOptions& options = SkillOptions()) = 0;*/
	PlayerStructAccessor::SkillOptions opt;
	opt.affectSkillpoints = true;
	myassert(!playerAccessor->setSkill(3, { 4, 2 }, opt));
	myassert(!playerAccessor->setSkill(5, { 20, 3 }, opt));
	myassert(playerAccessor->setSkill(5, { 1, 1 }, opt));
	myassert(playerAccessor->setSkill(5, { 0, 1 }, opt));
	// extra parentheses are required because otherwise preprocessor interprets "," as next macro argument
	myassert((playerAccessor->getSkill(5) == SkillValue{ 0, 0 }));
	opt.allowNegativeSkillpoints = true;
	myassert(playerAccessor->setSkill(10, { 5, 4 }, opt));
	myassert(playerAccessor->getSkillPoints() == -14);
	myassert(playerAccessor->setSkill(10, { 3, 4 }, opt));
	myassert((playerAccessor->getSkill(10) == SkillValue{ 3, 4 }));
	myassert(playerAccessor->getSkillPoints() == -9);
	myassert(playerAccessor->setSkill(12, { 2, 4 }, opt));
	myassert(playerAccessor->getSkillPoints() == -11);
	myassert((playerAccessor->getSkill(12) == SkillValue{ 2, 4 }));
	auto& sk = GameData::skills;
	std::vector<PlayerSkillValue> skillsToSet{ { &sk.at(10), {1, 1} }, { &sk.at(20), {6, 2} }, {&sk.at(2), {2, 3} } };
	const int SP = 5000;
	playerAccessor->setSkillPoints(SP);
	playerAccessor->setSkills(skillsToSet, opt);
	std::for_each(skillsToSet.begin(), skillsToSet.end(), [&myasserter](const PlayerSkillValue& psv)
		{
			myassert(playerAccessor->getSkill(psv.skill) == psv.value, psv.skill->name, playerAccessor->getSkill(psv.skill), psv.value);
		});
	myassert(playerAccessor->getSkillPoints() == SP + 5 - 20 - 2);
	// TODO: more tests, preferably some automated automated testing (use lambdas to perform one test and then supply multiple of them)

	// bits 0-3 - booleans
	// bits 4-7 - affect what
	// bits 8-9 - class constraint
	auto getOptionsFromNumber = [](int n) -> PlayerStructAccessor::SkillOptions
	{
		PlayerStructAccessor::SkillOptions opt;
		opt.affectSkillpoints = n & 0b1;
		opt.allowNegativeSkillpoints = n & 0b10;
		opt.affectGold = n & 0b100;
		opt.allowNegativeGold = n & 0b1000;
		for (int i = 4; i <= 7; ++i)
		{
			if (n & (1 << i))
			{
				opt.batchSetAffectWhichSkillCategories.push_back((SkillCategory)(i - 4));
			}
		}
		opt.classConstraint = static_cast<PlayerStructAccessor::ClassConstraint>((n & 0b11'0000'0000) >> 8);
		return opt;
	};
	
	int gameGold = 500000;
	auto testSkillFunctions = [pl, &myasserter, &gameGold](int testId, const std::unordered_map<PlayerSkill*, SkillValue>& setWhat, int gold, int skillpoints, const PlayerStructAccessor::SkillOptions& options) -> void
	{
		playerAccessor->setSkillPoints(skillpoints);
		for (const auto& [skillPtr, value] : setWhat)
		{
			int prevGold = gameGold;
			int prevSkillpoints = playerAccessor->getSkillPoints();
			int expectedGoldChange = skillPtr->getFullTrainCostForMastery((Mastery)value.mastery) - skillPtr->getFullTrainCostForMastery(playerAccessor->getSkill(skillPtr).mastery);
			int expectedSkillpointsChange = skillpointsSpentForSkill(value) - skillpointsSpentForSkill(playerAccessor->getSkill(skillPtr));
			bool success = playerAccessor->setSkill(skillPtr, value);
			std::vector<wxString> failReasons;
			if (options.affectGold && !options.allowNegativeGold && prevGold < expectedGoldChange)
			{
				failReasons.push_back(
					wxString::Format(
						"Test #%d should fail (partially), because gold is affected, negative not allowed, and "
						"current gold (%d) was less than required gold (%d) for skill %s",
						testId, prevGold, expectedGoldChange, skillPtr->name
					)
				);
			}
			if (options.affectSkillpoints && !options.allowNegativeSkillpoints && prevSkillpoints < expectedSkillpointsChange)
			{
				failReasons.push_back(
					wxString::Format(
						"Test #%d should fail (partially), because skillpoints are affected, negative not allowed, and "
						"current skillpoints (%d) were less than required skillpoints (%d) for skill %s (level: %s)",
						testId, prevSkillpoints, expectedSkillpointsChange, skillPtr->name, value.toString()
					)
				);
			}
			Mastery masteryConstrainedByClass = MAX_MASTERY;
			if (options.classConstraint == PlayerStructAccessor::CLASS_CONSTRAINT_NONE)
			{
				masteryConstrainedByClass = MAX_MASTERY;
			}
			else if (options.classConstraint == PlayerStructAccessor::CLASS_CONSTRAINT_CURRENT_CLASS)
			{
				masteryConstrainedByClass = playerAccessor->getClassPtr()->maximumSkillMasteries.at(skillPtr->id);
			}
			else
			{
				// nothing, idk if repeating code from accessor is a good idea
			}
			static const std::string constraintNames[] = {"none", "current class", "any promotion class"};
			if (value.mastery > (int)masteryConstrainedByClass && playerAccessor->getSkill(skillPtr).mastery > masteryConstrainedByClass)
			{
				failReasons.push_back(
					wxString::Format(
						"Test #%d should fail (partially), because class constraint (\"%s\") is not satisfied - "
						"maximum mastery is %d, new mastery is %d",
						testId, constraintNames[(int)options.classConstraint], (int)masteryConstrainedByClass, playerAccessor->getSkill(skillPtr).mastery
					)
				);
			}
		}
	};

	players[0] = oldPlayerZero;
	delete pl;
	CURRENT_PARTY_SIZE = oldCURRENT_PARTY_SIZE;
	return errors;
}

template std::vector<wxString> Tests::testPlayerStructAccessor<mm6::Player, mm6::Game>();
template std::vector<wxString> Tests::testPlayerStructAccessor<mm7::Player, mm7::Game>();
template std::vector<wxString> Tests::testPlayerStructAccessor<mm8::Player, mm8::Game>();

#pragma warning(push)
#pragma warning(disable: 6001)
#pragma warning(disable: 4700)// definitely initialized in dllApi.cpp, and if not I'll just get a segfault and fix it
// (I test with low level debugger on at all time, so should be easy
template<typename Player, typename Game>
std::vector<wxString> Tests::testMisc()
{
	std::vector<wxString> errors;
	bool failed;
	Asserter myasserter(errors, failed);
	Player** players = (Player**)players;
	for (int i = 0; i < MAX_PLAYERS; ++i) // TODO: player count can be different in mm8
	{

	}

	// bounds check
	//wxLogNull noLog;
	bool old = wxLog::EnableLogging(false);

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

	wxLog::EnableLogging(old);

	return errors;
}
#pragma warning(pop)

template std::vector<wxString> Tests::testMisc<mm6::Player, mm6::Game>();
template std::vector<wxString> Tests::testMisc<mm7::Player, mm7::Game>();
template std::vector<wxString> Tests::testMisc<mm8::Player, mm8::Game>();

std::vector<wxString> Tests::testSkillFunctions()
{
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	auto old1 = SKILL_COMBINE_MODE;
	auto old2 = MASTERY_BITS;
	auto old3 = SKILL_BITS;

	// rules as in mm7+
	SKILL_COMBINE_MODE = BIT_PER_MASTERY;
	MASTERY_BITS = { -1, -1, 6, 7, 8 };
	SKILL_BITS = 6;

	myassert(joinSkill({ 5, 2 }) == 0b1000101);
	myassert(joinSkill({ 10, 2 }) == 0b1001010);
	myassert(joinSkill({ 1, 4 }) == 0b100000001);
	myassert(joinSkill({ 0, 4 }) == 0b0);
	myassert(joinSkill({ 63, 4 }) == 0b100111111);
	myassert(joinSkill({ 15, 3 }) == 0b10001111);
	myassert(joinSkill({ 1, 3 }) == 0b10000001);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 0, 2 }) == 0b0);

	MASTERY_BITS = { -1, -1, 13, 14, 16 };
	SKILL_BITS = 10;
	myassert(joinSkill({ 3, 1 }) == 0b11);
	myassert(joinSkill({ 10, 2 }) == 0b10000000001010);
	myassert(joinSkill({ 512, 4 }) == 0b10000001000000000);
	myassert(joinSkill({ 63, 1 }) == 0b111111);
	myassert(joinSkill({ 25, 3 }) == 0b100000000011001);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 55, 4 }) == 0b10000000000110111);
	myassert(joinSkill({ 0, 4 }) == 0b0);

	SKILL_COMBINE_MODE = PACKED;
	SKILL_BITS = 4;
	myassert(joinSkill({ 3, 1 }) == 0b11);
	myassert(joinSkill({ 12, 3 }) == 0b101100);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 15, 4 }) == 0b111111);
	myassert(joinSkill({ 2, 3 }) == 0b100010);
	myassert(joinSkill({ 0, 4 }) == 0b0);
	myassert(joinSkill({ 3, 3 }) == 0b100011);
	myassert(joinSkill({ 2, 4 }) == 0b110010);

	SKILL_BITS = 6; // like in mm6
	myassert(joinSkill({ 3, 1 }) == 0b11);
	myassert(joinSkill({ 12, 3 }) == 0b10001100);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 4, 1 }) == 0b100);
	myassert(joinSkill({ 63, 1 }) == 0b111111);
	myassert(joinSkill({ 63, 4 }) == 0b11111111);
	myassert(joinSkill({ 12, 3 }) == 0b10001100);
	myassert(joinSkill({ 0, 3 }) == 0b0);
	myassert(joinSkill({ 1, 3 }) == 0b10000001);

	SKILL_COMBINE_MODE = BIT_PER_MASTERY;
	MASTERY_BITS = { -1, -1, 6, 7, 8 };
	SKILL_BITS = 6;
	// rules as in mm7+

	myassert(splitSkill(0b1000101) == SkillValue({ 5, 2 }));
	myassert(splitSkill(0b1001010) == SkillValue({ 10, 2 }));
	myassert(splitSkill(0b100000001) == SkillValue({ 1, 4 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));
	myassert(splitSkill(0b100111111) == SkillValue({ 63, 4 }));
	myassert(splitSkill(0b10001111) == SkillValue({ 15, 3 }));
	myassert(splitSkill(0b10000001) == SkillValue({ 1, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));

	MASTERY_BITS = { -1, -1, 13, 14, 16 };
	SKILL_BITS = 10;
	myassert(splitSkill(0b11) == SkillValue({ 3, 1 }));
	myassert(splitSkill(0b10000000001010) == SkillValue({ 10, 2 }));
	myassert(splitSkill(0b10000001000000000) == SkillValue({ 512, 4 }));
	myassert(splitSkill(0b111111) == SkillValue({ 63, 1 }));
	myassert(splitSkill(0b100000000011001) == SkillValue({ 25, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b10000000000110111) == SkillValue({ 55, 4 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));

	SKILL_COMBINE_MODE = PACKED;
	SKILL_BITS = 4;
	myassert(splitSkill(0b11) == SkillValue({ 3, 1 }));
	myassert(splitSkill(0b101100) == SkillValue({ 12, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b111111) == SkillValue({ 15, 4 }));
	myassert(splitSkill(0b100010) == SkillValue({ 2, 3 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));
	myassert(splitSkill(0b100011) == SkillValue({ 3, 3 }));
	myassert(splitSkill(0b110010) == SkillValue({ 2, 4 }));

	SKILL_BITS = 6; // like in mm6
	myassert(splitSkill(0b11) == SkillValue({ 3, 1 }));
	myassert(splitSkill(0b10001100) == SkillValue({ 12, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b100) == SkillValue({ 4, 1 }));
	myassert(splitSkill(0b111111) == SkillValue({ 63, 1 }));
	myassert(splitSkill(0b11111111) == SkillValue({ 63, 4 }));
	myassert(splitSkill(0b10001100) == SkillValue({ 12, 3 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));
	myassert(splitSkill(0b10000001) == SkillValue({ 1, 3 }));

	// restore old values
	std::tie(SKILL_COMBINE_MODE, MASTERY_BITS, SKILL_BITS) = std::make_tuple(old1, old2, old3);

	return errors;
}