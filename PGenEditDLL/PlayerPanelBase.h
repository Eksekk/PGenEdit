#pragma once
#include "main.h"
#include "ClassSettingsTab.h"
#include <wx/notebook.h>

class PlayerData;

// atm PlayerPanel and DefaultPlayerPanel could be merged into one class (and so this class is redundant),
// but I thought otherwise and don't want to change because they'll almost surely be different in future

class PlayerPanelBase : public wxPanel
{
public:
	PlayerPanelBase(wxWindow* parent, PlayerData* linkedGenerationData);

	wxBoxSizer* mainSizer;
	wxCheckBox* generationEnabledCheckbox;
	wxStaticText* m_staticText12;
	wxChoice* playerTypeChoice;
	wxRadioBox* strengthIndicatorRadioBox;
	wxNotebook* m_notebook2;
	wxPanel* levelPanel;
	wxRadioBox* generateWhatRadioBox;
	wxPanel* skillsPanel;
	wxStaticText* m_staticText111;
	wxTextCtrl* skillPointsMultiplier;
	wxPanel* itemsPanel;
	wxCheckBox* keepCurrentItemsCheckbox;
	wxPanel* statsPanel;
	wxPanel* resistancesPanel;
	wxCheckBox* exclusiveResistancesCheckbox;
	wxPanel* spellsPanel;
	wxCheckBox* zeroOutTimedSpellsCastsCheckbox;

	PlayerData* linkedGenerationData;
	ClassSettingsTab* classSettingsTab;
private:
	void onGenerationEnabledCheck(wxCommandEvent& event);
	void onPlayerTypeChoice(wxCommandEvent& event);
	void onStrengthIndicatorRadio(wxCommandEvent& event);
	void onGenerateWhatRadio(wxCommandEvent& event);
	void onSkillPointsMulEnter(wxCommandEvent& event);
	void onKeepCurrentItemsCheck(wxCommandEvent& event);
	void onExclusiveResistancesCheck(wxCommandEvent& event);
	void onZeroOutTimedSpellCastsCheck(wxCommandEvent& event);
};

