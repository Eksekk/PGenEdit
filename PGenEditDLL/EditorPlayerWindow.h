#pragma once
#include "pch.h"
#include "main.h"
#include "wx/notebook.h"
#include "EditorPlayerPanel.h"

class EditorSkillsPanel;
class EditorMainWindow;
class EditorStatisticsPanel;

enum PlayerWindowPanelType
{
    APPEARANCE_PANEL_INDEX = 0,
	STATISTICS_PANEL_INDEX = 1,
	SKILLS_PANEL_INDEX = 2,
	SPELLS_PANEL_INDEX = 3,
    ITEMS_PANEL_INDEX = 4,
	CONDITIONS_BUFFS_PANEL_INDEX = 5,
	AWARDS_PANEL_INDEX = 6
};

class EditorPlayerWindow : public wxFrame, public EditorPlayerPanel
{
private:
	bool myIsBeingDestroyed; // because apparently IsBeingDeleted() doesn't work,

	// and I'm too lazy to debug it
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
	EditorPlayerWindow(wxWindow* parent, int playerIndex, int rosterIndex);
	EditorPlayerWindow() = delete;

	void showModal();
	void onUpdateTimer(wxTimerEvent& event);
	virtual ~EditorPlayerWindow();

	void onCloseWindow(wxCloseEvent& event);
	bool AcceptsFocus() const override;
	void onActivate(wxActivateEvent& event);
	bool Destroy() override;
	void onTabChange(wxBookCtrlEvent& event);

	static const std::vector<std::pair<std::string, PlayerWindowPanelType>> panelNamesWithIndexes;
	static int getPanelIndexByType(PlayerWindowPanelType type);
	static std::string getPanelNameByType(PlayerWindowPanelType type);

	friend class GUI_tests;

	int setRosterIndex() override;


    void setDefaultCustomSettings() override;

    bool persist(Json& json) const override;

    bool unpersist(const Json& json) override;
	std::string getJsonPersistKey() const override;
private:
	wxBoxSizer* mainSizer;
	wxTimer* updateTimer;
};

