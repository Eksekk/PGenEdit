#pragma once
#include "pch.h"
#include "main.h"
class wxNotebook;
class EditorSkillsPanel;
class EditorMainWindow;
class EditorPlayerWindow : public wxFrame
{
private:

protected:
	wxPanel* mainPanel;
	wxNotebook* tabs;
	wxPanel* appearancePanel;
	wxPanel* propertiesPanel;
	wxPanel* statisticsPanel;
	EditorSkillsPanel* skillsPanel;
	wxPanel* spellsPanel;
	wxPanel* itemsPanel;
	wxPanel* conditionsAndBuffsPanel;
	wxPanel* awardsPanel;

	EditorMainWindow* mainWindow;

public:
	const int playerIndex;

	EditorPlayerWindow(wxWindow* parent, int playerIndex);

	void onUpdateTimer(wxTimerEvent& event);
	~EditorPlayerWindow();

	void onCloseWindow(wxCloseEvent& event);
private:
	wxBoxSizer* mainSizer;
	wxTimer* updateTimer;
};

