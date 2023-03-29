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

std::vector<wxString> GUI_tests::testAlignmentRadioBox()
{
	// need to pass nullptr!!! otherwise children of frame will be created as top level windows
	// and NtUserCreateWindowEx will fail with code 1406 (0x57E)
	wxFrame* w = new wxFrame(nullptr, wxID_ANY, "testFrame");
	Asserter myasserter;
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
	Asserter myasserter;

	int index = 2;
	// have to use original player addresses because changing them for mmextension is tricky
	AutoBackup backup(CURRENT_PARTY_SIZE, *reinterpret_cast<Player*>(players[index]));
	// PARTY SIZE IS 0 BEFORE
	CURRENT_PARTY_SIZE = index + 1;
	Player* pl = reinterpret_cast<Player*>(players[index]);
	memset(pl, 0, sizeof(Player));
	(void)playerAccessor->setPlayerOverride(pl);
	wxUIActionSimulator sim;

	// actual test code
	EditorPlayerWindow* window = eWindow->createPlayerWindow(index);
	myassert(window);
	EditorSkillsPanel* panel = window->skillsPanel;
	AutoClicker autoClick(*panel, sim);
	window->Show();
	window->tabs->SetSelection(EditorPlayerWindow::SKILLS_PANEL_INDEX);
	autoClick(panel->affectAvailableSkillpointsCheckbox);
	myassert(panel->options.affectSkillpoints);
	myassert(panel->allowNegativeSkillpointsRadio->IsEnabled());
	myassert(panel->dontAllowSpendingMoreThanAvailableSkillpointsRadio->IsEnabled());
	autoClick(panel->dontAllowSpendingMoreThanAvailableSkillpointsRadio);
	myassert(!panel->options.allowNegativeSkillpoints);
	autoClick(panel->affectAvailableSkillpointsCheckbox);
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
		autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(widget->IsShown(), skill->name);
		autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(!widget->IsShown(), skill->name);
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
		widget->SetFocus(); // IMPORTANT, or text won't work
		sim.Text("23");
		sim.Char(WXK_TAB); // lose focus
		dispatchWindowMessages();
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 23, 1 }), i);
		widget->SetFocus();
 		sim.Text("4");
		sim.Char(WXK_TAB);
		dispatchWindowMessages();
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 4, 1 }), i);

		// mastery choice
		i += 2; // different skill
		skill = &GameData::skills.at(i);
		widget = panel->widgetToSkillMap.at(skill);
		autoClick(widget->skillMastery);
		widget->SetFocus();
		sim.Select("Master");
		sim.MouseClick();
		dispatchWindowMessages();
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 1, 3 }), i - 2);
		autoClick(widget->skillMastery);
		widget->SetFocus();
		sim.Select("None");
		sim.MouseClick();
		dispatchWindowMessages();
		myassert(playerAccessor->getSkill(skill) == (SkillValue{ 0, 0 }), i - 2);
	}

	// class constraints
	autoClick(panel->classConstraintsCurrentClass);
	myassert(panel->options.classConstraint == PlayerStructAccessor::CLASS_CONSTRAINT_CURRENT_CLASS);
	autoClick(panel->classConstraintsNone);
	myassert(panel->options.classConstraint == PlayerStructAccessor::CLASS_CONSTRAINT_NONE);

	autoClick(panel->classConstraintsCurrentClass);
	Mastery m = playerAccessor->getSkillMaxMastery(5);
	playerAccessor->setSkill(5, { 33, 4 });
	panel->updateFromPlayerData();
	autoClick(panel->applyClassConstraintsButton);
	myassert(playerAccessor->getSkill(5).mastery <= m);

	// affect armor/weapons/...
	autoClick(panel->affectArmorCheckbox);
	autoClick(panel->affectWeaponsCheckbox);
	autoClick(panel->affectMiscCheckbox);
	myassert(
		existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_ARMOR)
		&& existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_WEAPON)
		&& existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_MISC)
	);
	autoClick(panel->affectWeaponsCheckbox);
	myassert(!existsInVector(panel->options.batchSetAffectWhichSkillCategories, SKILLCAT_WEAPON));

	// set all skills to
	panel->setAllSkillsToLevelSpinCtrl->SetValue(33);
	panel->setAllSkillsToMasteryChoice->SetSelection(2); // expert
	autoClick(panel->setAllSkillsToButton);
	myassert(playerAccessor->getSkill(3) == (SkillValue{ 33, 2 }));
	myassert(playerAccessor->getSkill(9) == (SkillValue{ 33, 2 }));

	// god mode
	autoClick(panel->godModeButton);
	myassert(playerAccessor->getSkill(11).mastery == MASTERY_GM);
	myassert(playerAccessor->getSkill(27).level == MAX_SKILL_LEVEL);

	// only already learned - skip (not using variable to keep track of it)

	eWindow->destroyPlayerWindow(index);
	playerAccessor->clearPlayerOverride();
	return myasserter.errors;
}

template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm8::Player, mm8::Game>();

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testGui()
{
	Asserter myasserter;
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

	int oldCURRENT_PARTY_SIZE = CURRENT_PARTY_SIZE;
	CURRENT_PARTY_SIZE = MAX_PLAYERS;

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

	eWindow->ProcessEvent(event2);

	auto playerWindow = eWindow->playerWindows[1];

	players[1] = oldPlayer;
	CURRENT_PARTY_SIZE = oldCURRENT_PARTY_SIZE;

	delete player;

	return mergeVectors({ myasserter.errors, testAlignmentRadioBox(), testEditorSkillsPanel<Player, Game>(), testEditorStatisticsPanel<Player, Game>() });
}

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testEditorStatisticsPanel()
{
	GameData::updateIsInGameAndPartySize();
	int index = 1;
	AutoBackup backup(CURRENT_PARTY_SIZE, *reinterpret_cast<Player*>(players[index]));
	CURRENT_PARTY_SIZE = index + 1;
	Player* pl = reinterpret_cast<Player*>(players[index]);
	memset(pl, 0, sizeof(Player));
	(void)playerAccessor->setPlayerOverride(pl);
	auto eWindow = wxGetApp().editorMainWindow;
	Asserter myasserter;
	EditorPlayerWindow* win = eWindow->createPlayerWindow(index);
	win->Show();
	EditorStatisticsPanel* panel = win->statisticsPanel;
	win->tabs->SetSelection(EditorPlayerWindow::STATISTICS_PANEL_INDEX);
	wxUIActionSimulator sim;
	AutoClicker autoClick(*panel, sim);
	wxASSERT(win->IsShown() && win->IsVisible());

	struct Test
	{
		wxSpinCtrl* baseValue;
		std::variant<std::monostate, int, wxSpinCtrl*> colorThreshold;
	};

	std::vector<Test> tests
	({
		Test{panel->extraAcValue, 5}
	});

	// current hp/sp - set/get, text color changing (threshold - full hp)

	// primary stats - set/get, bonus text color (0), black potion checkboxes get/set, TODO: condition effect values & text color

	// resistances - get/set, text color (0), TODO: spell effect values & color

	// mm6/7 extras - get/set, text color (0)

	// checkboxes



	eWindow->destroyPlayerWindow(index);
	playerAccessor->clearPlayerOverride();

	return myasserter.errors;
}
template std::vector<wxString> GUI_tests::testEditorStatisticsPanel<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testEditorStatisticsPanel<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testEditorStatisticsPanel<mm8::Player, mm8::Game>();

// explicit instantiation
template std::vector<wxString> GUI_tests::testGui<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testGui<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testGui<mm8::Player, mm8::Game>();

void GUI_tests::dispatchWindowMessages()
{
	// temporary message loop to fix wxYield() not working due to no direct event loop
	// for my dll
	MSG msg;
	while (PeekMessageA(&msg, 0, 0, 0, true))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void GUI_tests::scrollIntoView(wxScrolledWindow* scrolled, wxWindow* window)
{
	int scrollRateY = 0;
	scrolled->GetScrollPixelsPerUnit(nullptr, &scrollRateY);

	const wxPoint windowPos = scrolled->CalcUnscrolledPosition(window->GetPosition());
	scrolled->Scroll(0, windowPos.y / scrollRateY);
}

GUI_tests::AutoClicker::AutoClicker(wxScrolledWindow& scrolled, wxUIActionSimulator& sim) : scrolled(scrolled), sim(sim) {}

void GUI_tests::AutoClicker::operator()(wxWindow* window)
{
	scrollIntoView(&scrolled, window);
	sim.MouseMove(window->GetScreenPosition() + wxPoint(5, 5));
	sim.MouseClick();
	dispatchWindowMessages();
}
