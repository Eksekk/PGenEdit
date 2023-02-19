#pragma once
#include "pch.h"
#include "main.h"
class wxNotebook;
class EditorPlayerWindow : public wxFrame
{
private:

protected:
	wxPanel* mainPanel;
	wxNotebook* tabs;
	wxPanel* appearancePanel;
	wxPanel* propertiesPanel;
	wxPanel* statisticsPanel;
	wxPanel* skillsPanel;
	wxPanel* spellsPanel;
	wxPanel* itemsPanel;
	wxPanel* conditionsAndBuffsPanel;
	wxPanel* awardsPanel;

public:
	const int playerIndex;

	EditorPlayerWindow(wxWindow* parent, int playerIndex);

	~EditorPlayerWindow();

	void onCloseWindow(wxCloseEvent& event);
private:
	wxBoxSizer* mainSizer;
};

