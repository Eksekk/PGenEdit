#include "pch.h"
#include "GUI_tests.h"
#include "Asserter.h"
#include "AlignmentRadioBox.h"
#include "GuiApplication.h"
#include "EditorMainWindow.h"
#include "EditorPlayerWindow.h"
#include "EditorSkillsPanel.h"
#include "AutoBackup.h"

std::vector<wxString> GUI_tests::testAlignmentRadioBox()
{
	// need to pass nullptr!!! otherwise children of frame will be created as top level windows
	// and NtUserCreateWindowEx will fail with code 1406 (0x57E)
	wxFrame* w = new wxFrame(nullptr, wxID_ANY, "testFrame");
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
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
	return errors;
}

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testEditorSkillsPanel()
{
	auto party = Game::party;

	auto eWindow = wxGetApp().editorMainWindow;
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);

	int index = 2;
	AutoBackup backup(CURRENT_PARTY_SIZE, players[index]);
	CURRENT_PARTY_SIZE = index + 1;
	Player* pl = new Player;
	memset(pl, 0, sizeof(Player));
	players[index] = pl;
	(void)playerAccessor->forPlayer(index);
	eWindow->createPlayerWindow(index);
	wxUIActionSimulator sim;

	auto autoClick = [&sim](wxWindow* window)
	{
		sim.MouseMove(window->GetScreenPosition());
		sim.MouseClick();
		wxYield();
	};

	// actual test code

	EditorPlayerWindow* window = eWindow->playerWindows[index];
	myassert(window);
	EditorSkillsPanel* panel = window->skillsPanel;
	window->Show();
	window->tabs->SetSelection(EditorPlayerWindow::SKILLS_PANEL_INDEX);
	wxYield();
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
		myassert(!widget->IsEnabled(), skill->name);
		autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(widget->IsEnabled(), skill->name);
		autoClick(panel->showUnobtainableSkillsCheckbox);
		myassert(!widget->IsEnabled(), skill->name);
	}
	else
	{
		wxLogWarning("Not found any \"do not generate\" skill");
	}

	for (int i : { 2, 5, 8, 22, 23 })
	{
		// level
		PlayerSkill* skill = GameData::skills.at(i);
		auto* widget = panel->widgetToSkillMap.at(skill);
		autoClick(widget->skillLevel);
		sim.Text("23");
		sim.MouseDown();
		sim.MouseUp();
		myassert(playerAccessor->getSkill(skill) == SkillValue{ 23, 1 }, i);
		sim.Text("4");
		sim.MouseDown();
		sim.MouseUp();
		myassert(playerAccessor->getSkill(skill) == SkillValue{ 4, 1 }, i);

		// mastery choice
		i += 2; // different skill
		skill = GameData::skills.at(i);
		widget = panel->widgetToSkillMap.at(skill);
		autoClick(widget->skillMastery);
		sim.Select("Master");
		myassert(playerAccessor->getSkill(skill) == SkillValue{ 1, 3 }, i);
		autoClick(widget->skillMastery);
		sim.Select("None");
		myassert(playerAccessor->getSkill(skill) == SkillValue{ 0, 0 }, i);
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
	myassert(playerAccessor->getSkill(3) == SkillValue{ 33, 2 });
	myassert(playerAccessor->getSkill(9) == SkillValue{ 33, 2 });

	// god mode
	autoClick(panel->godModeButton);
	myassert(playerAccessor->getSkill(11).mastery == MASTERY_GM);
	myassert(playerAccessor->getSkill(27).level == MAX_SKILL_LEVEL);

	// only already learned - skip (not using variable to keep track of it)

	eWindow->destroyPlayerWindow(index);
	delete pl;
	return errors;
}

template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testEditorSkillsPanel<mm8::Player, mm8::Game>();

template<typename Player, typename Game>
std::vector<wxString> GUI_tests::testGui()
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

	return mergeVectors({ errors, testAlignmentRadioBox(), testEditorSkillsPanel() });
}

// explicit instantiation
template std::vector<wxString> GUI_tests::testGui<mm6::Player, mm6::Game>();
template std::vector<wxString> GUI_tests::testGui<mm7::Player, mm7::Game>();
template std::vector<wxString> GUI_tests::testGui<mm8::Player, mm8::Game>();