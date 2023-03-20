#pragma once
#include "pch.h"
#include "main.h"
#include <wx/collpane.h>

class wxSpinCtrl;
class wxSpinCtrlDouble;
class wxStaticLine;

class EditorStatisticsPanel : public wxScrolledWindow
{
private:
	void createImmediateStatSettings();
	void createStatisticsAdjuster();
	void createActionsPanel();
protected:
	wxStaticText* hpLabel;
	wxSpinCtrl* hpValue;
	wxStaticText* hpSlash;
	wxTextCtrl* fullHpText;
	wxCheckBox* infiniteHpCheckbox;
	wxStaticText* spLabel;
	wxSpinCtrl* spValue;
	wxStaticText* spSlash;
	wxTextCtrl* fullSpText1;
	wxCheckBox* infiniteHpCheckbox1;
	wxStaticText* baseClassLabel;
	wxChoice* baseClassChoice;
	wxRadioBox* tierRadioBox;
	wxRadioBox* alignmentRadioBox;
	wxStaticText* recoveryDelayMultiplierLabel;
	wxSpinCtrlDouble* recoveryDelayMultiplierValue;
	wxButton* recoverFullyButton;
	wxCheckBox* reduceBuffSpellRecoveryCheckbox;
	wxCheckBox* outOfCombatCheckbox;
	wxStaticLine* m_staticline39;
	wxStaticText* adjustStatisticsLabel;
	wxStaticText* primaryLabel;
	wxStaticText* statisticsBaseLabel;
	wxStaticText* statisticsBonusLabel;
	wxStaticText* m_staticText108;
	wxStaticText* m_staticText114;
	wxStaticText* mightLabel;
	wxSpinCtrl* mightBase;
	wxSpinCtrl* mightBonus;
	wxStaticText* m_staticText115;
	wxStaticText* personalityLabel;
	wxSpinCtrl* personalityBase;
	wxSpinCtrl* personalityBonus;
	wxStaticText* intellectLabel;
	wxSpinCtrl* intellectBase;
	wxSpinCtrl* intellectBonus;
	wxStaticText* enduranceLabel;
	wxSpinCtrl* enduranceBase;
	wxSpinCtrl* enduranceBonus;
	wxStaticText* speedLabel;
	wxSpinCtrl* speedBase;
	wxSpinCtrl* speedBonus;
	wxStaticText* accuracyLabel;
	wxSpinCtrl* accuracyBase;
	wxSpinCtrl* accuracyBonus;
	wxStaticText* luckLabel;
	wxSpinCtrl* luckBase;
	wxSpinCtrl* luckBonus;
	wxStaticLine* m_staticline201;
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
	wxCheckBox* m_checkBox87;
	wxStaticLine* m_staticline27;
	wxStaticText* resistancesLabel;
	wxStaticText* resistancesBaseLabel;
	wxStaticText* resistancesBonusLabel;
	wxStaticText* fireLabel;
	wxSpinCtrl* fireBase;
	wxSpinCtrl* fireBonus;
	wxStaticText* airLabel;
	wxSpinCtrl* airBase;
	wxSpinCtrl* airBonus;
	wxStaticLine* m_staticline211;
	wxCollapsiblePane* extraStatsPane;
	wxStaticText* extraMaxHpLabel;
	wxSpinCtrl* extraMaxHpValue;
	wxStaticText* extraMaxSpLabel;
	wxSpinCtrl* extraMaxSpValue;
	wxStaticText* extraMeleeAttackLabel;
	wxSpinCtrl* extraMeleeAttackValue;
	wxStaticText* extraMeleeDamageLabel;
	wxSpinCtrl* extraMeleeDamageValue;
	wxStaticText* extraRangedAttackLabel;
	wxSpinCtrl* extraRangedAttackValue;
	wxStaticText* extraRangedDamageLabel;
	wxSpinCtrl* extraRangedDamageValue;
	wxStaticLine* m_staticline33;
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

public:

	EditorStatisticsPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(723, 817), long style = wxTAB_TRAVERSAL | wxHSCROLL | wxVSCROLL, const wxString& name = wxEmptyString);

	~EditorStatisticsPanel();

};

