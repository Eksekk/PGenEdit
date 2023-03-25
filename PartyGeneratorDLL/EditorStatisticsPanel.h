#pragma once
#include "pch.h"
#include "main.h"
#include <wx/collpane.h>
#include "ResistanceWidget.h"

class wxSpinCtrl;
class wxSpinCtrlDouble;
class wxStaticLine;
class PlayerPrimaryStat;
class PrimaryStatWidget;
class PlayerClass;
class AlignmentRadioBox;

class EditorStatisticsPanel : public wxScrolledWindow
{
private:
	void createImmediateStatSettings();
	void createStatisticsAdjuster();
	void createActionsPanel();
	const int playerIndex;
protected:
	// stat-like data
	wxStaticText* hpLabel;
	wxSpinCtrl* hpValue;
	wxStaticText* hpSlash;
	wxTextCtrl* fullHpText;
	wxCheckBox* infiniteHpCheckbox;
	wxStaticText* spLabel;
	wxSpinCtrl* spValue;
	wxStaticText* spSlash;
	wxTextCtrl* fullSpText;
	wxCheckBox* infiniteSpCheckbox;
	wxStaticText* baseClassLabel;
	wxChoice* baseClassChoice;
	wxRadioBox* tierRadioBox;
	AlignmentRadioBox* alignmentRadioBox;
	wxStaticText* recoveryDelayMultiplierLabel;
	wxSpinCtrlDouble* recoveryDelayMultiplierValue;
	wxButton* recoverFullyButton;
	wxCheckBox* reduceBuffSpellRecoveryCheckbox;
	wxCheckBox* outOfCombatCheckbox;

	void onCurrentHpChange(wxCommandEvent& event);
	void onInfiniteHpCheck(wxCommandEvent& event);
	void onCurrentSpChange(wxCommandEvent& event);
	void onInfiniteSpCheck(wxCommandEvent& event);

	void onClassChoiceChange(wxCommandEvent& event);
	void onClassTierRadio(wxCommandEvent& event);
	void onClassAlignmentRadio(wxCommandEvent& event);

	void onRecoveryDelayMultiplierChange(wxCommandEvent& event);
	void onRecoverFullyPress(wxCommandEvent& event);
	void onReduceBuffSpellRecoveryCheck(wxCommandEvent& event);
	void onReduceBuffRecoveryOutOfCombatCheck(wxCommandEvent& event);

	wxStaticLine* immediateStatisticsStaticLine;

	// stat adjusters
	std::unordered_map<int, std::unique_ptr<PrimaryStatWidget>> primaryStatWidgetToStatIdMap;
	std::unordered_map<int, std::unique_ptr<ResistanceWidget>> resistanceWidgetToResIdMap;

	wxStaticText* adjustStatisticsLabel;
	wxStaticText* primaryLabel;
	wxStaticText* statisticsBaseLabel;
	wxStaticText* statisticsBonusLabel;
	wxStaticText* m_staticText108;
	wxStaticText* m_staticText114;
	wxStaticText* m_staticText115;
	wxStaticLine* primaryOtherStaticLine;
	wxStaticText* otherLabel;
	wxStaticText* extraAcLabel;
	wxSpinCtrl* extraAcValue;
	wxStaticText* ageLabel;
	wxSpinCtrl* ageBase;
	wxSpinCtrl* ageBonus;
	wxStaticText* levelLabel;
	wxSpinCtrl* levelBase;
	wxSpinCtrl* levelBonus;
	wxStaticBitmap* levelHelp;
	wxStaticText* experienceLabel;
	wxSpinCtrl* experience;
	wxStaticBitmap* experienceHelp;
	wxStaticLine* statisticsAdjusterVerticalLine;
	wxStaticText* resistancesLabel;
	wxStaticText* resistancesBaseLabel;
	wxStaticText* resistancesBonusLabel;
	wxStaticText* resistancesSpellEffectLabel;
	wxStaticLine* resistancesExtraStatsStaticLine;
	wxCollapsiblePane* extraStatsPane;
	struct StatExtra
	{
		wxStaticText* label;
		wxSpinCtrl* value;
	};
	std::unordered_map<wxSpinCtrl*, int> statIdToStatExtraControlMap;
	void onStatExtraChange(wxCommandEvent& event);

	wxStaticLine* statisticsActionsStaticLine;

	void onExtraAcValueChange(wxCommandEvent& event);
	void onAgeBaseValueChange(wxCommandEvent& event);
	void onAgeBonusValueChange(wxCommandEvent& event);
	void onLevelBaseValueChange(wxCommandEvent& event);
	void onLevelBonusValueChange(wxCommandEvent& event);
	void onExperienceChange(wxCommandEvent& event);

	// actions
	wxStaticText* actionsLabel;
	wxCheckBox* scaleWithLevelCheckbox;
	wxCheckBox* scaleWithRaceClassCheckbox;
	wxCheckBox* affectPrimaryCheckbox;
	wxCheckBox* affectResistancesCheckbox;
	wxCheckBox* affectMm67ExtrasCheckbox;
	wxCheckBox* affectOtherCheckbox;
	wxButton* minimumStatisticsButton;
	wxButton* maximumStatisticsButton;
	wxButton* setToRelativePowerButton;
	wxSlider* setToRelativePowerSlider;

	void onMinimumStatisticsPress(wxCommandEvent& event);
	void onMaximumStatisticsPress(wxCommandEvent& event);
	void onRelativePowerStatisticsPress(wxCommandEvent& event);

	wxBoxSizer* mainSizer;

	std::unordered_map<int, PlayerClass*> classToChoiceIndexMap;

	void updateFromPlayerData();

	void saveData();
	void loadData();

	void onActivateWindow(wxActivateEvent& event);
public:

	EditorStatisticsPanel(wxWindow* parent, int playerIndex);

	void updateFromPlayerData();
	~EditorStatisticsPanel();

};

