#include "pch.h"
#include "EditorSkillsPanel.h"
#include <wx/gbsizer.h>
#include "wx/artprov.h"
#include "PlayerSkill.h"
#include "GameData.h"
#include "PlayerStructAccessor.h"

EditorSkillsPanel::EditorSkillsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxScrolledWindow(parent, id, pos, size, style, name)
{
	SetScrollRate(35, 35);

	mainSizer = new wxBoxSizer(wxVERTICAL);

	createSkillPointsOptionsPanel();

	m_staticline29 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline29, 0, wxEXPAND | wxALL, 5);

	createSkillsPanel();

	mainSizer->Add(0, 25, 0, 0, 5);

	m_staticline28 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline28, 0, wxEXPAND | wxALL, 5);

	this->SetSizer(mainSizer);
	this->Layout();
}

void EditorSkillsPanel::updateFromPlayerSkills()
{
	std::vector<PlayerSkillValue> skills = playerAccessor->forPlayer(playerIndex)->getSkills();
	for (const auto& psv : skills)
	{
		widgetToSkillMap.at(psv.skill)->setValue(psv.value);
	}
}

void EditorSkillsPanel::onSkillValueChange(wxCommandEvent& event)
{
	auto* chooser = dynamic_cast<EditorSkillValueChooser*>(event.GetEventObject());
	PlayerSkill* skill = skillToWidgetMap.at(chooser);
	playerAccessor->forPlayer(playerIndex)->setSkill(skill, chooser->getValue());
}

void EditorSkillsPanel::onSkillPointsChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setSkillPoints(availableSkillPointsAmount->GetValue());
}

void EditorSkillsPanel::onAffectSkillPointsCheck(wxCommandEvent& event)
{
	bool on = event.IsChecked();
	options.affectSkillpoints = on;
	allowNegativeSkillpointsRadio->Enable(on);
	dontAllowSpendingMoreThanAvailableSkillpointsRadio->Enable(on);
}

void EditorSkillsPanel::onDontAllowSpendingMoreThanAvailableSpRadio(wxCommandEvent& event)
{
	options.allowNegativeSkillpoints = false;
}

void EditorSkillsPanel::onAllowNegativeSkillPointsRadio(wxCommandEvent& event)
{
	options.allowNegativeSkillpoints = true;
}

void EditorSkillsPanel::onAffectGoldCheck(wxCommandEvent& event)
{
	bool on = event.IsChecked();
	options.affectGold = on;
	allowNegativeGoldRadio->Enable(on);
	dontAllowSpendingMoreThanAvailableGoldRadio->Enable(on);
}

void EditorSkillsPanel::onDontAllowSpendingMoreThanAvailableGoldRadio(wxCommandEvent& event)
{
	options.allowNegativeGold = false;
}

void EditorSkillsPanel::onAllowNegativeGoldRadio(wxCommandEvent& event)
{
	options.allowNegativeGold = true;
}

void EditorSkillsPanel::onRespectClassConstraintsNoRadio(wxCommandEvent& event)
{
	options.classConstraint = PlayerStructAccessor::CLASS_CONSTRAINT_NONE;
}

void EditorSkillsPanel::onRespectClassConstraintsCurrentRadio(wxCommandEvent& event)
{
	options.classConstraint = PlayerStructAccessor::CLASS_CONSTRAINT_CURRENT_CLASS;
}

void EditorSkillsPanel::onRespectClassConstraintsPromotionRadio(wxCommandEvent& event)
{
	options.classConstraint = PlayerStructAccessor::CLASS_CONSTRAINT_ANY_PROMOTION_CLASS;
}

void EditorSkillsPanel::onApplyClassConstraintsButton(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->applyClassConstraints(options);
}

void EditorSkillsPanel::onAffectWeaponsCheck(wxCommandEvent& event)
{
	affectCheckboxHelper(event.IsChecked(), SKILLCAT_WEAPON);
}

void EditorSkillsPanel::onAffectArmorCheck(wxCommandEvent& event)
{
	affectCheckboxHelper(event.IsChecked(), SKILLCAT_ARMOR);
}

void EditorSkillsPanel::onAffectMagicCheck(wxCommandEvent& event)
{
	affectCheckboxHelper(event.IsChecked(), SKILLCAT_MAGIC);
}

void EditorSkillsPanel::onAffectMiscCheck(wxCommandEvent& event)
{
	affectCheckboxHelper(event.IsChecked(), SKILLCAT_MISC);
}

void EditorSkillsPanel::onGodModeButton(wxCommandEvent& event)
{
}

void EditorSkillsPanel::onSetAllSkillsButton(wxCommandEvent& event)
{
}

void EditorSkillsPanel::onOnlyAlreadyLearnedCheck(wxCommandEvent& event)
{
}

void EditorSkillsPanel::affectCheckboxHelper(bool on, SkillCategory cat)
{
	auto& vec = options.batchSetAffectWhichSkillCategories;
	if (on && !existsInVector(vec, cat))
	{
		vec.push_back(cat);
	}
	else if (on && existsInVector(vec, cat))
	{
		vec.erase(vec.begin() + indexInVector(vec, cat));
	}
}

EditorSkillsPanel::~EditorSkillsPanel()
{
}

void EditorSkillsPanel::createSkillPointsOptionsPanel()
{
	skillPointsAndOptionsHeader = new wxStaticText(this, wxID_ANY, _("Skill points && options"), wxDefaultPosition, wxDefaultSize, 0);
	skillPointsAndOptionsHeader->Wrap(-1);
	skillPointsAndOptionsHeader->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(skillPointsAndOptionsHeader, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxBoxSizer* skillPointsSizer;
	skillPointsSizer = new wxBoxSizer(wxHORIZONTAL);

	availableSkillPointsLabel = new wxStaticText(this, wxID_ANY, _("Skill points:"), wxDefaultPosition, wxDefaultSize, 0);
	availableSkillPointsLabel->Wrap(-1);
	skillPointsSizer->Add(availableSkillPointsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	availableSkillPointsAmount = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999999, 0);
	skillPointsSizer->Add(availableSkillPointsAmount, 0, wxALL, 5);


	mainSizer->Add(skillPointsSizer, 0, wxEXPAND, 5);

	wxBoxSizer* spentSkillPointsSizer;
	spentSkillPointsSizer = new wxBoxSizer(wxHORIZONTAL);

	spentSkillPointsLabel = new wxStaticText(this, wxID_ANY, _("Spent skill points:"), wxDefaultPosition, wxDefaultSize, 0);
	spentSkillPointsLabel->Wrap(-1);
	spentSkillPointsLabel->SetToolTip(_("Total for all learned skills"));

	spentSkillPointsSizer->Add(spentSkillPointsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	spentSkillPointsValue = new wxTextCtrl(this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
	spentSkillPointsValue->Enable(false);

	spentSkillPointsSizer->Add(spentSkillPointsValue, 0, wxALL, 5);


	mainSizer->Add(spentSkillPointsSizer, 0, wxEXPAND, 5);

	wxBoxSizer* optionsSizer;
	optionsSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* optionsSkillpointsSizer;
	optionsSkillpointsSizer = new wxBoxSizer(wxHORIZONTAL);

	affectAvailableSkillpointsCheckbox = new wxCheckBox(this, wxID_ANY, _("Affect available skillpoints:"), wxDefaultPosition, wxDefaultSize, 0);
	optionsSkillpointsSizer->Add(affectAvailableSkillpointsCheckbox, 0, wxALL, 5);

	dontAllowSpendingMoreThanAvailableSkillpointsRadio = new wxRadioButton(this, wxID_ANY, _("Don't allow spending more than available"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	optionsSkillpointsSizer->Add(dontAllowSpendingMoreThanAvailableSkillpointsRadio, 0, wxALL, 5);

	allowNegativeSkillpointsRadio = new wxRadioButton(this, wxID_ANY, _("Allow negative skillpoints"), wxDefaultPosition, wxDefaultSize, 0);
	allowNegativeSkillpointsRadio->SetToolTip(_("Might not work correctly ingame. Use at your own risk"));

	optionsSkillpointsSizer->Add(allowNegativeSkillpointsRadio, 0, wxALL, 5);


	optionsSizer->Add(optionsSkillpointsSizer, 1, wxEXPAND, 5);

	wxBoxSizer* optionsGoldSizer;
	optionsGoldSizer = new wxBoxSizer(wxHORIZONTAL);

	affectGoldCheckbox = new wxCheckBox(this, wxID_ANY, _("Affect gold:"), wxDefaultPosition, wxDefaultSize, 0);
	optionsGoldSizer->Add(affectGoldCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	dontAllowSpendingMoreThanAvailableGoldRadio = new wxRadioButton(this, wxID_ANY, _("Don't allow spending more than available"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	optionsGoldSizer->Add(dontAllowSpendingMoreThanAvailableGoldRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	allowNegativeGoldRadio = new wxRadioButton(this, wxID_ANY, _("Allow negative gold"), wxDefaultPosition, wxDefaultSize, 0);
	allowNegativeGoldRadio->SetToolTip(_("Might not work correctly ingame. Use at your own risk"));

	optionsGoldSizer->Add(allowNegativeGoldRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	goldDisplayText = new wxTextCtrl(this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
	goldDisplayText->Enable(false);
	goldDisplayText->SetToolTip(_("Current gold"));

	optionsGoldSizer->Add(goldDisplayText, 0, wxALL, 5);

	goldLabel = new wxStaticText(this, wxID_ANY, _("G"), wxDefaultPosition, wxDefaultSize, 0);
	goldLabel->Wrap(-1);
	optionsGoldSizer->Add(goldLabel, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);


	optionsSizer->Add(optionsGoldSizer, 1, wxEXPAND, 5);


	mainSizer->Add(optionsSizer, 0, wxEXPAND, 5);
}

void EditorSkillsPanel::createSkillsPanel()
{
	skillValuesLabel = new wxStaticText(this, wxID_ANY, _("Set skill values:"), wxDefaultPosition, wxDefaultSize, 0);
	skillValuesLabel->Wrap(-1);
	skillValuesLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(skillValuesLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	mainSizer->Add(0, 25, 0, 0, 5);

	wxGridBagSizer* skillsSizer;
	skillsSizer = new wxGridBagSizer(5, 5);
	skillsSizer->SetFlexibleDirection(wxBOTH);
	skillsSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

#define CREATESIZER(name) wxFlexGridSizer* name; \
	name = new wxFlexGridSizer(0, 1, 5, 0); \
	name->SetFlexibleDirection(wxHORIZONTAL); \
	name->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED)

	CREATESIZER(weaponSkillsFgSizer);
	skillsSizer->Add(weaponSkillsFgSizer, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND, 5);

	m_staticline121 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	skillsSizer->Add(m_staticline121, wxGBPosition(0, 1), wxGBSpan(3, 1), wxEXPAND | wxALL, 5);

	CREATESIZER(armorSkillsFgSizer);
	skillsSizer->Add(armorSkillsFgSizer, wxGBPosition(0, 2), wxGBSpan(1, 1), wxEXPAND, 5);

	m_staticline151 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	skillsSizer->Add(m_staticline151, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 5);
	m_staticline16 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	skillsSizer->Add(m_staticline16, wxGBPosition(1, 2), wxGBSpan(1, 1), wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	CREATESIZER(magicSkillsFgSizer);
	skillsSizer->Add(magicSkillsFgSizer, wxGBPosition(2, 0), wxGBSpan(1, 1), wxEXPAND, 5);

	CREATESIZER(miscSkillsFgSizer);
	skillsSizer->Add(miscSkillsFgSizer, wxGBPosition(2, 2), wxGBSpan(1, 1), wxEXPAND, 5);
#undef CREATESIZER

	// FILL WITH SKILLS
	for (auto& [id, skill] : GameData::skills)
	{
		EditorSkillValueChooser* chooser = new EditorSkillValueChooser(this, skill.name);
		widgetToSkillMap[&skill] = chooser;
		int id = chooser->GetId();
		widgetToWidgetIdMap[id] = chooser;
		chooser->setValue(SkillValue{ 0, 0 });
		chooser->skillLevel->Bind(wxEVT_SPINCTRL, &EditorSkillsPanel::onSkillValueChange, this);
		chooser->skillMastery->Bind(wxEVT_CHOICE, &EditorSkillsPanel::onSkillValueChange, this);
		switch (skill.category)
		{
		case SKILLCAT_WEAPON:
			weaponSkillsFgSizer->Add(chooser);
			break;
		case SKILLCAT_ARMOR:
			armorSkillsFgSizer->Add(chooser);
			break;
		case SKILLCAT_MAGIC:
			magicSkillsFgSizer->Add(chooser);
			break;
		case SKILLCAT_MISC:
			miscSkillsFgSizer->Add(chooser);
			break;
		default:
			wxLogError("Unknown skill category %d", (int)skill.category);
		}
	}
	skillToWidgetMap = invertMap(widgetToSkillMap);

	mainSizer->Add(skillsSizer, 0, 0, 5);
}

void EditorSkillsPanel::createActionsPanel()
{
	actionsLabel = new wxStaticText(this, wxID_ANY, _("Actions:"), wxDefaultPosition, wxDefaultSize, 0);
	actionsLabel->Wrap(-1);
	actionsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(actionsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxBoxSizer* checkboxesSizer;
	checkboxesSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer* classConstraintsSizer;
	classConstraintsSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Respect class constraints?")), wxHORIZONTAL);

	classConstraintsNone = new wxRadioButton(classConstraintsSizer->GetStaticBox(), wxID_ANY, _("No"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	classConstraintsNone->SetValue(true);
	classConstraintsSizer->Add(classConstraintsNone, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	classConstraintsCurrentClass = new wxRadioButton(classConstraintsSizer->GetStaticBox(), wxID_ANY, _("Of current class"), wxDefaultPosition, wxDefaultSize, 0);
	classConstraintsSizer->Add(classConstraintsCurrentClass, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	classConstraintsPromotionClass = new wxRadioButton(classConstraintsSizer->GetStaticBox(), wxID_ANY, _("Of any promotion class"), wxDefaultPosition, wxDefaultSize, 0);
	classConstraintsPromotionClass->SetToolTip(_("The one which has highest mastery possible"));

	classConstraintsSizer->Add(classConstraintsPromotionClass, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	applyClassConstraintsButton = new wxButton(classConstraintsSizer->GetStaticBox(), wxID_ANY, _("Apply right now"), wxDefaultPosition, wxDefaultSize, 0);
	applyClassConstraintsButton->SetToolTip(_("Only applies class constraints and takes into account gold and skillpoint settings. No other action is done"));

	classConstraintsSizer->Add(applyClassConstraintsButton, 0, wxALL, 5);


	checkboxesSizer->Add(classConstraintsSizer, 0, 0, 5);

	respectClassConstraintsTooltip = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON), wxDefaultPosition, wxDefaultSize, 0);
	respectClassConstraintsTooltip->SetToolTip(_("Skills will be learned at maximum level class supports. This means any use will reduce affected skill to compatible level! Skills class can't learn will be unlearned."));

	checkboxesSizer->Add(respectClassConstraintsTooltip, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	mainSizer->Add(checkboxesSizer, 0, wxEXPAND, 5);

	wxStaticBoxSizer* affectSizer;
	affectSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Affect which skill categories?")), wxHORIZONTAL);

	affectWeaponsCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Weapons"), wxDefaultPosition, wxDefaultSize, 0);
	affectWeaponsCheckbox->SetValue(true);
	affectSizer->Add(affectWeaponsCheckbox, 0, wxALL, 5);

	affectArmorCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Armor"), wxDefaultPosition, wxDefaultSize, 0);
	affectArmorCheckbox->SetValue(true);
	affectSizer->Add(affectArmorCheckbox, 0, wxALL, 5);

	affectMagicCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Magic"), wxDefaultPosition, wxDefaultSize, 0);
	affectMagicCheckbox->SetValue(true);
	affectSizer->Add(affectMagicCheckbox, 0, wxALL, 5);

	affectMiscCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Misc"), wxDefaultPosition, wxDefaultSize, 0);
	affectMiscCheckbox->SetValue(true);
	affectSizer->Add(affectMiscCheckbox, 0, wxALL, 5);


	mainSizer->Add(affectSizer, 0, 0, 5);

	wxStaticBoxSizer* learnSizer;
	learnSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Learn")), wxHORIZONTAL);

	wxBoxSizer* learnButtonsSizer;
	learnButtonsSizer = new wxBoxSizer(wxVERTICAL);

	godModeButton = new wxButton(learnSizer->GetStaticBox(), wxID_ANY, _("Learn all skills at maximum level game supports (god mode)"), wxDefaultPosition, wxDefaultSize, 0);
	learnButtonsSizer->Add(godModeButton, 0, wxALL, 5);

	wxBoxSizer* learnAllSkillsAtSizer;
	learnAllSkillsAtSizer = new wxBoxSizer(wxHORIZONTAL);

	setAllSkillsToButton = new wxButton(learnSizer->GetStaticBox(), wxID_ANY, _("Set all skills to:"), wxDefaultPosition, wxDefaultSize, 0);
	learnAllSkillsAtSizer->Add(setAllSkillsToButton, 0, wxALL, 5);

	setAllSkillsToLevelSpinCtrl = new wxSpinCtrl(learnSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 1);
	learnAllSkillsAtSizer->Add(setAllSkillsToLevelSpinCtrl, 0, wxALL, 5);

	wxString setAllSkillsToMasteryChoiceChoices[] = { _("None"), _("Novice"), _("Expert"), _("Master"), _("Grandmaster") };
	int setAllSkillsToMasteryChoiceNChoices = sizeof(setAllSkillsToMasteryChoiceChoices) / sizeof(wxString);
	setAllSkillsToMasteryChoice = new wxChoice(learnSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, setAllSkillsToMasteryChoiceNChoices, setAllSkillsToMasteryChoiceChoices, 0);
	setAllSkillsToMasteryChoice->SetSelection(1);
	learnAllSkillsAtSizer->Add(setAllSkillsToMasteryChoice, 0, wxALL, 5);


	learnButtonsSizer->Add(learnAllSkillsAtSizer, 0, wxEXPAND, 5);


	learnSizer->Add(learnButtonsSizer, 0, 0, 5);

	m_staticline31 = new wxStaticLine(learnSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	learnSizer->Add(m_staticline31, 0, wxEXPAND, 5);

	wxBoxSizer* learnSettingsSizer;
	learnSettingsSizer = new wxBoxSizer(wxHORIZONTAL);

	onlyAlreadyLearnedCheckbox = new wxCheckBox(learnSizer->GetStaticBox(), wxID_ANY, _("Only already learned"), wxDefaultPosition, wxDefaultSize, 0);
	learnSettingsSizer->Add(onlyAlreadyLearnedCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	learnSizer->Add(learnSettingsSizer, 1, wxEXPAND, 5);


	mainSizer->Add(learnSizer, 0, 0, 5);

	wxBoxSizer* resetLearnedSkillsSizer;
	resetLearnedSkillsSizer = new wxBoxSizer(wxVERTICAL);


	mainSizer->Add(resetLearnedSkillsSizer, 1, wxEXPAND, 5);
}