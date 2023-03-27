#pragma once
#include "pch.h"
#include "main.h"
class wxNotebook;
class EditorSkillsPanel;
class EditorMainWindow;
class EditorStatisticsPanel;

class EditorPlayerWindow : public wxFrame
{
private:

protected:
	wxPanel* mainPanel;
	wxNotebook* tabs;
	wxPanel* appearancePanel;
	EditorStatisticsPanel* statisticsPanel;
	EditorSkillsPanel* skillsPanel;
	wxPanel* spellsPanel;
	wxPanel* itemsPanel;
	wxPanel* conditionsAndBuffsPanel;
	wxPanel* awardsPanel;

	EditorMainWindow* mainWindow;
	wxWindowDisabler* windowDisabler;
	wxEventLoop* loop;

public:
	static const int APPEARANCE_PANEL_INDEX = 0, STATISTICS_PANEL_INDEX = 1, SKILLS_PANEL_INDEX = 2, SPELLS_PANEL_INDEX = 3,
		ITEMS_PANEL_INDEX = 4, CONDITIONS_BUFFS_PANEL_INDEX = 5, AWARDS_PANEL_INDEX = 6;
	const int playerIndex;

	EditorPlayerWindow(wxWindow* parent, int playerIndex);

	void showModal();
	void onUpdateTimer(wxTimerEvent& event);
	virtual ~EditorPlayerWindow();

	void onCloseWindow(wxCloseEvent& event);
	bool AcceptsFocus() const override;
	void onActivate(wxActivateEvent& event);

	friend class GUI_tests;
private:
	wxBoxSizer* mainSizer;
	wxTimer* updateTimer;
};

