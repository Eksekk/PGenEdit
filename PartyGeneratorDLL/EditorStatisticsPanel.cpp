#include "pch.h"
#include "EditorStatisticsPanel.h"
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/gbsizer.h>
#include <wx/artprov.h>

void EditorStatisticsPanel::createImmediateStatSettings()
{
}

void EditorStatisticsPanel::createStatisticsAdjuster()
{
}

void EditorStatisticsPanel::createActionsPanel()
{
}

EditorStatisticsPanel::EditorStatisticsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxScrolledWindow(parent, id, pos, size, style, name)
{
	this->SetScrollRate(5, 5);
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* hpSpSizer;
	hpSpSizer = new wxFlexGridSizer(2, 0, 0, 0);
	hpSpSizer->SetFlexibleDirection(wxBOTH);
	hpSpSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	hpLabel = new wxStaticText(this, wxID_ANY, _("Current HP:"), wxDefaultPosition, wxDefaultSize, 0);
	hpLabel->Wrap(-1);
	hpSpSizer->Add(hpLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	hpValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, -99999, 99999, 0);
	hpSpSizer->Add(hpValue, 0, wxALL, 5);

	hpSlash = new wxStaticText(this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0);
	hpSlash->Wrap(-1);
	hpSlash->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	hpSpSizer->Add(hpSlash, 0, wxALIGN_CENTER_VERTICAL, 5);

	fullHpText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
#ifdef __WXGTK__
	if (!fullHpText->HasFlag(wxTE_MULTILINE))
	{
		fullHpText->SetMaxLength(6);
	}
#else
	fullHpText->SetMaxLength(6);
#endif
	fullHpText->Enable(false);
	fullHpText->SetMaxSize(wxSize(70, -1));

	hpSpSizer->Add(fullHpText, 0, wxALL, 5);


	hpSpSizer->Add(20, 0, 0, 0, 5);

	infiniteHpCheckbox = new wxCheckBox(this, wxID_ANY, _("Infinite"), wxDefaultPosition, wxDefaultSize, 0);
	infiniteHpCheckbox->SetToolTip(_("Heavy enough attacks can still kill you"));

	hpSpSizer->Add(infiniteHpCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	spLabel = new wxStaticText(this, wxID_ANY, _("Current SP:"), wxDefaultPosition, wxDefaultSize, 0);
	spLabel->Wrap(-1);
	hpSpSizer->Add(spLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	spValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, -99999, 99999, 0);
	hpSpSizer->Add(spValue, 0, wxALL, 5);

	spSlash = new wxStaticText(this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0);
	spSlash->Wrap(-1);
	spSlash->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	hpSpSizer->Add(spSlash, 0, wxALIGN_CENTER_VERTICAL, 5);

	fullSpText1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
#ifdef __WXGTK__
	if (!fullSpText1->HasFlag(wxTE_MULTILINE))
	{
		fullSpText1->SetMaxLength(6);
	}
#else
	fullSpText1->SetMaxLength(6);
#endif
	fullSpText1->Enable(false);
	fullSpText1->SetMaxSize(wxSize(70, -1));

	hpSpSizer->Add(fullSpText1, 0, wxALL, 5);


	hpSpSizer->Add(20, 0, 0, 0, 5);

	infiniteHpCheckbox1 = new wxCheckBox(this, wxID_ANY, _("Infinite"), wxDefaultPosition, wxDefaultSize, 0);
	infiniteHpCheckbox1->SetToolTip(_("Heavy enough attacks can still kill you"));

	hpSpSizer->Add(infiniteHpCheckbox1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	mainSizer->Add(hpSpSizer, 0, 0, 5);

	wxBoxSizer* statLikeDataSizer;
	statLikeDataSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer* classSizer;
	classSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Class")), wxVERTICAL);

	wxGridBagSizer* innerClassSizer;
	innerClassSizer = new wxGridBagSizer(0, 15);
	innerClassSizer->SetFlexibleDirection(wxBOTH);
	innerClassSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	baseClassLabel = new wxStaticText(classSizer->GetStaticBox(), wxID_ANY, _("Base"), wxDefaultPosition, wxDefaultSize, 0);
	baseClassLabel->Wrap(-1);
	innerClassSizer->Add(baseClassLabel, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxArrayString baseClassChoiceChoices;
	baseClassChoice = new wxChoice(classSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, baseClassChoiceChoices, 0);
	baseClassChoice->SetSelection(0);
	innerClassSizer->Add(baseClassChoice, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL, 5);

	wxString tierRadioBoxChoices[] = { _("0"), _("1"), _("2") };
	int tierRadioBoxNChoices = sizeof(tierRadioBoxChoices) / sizeof(wxString);
	tierRadioBox = new wxRadioBox(classSizer->GetStaticBox(), wxID_ANY, _("Tier"), wxDefaultPosition, wxDefaultSize, tierRadioBoxNChoices, tierRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	tierRadioBox->SetSelection(1);
	innerClassSizer->Add(tierRadioBox, wxGBPosition(0, 1), wxGBSpan(2, 1), wxALL, 5);

	wxString alignmentRadioBoxChoices[] = { _("Neutral"), _("Light"), _("Dark") };
	int alignmentRadioBoxNChoices = sizeof(alignmentRadioBoxChoices) / sizeof(wxString);
	alignmentRadioBox = new wxRadioBox(classSizer->GetStaticBox(), wxID_ANY, _("Alignment"), wxDefaultPosition, wxDefaultSize, alignmentRadioBoxNChoices, alignmentRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	alignmentRadioBox->SetSelection(0);
	innerClassSizer->Add(alignmentRadioBox, wxGBPosition(0, 2), wxGBSpan(2, 1), wxALL, 5);


	classSizer->Add(innerClassSizer, 1, wxEXPAND, 5);


	statLikeDataSizer->Add(classSizer, 0, wxALL, 5);

	wxStaticBoxSizer* recoveryDelaySizer;
	recoveryDelaySizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Recovery delay settings")), wxVERTICAL);

	wxBoxSizer* mainRecoveryDelaySizer;
	mainRecoveryDelaySizer = new wxBoxSizer(wxHORIZONTAL);

	recoveryDelayMultiplierLabel = new wxStaticText(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Multiplier:"), wxDefaultPosition, wxDefaultSize, 0);
	recoveryDelayMultiplierLabel->Wrap(-1);
	mainRecoveryDelaySizer->Add(recoveryDelayMultiplierLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	recoveryDelayMultiplierValue = new wxSpinCtrlDouble(recoveryDelaySizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 20, 1.000000, 0.05);
	recoveryDelayMultiplierValue->SetDigits(2);
	mainRecoveryDelaySizer->Add(recoveryDelayMultiplierValue, 0, wxALL, 5);


	mainRecoveryDelaySizer->Add(30, 0, 0, wxEXPAND, 5);

	recoverFullyButton = new wxButton(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Recover fully right now"), wxDefaultPosition, wxDefaultSize, 0);
	mainRecoveryDelaySizer->Add(recoverFullyButton, 0, wxALL, 5);


	recoveryDelaySizer->Add(mainRecoveryDelaySizer, 0, wxEXPAND, 5);

	wxBoxSizer* buffRecoveryDelaySizer;
	buffRecoveryDelaySizer = new wxBoxSizer(wxHORIZONTAL);

	reduceBuffSpellRecoveryCheckbox = new wxCheckBox(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Heavily reduce recovery after casting buffs"), wxDefaultPosition, wxDefaultSize, 0);
	buffRecoveryDelaySizer->Add(reduceBuffSpellRecoveryCheckbox, 0, wxALL, 5);

	outOfCombatCheckbox = new wxCheckBox(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Only out of combat"), wxDefaultPosition, wxDefaultSize, 0);
	outOfCombatCheckbox->SetValue(true);
	outOfCombatCheckbox->SetToolTip(_("Green \"enemy detector\""));

	buffRecoveryDelaySizer->Add(outOfCombatCheckbox, 0, wxALL, 5);


	recoveryDelaySizer->Add(buffRecoveryDelaySizer, 1, wxEXPAND, 5);


	statLikeDataSizer->Add(recoveryDelaySizer, 0, wxALL, 5);


	mainSizer->Add(statLikeDataSizer, 1, wxEXPAND, 5);

	m_staticline39 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline39, 0, wxEXPAND | wxALL, 5);

	adjustStatisticsLabel = new wxStaticText(this, wxID_ANY, _("Adjust statistics"), wxDefaultPosition, wxDefaultSize, 0);
	adjustStatisticsLabel->Wrap(-1);
	adjustStatisticsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(adjustStatisticsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	mainSizer->Add(0, 20, 0, 0, 5);

	wxBoxSizer* statisticsAdjusterSizer;
	statisticsAdjusterSizer = new wxBoxSizer(wxHORIZONTAL);

	wxGridBagSizer* statisticsSizer;
	statisticsSizer = new wxGridBagSizer(0, 0);
	statisticsSizer->SetFlexibleDirection(wxBOTH);
	statisticsSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	primaryLabel = new wxStaticText(this, wxID_ANY, _("Primary"), wxDefaultPosition, wxDefaultSize, 0);
	primaryLabel->Wrap(-1);
	primaryLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	statisticsSizer->Add(primaryLabel, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	statisticsBaseLabel = new wxStaticText(this, wxID_ANY, _("Base"), wxDefaultPosition, wxDefaultSize, 0);
	statisticsBaseLabel->Wrap(-1);
	statisticsSizer->Add(statisticsBaseLabel, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	statisticsBonusLabel = new wxStaticText(this, wxID_ANY, _("Bonus"), wxDefaultPosition, wxDefaultSize, 0);
	statisticsBonusLabel->Wrap(-1);
	statisticsSizer->Add(statisticsBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText108 = new wxStaticText(this, wxID_ANY, _("Black potion used"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText108->Wrap(-1);
	statisticsSizer->Add(m_staticText108, wxGBPosition(1, 4), wxGBSpan(1, 1), wxALL, 5);

	m_staticText114 = new wxStaticText(this, wxID_ANY, _("Condition effect"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText114->Wrap(-1);
	statisticsSizer->Add(m_staticText114, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL, 5);

	mightLabel = new wxStaticText(this, wxID_ANY, _("Might"), wxDefaultPosition, wxDefaultSize, 0);
	mightLabel->Wrap(-1);
	mightLabel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	statisticsSizer->Add(mightLabel, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	mightBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	mightBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(mightBase, wxGBPosition(2, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	mightBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	mightBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	mightBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(mightBonus, wxGBPosition(2, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText115 = new wxStaticText(this, wxID_ANY, _("-30%"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText115->Wrap(-1);
	m_staticText115->SetForegroundColour(wxColour(236, 0, 0));

	statisticsSizer->Add(m_staticText115, wxGBPosition(2, 3), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	personalityLabel = new wxStaticText(this, wxID_ANY, _("Personality"), wxDefaultPosition, wxDefaultSize, 0);
	personalityLabel->Wrap(-1);
	statisticsSizer->Add(personalityLabel, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL, 5);

	personalityBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	personalityBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(personalityBase, wxGBPosition(3, 1), wxGBSpan(1, 1), wxALL, 5);

	personalityBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	personalityBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	personalityBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(personalityBonus, wxGBPosition(3, 2), wxGBSpan(1, 1), wxALL, 5);

	intellectLabel = new wxStaticText(this, wxID_ANY, _("Intellect"), wxDefaultPosition, wxDefaultSize, 0);
	intellectLabel->Wrap(-1);
	statisticsSizer->Add(intellectLabel, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALL, 5);

	intellectBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	intellectBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(intellectBase, wxGBPosition(4, 1), wxGBSpan(1, 1), wxALL, 5);

	intellectBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	intellectBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	intellectBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(intellectBonus, wxGBPosition(4, 2), wxGBSpan(1, 1), wxALL, 5);

	enduranceLabel = new wxStaticText(this, wxID_ANY, _("Endurance"), wxDefaultPosition, wxDefaultSize, 0);
	enduranceLabel->Wrap(-1);
	statisticsSizer->Add(enduranceLabel, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALL, 5);

	enduranceBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	enduranceBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(enduranceBase, wxGBPosition(5, 1), wxGBSpan(1, 1), wxALL, 5);

	enduranceBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	enduranceBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	enduranceBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(enduranceBonus, wxGBPosition(5, 2), wxGBSpan(1, 1), wxALL, 5);

	speedLabel = new wxStaticText(this, wxID_ANY, _("Speed"), wxDefaultPosition, wxDefaultSize, 0);
	speedLabel->Wrap(-1);
	statisticsSizer->Add(speedLabel, wxGBPosition(6, 0), wxGBSpan(1, 1), wxALL, 5);

	speedBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	speedBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(speedBase, wxGBPosition(6, 1), wxGBSpan(1, 1), wxALL, 5);

	speedBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	speedBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	speedBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(speedBonus, wxGBPosition(6, 2), wxGBSpan(1, 1), wxALL, 5);

	accuracyLabel = new wxStaticText(this, wxID_ANY, _("Accuracy"), wxDefaultPosition, wxDefaultSize, 0);
	accuracyLabel->Wrap(-1);
	statisticsSizer->Add(accuracyLabel, wxGBPosition(7, 0), wxGBSpan(1, 1), wxALL, 5);

	accuracyBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	accuracyBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(accuracyBase, wxGBPosition(7, 1), wxGBSpan(1, 1), wxALL, 5);

	accuracyBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	accuracyBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	accuracyBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(accuracyBonus, wxGBPosition(7, 2), wxGBSpan(1, 1), wxALL, 5);

	luckLabel = new wxStaticText(this, wxID_ANY, _("Luck"), wxDefaultPosition, wxDefaultSize, 0);
	luckLabel->Wrap(-1);
	statisticsSizer->Add(luckLabel, wxGBPosition(8, 0), wxGBSpan(1, 1), wxALL, 5);

	luckBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	luckBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(luckBase, wxGBPosition(8, 1), wxGBSpan(1, 1), wxALL, 5);

	luckBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	luckBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	luckBonus->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	statisticsSizer->Add(luckBonus, wxGBPosition(8, 2), wxGBSpan(1, 1), wxALL, 5);

	m_staticline201 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	statisticsSizer->Add(m_staticline201, wxGBPosition(9, 0), wxGBSpan(1, 4), wxEXPAND | wxALL, 5);

	otherLabel = new wxStaticText(this, wxID_ANY, _("Other"), wxDefaultPosition, wxDefaultSize, 0);
	otherLabel->Wrap(-1);
	otherLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	statisticsSizer->Add(otherLabel, wxGBPosition(10, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	extraAcLabel = new wxStaticText(this, wxID_ANY, _("Extra AC"), wxDefaultPosition, wxDefaultSize, 0);
	extraAcLabel->Wrap(-1);
	extraAcLabel->SetToolTip(_("Doesn't include stoneskin"));

	statisticsSizer->Add(extraAcLabel, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALL, 5);

	extraAcValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraAcValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(extraAcValue, wxGBPosition(11, 2), wxGBSpan(1, 1), wxALL, 5);

	ageLabel = new wxStaticText(this, wxID_ANY, _("Age"), wxDefaultPosition, wxDefaultSize, 0);
	ageLabel->Wrap(-1);
	statisticsSizer->Add(ageLabel, wxGBPosition(13, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	ageBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	ageBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(ageBase, wxGBPosition(13, 1), wxGBSpan(1, 1), wxALL, 5);

	ageBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	ageBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(ageBonus, wxGBPosition(13, 2), wxGBSpan(1, 1), wxALL, 5);

	levelLabel = new wxStaticText(this, wxID_ANY, _("Level"), wxDefaultPosition, wxDefaultSize, 0);
	levelLabel->Wrap(-1);
	statisticsSizer->Add(levelLabel, wxGBPosition(14, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	levelBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	levelBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(levelBase, wxGBPosition(14, 1), wxGBSpan(1, 1), wxALL, 5);

	levelBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	levelBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(levelBonus, wxGBPosition(14, 2), wxGBSpan(1, 1), wxALL, 5);

	levelHelp = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON), wxDefaultPosition, wxDefaultSize, 0);
	levelHelp->SetToolTip(_("Also changes experience - at least minimum required for base level"));

	statisticsSizer->Add(levelHelp, wxGBPosition(14, 3), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	experienceLabel = new wxStaticText(this, wxID_ANY, _("Experience"), wxDefaultPosition, wxDefaultSize, 0);
	experienceLabel->Wrap(-1);
	statisticsSizer->Add(experienceLabel, wxGBPosition(15, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	experience = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	experience->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	statisticsSizer->Add(experience, wxGBPosition(15, 1), wxGBSpan(1, 1), wxALL, 5);

	experienceHelp = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON), wxDefaultPosition, wxDefaultSize, 0);
	experienceHelp->SetToolTip(_("Enough to train to level %d"));

	statisticsSizer->Add(experienceHelp, wxGBPosition(15, 3), wxGBSpan(1, 1), wxALL, 5);

	m_checkBox87 = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	statisticsSizer->Add(m_checkBox87, wxGBPosition(2, 4), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	statisticsAdjusterSizer->Add(statisticsSizer, 0, 0, 5);

	m_staticline27 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	statisticsAdjusterSizer->Add(m_staticline27, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* extraStatsSizer;
	extraStatsSizer = new wxBoxSizer(wxVERTICAL);

	wxGridBagSizer* resistancesSizer;
	resistancesSizer = new wxGridBagSizer(0, 0);
	resistancesSizer->SetFlexibleDirection(wxBOTH);
	resistancesSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	resistancesLabel = new wxStaticText(this, wxID_ANY, _("Resistances"), wxDefaultPosition, wxDefaultSize, 0);
	resistancesLabel->Wrap(-1);
	resistancesLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	resistancesSizer->Add(resistancesLabel, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesBaseLabel = new wxStaticText(this, wxID_ANY, _("Base"), wxDefaultPosition, wxDefaultSize, 0);
	resistancesBaseLabel->Wrap(-1);
	resistancesSizer->Add(resistancesBaseLabel, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesBonusLabel = new wxStaticText(this, wxID_ANY, _("Bonus"), wxDefaultPosition, wxDefaultSize, 0);
	resistancesBonusLabel->Wrap(-1);
	resistancesSizer->Add(resistancesBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	fireLabel = new wxStaticText(this, wxID_ANY, _("Fire"), wxDefaultPosition, wxDefaultSize, 0);
	fireLabel->Wrap(-1);
	resistancesSizer->Add(fireLabel, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	fireBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	fireBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	resistancesSizer->Add(fireBase, wxGBPosition(2, 1), wxGBSpan(1, 1), wxALL, 5);

	fireBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	fireBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	resistancesSizer->Add(fireBonus, wxGBPosition(2, 2), wxGBSpan(1, 1), wxALL, 5);

	airLabel = new wxStaticText(this, wxID_ANY, _("Air"), wxDefaultPosition, wxDefaultSize, 0);
	airLabel->Wrap(-1);
	resistancesSizer->Add(airLabel, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL, 5);

	airBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	airBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	resistancesSizer->Add(airBase, wxGBPosition(3, 1), wxGBSpan(1, 1), wxALL, 5);

	airBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	airBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	resistancesSizer->Add(airBonus, wxGBPosition(3, 2), wxGBSpan(1, 1), wxALL, 5);


	extraStatsSizer->Add(resistancesSizer, 0, wxEXPAND, 5);

	m_staticline211 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	extraStatsSizer->Add(m_staticline211, 0, wxEXPAND | wxALL, 5);

	extraStatsPane = new wxCollapsiblePane(this, wxID_ANY, _("MM6/7 only"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE);
	extraStatsPane->Collapse(false);

	extraStatsPane->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer6->SetFlexibleDirection(wxBOTH);
	fgSizer6->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	extraMaxHpLabel = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _("Extra max HP"), wxDefaultPosition, wxDefaultSize, 0);
	extraMaxHpLabel->Wrap(-1);
	fgSizer6->Add(extraMaxHpLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	extraMaxHpValue = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraMaxHpValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	fgSizer6->Add(extraMaxHpValue, 0, wxALL, 5);

	extraMaxSpLabel = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _("Extra max SP"), wxDefaultPosition, wxDefaultSize, 0);
	extraMaxSpLabel->Wrap(-1);
	fgSizer6->Add(extraMaxSpLabel, 0, wxALL, 5);

	extraMaxSpValue = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraMaxSpValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	fgSizer6->Add(extraMaxSpValue, 0, wxALL, 5);

	extraMeleeAttackLabel = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _("Extra melee attack"), wxDefaultPosition, wxDefaultSize, 0);
	extraMeleeAttackLabel->Wrap(-1);
	fgSizer6->Add(extraMeleeAttackLabel, 0, wxALL, 5);

	extraMeleeAttackValue = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraMeleeAttackValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	fgSizer6->Add(extraMeleeAttackValue, 0, wxALL, 5);

	extraMeleeDamageLabel = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _("Extra melee damage"), wxDefaultPosition, wxDefaultSize, 0);
	extraMeleeDamageLabel->Wrap(-1);
	fgSizer6->Add(extraMeleeDamageLabel, 0, wxALL, 5);

	extraMeleeDamageValue = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraMeleeDamageValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	fgSizer6->Add(extraMeleeDamageValue, 0, wxALL, 5);

	extraRangedAttackLabel = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _("Extra ranged attack"), wxDefaultPosition, wxDefaultSize, 0);
	extraRangedAttackLabel->Wrap(-1);
	fgSizer6->Add(extraRangedAttackLabel, 0, wxALL, 5);

	extraRangedAttackValue = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraRangedAttackValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	fgSizer6->Add(extraRangedAttackValue, 0, wxALL, 5);

	extraRangedDamageLabel = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _("Extra ranged damage"), wxDefaultPosition, wxDefaultSize, 0);
	extraRangedDamageLabel->Wrap(-1);
	fgSizer6->Add(extraRangedDamageLabel, 0, wxALL, 5);

	extraRangedDamageValue = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraRangedDamageValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	fgSizer6->Add(extraRangedDamageValue, 0, wxALL, 5);


	extraStatsPane->GetPane()->SetSizer(fgSizer6);
	extraStatsPane->GetPane()->Layout();
	fgSizer6->Fit(extraStatsPane->GetPane());
	extraStatsSizer->Add(extraStatsPane, 0, wxEXPAND | wxALL, 5);


	statisticsAdjusterSizer->Add(extraStatsSizer, 1, wxEXPAND, 5);


	mainSizer->Add(statisticsAdjusterSizer, 0, wxEXPAND, 5);

	m_staticline33 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline33, 0, wxEXPAND | wxALL, 5);

	actionsLabel = new wxStaticText(this, wxID_ANY, _("Actions"), wxDefaultPosition, wxDefaultSize, 0);
	actionsLabel->Wrap(-1);
	actionsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(actionsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	scaleWithLevelCheckbox = new wxCheckBox(this, wxID_ANY, _("Scale with level"), wxDefaultPosition, wxDefaultSize, 0);
	mainSizer->Add(scaleWithLevelCheckbox, 0, wxALL, 5);

	scaleWithRaceClassCheckbox = new wxCheckBox(this, wxID_ANY, _("Scale with race/class"), wxDefaultPosition, wxDefaultSize, 0);
	scaleWithRaceClassCheckbox->SetToolTip(_("Knight will receive more might and endurance, elves more intellect, thieves accuracy and speed etc."));

	mainSizer->Add(scaleWithRaceClassCheckbox, 0, wxALL, 5);

	wxStaticBoxSizer* affectWhatSizer;
	affectWhatSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Affect")), wxHORIZONTAL);

	affectPrimaryCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("Primary"), wxDefaultPosition, wxDefaultSize, 0);
	affectPrimaryCheckbox->SetValue(true);
	affectWhatSizer->Add(affectPrimaryCheckbox, 0, wxALL, 5);

	affectResistancesCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("Resistances"), wxDefaultPosition, wxDefaultSize, 0);
	affectResistancesCheckbox->SetValue(true);
	affectWhatSizer->Add(affectResistancesCheckbox, 0, wxALL, 5);

	affectMm67ExtrasCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("MM6/7 extras"), wxDefaultPosition, wxDefaultSize, 0);
	affectMm67ExtrasCheckbox->SetValue(true);
	affectWhatSizer->Add(affectMm67ExtrasCheckbox, 0, wxALL, 5);

	affectOtherCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("Other"), wxDefaultPosition, wxDefaultSize, 0);
	affectOtherCheckbox->SetValue(true);
	affectWhatSizer->Add(affectOtherCheckbox, 0, wxALL, 5);


	mainSizer->Add(affectWhatSizer, 0, wxALL, 5);

	minimumStatisticsButton = new wxButton(this, wxID_ANY, _("Set to minimum possible"), wxDefaultPosition, wxDefaultSize, 0);
	mainSizer->Add(minimumStatisticsButton, 0, wxALL, 5);

	maximumStatisticsButton = new wxButton(this, wxID_ANY, _("Set to maximum possible"), wxDefaultPosition, wxDefaultSize, 0);
	mainSizer->Add(maximumStatisticsButton, 0, wxALL, 5);

	wxBoxSizer* setToRelativePowerSizer;
	setToRelativePowerSizer = new wxBoxSizer(wxHORIZONTAL);

	setToRelativePowerButton = new wxButton(this, wxID_ANY, _("Set to relative power:"), wxDefaultPosition, wxDefaultSize, 0);
	setToRelativePowerSizer->Add(setToRelativePowerButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	setToRelativePowerSlider = new wxSlider(this, wxID_ANY, 5, 1, 25, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	setToRelativePowerSizer->Add(setToRelativePowerSlider, 1, wxALL, 5);


	mainSizer->Add(setToRelativePowerSizer, 0, wxEXPAND, 5);


	this->SetSizer(mainSizer);
	this->Layout();
	mainSizer->Fit(this);
	mainSizer->Add(this, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(mainSizer);
	this->Layout();
}

EditorStatisticsPanel::~EditorStatisticsPanel()
{
}