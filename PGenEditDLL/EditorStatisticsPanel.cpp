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
#include "Profiler.h"
#include "HookParams.h"
#include "SaveGameData.h"
#include "Enum_const.h"

using namespace consts; // TODO: remove

//, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(723, 817),
//	long style = wxTAB_TRAVERSAL | wxHSCROLL | wxVSCROLL, const wxString& name = wxEmptyString)
EditorStatisticsPanel::EditorStatisticsPanel(wxWindow* parent, int playerIndex, int rosterIndex) : EditorPlayerPanel(playerIndex, rosterIndex), wxScrolledWindow(parent)
{
	Freeze();
    Bind(wxEVT_ACTIVATE, &EditorStatisticsPanel::onActivateWindow, this);
    Profiler profiler;
    //profiler.start("Creating statistics panel");
	this->SetScrollRate(15, 15);
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
	updateFromPlayerData();
	Thaw();
	//profiler.logResults();
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
	// class
	processClassControlsChange(CLASS_CHANGE_ALL, true);
	(void)playerAccessor->forPlayer(playerIndex);

	// hp, sp
	int maxHp = playerAccessor->getFullHp(), maxSp = playerAccessor->getFullSp();
	fullHpText->SetValue(wxString::Format("%d", maxHp));
	fullSpText->SetValue(wxString::Format("%d", maxSp));
	int currHp = playerAccessor->getHp(), currSp = playerAccessor->getSp();
	redBlackGreenTextThreshold(currentHpValue, currHp, maxHp);
	redBlackGreenTextThreshold(currentSpValue, currSp, maxSp);
	currentHpValue->SetValue(currHp);
	currentSpValue->SetValue(currSp);

	// stat adjusters
	for (auto& [statId, widgetPtr] : primaryStatWidgetToStatIdMap)
	{
		widgetPtr->updateFromPlayerData();
	}
	for (auto& [resId, widgetPtr] : resistanceWidgetToResIdMap)
	{
		widgetPtr->updateFromPlayerData();
	}
	for (auto& [widgetPtr, statId] : statIdToStatExtraSpinCtrlMap)
	{
		int value = playerAccessor->forPlayer(playerIndex)->getStatBonus(statId);
		redBlackGreenTextThreshold(widgetPtr, value, 0);
		widgetPtr->SetValue(value);
	}

	int acValue = playerAccessor->getStatBonus(STAT_ARMOR_CLASS);
	int64_t expVal = playerAccessor->getExperience();
	// TODO: age base needs to be calculated manually
	//auto [ageBaseVal, ageBonusVal] = playerAccessor->getStatBaseBonus(STAT_AGE);
	auto ageBonusVal = playerAccessor->getStatBonus(STAT_AGE);
	auto [levelBaseVal, levelBonusVal] = playerAccessor->getStatBaseBonus(STAT_LEVEL);
	redBlackGreenTextThreshold(extraAcValue, acValue, 0);
	redBlackGreenTextThreshold(ageBonus, ageBonusVal, 0);
	redBlackGreenTextThreshold(levelBonus, levelBonusVal, 0);
	for (std::pair<wxSpinCtrl*, int> pairs[]{ {extraAcValue, acValue}/*, {ageBase, ageBaseVal}*/, {ageBonus, ageBonusVal}, {levelBase, levelBaseVal}, {levelBonus, levelBonusVal} };
		auto [spin, val] : pairs)
	{
		spin->SetValue(val);
	}
	experience->SetValue(expVal);
}

void EditorStatisticsPanel::onActivateWindow(wxActivateEvent& event)
{
	if (event.GetActive())
	{
		saveGameData.loadEditorPlayerPanelData(*this);
		updateFromPlayerData();
	}
	else
	{
		saveGameData.saveEditorPlayerPanelData(*this);
	}
}

void EditorStatisticsPanel::createImmediateStatSettings()
{
	wxFlexGridSizer* hpSpSizer;
	hpSpSizer = new wxFlexGridSizer(2, 0, 0, 0);
	hpSpSizer->SetFlexibleDirection(wxBOTH);
	hpSpSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	currentHpLabel = new wxStaticText(this, wxID_ANY, _("Current HP:"));
	hpSpSizer->Add(currentHpLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	auto [hpSpMin, hpSpMax] = boundsByType<int32_t>;
	currentHpValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, hpSpMin, hpSpMax, 0);
	hpSpSizer->Add(currentHpValue, 0, wxALL, 5);
	currentHpValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onCurrentHpChange, this);

	currentHpSlash = new wxStaticText(this, wxID_ANY, _("/"));
	currentHpSlash->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	hpSpSizer->Add(currentHpSlash, 0, wxALIGN_CENTER_VERTICAL, 5);

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

	currentSpLabel = new wxStaticText(this, wxID_ANY, _("Current SP:"));
	hpSpSizer->Add(currentSpLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	currentSpValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, hpSpMin, hpSpMax, 0);
	hpSpSizer->Add(currentSpValue, 0, wxALL, 5);
	currentSpValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onCurrentSpChange, this);

	currentSpSlash = new wxStaticText(this, wxID_ANY, _("/"));
	currentSpSlash->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	hpSpSizer->Add(currentSpSlash, 0, wxALIGN_CENTER_VERTICAL, 5);

	fullSpText = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	fullSpText->Enable(false);
	fullSpText->SetMaxSize(wxSize(100, -1));

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
	wxStaticBox* staticBox = classSizer->GetStaticBox();

	wxGridBagSizer* innerClassSizer;
	innerClassSizer = new wxGridBagSizer(0, 15);

	// NO CONST INT, because ranges will error out
	std::vector<std::pair<int, PlayerClass*>> allClasses;
	allClasses.reserve(GameData::classes.size());
	std::transform(GameData::classes.begin(), GameData::classes.end(), std::back_inserter(allClasses), [](auto& pair) { return std::make_pair(pair.first, &pair.second); });
	std::ranges::sort(allClasses, [](const auto& pair1, const auto& pair2) -> bool
		{
			return pair1.second->name < pair2.second->name; // TODO: change sorting?
		});
	wxString classStr = gameHasClassAlignment() ? "%s, %d, %s" : "%s, %d";
	wxArrayString baseClassChoices, fullClassChoices;
	int baseClassCounter = 0, classCounter = 0;
	fullClassChoices.reserve(allClasses.size());
	for (auto& [id, classPtr] : allClasses)
	{
		if (classPtr->tier == 0)
		{
			classPtrToBaseClassChoiceIdMap[baseClassCounter++] = classPtr;
			baseClassChoices.Add(classPtr->name);
		}
		wxString formattedClassText = gameHasClassAlignment()
			? wxString::Format(classStr, classPtr->name, classPtr->tier, classPtr->getFormattedAlignment())
			: wxString::Format(classStr, classPtr->name, classPtr->tier);
		fullClassChoices.Add(std::move(formattedClassText));
		classToFullChoiceIdMap[classCounter++] = classPtr;
	}
	fullChoiceIdToClassMap = invertMap(classToFullChoiceIdMap);
	baseClassChoiceIdToClassPtrMap = invertMap(classPtrToBaseClassChoiceIdMap);

	wxStaticText* fullClassLabel = new wxStaticText(staticBox, wxID_ANY, _("Full class"));
	innerClassSizer->Add(fullClassLabel, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	fullClassChoice = new wxChoice(staticBox, wxID_ANY, wxDefaultPosition, wxDefaultSize, fullClassChoices);
	fullClassChoice->Bind(wxEVT_CHOICE, &EditorStatisticsPanel::onFullClassChoiceSelect, this);
	innerClassSizer->Add(fullClassChoice, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL, 5);

	wxStaticLine* classSettingsVerticalLine = new wxStaticLine(staticBox, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	innerClassSizer->Add(classSettingsVerticalLine, wxGBPosition(0, 1), wxGBSpan(2, 1), wxALL, 5);

	baseClassLabel = new wxStaticText(staticBox, wxID_ANY, _("Base"));
	innerClassSizer->Add(baseClassLabel, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	baseClassChoice = new wxChoice(staticBox, wxID_ANY, wxDefaultPosition, wxDefaultSize, baseClassChoices, 0);
	baseClassChoice->Bind(wxEVT_CHOICE, &EditorStatisticsPanel::onBaseClassChoiceChange, this);
	innerClassSizer->Add(baseClassChoice, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL, 5);

	wxString tierRadioBoxChoices[] = { _("0"), _("1"), _("2") };
	int tierRadioBoxNChoices = sizeof(tierRadioBoxChoices) / sizeof(wxString);
	tierRadioBox = new wxRadioBox(staticBox, wxID_ANY, _("Tier"), wxDefaultPosition, wxDefaultSize, tierRadioBoxNChoices, tierRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	tierRadioBox->Bind(wxEVT_RADIOBOX, &EditorStatisticsPanel::onClassTierRadio, this);
	innerClassSizer->Add(tierRadioBox, wxGBPosition(0, 3), wxGBSpan(2, 1), wxALL, 5);

	alignmentRadioBox = new AlignmentRadioBox(staticBox, "Alignment", false);
	alignmentRadioBox->Bind(wxEVT_RADIOBOX, &EditorStatisticsPanel::onClassAlignmentRadio, this);
	innerClassSizer->Add(alignmentRadioBox, wxGBPosition(0, 4), wxGBSpan(2, 1), wxALL, 5);
	if (!gameHasClassAlignment())
	{
		alignmentRadioBox->Disable();
	}

	classSizer->Add(innerClassSizer, 1, wxEXPAND, 5);

	statLikeDataSizer->Add(classSizer, 0, wxALL, 5);

	wxStaticBoxSizer* recoveryDelaySizer;
	recoveryDelaySizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Recovery delay settings")), wxVERTICAL);

	wxBoxSizer* mainRecoveryDelaySizer;
	mainRecoveryDelaySizer = new wxBoxSizer(wxHORIZONTAL);

	recoveryDelayMultiplierLabel = new wxStaticText(recoveryDelaySizer->GetStaticBox(), wxID_ANY, _("Multiplier:"));
	mainRecoveryDelaySizer->Add(recoveryDelayMultiplierLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	recoveryDelayMultiplierValue = new wxSpinCtrlDouble(recoveryDelaySizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 5, 1.000000, 0.05);
	recoveryDelayMultiplierValue->SetDigits(2);
	recoveryDelayMultiplierValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onRecoveryDelayMultiplierChange, this);
	mainRecoveryDelaySizer->Add(recoveryDelayMultiplierValue, 0, wxALL, 5);


	mainRecoveryDelaySizer->Add(30, 0, 0, wxEXPAND, 5);
	noRecoveryCheckbox = new wxCheckBox(recoveryDelaySizer->GetStaticBox(), wxID_ANY, "No recovery");
	noRecoveryCheckbox->Bind(wxEVT_CHECKBOX, &EditorStatisticsPanel::onNoRecoveryCheck, this);
    mainRecoveryDelaySizer->Add(noRecoveryCheckbox, 0, wxALL, 5);

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
	Profiler profiler; 
	profiler.start("create statistics adjuster");
	adjustStatisticsLabel = new wxStaticText(this, wxID_ANY, _("Adjust statistics"));
	adjustStatisticsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	mainSizer->Add(adjustStatisticsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	mainSizer->Add(0, 20, 0, 0, 5);

	wxBoxSizer* statisticsAdjusterSizer;
	statisticsAdjusterSizer = new wxBoxSizer(wxHORIZONTAL);

	wxGridBagSizer* primaryOtherStatisticsSizer;
	primaryOtherStatisticsSizer = new wxGridBagSizer(5, 5);

	primaryLabel = new wxStaticText(this, wxID_ANY, _("Primary"));
	primaryLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	primaryOtherStatisticsSizer->Add(primaryLabel, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	statisticsBaseLabel = new wxStaticText(this, wxID_ANY, _("Base"));
	primaryOtherStatisticsSizer->Add(statisticsBaseLabel, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	statisticsBonusLabel = new wxStaticText(this, wxID_ANY, _("Bonus"));
	primaryOtherStatisticsSizer->Add(statisticsBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	blackPotionUsedLabel = new wxStaticText(this, wxID_ANY, _("Black potion used"));
	primaryOtherStatisticsSizer->Add(blackPotionUsedLabel, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL, 5);

	conditionEffectLabel = new wxStaticText(this, wxID_ANY, _("Condition effect"));
	primaryOtherStatisticsSizer->Add(conditionEffectLabel, wxGBPosition(1, 4), wxGBSpan(1, 1), wxALL, 5);

	int row = 2;
	for (auto& [id, stat] : GameData::primaryStats)
	{
		primaryStatWidgetToStatIdMap.emplace(id, std::make_unique<PrimaryStatWidget>(this, primaryOtherStatisticsSizer, row++, stat.get(), playerIndex));
	}

	primaryOtherStaticLine = new wxStaticLine(this);
	primaryOtherStatisticsSizer->Add(primaryOtherStaticLine, wxGBPosition(9, 0), wxGBSpan(1, 5), wxEXPAND | wxALL, 5);

	otherLabel = new wxStaticText(this, wxID_ANY, _("Other"));
	otherLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	primaryOtherStatisticsSizer->Add(otherLabel, wxGBPosition(10, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	extraAcLabel = new wxStaticText(this, wxID_ANY, _("Extra AC"));
	extraAcLabel->SetToolTip(_("Doesn't include stoneskin"));
	primaryOtherStatisticsSizer->Add(extraAcLabel, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALL, 5);

	extraAcValue = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	extraAcValue->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onExtraAcValueChange, this);
	primaryOtherStatisticsSizer->Add(extraAcValue, wxGBPosition(11, 2), wxGBSpan(1, 1), wxALL, 5);

	ageLabel = new wxStaticText(this, wxID_ANY, _("Age"));
	primaryOtherStatisticsSizer->Add(ageLabel, wxGBPosition(13, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	ageBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	ageBase->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onAgeBaseValueChange, this);
	primaryOtherStatisticsSizer->Add(ageBase, wxGBPosition(13, 1), wxGBSpan(1, 1), wxALL, 5);

	ageBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	ageBonus->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onAgeBonusValueChange, this);
	primaryOtherStatisticsSizer->Add(ageBonus, wxGBPosition(13, 2), wxGBSpan(1, 1), wxALL, 5);

	levelLabel = new wxStaticText(this, wxID_ANY, _("Level"));
	primaryOtherStatisticsSizer->Add(levelLabel, wxGBPosition(14, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	levelBase = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	levelBase->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onLevelBaseValueChange, this);
	primaryOtherStatisticsSizer->Add(levelBase, wxGBPosition(14, 1), wxGBSpan(1, 1), wxALL, 5);

	levelBonus = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	levelBonus->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onLevelBonusValueChange, this);
	primaryOtherStatisticsSizer->Add(levelBonus, wxGBPosition(14, 2), wxGBSpan(1, 1), wxALL, 5);

	levelHelp = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON));
	levelHelp->SetToolTip(_("Also changes experience - at least minimum required for base level"));
	primaryOtherStatisticsSizer->Add(levelHelp, wxGBPosition(14, 3), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	experienceLabel = new wxStaticText(this, wxID_ANY, _("Experience"));
	primaryOtherStatisticsSizer->Add(experienceLabel, wxGBPosition(15, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	experience = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -32767, 32767, 0);
	experience->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onExperienceChange, this);
	primaryOtherStatisticsSizer->Add(experience, wxGBPosition(15, 1), wxGBSpan(1, 1), wxALL, 5);

	experienceHelp = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON));
	experienceHelp->SetToolTip(_("Enough to train to level %d"));
	primaryOtherStatisticsSizer->Add(experienceHelp, wxGBPosition(15, 3), wxGBSpan(1, 1), wxALL, 5);

	statisticsAdjusterSizer->Add(primaryOtherStatisticsSizer, 0, wxALL, 5);

	statisticsAdjusterVerticalLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	statisticsAdjusterSizer->Add(statisticsAdjusterVerticalLine, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* resistanceExtraStatsSizer = new wxBoxSizer(wxVERTICAL);

	wxGridBagSizer* resistancesSizer = new wxGridBagSizer(5, 5);

	resistancesLabel = new wxStaticText(this, wxID_ANY, _("Resistances"));
	resistancesLabel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	resistancesSizer->Add(resistancesLabel, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesBaseLabel = new wxStaticText(this, wxID_ANY, _("Base"));
	resistancesSizer->Add(resistancesBaseLabel, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesBonusLabel = new wxStaticText(this, wxID_ANY, _("Bonus"));
	resistancesSizer->Add(resistancesBonusLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	resistancesSpellEffectLabel = new wxStaticText(this, wxID_ANY, _("Spell effect"));
	resistancesSizer->Add(resistancesSpellEffectLabel, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	row = 2;
	for (int i : consts::STATS_RESISTANCES)
	{
		auto& resPtr = GameData::resistances.at(i);
		resistanceWidgetToResIdMap.emplace(i, std::make_unique<ResistanceWidget>(this, resistancesSizer, row++, resPtr.get(), playerIndex));
	}

	resistanceExtraStatsSizer->Add(resistancesSizer, 0, wxEXPAND | wxALL, 5);

	resistancesExtraStatsStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	resistanceExtraStatsSizer->Add(resistancesExtraStatsStaticLine, 0, wxEXPAND | wxALL, 5);

	extraStatsPane = new wxCollapsiblePane(this, wxID_ANY, _("MM6/7 only"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE);
	extraStatsPane->Collapse(true);
	extraStatsPane->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));
	extraStatsPane->Bind(wxEVT_COLLAPSIBLEPANE_CHANGED, &EditorStatisticsPanel::onExtraStatsPaneClick, this);

	wxFlexGridSizer* statExtrasSizer;
	statExtrasSizer = new wxFlexGridSizer(0, 2, 0, 0);
	statExtrasSizer->SetFlexibleDirection(wxBOTH);
	statExtrasSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	const std::array<std::pair<const char*, int>, 7> extraStats{{
		{"Extra max HP", STAT_HIT_POINTS_BONUS}, {"Extra max SP", STAT_SPELL_POINTS_BONUS}, {"Extra melee attack", STAT_MELEE_ATTACK_BONUS},
		{"Extra melee damage", STAT_MELEE_DAMAGE_BONUS}, {"Extra ranged attack", STAT_RANGED_ATTACK_BONUS}, {"Extra ranged damage", STAT_RANGED_DAMAGE_BONUS}
	}};

	auto extrasFlags = wxSizerFlags().CenterVertical().Border(wxALL, 5);
	for (const auto& [name, statId] : extraStats)
	{
		auto [low, high] = boundsByType<int8_t>;
		StatExtra stat;
		stat.label = new wxStaticText(extraStatsPane->GetPane(), wxID_ANY, _(name));
		stat.value = new wxSpinCtrl(extraStatsPane->GetPane(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, low, high);
		stat.value->Bind(wxEVT_SPINCTRL, &EditorStatisticsPanel::onStatExtraChange, this);
		statExtrasSizer->Add(stat.label, extrasFlags);
		statExtrasSizer->Add(stat.value, extrasFlags);
		if (MMVER == 8)
		{
			stat.label->Disable();
			stat.value->Disable();
		}
		statIdToStatExtraSpinCtrlMap[stat.value] = statId;
	}

	extraStatsPane->GetPane()->SetSizer(statExtrasSizer);
	extraStatsPane->GetPane()->Layout();
	statExtrasSizer->Fit(extraStatsPane->GetPane());
	resistanceExtraStatsSizer->Add(extraStatsPane, 0, wxEXPAND | wxALL, 5);

	statisticsAdjusterSizer->Add(resistanceExtraStatsSizer, 1, wxALL | wxEXPAND, 5);

	mainSizer->Add(statisticsAdjusterSizer, 0, wxALL | wxEXPAND, 5);
	//profiler.logResults();
}

void EditorStatisticsPanel::createActionsPanel()
{
	actionsLabel = new wxStaticText(this, wxID_ANY, _("Actions"));
	actionsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
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

int EditorStatisticsPanel::setRosterIndex()
{
    throw std::logic_error("The method or operation is not implemented.");
}
void EditorStatisticsPanel::setDefaultCustomSettings()
{
    throw std::logic_error("The method or operation is not implemented.");
}

std::string EditorStatisticsPanel::getJsonPersistKey() const
{
	return "statistics";
}

bool EditorStatisticsPanel::persist(Json& json) const
{
	Json& recoveryMuls = json["recoveryMultipliers"];
	return true;
}

bool EditorStatisticsPanel::unpersist(const Json& json)
{
	return true;
}

void EditorStatisticsPanel::onCurrentHpChange(wxCommandEvent& event)
{
	redBlackGreenTextThreshold(currentHpValue, currentHpValue->GetValue(), playerAccessor->forPlayer(playerIndex)->getFullHp());
	currentHpValue->Refresh();
	playerAccessor->forPlayer(playerIndex)->setHp(currentHpValue->GetValue());
}

void EditorStatisticsPanel::onInfiniteHpCheck(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onCurrentSpChange(wxCommandEvent& event)
{
	redBlackGreenTextThreshold(currentSpValue, currentSpValue->GetValue(), playerAccessor->forPlayer(playerIndex)->getFullSp());
	currentSpValue->Refresh();
	playerAccessor->forPlayer(playerIndex)->setSp(currentSpValue->GetValue());
}

void EditorStatisticsPanel::onInfiniteSpCheck(wxCommandEvent& event)
{
}

void EditorStatisticsPanel::onBaseClassChoiceChange(wxCommandEvent& event)
{
	// tier 0 or 1 - change class
	// tier 2 - change class, pick similar alignment
	processClassControlsChange(CLASS_CHANGE_BASE, false);
}

void EditorStatisticsPanel::onClassTierRadio(wxCommandEvent& event)
{
	processClassControlsChange(CLASS_CHANGE_TIER, false);
}

void EditorStatisticsPanel::onClassAlignmentRadio(wxCommandEvent& event)
{
	processClassControlsChange(CLASS_CHANGE_ALIGNMENT, false);
}

std::tuple<PlayerClass*, bool, bool, bool> pickNewClass(PlayerClass* const currentClass, const std::vector<PlayerClass*>& tree, int newTier, Alignment al)
{
	PlayerClass* finalClass = nullptr, *differentAlignmentClass = nullptr;
	bool hasNeutral = false, hasLight = false, hasDark = false; // is neutral alignment available for this class tree? etc.
    for (PlayerClass* classPtr : tree)
    {
		// TODO: use new "alignment is available" variable in player class
        if (classPtr->tier == newTier)
        {
			if (classPtr->alignment == al)
            {
                finalClass = classPtr;
			}
			else if (!differentAlignmentClass/* && classPtr->id != currentClass->id*/)
			{
				differentAlignmentClass = classPtr;
            }

            switch (classPtr->alignment)
            {

            case ALIGNMENT_NEUTRAL: hasNeutral = true; break;
            case ALIGNMENT_LIGHT: hasLight = true; break;
            case ALIGNMENT_DARK: hasDark = true; break;
            default:
            {
                wxFAIL_MSG(wxString::Format("Unknown alignment %d", (int)classPtr->alignment));
            }

            }
        }
    }
	finalClass = finalClass ? finalClass : differentAlignmentClass;
	wxASSERT_MSG(finalClass != nullptr, "Final class is null");
	return { finalClass, hasNeutral, hasLight, hasDark };
};

void EditorStatisticsPanel::processClassControlsChange(ClassChangeWhat what, bool fromPlayerData)
{
	wxASSERT(gameHasClassAlignment());
	PlayerClass* oldClas = playerAccessor->forPlayer(playerIndex)->getClassPtr();
	// get consistent alignments by sorting
	static const auto sort = [](std::vector<PlayerClass*>& vec) -> void
	{
		std::ranges::sort(vec, [](PlayerClass* const clas1, PlayerClass* const clas2) {return clas1->id < clas2->id; });
	};
	auto currClass = playerAccessor->forPlayer(playerIndex)->getClassPtr();
	PlayerClass* clas = nullptr;
	bool hasNeutral = false, hasLight = false, hasDark = false;
	if (what == CLASS_CHANGE_BASE)
	{
		PlayerClass* newBaseClass = classPtrToBaseClassChoiceIdMap.at(baseClassChoice->GetSelection());
		auto tree = newBaseClass->getClassTree(PlayerClass::TreeOptions(true, true, true));
		sort(tree);
		std::tie(clas, hasNeutral, hasLight, hasDark) = pickNewClass(currClass, tree, currClass->tier, currClass->alignment);
	}
	else if (what == CLASS_CHANGE_TIER)
	{
		// 0 -> 1, 1 -> 0 = change tier only, disable alignment
		// 0 -> 2, 1 -> 2 = change tier, enable alignment selectively, pick first enabled
		// 2 -> 0, 2 -> 1 = change tier, disable alignment
		int newTier = tierRadioBox->GetSelection(), oldTier = currClass->tier;
		auto tree = oldClas->getClassTree(PlayerClass::TreeOptions(true, true, true));
		sort(tree);
		std::tie(clas, hasNeutral, hasLight, hasDark) = pickNewClass(currClass, tree, newTier, ALIGNMENT_NEUTRAL);
	}
	else if (what == CLASS_CHANGE_ALIGNMENT)
	{
		auto tree = oldClas->getClassTree(PlayerClass::TreeOptions(true, true, true));
		sort(tree);
		std::tie(clas, hasNeutral, hasLight, hasDark) = pickNewClass(currClass, tree, currClass->tier, alignmentRadioBox->getSelectedAlignment());
	}
	else if (what == CLASS_CHANGE_ALL) // class is given in class combo box or need update from player data
	{
		clas = fromPlayerData ? playerAccessor->getClassPtr() : classToFullChoiceIdMap.at(fullClassChoice->GetSelection());
		// calling this function here to have consistent hasXXX calculation, even though main result is not used
		std::tie(std::ignore, hasNeutral, hasLight, hasDark) = pickNewClass(currClass, clas->getEntireClassTree(), clas->tier, clas->alignment);
		baseClassChoice->SetSelection(baseClassChoiceIdToClassPtrMap.at(clas->getStarterClass()));
		tierRadioBox->SetSelection(clas->tier);
	}
	else
	{
		wxFAIL;
		assert(false);
    }
    alignmentRadioBox->setSelection(clas->alignment);
    alignmentRadioBox->Enable(hasLight || hasDark);
	playerAccessor->setClass(clas);
	fullClassChoice->SetSelection(fullChoiceIdToClassMap.at(clas));
	for (std::pair<Alignment, bool> pairs[]{ {ALIGNMENT_NEUTRAL, hasNeutral}, {ALIGNMENT_LIGHT, hasLight }, {ALIGNMENT_DARK, hasDark} };
		auto [al, enabled] : pairs)
	{
		alignmentRadioBox->enableAlignment(al, enabled);
	}

	// unlearn skills/spells - either make CLASS_CHANGE_ALL, or put unlearning in calling function after calling with all three enum values
}
void EditorStatisticsPanel::onRecoveryDelayMultiplierChange(wxCommandEvent& event)
{
	HookParams::recoveryMultiplier[rosterIndex] = dynamic_cast<wxSpinCtrlDouble*>(event.GetEventObject())->GetValue();
}

void EditorStatisticsPanel::onRecoverFullyPress(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setRecoveryDelay(0);
}

void EditorStatisticsPanel::onReduceBuffSpellRecoveryCheck(wxCommandEvent& event)
{
	HookParams::buffSpellRecoveryReduced[rosterIndex] = event.IsChecked();
}

void EditorStatisticsPanel::onReduceBuffRecoveryOutOfCombatCheck(wxCommandEvent& event)
{
    HookParams::buffSpellRecoveryReducedOnlyOutOfCombat[rosterIndex] = event.IsChecked();
}

void EditorStatisticsPanel::onFullClassChoiceSelect(wxCommandEvent& event)
{
	processClassControlsChange(CLASS_CHANGE_ALL, false);
}

void EditorStatisticsPanel::onNoRecoveryCheck(wxCommandEvent& event)
{
    wxASSERT_MSG(playerIndex >= 0 && playerIndex <= MAX_PLAYERS, wxString::Format("Invalid player index %d", playerIndex));
    HookParams::noRecoveryEnabled[playerIndex] = event.IsChecked();
	recoveryDelayMultiplierLabel->Enable(!event.IsChecked());
	recoveryDelayMultiplierValue->Enable(!event.IsChecked());
}
void EditorStatisticsPanel::onExtraStatsPaneClick(wxCollapsiblePaneEvent& event)
{
	SendSizeEvent();
	event.Skip();
}

void EditorStatisticsPanel::onStatExtraChange(wxCommandEvent& event)
{
	if (MMVER == 8) return;
	wxSpinCtrl* ctrl = /*static*/dynamic_cast<wxSpinCtrl*>(event.GetEventObject());
	int statId = statIdToStatExtraSpinCtrlMap.at(ctrl);
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
	redBlackGreenTextThreshold(levelBonus, levelBonus->GetValue(), 0);
	playerAccessor->forPlayer(playerIndex)->setStatBonus(STAT_LEVEL, levelBonus->GetValue());
}
void EditorStatisticsPanel::onExperienceChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setExperience(experience->GetValue());
}