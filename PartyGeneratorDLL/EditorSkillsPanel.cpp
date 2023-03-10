#include "pch.h"
#include "EditorSkillsPanel.h"
#include <wx/gbsizer.h>
#include "wx/artprov.h"
#include "PlayerSkill.h"
#include "GameData.h"
#include "PlayerStructAccessor.h"
#include <globals.h>
#include "PartyStructAccessor.h"
extern wxTimer* mainUpdateTimer;

EditorSkillsPanel::EditorSkillsPanel(wxWindow* parent, int playerIndex) : wxScrolledWindow(parent), playerIndex(playerIndex)
{
	SetScrollRate(10, 10);

	//SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_MENU));

	mainSizer = new wxBoxSizer(wxVERTICAL);

	createSkillPointsOptionsPanel();

	m_staticline29 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline29, 0, wxEXPAND | wxALL, 5);

	createSkillsPanel();

	mainSizer->Add(0, 25, 0, 0, 5);

	m_staticline28 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline28, 0, wxEXPAND | wxALL, 5);

	/*updateCallback = [this] {
		if (this->IsShown())
		{
			this->updateSkillBonuses();
			this->updateFromPlayerSkills();
		}
	};*/

	createActionsPanel();

	// DOESN'T WORK ON WXNOTEBOOK / WXPANEL
// 	Bind(wxEVT_SET_FOCUS, &EditorSkillsPanel::onSetFocus, this);
// 	Bind(wxEVT_ACTIVATE, &EditorSkillsPanel::onActivate, this);

	this->SetSizer(mainSizer);
	this->Layout();
}

void EditorSkillsPanel::updateFromPlayerData()
{
	updateSkillBonuses();
	std::vector<PlayerSkillValue> skills = playerAccessor->forPlayer(playerIndex)->getSkills();
	for (const auto& psv : skills)
	{
		widgetToSkillMap.at(psv.skill)->setValue(psv.value);
	}
	goldDisplayText->SetLabel(wxString::Format("%d", partyAccessor->getGold()));
	spentSkillPointsValue->SetValue(wxString::Format("%d", playerAccessor->getSpentSkillPoints()));
	availableSkillPointsAmount->SetValue(wxString::Format("%d", playerAccessor->getSkillPoints()));
	Layout();
}

void EditorSkillsPanel::updateSkillBonuses()
{
	if (MMVER == 6 || !inGame) return;
	(void)playerAccessor->forPlayer(playerIndex);
	for (auto& [id, skill] : GameData::skills)
	{
		auto* widget = widgetToSkillMap.at(&skill);
		int bonus = playerAccessor->getSkillBonus(id);
		widget->updateSkillBonus(bonus);
	}
}

void EditorSkillsPanel::skillConstraintErrorMsgBox(bool multiple)
{
	const wxString error = multiple ? "Some skills could not be set due to constraints." : "Skill could not be set due to constraints.";
	const wxString caption = multiple ? "Action partially completed" : "Action not completed";
	wxMessageBox(error, caption, wxOK | wxICON_INFORMATION, this);
}

void EditorSkillsPanel::onSkillValueChange(wxCommandEvent& event)
{
	auto* chooser = dynamic_cast<EditorSkillValueChooser*>(event.GetEventObject());
	PlayerSkill* skill = skillToWidgetMap.at(chooser);
	SkillValue oldValue = playerAccessor->forPlayer(playerIndex)->getSkill(skill);
	SkillValue newValue = chooser->getValue();
	if (oldValue.isZero() && (newValue.level > 0 || newValue.mastery > 0))
	{
		newValue.level = std::max(newValue.level, 1);
		newValue.mastery = std::max(newValue.mastery, (int)MASTERY_NOVICE);
	}
	else if (newValue.isZero() && (oldValue.level > 0 || oldValue.mastery > 0))
	{
		newValue = SkillValue{ 0, 0 };
	}
	if (!playerAccessor->setSkill(skill, newValue, options))
	{
		skillConstraintErrorMsgBox(false);
	}
	else
	{
		newValue = playerAccessor->getSkill(skill); // might have been reduced by class constraint
		chooser->setValue(newValue);
		chooser->updateSkillBonus(playerAccessor->getSkillBonus(skill));
		Layout();
		if (options.affectSkillpoints)
		{
			onSkillPointsChange(event);
		}
		if (options.affectGold)
		{
			goldDisplayText->SetValue(wxString::Format("%d", partyAccessor->getGold()));
		}
		spentSkillPointsValue->SetValue(wxString::Format("%d", playerAccessor->getSpentSkillPoints()));
	}
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
	updateFromPlayerData();
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
	bool learnedOnly = onlyAlreadyLearnedCheckbox->IsChecked();
	std::vector<PlayerSkillValue> skillsToSet;
	(void)playerAccessor->forPlayer(playerIndex);
	for (auto& [id, skill] : GameData::skills)
	{
		if (!learnedOnly || !playerAccessor->getSkill(&skill).isZero())
		{
			skillsToSet.push_back(PlayerSkillValue{ &skill, SkillValue{ MAX_SKILL_LEVEL, MAX_MASTERY } });
		}
	}
	if (!playerAccessor->setSkills(skillsToSet, options))
	{
		skillConstraintErrorMsgBox(true);
	}
	updateFromPlayerData();
}

void EditorSkillsPanel::onSetAllSkillsButton(wxCommandEvent& event)
{
	bool learnedOnly = onlyAlreadyLearnedCheckbox->IsChecked();
	std::vector<PlayerSkillValue> skillsToSet;
	SkillValue val{ setAllSkillsToLevelSpinCtrl->GetValue(), static_cast<Mastery>(setAllSkillsToMasteryChoice->GetSelection()) };
	(void)playerAccessor->forPlayer(playerIndex);
	for (auto& [id, skill] : GameData::skills)
	{
		if (!learnedOnly || !playerAccessor->getSkill(&skill).isZero())
		{
			skillsToSet.push_back(PlayerSkillValue{ &skill, val });
		}
	}
	if (!playerAccessor->forPlayer(playerIndex)->setSkills(skillsToSet, options))
	{
		skillConstraintErrorMsgBox(true);
	}
	updateFromPlayerData();
}

void EditorSkillsPanel::onOnlyAlreadyLearnedCheck(wxCommandEvent& event)
{
	
}

void EditorSkillsPanel::onShowUnobtainableSkillsCheck(wxCommandEvent& event)
{
	for (auto& [id, skill] : GameData::skills)
	{
		if (skill.doNotGenerate)
		{
			auto* chooser = widgetToSkillMap.at(&skill);
			chooser->Show(event.IsChecked());
		}
	}
	Layout();
	// somehow Layout() got broken, idk if by adding colors to choosers or (more probable) adding inner panel,
	// so need to send size event to have correct layout
	SendSizeEvent();
}

void EditorSkillsPanel::affectCheckboxHelper(bool on, SkillCategory cat)
{
	auto& vec = options.batchSetAffectWhichSkillCategories;
	if (on && !existsInVector(vec, cat))
	{
		vec.push_back(cat);
	}
	else if (!on && existsInVector(vec, cat))
	{
		vec.erase(vec.begin() + indexInVector(vec, cat));
	}
}

void EditorSkillsPanel::onScrollStart(wxScrollWinEvent& event)
{
	Freeze();
}

void EditorSkillsPanel::onScrollRelease(wxScrollWinEvent& event)
{
	Thaw();
	Update();
}

EditorSkillsPanel::~EditorSkillsPanel()
{
}

bool EditorSkillsPanel::AcceptsFocus() const
{
	return true;
}

void EditorSkillsPanel::createSkillPointsOptionsPanel()
{
	skillPointsAndOptionsHeader = new wxStaticText(this, wxID_ANY, _("Skill points && options"), wxDefaultPosition, wxDefaultSize, 0); // && is ampersand escape
	skillPointsAndOptionsHeader->Wrap(-1);
	skillPointsAndOptionsHeader->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(skillPointsAndOptionsHeader, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	mainSizer->AddSpacer(30);

	wxBoxSizer* skillPointsSizer;
	skillPointsSizer = new wxBoxSizer(wxHORIZONTAL);

	availableSkillPointsLabel = new wxStaticText(this, wxID_ANY, _("Skill points:"), wxDefaultPosition, wxDefaultSize, 0);
	availableSkillPointsLabel->Wrap(-1);
	skillPointsSizer->Add(availableSkillPointsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	availableSkillPointsAmount = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999999, 0);
	skillPointsSizer->Add(availableSkillPointsAmount, 0, wxALL, 5);
	availableSkillPointsAmount->Bind(wxEVT_SPINCTRL, &EditorSkillsPanel::onSkillPointsChange, this);

	wxBoxSizer* spentSkillPointsSizer;
	spentSkillPointsSizer = new wxBoxSizer(wxHORIZONTAL);

	spentSkillPointsLabel = new wxStaticText(this, wxID_ANY, _("Spent skill points:"), wxDefaultPosition, wxDefaultSize, 0);
	spentSkillPointsLabel->Wrap(-1);
	spentSkillPointsLabel->SetToolTip(_("Total for all learned skills"));

	spentSkillPointsSizer->Add(spentSkillPointsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	spentSkillPointsValue = new wxTextCtrl(this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
	spentSkillPointsValue->Enable(false);

	spentSkillPointsSizer->Add(spentSkillPointsValue, 0, wxALL, 5);

	skillPointsSizer->AddSpacer(30);

	skillPointsSizer->Add(spentSkillPointsSizer, 0, wxEXPAND, 5);

	mainSizer->Add(skillPointsSizer, 0, wxEXPAND, 5);

	wxBoxSizer* optionsSizer;
	optionsSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* optionsSkillpointsSizer;
	optionsSkillpointsSizer = new wxBoxSizer(wxHORIZONTAL);

	affectAvailableSkillpointsCheckbox = new wxCheckBox(this, wxID_ANY, _("Affect available skillpoints:"), wxDefaultPosition, wxDefaultSize, 0);
	optionsSkillpointsSizer->Add(affectAvailableSkillpointsCheckbox, 0, wxALL, 5);
	affectAvailableSkillpointsCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onAffectSkillPointsCheck, this);

	dontAllowSpendingMoreThanAvailableSkillpointsRadio = new wxRadioButton(this, wxID_ANY, _("Don't allow spending more than available"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	optionsSkillpointsSizer->Add(dontAllowSpendingMoreThanAvailableSkillpointsRadio, 0, wxALL, 5);
	dontAllowSpendingMoreThanAvailableSkillpointsRadio->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onDontAllowSpendingMoreThanAvailableSpRadio, this);
	dontAllowSpendingMoreThanAvailableSkillpointsRadio->Disable();

	allowNegativeSkillpointsRadio = new wxRadioButton(this, wxID_ANY, _("Allow negative skillpoints"), wxDefaultPosition, wxDefaultSize, 0);
	allowNegativeSkillpointsRadio->SetToolTip(_("Might not work correctly ingame. Use at your own risk"));
	allowNegativeSkillpointsRadio->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onAllowNegativeSkillPointsRadio, this);
	allowNegativeSkillpointsRadio->Disable();

	optionsSkillpointsSizer->Add(allowNegativeSkillpointsRadio, 0, wxALL, 5);


	optionsSizer->Add(optionsSkillpointsSizer, 1, wxEXPAND, 5);

	wxBoxSizer* optionsGoldSizer;
	optionsGoldSizer = new wxBoxSizer(wxHORIZONTAL);

	affectGoldCheckbox = new wxCheckBox(this, wxID_ANY, _("Affect gold:"), wxDefaultPosition, wxDefaultSize, 0);
	optionsGoldSizer->Add(affectGoldCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	affectGoldCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onAffectGoldCheck, this);

	dontAllowSpendingMoreThanAvailableGoldRadio = new wxRadioButton(this, wxID_ANY, _("Don't allow spending more than available"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	optionsGoldSizer->Add(dontAllowSpendingMoreThanAvailableGoldRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	dontAllowSpendingMoreThanAvailableGoldRadio->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onDontAllowSpendingMoreThanAvailableGoldRadio, this);
	dontAllowSpendingMoreThanAvailableGoldRadio->Disable();

	allowNegativeGoldRadio = new wxRadioButton(this, wxID_ANY, _("Allow negative gold"), wxDefaultPosition, wxDefaultSize, 0);
	allowNegativeGoldRadio->SetToolTip(_("Might not work correctly ingame. Use at your own risk"));
	allowNegativeGoldRadio->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onAllowNegativeGoldRadio, this);
	allowNegativeGoldRadio->Disable();

	optionsGoldSizer->Add(allowNegativeGoldRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	goldDisplayText = new wxTextCtrl(this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
	goldDisplayText->Enable(false);
	goldDisplayText->SetToolTip(_("Current gold"));

	optionsGoldSizer->Add(goldDisplayText, 0, wxALL, 5);

	goldLabel = new wxStaticText(this, wxID_ANY, _("G"), wxDefaultPosition, wxDefaultSize, 0);
	goldLabel->Wrap(-1);
	optionsGoldSizer->Add(goldLabel, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);


	optionsSizer->Add(optionsGoldSizer, 1, wxEXPAND, 5);

	wxBoxSizer* classConstraintsSizer;
	classConstraintsSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer* classConstraintsInnerSizer;
	classConstraintsInnerSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Respect class constraints?")), wxHORIZONTAL);

	classConstraintsNone = new wxRadioButton(classConstraintsInnerSizer->GetStaticBox(), wxID_ANY, _("No"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	classConstraintsNone->SetValue(true);
	classConstraintsInnerSizer->Add(classConstraintsNone, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	classConstraintsNone->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onRespectClassConstraintsNoRadio, this);

	classConstraintsCurrentClass = new wxRadioButton(classConstraintsInnerSizer->GetStaticBox(), wxID_ANY, _("Of current class"), wxDefaultPosition, wxDefaultSize, 0);
	classConstraintsInnerSizer->Add(classConstraintsCurrentClass, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	classConstraintsCurrentClass->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onRespectClassConstraintsCurrentRadio, this);

	classConstraintsPromotionClass = new wxRadioButton(classConstraintsInnerSizer->GetStaticBox(), wxID_ANY, _("Of any promotion class"), wxDefaultPosition, wxDefaultSize, 0);
	classConstraintsPromotionClass->SetToolTip(_("The one which has highest mastery possible"));
	classConstraintsPromotionClass->Bind(wxEVT_RADIOBUTTON, &EditorSkillsPanel::onRespectClassConstraintsPromotionRadio, this);

	classConstraintsInnerSizer->Add(classConstraintsPromotionClass, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	applyClassConstraintsButton = new wxButton(classConstraintsInnerSizer->GetStaticBox(), wxID_ANY, _("Apply right now"), wxDefaultPosition, wxDefaultSize, 0);
	applyClassConstraintsButton->SetToolTip(_("Only applies class constraints and takes into account gold and skillpoint settings. No other action is done"));
	applyClassConstraintsButton->Bind(wxEVT_BUTTON, &EditorSkillsPanel::onApplyClassConstraintsButton, this);

	classConstraintsInnerSizer->Add(applyClassConstraintsButton, 0, wxALL, 5);


	classConstraintsSizer->Add(classConstraintsInnerSizer, 0, wxALL, 5);

	respectClassConstraintsTooltip = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON), wxDefaultPosition, wxDefaultSize, 0);
	respectClassConstraintsTooltip->SetToolTip(_("Skills will be learned at maximum level class supports. This means any use will reduce affected skill to compatible level! Skills class can't learn will be unlearned."));

	classConstraintsSizer->Add(respectClassConstraintsTooltip, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	optionsSizer->Add(classConstraintsSizer, 0, wxEXPAND, 5);

	mainSizer->Add(optionsSizer, 0, wxEXPAND, 5);
}

void EditorSkillsPanel::createSkillsPanel()
{
	skillValuesLabel = new wxStaticText(this, wxID_ANY, _("Set skill values:"), wxDefaultPosition, wxDefaultSize, 0);
	skillValuesLabel->Wrap(-1);
	skillValuesLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	mainSizer->Add(skillValuesLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	mainSizer->Add(0, 25, 0, 0, 5);
	showUnobtainableSkillsCheckbox = new wxCheckBox(this, wxID_ANY, "Show unobtainable skills");
	showUnobtainableSkillsCheckbox->SetToolTip("They are useless, unless a mod changes them");
	showUnobtainableSkillsCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onShowUnobtainableSkillsCheck, this);
	mainSizer->Add(showUnobtainableSkillsCheckbox, wxSizerFlags().Border(wxALL, 5));

	wxBoxSizer* skillsSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* leftSkillsSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightSkillsSizer = new wxBoxSizer(wxVERTICAL);

	m_staticline121 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	skillsSizerHorizontal->Add(leftSkillsSizer, wxSizerFlags(1).Expand());
	skillsSizerHorizontal->Add(m_staticline121, wxSizerFlags().Expand());
	skillsSizerHorizontal->Add(rightSkillsSizer, wxSizerFlags(1).Expand());

	const wxSizerFlags skillSizerFlags = wxSizerFlags().Expand().Border(wxALL, 5);

	static wxColour skillCategoriesLabelColour(135, 132, 73);
	static wxFont skillCategoriesLabelFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD);
	static wxSizerFlags skillCategoriesLabelFlags = wxSizerFlags().Border(wxBOTTOM, 5);

	wxBoxSizer* weaponSkillsSizer = new wxBoxSizer(wxVERTICAL);
	leftSkillsSizer->Add(weaponSkillsSizer, skillSizerFlags);
	wxStaticText* weaponSkillsSizerLabel = new wxStaticText(this, wxID_ANY, _("Weapons"));
	weaponSkillsSizerLabel->SetOwnFont(skillCategoriesLabelFont);
	weaponSkillsSizerLabel->SetOwnForegroundColour(skillCategoriesLabelColour);
	weaponSkillsSizer->Add(weaponSkillsSizerLabel, skillCategoriesLabelFlags);

	wxBoxSizer* armorSkillsSizer = new wxBoxSizer(wxVERTICAL);
	rightSkillsSizer->Add(armorSkillsSizer, skillSizerFlags);
	wxStaticText* armorSkillsSizerLabel = new wxStaticText(this, wxID_ANY, _("Armor"));
	armorSkillsSizerLabel->SetOwnFont(skillCategoriesLabelFont);
	armorSkillsSizerLabel->SetOwnForegroundColour(skillCategoriesLabelColour);
	armorSkillsSizer->Add(armorSkillsSizerLabel, skillCategoriesLabelFlags);

	m_staticline151 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	leftSkillsSizer->Add(m_staticline151, wxSizerFlags().Expand().Border(wxALL & (~wxRIGHT), 5));
	m_staticline16 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	rightSkillsSizer->Add(m_staticline16, wxSizerFlags().Expand().Border(wxALL & (~wxLEFT), 5));

	wxBoxSizer* magicSkillsSizer = new wxBoxSizer(wxVERTICAL);
	leftSkillsSizer->Add(magicSkillsSizer, skillSizerFlags);
	wxStaticText* magicSkillsSizerLabel = new wxStaticText(this, wxID_ANY, _("Magic"));
	magicSkillsSizerLabel->SetOwnFont(skillCategoriesLabelFont);
	magicSkillsSizerLabel->SetOwnForegroundColour(skillCategoriesLabelColour);
	magicSkillsSizer->Add(magicSkillsSizerLabel, skillCategoriesLabelFlags);

	wxBoxSizer* miscSkillsSizer = new wxBoxSizer(wxVERTICAL);
	rightSkillsSizer->Add(miscSkillsSizer, skillSizerFlags);
	wxStaticText* miscSkillsSizerLabel = new wxStaticText(this, wxID_ANY, _("Misc"));
	miscSkillsSizerLabel->SetOwnFont(skillCategoriesLabelFont);
	miscSkillsSizerLabel->SetOwnForegroundColour(skillCategoriesLabelColour);
	miscSkillsSizer->Add(miscSkillsSizerLabel, skillCategoriesLabelFlags);

	// FILL WITH SKILLS
	wxASSERT(GameData::skills.size() > 10);
// 	widgetToSkillMap.reserve(GameData::skills.size()); // INCREASES LOAD TIME ???
// 	widgetToWidgetIdMap.reserve(GameData::skills.size());
	Freeze();
	Profiler profiler;
	profiler.startAggregate("Creating skill value choosers");
	// unobtainable skills are at the end to not cause problems with every-row-is-other-color system
	std::vector<PlayerSkill*> skillsInOrder;
	skillsInOrder.resize(GameData::skills.size());
	std::vector<PlayerSkill*> doNotGenerateSkills;
	int i = 0;
	for (auto& [id, skill] : GameData::skills)
	{
		if (skill.doNotGenerate)
		{
			doNotGenerateSkills.push_back(&skill);
		}
		else
		{
			skillsInOrder[i++] = &skill;
		}
	}
	const int firstNewIndex = i;
	while (i < skillsInOrder.size())
	{
		skillsInOrder[i] = doNotGenerateSkills[i - firstNewIndex];
		++i;
	}

	const wxSizerFlags chooserFlags = wxSizerFlags().Expand(); // Expand is important; no border here - set in chooser in inner panel
	for (PlayerSkill* skillPtr : skillsInOrder)
	{
		profiler.startAggregatePart();
		EditorSkillValueChooser* chooser = new EditorSkillValueChooser(this, skillPtr->name);
		widgetToSkillMap[skillPtr] = chooser;
		int id = chooser->GetId();
		widgetToWidgetIdMap[id] = chooser;
		chooser->setValue(SkillValue{ 0, 0 });
		chooser->Bind(SKILL_VALUE_CHANGE, &EditorSkillsPanel::onSkillValueChange, this);

		switch (skillPtr->category)
		{
		case SKILLCAT_WEAPON:
			weaponSkillsSizer->Add(chooser, chooserFlags);
			break;
		case SKILLCAT_ARMOR:
			armorSkillsSizer->Add(chooser, chooserFlags);
			break;
		case SKILLCAT_MAGIC:
			magicSkillsSizer->Add(chooser, chooserFlags);
			break;
		case SKILLCAT_MISC:
			miscSkillsSizer->Add(chooser, chooserFlags);
			break;
		default:
			wxLogError("Unknown skill category %d (skill %d, name %s)", (int)skillPtr->category, skillPtr->id, skillPtr->name);
		}
		if (skillPtr->doNotGenerate)
		{
			chooser->Hide();
		}
		profiler.endAggregatePart();
	}

	// colors
	static const wxColour COLOR_FIRST{ 240, 238, 192 }, COLOR_SECOND{ 214, 212, 169 };
	const wxBoxSizer* const sizers[4] = { weaponSkillsSizer, armorSkillsSizer, magicSkillsSizer, miscSkillsSizer };
	for (auto sizer : sizers)
	{
		bool diffColor = false;
		auto children = sizer->GetChildren();
		for (int i = 1; i < children.size(); ++i) // i = 1 -- skip label
		{
			const wxSizerItem* const item = children[i];
			EditorSkillValueChooser* const chooser = static_cast<EditorSkillValueChooser*>(item->GetWindow());
			if (!diffColor)
			{
				diffColor = true;
				chooser->setRowColor(COLOR_FIRST);
			}
			else
			{
				diffColor = false;
				chooser->setRowColor(COLOR_SECOND);
			}
		}
	}
	profiler.endAggregate();
	Thaw();
	wxLogMessage(profiler.getAggregateDurationStr());
	skillToWidgetMap = invertMap(widgetToSkillMap);
	mainSizer->Add(skillsSizerHorizontal, 1, 0, 5);
}

void EditorSkillsPanel::createActionsPanel()
{
	actionsLabel = new wxStaticText(this, wxID_ANY, _("Actions:"), wxDefaultPosition, wxDefaultSize, 0);
	actionsLabel->Wrap(-1);
	actionsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	mainSizer->Add(actionsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxStaticBoxSizer* affectSizer;
	affectSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Affect which skill categories?")), wxHORIZONTAL);

	affectWeaponsCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Weapons"), wxDefaultPosition, wxDefaultSize, 0);
	affectWeaponsCheckbox->SetValue(true);
	affectSizer->Add(affectWeaponsCheckbox, 0, wxALL, 5);
	affectWeaponsCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onAffectWeaponsCheck, this);

	affectArmorCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Armor"), wxDefaultPosition, wxDefaultSize, 0);
	affectArmorCheckbox->SetValue(true);
	affectSizer->Add(affectArmorCheckbox, 0, wxALL, 5);
	affectArmorCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onAffectArmorCheck, this);

	affectMagicCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Magic"), wxDefaultPosition, wxDefaultSize, 0);
	affectMagicCheckbox->SetValue(true);
	affectSizer->Add(affectMagicCheckbox, 0, wxALL, 5);
	affectMagicCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onAffectMagicCheck, this);

	affectMiscCheckbox = new wxCheckBox(affectSizer->GetStaticBox(), wxID_ANY, _("Misc"), wxDefaultPosition, wxDefaultSize, 0);
	affectMiscCheckbox->SetValue(true);
	affectSizer->Add(affectMiscCheckbox, 0, wxALL, 5);
	affectMiscCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onAffectMiscCheck, this);


	mainSizer->Add(affectSizer, 0, wxALL, 5);

	wxStaticBoxSizer* learnSizer;
	learnSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Learn")), wxHORIZONTAL);

	wxBoxSizer* learnButtonsSizer;
	learnButtonsSizer = new wxBoxSizer(wxVERTICAL);

	godModeButton = new wxButton(learnSizer->GetStaticBox(), wxID_ANY, _("Learn all skills at maximum level game supports (god mode)"), wxDefaultPosition, wxDefaultSize, 0);
	learnButtonsSizer->Add(godModeButton, 0, wxALL, 5);
	godModeButton->Bind(wxEVT_BUTTON, &EditorSkillsPanel::onGodModeButton, this);

	wxBoxSizer* learnAllSkillsAtSizer;
	learnAllSkillsAtSizer = new wxBoxSizer(wxHORIZONTAL);

	setAllSkillsToButton = new wxButton(learnSizer->GetStaticBox(), wxID_ANY, _("Set all skills to:"), wxDefaultPosition, wxDefaultSize, 0);
	learnAllSkillsAtSizer->Add(setAllSkillsToButton, 0, wxALL, 5);
	setAllSkillsToButton->Bind(wxEVT_BUTTON, &EditorSkillsPanel::onSetAllSkillsButton, this);

	setAllSkillsToLevelSpinCtrl = new wxSpinCtrl(learnSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_SKILL_LEVEL, 1);
	learnAllSkillsAtSizer->Add(setAllSkillsToLevelSpinCtrl, 0, wxALL, 5);

	static const wxString setAllSkillsToMasteryChoiceChoices[] = { _("None"), _("Novice"), _("Expert"), _("Master"), _("GM") };
	int setAllSkillsToMasteryChoiceNChoices = MAX_MASTERY + 1; // work both with mm6 and mm7-8
	setAllSkillsToMasteryChoice = new wxChoice(learnSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, setAllSkillsToMasteryChoiceNChoices, setAllSkillsToMasteryChoiceChoices, 0);
	setAllSkillsToMasteryChoice->SetSelection(1);
	learnAllSkillsAtSizer->Add(setAllSkillsToMasteryChoice, 0, wxALL, 5);

	learnButtonsSizer->Add(learnAllSkillsAtSizer, 0, wxEXPAND, 5);

	learnSizer->Add(learnButtonsSizer, 0, wxALL, 5);

	m_staticline31 = new wxStaticLine(learnSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	learnSizer->Add(m_staticline31, 0, wxEXPAND, 5);

	wxBoxSizer* learnSettingsSizer;
	learnSettingsSizer = new wxBoxSizer(wxHORIZONTAL);

	onlyAlreadyLearnedCheckbox = new wxCheckBox(learnSizer->GetStaticBox(), wxID_ANY, _("Only already learned"), wxDefaultPosition, wxDefaultSize, 0);
	learnSettingsSizer->Add(onlyAlreadyLearnedCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	onlyAlreadyLearnedCheckbox->Bind(wxEVT_CHECKBOX, &EditorSkillsPanel::onOnlyAlreadyLearnedCheck, this);

	learnSizer->Add(learnSettingsSizer, 1, wxEXPAND, 5);

	mainSizer->Add(learnSizer, 0, wxALL, 5);
}