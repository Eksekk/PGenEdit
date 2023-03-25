#include "pch.h"
#include "EditorStatisticsPanel.h"
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/gbsizer.h>
#include <wx/artprov.h>
#include "Utility.h"
#include "GameData.h"
#include "AlignmentRadioBox.h"
#include "PrimaryStatWidget.h"
#include "PlayerStructAccessor.h"

//, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(723, 817),
//	long style = wxTAB_TRAVERSAL | wxHSCROLL | wxVSCROLL, const wxString& name = wxEmptyString)
EditorStatisticsPanel::EditorStatisticsPanel(wxWindow* parent, int playerIndex) : playerIndex(playerIndex), wxScrolledWindow(parent)
{
	this->SetScrollRate(5, 5);
	mainSizer = new wxBoxSizer(wxVERTICAL);

	createImmediateStatSettings();

	immediateStatisticsStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(immediateStatisticsStaticLine, 0, wxEXPAND | wxALL, 5);

	createStatisticsAdjuster();

	statisticsActionsStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(statisticsActionsStaticLine, 0, wxEXPAND | wxALL, 5);

	createActionsPanel();

	mainSizer->Fit(this);
	this->SetSizer(mainSizer);
	this->Layout();
}

void EditorStatisticsPanel::onMinimumStatisticsPress(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onMaximumStatisticsPress(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onRelativePowerStatisticsPress(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::updateFromPlayerData()
{
	for (auto& [statId, widget] : primaryStatWidgetToStatIdMap)
	{
		widget->updateFromPlayerData();
	}
	for (auto& [resId, widget] : resistanceWidgetToResIdMap)
	{
		widget->updateFromPlayerData();
	}
	wxFAIL; // TODO
}

void EditorStatisticsPanel::saveData()
{
}

void EditorStatisticsPanel::loadData()
{
}

void EditorStatisticsPanel::onActivateWindow(wxActivateEvent& event)
{
}

void EditorStatisticsPanel::createImmediateStatSettings()
{
	wxFlexGridSizer* hpSpSizer;
	hpSpSizer = new wxFlexGridSizer(2, 0, 0, 0);
	hpSpSizer->SetFlexibleDirection(wxBOTH);
	hpSpSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	hpLabel = new wxStaticText(this, wxID_ANY, _("Current HP:"));
	hpLabel->Wrap(-1);
	hpSpSizer->Add(hpLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	auto [hpSpMin, hpSpMax] = boundsByType<int32_t>;
	hpValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, hpSpMin, hpSpMax, 0);
	hpSpSizer->Add(hpValue, 0, wxALL, 5);
	hpValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onCurrentHpChange, this);

	hpSlash = new wxStaticText(this, wxID_ANY, _("/"));
	hpSlash->Wrap(-1);
	hpSlash->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	hpSpSizer->Add(hpSlash, 0, wxALIGN_CENTER_VERTICAL, 5);

	fullHpText = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	fullHpText->SetMaxLength(6);
	fullHpText->Enable(false);
	fullHpText->SetMaxSize(wxSize(70, -1));

	hpSpSizer->Add(fullHpText, 0, wxALL, 5);


	hpSpSizer->Add(20, 0, 0, 0, 5);

	infiniteHpCheckbox = new wxCheckBox(this, wxID_ANY, _("Infinite"));
	infiniteHpCheckbox->SetToolTip(_("Heavy enough attacks can still kill you"));
	infiniteHpCheckbox->Bind(wxEVT_CHECKBOX, &EditorStatisticsPanel::onInfiniteHpCheck, this);

	hpSpSizer->Add(infiniteHpCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	spLabel = new wxStaticText(this, wxID_ANY, _("Current SP:"));
	spLabel->Wrap(-1);
	hpSpSizer->Add(spLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	spValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, hpSpMin, hpSpMax, 0);
	hpSpSizer->Add(spValue, 0, wxALL, 5);
	spValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onCurrentSpChange, this);

	spSlash = new wxStaticText(this, wxID_ANY, _("/"));
	spSlash->Wrap(-1);
	spSlash->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	hpSpSizer->Add(spSlash, 0, wxALIGN_CENTER_VERTICAL, 5);

	fullSpText = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	fullSpText->SetMaxLength(6);
	fullSpText->Enable(false);
	fullSpText->SetMaxSize(wxSize(70, -1));

	hpSpSizer->Add(fullSpText, 0, wxALL, 5);


	hpSpSizer->Add(20, 0, 0, 0, 5);

	infiniteSpCheckbox = new wxCheckBox(this, wxID_ANY, _("Infinite"));
	infiniteSpCheckbox->Bind(wxEVT_CHECKBOX, &EditorStatisticsPanel::onInfiniteSpCheck, this);

	hpSpSizer->Add(infiniteSpCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	mainSizer->Add(hpSpSizer, 0, 0, 5);

	wxBoxSizer* statLikeDataSizer;
	statLikeDataSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer* classSizer;
	classSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Class")), wxVERTICAL);

	wxGridBagSizer* innerClassSizer;
	innerClassSizer = new wxGridBagSizer(0, 15);
	innerClassSizer->SetFlexibleDirection(wxBOTH);
	innerClassSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	baseClassLabel = new wxStaticText(classSizer->GetStaticBox(), wxID_ANY, _("Base"));
	baseClassLabel->Wrap(-1);
	innerClassSizer->Add(baseClassLabel, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxArrayString classChoices;
	int i = 0;
	for (auto& [id, clas] : GameData::classes)
	{
		if (clas.tier == 0)
		{
			classToChoiceIndexMap[i++] = &clas;
			classChoices.Add(clas.name);
		}
	}
	baseClassChoice = new wxChoice(classSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, classChoices, 0);
	baseClassChoice->SetSelection(0);
	baseClassChoice->Bind(wxEVT_CHOICE, &EditorStatisticsPanel::onClassChoiceChange, this);
	innerClassSizer->Add(baseClassChoice, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL, 5);

	wxString tierRadioBoxChoices[] = { _("0"), _("1"), _("2") };
	int tierRadioBoxNChoices = sizeof(tierRadioBoxChoices) / sizeof(wxString);
	tierRadioBox = new wxRadioBox(classSizer->GetStaticBox(), wxID_ANY, _("Tier"), wxDefaultPosition, wxDefaultSize, tierRadioBoxNChoices, tierRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	tierRadioBox->SetSelection(0);
	tierRadioBox->Bind(wxEVT_RADIOBOX, &EditorStatisticsPanel::onClassTierRadio, this);
	innerClassSizer->Add(tierRadioBox, wxGBPosition(0, 1), wxGBSpan(2, 1), wxALL, 5);

	alignmentRadioBox = new AlignmentRadioBox(this, "Alignment", false);
	alignmentRadioBox->SetSelection(0);
	alignmentRadioBox->Bind(wxEVT_RADIOBOX, &EditorStatisticsPanel::onClassAlignmentRadio, this);
	innerClassSizer->Add(alignmentRadioBox, wxGBPosition(0, 2), wxGBSpan(2, 1), wxALL, 5);

	classSizer->Add(innerClassSizer, 1, wxEXPAND, 5);

	statLikeDataSizer->Add(classSizer, 0, wxALL, 5);

	wxStaticBoxSizer* recoveryDelaySizer;
	recoveryDelaySizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Recovery delay settings")), wxVERTICAL);

	wxBoxSizer* mainRecoveryDelaySizer;
	mainRecoveryDelaySizer = new wxBoxSizer(wxHORIZONTAL);

	recoveryDelayMultiplierLabel = new wxStaticText(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Multiplier:"));
	recoveryDelayMultiplierLabel->Wrap(-1);
	mainRecoveryDelaySizer->Add(recoveryDelayMultiplierLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	recoveryDelayMultiplierValue = new wxSpinCtrlDouble(recoveryDelaySizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 20, 1.000000, 0.05);
	recoveryDelayMultiplierValue->SetDigits(2);
	recoveryDelayMultiplierValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onRecoveryDelayMultiplierChange, this);
	mainRecoveryDelaySizer->Add(recoveryDelayMultiplierValue, 0, wxALL, 5);


	mainRecoveryDelaySizer->Add(30, 0, 0, wxEXPAND, 5);

	recoverFullyButton = new wxButton(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Recover fully right now"));
	recoverFullyButton->Bind(wxEVT_BUTTON, &EditorStatisticsPanel::onRecoverFullyPress, this);
	mainRecoveryDelaySizer->Add(recoverFullyButton, 0, wxALL, 5);


	recoveryDelaySizer->Add(mainRecoveryDelaySizer, 0, wxEXPAND, 5);

	wxBoxSizer* buffRecoveryDelaySizer;
	buffRecoveryDelaySizer = new wxBoxSizer(wxHORIZONTAL);

	reduceBuffSpellRecoveryCheckbox = new wxCheckBox(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Heavily reduce recovery after casting buffs"));
	buffRecoveryDelaySizer->Add(reduceBuffSpellRecoveryCheckbox, 0, wxALL, 5);
	reduceBuffSpellRecoveryCheckbox->Bind(wxEVT_CHECKBOX, &EditorStatisticsPanel::onReduceBuffSpellRecoveryCheck, this);

	outOfCombatCheckbox = new wxCheckBox(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Only out of combat"));
	outOfCombatCheckbox->SetValue(true);
	outOfCombatCheckbox->SetToolTip(_("Green \"enemy detector\""));
	outOfCombatCheckbox->Bind(wxEVT_CHECKBOX, &EditorStatisticsPanel::onReduceBuffRecoveryOutOfCombatCheck, this);
	buffRecoveryDelaySizer->Add(outOfCombatCheckbox, 0, wxALL, 5);


	recoveryDelaySizer->Add(buffRecoveryDelaySizer, 1, wxEXPAND, 5);


	statLikeDataSizer->Add(recoveryDelaySizer, 0, wxALL, 5);


	mainSizer->Add(statLikeDataSizer, 1, wxEXPAND, 5);
}

void EditorStatisticsPanel::createStatisticsAdjuster()
{
	adjustStatisticsLabel = new wxStaticText(this, wxID_ANY, _("Adjust statistics"));
	adjustStatisticsLabel->Wrap(-1);
	adjustStatisticsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(adjustStatisticsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	mainSizer->Add(0, 20, 0, 0, 5);

	wxBoxSizer* statisticsAdjusterSizer;
	statisticsAdjusterSizer = new wxBoxSizer(wxHORIZONTAL);

	wxGridBagSizer* primaryOtherStatisticsSizer;
	primaryOtherStatisticsSizer = new wxGridBagSizer(0, 0);
	primaryOtherStatisticsSizer->SetFlexibleDirection(wxBOTH);
	primaryOtherStatisticsSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	primaryLabel = new wxStaticText(this, wxID_ANY, _("Primary"));
	primaryLabel->Wrap(-1);
	primaryLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	primaryOtherStatisticsSizer->Add(primaryLabel, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	statisticsBaseLabel = new wxStaticText(this, wxID_ANY, _("Base"));
	statisticsBaseLabel->Wrap(-1);
	primaryOtherStatisticsSizer->Add(statisticsBaseLabel, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	statisticsBonusLabel = new wxStaticText(this, wxID_ANY, _("Bonus"));
	statisticsBonusLabel->Wrap(-1);
	primaryOtherStatisticsSizer->Add(statisticsBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText108 = new wxStaticText(this, wxID_ANY, _("Black potion used"));
	m_staticText108->Wrap(-1);
	primaryOtherStatisticsSizer->Add(m_staticText108, wxGBPosition(1, 4), wxGBSpan(1, 1), wxALL, 5);

	m_staticText114 = new wxStaticText(this, wxID_ANY, _("Condition effect"));
	m_staticText114->Wrap(-1);
	primaryOtherStatisticsSizer->Add(m_staticText114, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL, 5);

	int row = 2;
	for (auto& [id, stat] : GameData::primaryStats)
	{
		primaryStatWidgetToStatIdMap.emplace(id, std::make_unique<PrimaryStatWidget>(this, primaryOtherStatisticsSizer, row++, stat.get(), playerIndex));
	}

	primaryOtherStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	primaryOtherStatisticsSizer->Add(primaryOtherStaticLine, wxGBPosition(9, 0), wxGBSpan(1, 4), wxEXPAND | wxALL, 5);

	otherLabel = new wxStaticText(this, wxID_ANY, _("Other"));
	otherLabel->Wrap(-1);
	otherLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	primaryOtherStatisticsSizer->Add(otherLabel, wxGBPosition(10, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	extraAcLabel = new wxStaticText(this, wxID_ANY, _("Extra AC"));
	extraAcLabel->Wrap(-1);
	extraAcLabel->SetToolTip(_("Doesn't include stoneskin"));

	primaryOtherStatisticsSizer->Add(extraAcLabel, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALL, 5);

	extraAcValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraAcValue->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	extraAcValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onExtraAcValueChange, this);

	primaryOtherStatisticsSizer->Add(extraAcValue, wxGBPosition(11, 2), wxGBSpan(1, 1), wxALL, 5);

	ageLabel = new wxStaticText(this, wxID_ANY, _("Age"));
	ageLabel->Wrap(-1);
	primaryOtherStatisticsSizer->Add(ageLabel, wxGBPosition(13, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	ageBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	ageBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	ageBase->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onAgeBaseValueChange, this);

	primaryOtherStatisticsSizer->Add(ageBase, wxGBPosition(13, 1), wxGBSpan(1, 1), wxALL, 5);

	ageBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	ageBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	ageBonus->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onAgeBonusValueChange, this);

	primaryOtherStatisticsSizer->Add(ageBonus, wxGBPosition(13, 2), wxGBSpan(1, 1), wxALL, 5);

	levelLabel = new wxStaticText(this, wxID_ANY, _("Level"));
	levelLabel->Wrap(-1);
	primaryOtherStatisticsSizer->Add(levelLabel, wxGBPosition(14, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	levelBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	levelBase->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	levelBase->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onLevelBaseValueChange, this);

	primaryOtherStatisticsSizer->Add(levelBase, wxGBPosition(14, 1), wxGBSpan(1, 1), wxALL, 5);

	levelBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	levelBonus->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	levelBonus->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onLevelBonusValueChange, this);

	primaryOtherStatisticsSizer->Add(levelBonus, wxGBPosition(14, 2), wxGBSpan(1, 1), wxALL, 5);

	levelHelp = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON));
	levelHelp->SetToolTip(_("Also changes experience - at least minimum required for base level"));

	primaryOtherStatisticsSizer->Add(levelHelp, wxGBPosition(14, 3), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	experienceLabel = new wxStaticText(this, wxID_ANY, _("Experience"));
	experienceLabel->Wrap(-1);
	primaryOtherStatisticsSizer->Add(experienceLabel, wxGBPosition(15, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	experience = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	experience->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	experience->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onExperienceChange, this);

	primaryOtherStatisticsSizer->Add(experience, wxGBPosition(15, 1), wxGBSpan(1, 1), wxALL, 5);

	experienceHelp = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON));
	experienceHelp->SetToolTip(_("Enough to train to level %d"));

	primaryOtherStatisticsSizer->Add(experienceHelp, wxGBPosition(15, 3), wxGBSpan(1, 1), wxALL, 5);

	statisticsAdjusterSizer->Add(primaryOtherStatisticsSizer, 0, 0, 5);

	statisticsAdjusterVerticalLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	statisticsAdjusterSizer->Add(statisticsAdjusterVerticalLine, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* resistanceExtraStatsSizer;
	resistanceExtraStatsSizer = new wxBoxSizer(wxVERTICAL);

	wxGridBagSizer* resistancesSizer;
	resistancesSizer = new wxGridBagSizer(0, 0);
	resistancesSizer->SetFlexibleDirection(wxBOTH);
	resistancesSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	resistancesLabel = new wxStaticText(this, wxID_ANY, _("Resistances"));
	resistancesLabel->Wrap(-1);
	resistancesLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	resistancesSizer->Add(resistancesLabel, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesBaseLabel = new wxStaticText(this, wxID_ANY, _("Base"));
	resistancesBaseLabel->Wrap(-1);
	resistancesSizer->Add(resistancesBaseLabel, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesBonusLabel = new wxStaticText(this, wxID_ANY, _("Bonus"));
	resistancesBonusLabel->Wrap(-1);
	resistancesSizer->Add(resistancesBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesSpellEffectLabel = new wxStaticText(this, wxID_ANY, _("Spell effect"));
	resistancesBonusLabel->Wrap(-1);
	resistancesSizer->Add(resistancesBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	row = 2;
	for (int i : STATS_RESISTANCES)
	{
		auto& resPtr = GameData::resistances.at(i);
		resistanceWidgetToResIdMap.emplace(i, std::make_unique<ResistanceWidget>(i, resistancesSizer, row++, resPtr.get(), playerIndex));
	}

	resistanceExtraStatsSizer->Add(resistancesSizer, 0, wxEXPAND, 5);

	resistancesExtraStatsStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	resistanceExtraStatsSizer->Add(resistancesExtraStatsStaticLine, 0, wxEXPAND | wxALL, 5);

	extraStatsPane = new wxCollapsiblePane(this, wxID_ANY, _("MM6/7 only"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE);
	extraStatsPane->Collapse(false);

	extraStatsPane->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	wxFlexGridSizer* statExtrasSizer;
	statExtrasSizer = new wxFlexGridSizer(0, 2, 0, 0);
	statExtrasSizer->SetFlexibleDirection(wxBOTH);
	statExtrasSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	const std::array<std::pair<const char*, int>, 7> extraStats{{
		{"Extra max HP", STAT_HIT_POINTS_BONUS}, {"Extra max SP", STAT_SPELL_POINTS_BONUS}, {"Extra melee attack", STAT_MELEE_ATTACK_BONUS},
		{"Extra melee damage", STAT_MELEE_DAMAGE_BONUS}, {"Extra ranged attack", STAT_RANGED_ATTACK_BONUS}, {"Extra ranged damage", STAT_RANGED_DAMAGE_BONUS}
	}};

	for (const auto& [name, statId] : extraStats)
	{
		auto [low, high] = boundsByType<int8_t>;
		StatExtra stat;
		stat.label = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _(name));
		stat.value = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, low, high);
		stat.value->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onStatExtraChange, this);
		statExtrasSizer->Add(stat.label, wxSizerFlags().CenterVertical().Border(wxALL, 5));
		statExtrasSizer->Add(stat.value, wxSizerFlags().CenterVertical().Border(wxALL, 5));
		if (MMVER == 8)
		{
			stat.label->Disable();
			stat.value->Disable();
		}
		statIdToStatExtraControlMap[stat.value] = statId;
	}

	extraStatsPane->GetPane()->SetSizer(statExtrasSizer);
	extraStatsPane->GetPane()->Layout();
	statExtrasSizer->Fit(extraStatsPane->GetPane());
	resistanceExtraStatsSizer->Add(extraStatsPane, 0, wxEXPAND | wxALL, 5);

	statisticsAdjusterSizer->Add(resistanceExtraStatsSizer, 1, wxEXPAND, 5);

	mainSizer->Add(statisticsAdjusterSizer, 0, wxEXPAND, 5);
}

void EditorStatisticsPanel::createActionsPanel()
{
	actionsLabel = new wxStaticText(this, wxID_ANY, _("Actions"));
	actionsLabel->Wrap(-1);
	actionsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(actionsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	scaleWithLevelCheckbox = new wxCheckBox(this, wxID_ANY, _("Scale with level"));
	mainSizer->Add(scaleWithLevelCheckbox, 0, wxALL, 5);

	scaleWithRaceClassCheckbox = new wxCheckBox(this, wxID_ANY, _("Scale with race/class"));
	scaleWithRaceClassCheckbox->SetToolTip(_("Knight will receive more might and endurance, elves more intellect, thieves accuracy and speed etc."));

	mainSizer->Add(scaleWithRaceClassCheckbox, 0, wxALL, 5);

	wxStaticBoxSizer* affectWhatSizer;
	affectWhatSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Affect")), wxHORIZONTAL);

	affectPrimaryCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("Primary"));
	affectPrimaryCheckbox->SetValue(true);
	affectWhatSizer->Add(affectPrimaryCheckbox, 0, wxALL, 5);

	affectResistancesCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("Resistances"));
	affectResistancesCheckbox->SetValue(true);
	affectWhatSizer->Add(affectResistancesCheckbox, 0, wxALL, 5);

	affectMm67ExtrasCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("MM6/7 extras"));
	affectMm67ExtrasCheckbox->SetValue(true);
	affectWhatSizer->Add(affectMm67ExtrasCheckbox, 0, wxALL, 5);

	affectOtherCheckbox = new wxCheckBox(affectWhatSizer->GetStaticBox(), wxID_ANY, _("Other"));
	affectOtherCheckbox->SetValue(true);
	affectWhatSizer->Add(affectOtherCheckbox, 0, wxALL, 5);


	mainSizer->Add(affectWhatSizer, 0, wxALL, 5);

	minimumStatisticsButton = new wxButton(this, wxID_ANY, _("Set to minimum possible"));
	minimumStatisticsButton->Bind(wxEVT_BUTTON, &EditorStatisticsPanel::onMinimumStatisticsPress, this);
	mainSizer->Add(minimumStatisticsButton, 0, wxALL, 5);

	maximumStatisticsButton = new wxButton(this, wxID_ANY, _("Set to maximum possible"));
	maximumStatisticsButton->Bind(wxEVT_BUTTON, &EditorStatisticsPanel::onMaximumStatisticsPress, this);
	mainSizer->Add(maximumStatisticsButton, 0, wxALL, 5);

	wxBoxSizer* setToRelativePowerSizer;
	setToRelativePowerSizer = new wxBoxSizer(wxHORIZONTAL);

	setToRelativePowerButton = new wxButton(this, wxID_ANY, _("Set to relative power:"));
	setToRelativePowerButton->Bind(wxEVT_BUTTON, &EditorStatisticsPanel::onRelativePowerStatisticsPress, this);
	setToRelativePowerSizer->Add(setToRelativePowerButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	setToRelativePowerSlider = new wxSlider(this, wxID_ANY, 5, 1, 25, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	setToRelativePowerSizer->Add(setToRelativePowerSlider, 1, wxALL, 5);


	mainSizer->Add(setToRelativePowerSizer, 0, wxEXPAND, 5);
}

EditorStatisticsPanel::~EditorStatisticsPanel()
{
}

void EditorStatisticsPanel::onCurrentHpChange(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onInfiniteHpCheck(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onCurrentSpChange(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onInfiniteSpCheck(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onClassChoiceChange(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onClassTierRadio(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onClassAlignmentRadio(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onRecoveryDelayMultiplierChange(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onRecoverFullyPress(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onReduceBuffSpellRecoveryCheck(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onReduceBuffRecoveryOutOfCombatCheck(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onStatExtraChange(wxCommandEvent& event)
{
	if (MMVER == 8) return;
	wxSpinCtrl* ctrl = /*static*/dynamic_cast<wxSpinCtrl*>(event.GetEventObject());
	int statId = statIdToStatExtraControlMap.at(ctrl);
	playerAccessor->forPlayer(playerIndex)->setStatBonus(statId, ctrl->GetValue());
}
void EditorStatisticsPanel::onExtraAcValueChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBonus(STAT_ARMOR_CLASS, extraAcValue->GetValue());
}

void EditorStatisticsPanel::onAgeBaseValueChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBase(STAT_AGE, ageBase->GetValue());
}

void EditorStatisticsPanel::onAgeBonusValueChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBonus(STAT_AGE, ageBonus->GetValue());
}

void EditorStatisticsPanel::onLevelBaseValueChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBase(STAT_LEVEL, levelBase->GetValue());
}

void EditorStatisticsPanel::onLevelBonusValueChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBonus(STAT_LEVEL, levelBonus->GetValue());
}
void EditorStatisticsPanel::onExperienceChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setExperience(experience->GetValue());
}