#include "pch.h"
#include "GUI_tests.h"
#include "Asserter.h"
#include "AlignmentRadioBox.h"
#include "GuiApplication.h"
#include "EditorMainWindow.h"
#include "EditorPlayerWindow.h"
#include "EditorSkillsPanel.h"
#include "AutoBackup.h"
#include <wx/spinctrl.h>
#include <wx/uiaction.h>
#include "PartyStructAccessor.h"
#include "PlayerStructAccessor.h"
#include "GameData.h"
#include <wx/notebook.h>
#include "GeneralPanel.h"
#include "DefaultPlayerPanel.h"
#include "PlayerPanel.h"
#include "PlayerData.h"
#include "EditorStatisticsPanel.h"
#include "MainWindow.h"
#include "GuiTestHelper.h"
#include "NotebookReplaceableTabs.h"
#include "PrimaryStatWidget.h"

std::vector<wxString> GUI_tests::testAlignmentRadioBox()
{
	// need to pass nullptr!!! otherwise children of frame will be created as top level windows
	// and NtUserCreateWindowEx will fail with code 1406 (0x57E)
	wxFrame* w = new wxFrame(nullptr, wxID_ANY, "testFrame");
	Asserter myasserter("Alignment radio box");
	AlignmentRadioBox* b1 = new AlignmentRadioBox(w, "a"), * b2 = new AlignmentRadioBox(w, "b");
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
	return myasserter.errors;
}

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testEditorSkillsPanel()
{
	auto party = Game::party;
	GameData::updateIsInGameAndPartySize();
	auto eWindow = wxGetApp().editorMainWindow;
	Asserter myasserter("editor skills panel");

	int index = std::min(2, std::max(CURRENT_PARTY_SIZE - 1, 0));
	Player* pl = reinterpret_cast<Player*>(playersInParty[index]);
	// have to use original player addresses because changing them for mmextension is tricky
	AutoBackup backup(CURRENT_PARTY_SIZE, *pl);
	// PARTY SIZE IS 0 BEFORE
	CURRENT_PARTY_SIZE = index + 1;
	memset(pl, 0, sizeof(Player));
	(void)playerAccessor->forPlayer(index);
	wxUIActionSimulator sim;

	// actual test code
    EditorPlayerWindow* window = eWindow->createPlayerWindow(index);
    window->tabs->SetSelection(PlayerWindowPanelType::SKILLS_PANEL_INDEX);
	myassert(window);
	if (!window)
	{
		return myasserter.errors;
	}
	EditorSkillsPanel* panel = dynamic_cast<EditorSkillsPanel*>(window->tabs->GetCurrentPage());
	GuiTestHelper helper(*panel, sim, myasserter);
	window->Show();
	helper.autoClick(panel->affectAvailableSkillpointsCheckbox);
	myassert(panel->options.affectSkillpoints);
	myassert(panel->allowNegativeSkillpointsRadio->IsEnabled());
	myassert(panel->dontAllowSpendingMoreThanAvailableSkillpointsRadio->IsEnabled());
	helper.autoClick(panel->dontAllowSpendingMoreThanAvailableSkillpointsRadio);
	myassert(!panel->options.allowNegativeSkillpoints);
	helper.autoClick(panel->affectAvailableSkillpointsCheckbox);
	myassert(!panel->options.affectSkillpoints);
	myassert(!panel->dontAllowSpendingMoreThanAvailableSkillpointsRadio->IsEnabled());

	int val;
	panel->goldDisplayText->GetValue().ToInt(&val);
	myassert(partyAccessor->getGold() == val);
	int oldGold = partyAccessor->getGold();
	partyAccessor->setGold(val + 43437);
	panel->updateFromPlayerData();
	panel->goldDisplayText->GetValue().ToInt(&val);
	myassert(val == partyAccessor->getGold());

	myassert(panel->availableSkillPointsAmount->GetValue() == playerAccessor->getSkillPoints());
	playerAccessor->setSkillPoints(500053);
	panel->updateFromPlayerData();
	myassert(panel->availableSkillPointsAmount->GetValue() == playerAccessor->getSkillPoints());
	helper.autoText(panel->availableSkillPointsAmount, "34237");
	panel->updateFromPlayerData();
	myassert(panel->availableSkillPointsAmount->GetValue() == 34237);

	playerAccessor->setSkill(5, SkillValue{ 4, 2 });
	panel->updateFromPlayerData();
	panel->spentSkillPointsValue->GetValue().ToInt(&val);
	myassert(val == 9);

	std::vector<PlayerSkill*> doNotGenerateSkills;
	for (auto& [id, skill] : GameData::skills)
	{
		if (skill.doNotGenerate)
		{
			doNotGenerateSkills.push_back(&skill);
		}
	}
	if (doNotGenerateSkills.size() > 0)
	{
		PlayerSkill* skill = doNotGenerateSkills.front();
		auto widget = panel->widgetToSkillMap.at(skill);
		myassert(!widget->IsShown(), skill->name);
		helper.autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(widget->IsShown(), skill->name);
		helper.autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(!widget->IsShown(), skill->name);
		helper.autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(widget->IsShown(), skill->name);
	}
	else
	{
		wxLogWarning("Not found any \"do not generate\" skill");
	}

	for (auto list = { 2, 5, 8, 22, 23 }; int i : list)
	{
		// level
		PlayerSkill* skill = &GameData::skills.at(i);
		auto* widget = panel->widgetToSkillMap.at(skill);
		helper.autoText(widget->skillLevel, "23");
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 23, 1 }), i);
		helper.autoText(widget->skillLevel, "4");
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 4, 1 }), i);
		helper.autoClick(widget->skillLevel);

		// mastery choice
		i += 2; // different skill
		skill = &GameData::skills.at(i);
		widget = panel->widgetToSkillMap.at(skill);
		// down arrow DOESN'T ADVANCE SELECTION INDEX
		
		// PROBLEM
		/*
		 // We prefer to exactly emulate what a(keyboard) user would do, so prefer
		 // to emulate selecting the first item of the control if possible (this
		 // works with wxChoice, wxListBox and wxComboBox with wxCB_READONLY style
		 // under MSW).
			 if (container->GetSelection() != 0)
			 {
				 Char(WXK_HOME);
				 wxYield();

				 // But if this didn't work, set the selection programmatically.
				 if (container->GetSelection() != 0)
					 container->SetSelection(0);
			 }
		 **/
		helper.autoSelect(widget->skillMastery, "Master");
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 1, 3 }), i - 2);
		helper.autoSelect(widget->skillMastery, "None");
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 0, 0 }), i - 2);
	}

	// class constraints
	helper.autoClick(panel->classConstraintsCurrentClass);
	myassert(panel->options.classConstraint == PlayerStructAccessor::CLASS_CONSTRAINT_CURRENT_CLASS);
	helper.autoClick(panel->classConstraintsNone);
	myassert(panel->options.classConstraint == PlayerStructAccessor::CLASS_CONSTRAINT_NONE);

	helper.autoClick(panel->classConstraintsCurrentClass);
	Mastery m = playerAccessor->getSkillMaxMastery(5);
	playerAccessor->setSkill(5, { 33, 4 });
	panel->updateFromPlayerData();
	helper.autoClick(panel->applyClassConstraintsButton);
	myassert(playerAccessor->getSkill(5).mastery <= m);
	helper.autoClick(panel->classConstraintsNone);

	// affect armor/weapons/...
	helper.autoClick(panel->affectArmorCheckbox);
	helper.autoClick(panel->affectWeaponsCheckbox);
	helper.autoClick(panel->affectMiscCheckbox);
	myassert(
		!existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_ARMOR)
		&& !existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_WEAPON)
		&& !existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_MISC)
	);
	helper.autoClick(panel->affectArmorCheckbox);
	helper.autoClick(panel->affectWeaponsCheckbox);
	helper.autoClick(panel->affectMiscCheckbox);
	myassert(
		existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_ARMOR)
		&& existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_WEAPON)
		&& existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_MISC)
	);

	// set all skills to
	panel->setAllSkillsToLevelSpinCtrl->SetValue(33);
	panel->setAllSkillsToMasteryChoice->SetSelection(2); // expert
	helper.autoClick(panel->setAllSkillsToButton);
	myassert(playerAccessor->getSkill(3) == (SkillValue{ 33, 2 }));
	myassert(playerAccessor->getSkill(9) == (SkillValue{ 33, 2 }));

	// god mode
	helper.autoClick(panel->godModeButton);
	myassert(playerAccessor->getSkill(11).mastery == MASTERY_GM);
	myassert(playerAccessor->getSkill(27).level == MAX_SKILL_LEVEL);

	// only already learned - skip (not using variable to keep track of it)

	eWindow->destroyPlayerWindow(index);
	return myasserter.errors;
}

template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm8::Player, mm8::Game>();

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testGui()
{
	Asserter myasserter("GUI");
	// LATER (party generator window not created yet)
// 	auto tabs = wxGetApp().mainWindow->tabs;
// 	myassert(tabs->GetPageCount() == MainWindow::FIRST_PLAYER_PAGE + MAX_PLAYERS);
// 	myassert(dynamic_cast<GeneralPanel*>(tabs->GetPage(MainWindow::GENERAL_PANEL_PAGE)));
// 	auto defPanel = dynamic_cast<DefaultPlayerPanel*>(tabs->GetPage(MainWindow::DEFAULT_PLAYER_PAGE));
// 	if (myassert(defPanel) && defPanel != nullptr)
// 	{
// 		myassert(dynamic_cast<PlayerData*>(defPanel->linkedGenerationData));
// 	}
// 	for (int i = 0; i < MAX_PLAYERS; ++i)
// 	{
// 		auto playerPanel = dynamic_cast<PlayerPanel*>(tabs->GetPage(i + MainWindow::FIRST_PLAYER_PAGE));
// 		myassert(playerPanel, wxString::Format("iteration %d", i));
// 		if (playerPanel)
// 		{
// 			myassert(playerPanel->linkedGenerationData, wxString::Format("iteration %d", i));
// 		}
// 	}

	// main editor window and player windows

	auto eWindow = wxGetApp().editorMainWindow;
	// DISABLED BECAUSE BLINKING WINDOWS ARE ANNOYING
// 	for (int i = 0; i < MAX_PLAYERS; ++i)
// 	{
// 		eWindow->playerWindows[i]->Freeze();
// 		myassert(eWindow->playerWindows[i]->playerIndex == i, i, eWindow->playerWindows[i]->playerIndex);
// 		bool wasVisiblePreviously = eWindow->playerWindows[i]->IsShown();
// 		eWindow->playerWindows[i]->Hide();
// 		wxCommandEvent event(wxEVT_BUTTON, eWindow->playerButtonIds[i]);
// 		event.SetEventObject(eWindow);
// 		// THE ONLY WAY TO PROCESS EVENTS BOUND TO BUTTONS ETC AND HANDLED IN WINDOW
// 		// frame's ProcessEvent() doesn't work when event from button is bound to frame
// 		// and button's method is protected
// 		eWindow->playerButtons[i]->HandleWindowEvent(event);
// 		myassert(eWindow->playerWindows[i]->IsShown(), i);
// 		eWindow->playerWindows[i]->Show(wasVisiblePreviously);
// 		eWindow->playerWindows[i]->Thaw();
// 	}
// 
// 	bool wasVisiblePreviously = eWindow->IsShown();
// 	eWindow->Show();
// 	wxCloseEvent event(wxEVT_CLOSE_WINDOW);
// 	// here process event works, because event is directly bound to frame (calling its Bind() method, not button's), also we friended "Tests" class
// 	eWindow->ProcessEvent(event);
// 	myassert(!eWindow->IsShown());
// 	eWindow->Show(wasVisiblePreviously);

	Player* player = new Player;
	memset(player, 0, sizeof(Player));
	int index = std::min(1, std::max(CURRENT_PARTY_SIZE - 1, 0));
	AutoBackup b(playersInParty[index]);
	playersInParty[index] = player;

	auto oldName = playerAccessor->forPlayer(index)->getName();
	playerAccessor->setName("abcd");
	wxTimerEvent event2(*(eWindow->updateTimer));
	eWindow->ProcessEvent(event2);
	myassert(eWindow->playerButtons[index]->GetLabel() == "abcd", eWindow->playerButtons[index]->GetLabel());
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

	eWindow->ProcessEvent(event2);

	auto playerWindow = eWindow->playerWindows[index];

	delete player;

	return mergeVectors({ myasserter.errors, testAlignmentRadioBox(), testEditorSkillsPanel<Player, Game>(), testEditorStatisticsPanel<Player, Game>() });
}

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testEditorStatisticsPanel()
{
	GameData::updateIsInGameAndPartySize();
	int index = std::min(1, std::max(CURRENT_PARTY_SIZE - 1, 0));
	AutoBackup backup(*reinterpret_cast<Player*>(playersInParty[index]));
	Player* pl = reinterpret_cast<Player*>(playersInParty[index]);
	memset(pl, 0, sizeof(Player));
	(void)playerAccessor->forPlayer(index);
	auto eWindow = wxGetApp().editorMainWindow;
	Asserter myasserter("Statistics panel");
    EditorPlayerWindow* win = eWindow->createPlayerWindow(index);
    win->tabs->SetSelection(PlayerWindowPanelType::STATISTICS_PANEL_INDEX);
    EditorStatisticsPanel* panel = dynamic_cast<EditorStatisticsPanel*>(win->tabs->GetCurrentPage());
    win->Show();
	wxUIActionSimulator sim;
	GuiTestHelper helper(*panel, sim, myasserter);
	wxASSERT(win->IsShown() && win->IsVisible());

	// tests to check that modifying fields changes actual value in player struct
	struct Test
	{
		wxSpinCtrl* baseValue;
		//std::variant<std::monostate, int, wxSpinCtrl*> colorThreshold;
		std::variant<uint8_t Player::*, uint16_t Player::*, uint32_t Player::*, uint64_t Player::*, int8_t Player::*, int16_t Player::*, int32_t Player::*, int64_t Player::*> member;
	};

	auto& statWidgets = panel->primaryStatWidgetToStatIdMap;
	auto& resWidgets = panel->resistanceWidgetToResIdMap;
	std::vector<Test> tests
	({
		// might, intellect, personality, endurance, speed, accuracy, luck, fire res, air res, water res, earth res, spirit res, mind res, body res, light res, dark res (all with bonus field too)

		Test{.baseValue = statWidgets[consts::STAT_MIGHT]->base, .member = &Player::mightBase},
		Test{.baseValue = statWidgets[consts::STAT_MIGHT]->bonus, .member = &Player::mightBonus},
		Test{.baseValue = statWidgets[consts::STAT_INTELLECT]->base, .member = &Player::intellectBase},
		Test{.baseValue = statWidgets[consts::STAT_INTELLECT]->bonus, .member = &Player::intellectBonus},
		Test{.baseValue = statWidgets[consts::STAT_PERSONALITY]->base, .member = &Player::personalityBase},
		Test{.baseValue = statWidgets[consts::STAT_PERSONALITY]->bonus, .member = &Player::personalityBonus},
		Test{.baseValue = statWidgets[consts::STAT_ENDURANCE]->base, .member = &Player::enduranceBase},
		Test{.baseValue = statWidgets[consts::STAT_ENDURANCE]->bonus, .member = &Player::enduranceBonus},
		Test{.baseValue = statWidgets[consts::STAT_SPEED]->base, .member = &Player::speedBase},
		Test{.baseValue = statWidgets[consts::STAT_SPEED]->bonus, .member = &Player::speedBonus},
		Test{.baseValue = statWidgets[consts::STAT_ACCURACY]->base, .member = &Player::accuracyBase},
		Test{.baseValue = statWidgets[consts::STAT_ACCURACY]->bonus, .member = &Player::accuracyBonus},
		Test{.baseValue = statWidgets[consts::STAT_LUCK]->base, .member = &Player::luckBase},
		Test{.baseValue = statWidgets[consts::STAT_LUCK]->bonus, .member = &Player::luckBonus},
	});

	if constexpr (SAME(Player, mm6::Player))
	{
		tests.insert(tests.end(), std::move(std::initializer_list<Test>{
			Test{.baseValue = resWidgets[consts::DMG_FIRE]->base, .member = &Player::fireResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_FIRE]->bonus, .member = &Player::fireResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_ELEC]->base, .member = &Player::elecResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_ELEC]->bonus, .member = &Player::elecResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_COLD]->base, .member = &Player::coldResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_COLD]->bonus, .member = &Player::coldResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_POISON]->base, .member = &Player::poisonResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_POISON]->bonus, .member = &Player::poisonResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_MAGIC]->base, .member = &Player::magicResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_MAGIC]->bonus, .member = &Player::magicResistanceBonus },
			}));
	}
	else
	{
		tests.insert(tests.end(), std::move(std::initializer_list<Test>{
			Test{.baseValue = resWidgets[consts::DMG_FIRE]->base, .member = &Player::fireResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_FIRE]->bonus, .member = &Player::fireResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_AIR]->base, .member = &Player::airResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_AIR]->bonus, .member = &Player::airResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_WATER]->base, .member = &Player::waterResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_WATER]->bonus, .member = &Player::waterResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_EARTH]->base, .member = &Player::earthResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_EARTH]->bonus, .member = &Player::earthResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_SPIRIT]->base, .member = &Player::spiritResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_SPIRIT]->bonus, .member = &Player::spiritResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_MIND]->base, .member = &Player::mindResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_MIND]->bonus, .member = &Player::mindResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_BODY]->base, .member = &Player::bodyResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_BODY]->bonus, .member = &Player::bodyResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_LIGHT]->base, .member = &Player::lightResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_LIGHT]->bonus, .member = &Player::lightResistanceBonus },
			Test{.baseValue = resWidgets[consts::DMG_DARK]->base, .member = &Player::darkResistanceBase },
			Test{.baseValue = resWidgets[consts::DMG_DARK]->bonus, .member = &Player::darkResistanceBonus },
		}));
	}

	// mm6/7 bonuses
	if constexpr (SAME(Player, mm6::Player) || SAME(Player, mm7::Player))
	{
		auto& extraStats = panel->statExtraToStatIdSpinCtrlMap;
		// melee/ranged attack/damage bonus, full sp bonus, full hp bonus
		tests.insert(tests.end(), std::move(std::initializer_list<Test>{
			Test{.baseValue = extraStats.at(consts::STAT_MELEE_ATTACK_BONUS), .member = &Player::meleeAttackBonus },
			Test{.baseValue = extraStats.at(consts::STAT_MELEE_DAMAGE_BONUS), .member = &Player::meleeDamageBonus },
			Test{.baseValue = extraStats.at(consts::STAT_RANGED_ATTACK_BONUS), .member = &Player::rangedAttackBonus },
			Test{.baseValue = extraStats.at(consts::STAT_RANGED_DAMAGE_BONUS), .member = &Player::rangedDamageBonus },
			Test{.baseValue = extraStats.at(consts::STAT_HIT_POINTS_BONUS), .member = &Player::fullHPBonus },
			Test{.baseValue = extraStats.at(consts::STAT_SPELL_POINTS_BONUS), .member = &Player::fullSPBonus },
			}));
	}

	// current hp/sp - set/get, text color changing (threshold - full hp)

	// primary stats - set/get, bonus text color (0), black potion checkboxes get/set, TODO: condition effect values & text color

	// resistances - get/set, text color (0), TODO: spell effect values & color

	// mm6/7 extras - get/set, text color (0)

	// checkboxes

	eWindow->destroyPlayerWindow(index);

	return myasserter.errors;
}
template std::vector<wxString> GUI_tests::testEditorStatisticsPanel<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testEditorStatisticsPanel<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testEditorStatisticsPanel<mm8::Player, mm8::Game>();

// explicit instantiation
template std::vector<wxString> GUI_tests::testGui<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testGui<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testGui<mm8::Player, mm8::Game>();
