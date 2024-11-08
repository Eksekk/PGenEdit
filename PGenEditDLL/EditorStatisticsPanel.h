#pragma once
#include "main.h"
#include <wx/collpane.h>
#include "ResistanceWidget.h"
#include "Enum_const.h"
#include "EditorPlayerPanel.h"

class wxSpinCtrl;
class wxSpinCtrlDouble;
class wxStaticLine;
class PlayerPrimaryStat;
class PrimaryStatWidget;
class PlayerClass;
class AlignmentRadioBox;

class EditorStatisticsPanel : public wxScrolledWindow, public EditorPlayerPanel
{
private:
	void createImmediateStatSettings();
	void createStatisticsAdjuster();
	void createActionsPanel();
protected:
	// stat-like data
	wxStaticText* currentHpLabel;
	wxSpinCtrl* currentHpValue;
	wxStaticText* currentHpSlash;
	wxTextCtrl* fullHpText;
	wxCheckBox* infiniteHpCheckbox;
	wxStaticText* currentSpLabel;
	wxSpinCtrl* currentSpValue;
	wxStaticText* currentSpSlash;
	wxTextCtrl* fullSpText;
	wxCheckBox* infiniteSpCheckbox;
	wxStaticText* baseClassLabel;
	wxChoice* baseClassChoice;
	wxRadioBox* tierRadioBox;
	wxChoice* fullClassChoice;
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

	void onBaseClassChoiceChange(wxCommandEvent& event);
	void onClassTierRadio(wxCommandEvent& event);
	void onClassAlignmentRadio(wxCommandEvent& event);
	enum ClassChangeWhat
	{
		CLASS_CHANGE_ALL, CLASS_CHANGE_BASE, CLASS_CHANGE_TIER, CLASS_CHANGE_ALIGNMENT
	};
	void processClassControlsChange(ClassChangeWhat what, bool fromPlayerData);

	void onRecoveryDelayMultiplierChange(wxCommandEvent& event);
	void onRecoverFullyPress(wxCommandEvent& event);
	void onReduceBuffSpellRecoveryCheck(wxCommandEvent& event);
	void onReduceBuffRecoveryOutOfCombatCheck(wxCommandEvent& event);
	void onFullClassChoiceSelect(wxCommandEvent& event);
	
	wxCheckBox* noRecoveryCheckbox;
    void onNoRecoveryCheck(wxCommandEvent& event);

	std::unordered_map<PlayerClass*, int> fullChoiceIdToClassMap;
	std::unordered_map<int, PlayerClass*> classToFullChoiceIdMap;
	std::unordered_map<int, PlayerClass*> classPtrToBaseClassChoiceIdMap;
	std::unordered_map<PlayerClass*, int> baseClassChoiceIdToClassPtrMap;

	wxStaticLine* immediateStatisticsStaticLine;

	// stat adjusters
	wxStaticText* adjustStatisticsLabel;
	wxStaticText* primaryLabel;
	wxStaticText* statisticsBaseLabel;
	wxStaticText* statisticsBonusLabel;
	wxStaticText* blackPotionUsedLabel;
	wxStaticText* conditionEffectLabel;
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
	std::unordered_map<int, std::unique_ptr<PrimaryStatWidget>> primaryStatWidgetToStatIdMap;
	// NOTE: indexed by stat ids, not by damage type ids
	std::unordered_map<int, std::unique_ptr<ResistanceWidget>> resistanceWidgetToResIdMap;
	std::unordered_map<wxSpinCtrl*, int> statIdToStatExtraSpinCtrlMap;
	std::unordered_map<int, wxSpinCtrl*> statExtraToStatIdSpinCtrlMap;

	void onExtraStatsPaneClick(wxCollapsiblePaneEvent& event);
	void onStatExtraChange(wxCommandEvent& event);

	void onExtraAcValueChange(wxCommandEvent& event);
	void onAgeBaseValueChange(wxCommandEvent& event);
	void onAgeBonusValueChange(wxCommandEvent& event);
	void onLevelBaseValueChange(wxCommandEvent& event);
	void onLevelBonusValueChange(wxCommandEvent& event);
    void onExperienceChange(wxCommandEvent& event);

    wxStaticLine* statisticsActionsStaticLine;

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

	void onActivateWindow(wxActivateEvent& event);
public:
	EditorStatisticsPanel(wxWindow* parent, int playerIndex, int rosterIndex);
	EditorStatisticsPanel() = delete;

	~EditorStatisticsPanel();

	friend class GUI_tests;

	bool persist(Json& json) const override;
	bool unpersist(const Json& json) override;

	int setRosterIndex() override;


	void setDefaultCustomSettings() override;

	std::string getJsonPersistKey() const override;
    void updateFromPlayerData() override;
};

