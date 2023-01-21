#include "pch.h"
#include "PlayerPanelBase.h"
#include "PlayerData.h"

PlayerPanelBase::PlayerPanelBase(wxWindow* parent, PlayerData* linkedGenerationData) : wxPanel(parent), linkedGenerationData(linkedGenerationData)
{
	assert(linkedGenerationData);
	mainSizer = new wxBoxSizer(wxVERTICAL);

	generationEnabledCheckbox = new wxCheckBox(this, wxID_ANY, _("Generate for this player"), wxDefaultPosition, wxDefaultSize, 0);
	mainSizer->Add(generationEnabledCheckbox, 0, wxALL, 5);
	generationEnabledCheckbox->Bind(wxEVT_CHECKBOX, &PlayerPanelBase::onGenerationEnabledCheck, this);

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText12 = new wxStaticText(this, wxID_ANY, _("Player type:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText12->Wrap(-1);
	bSizer27->Add(m_staticText12, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxString playerTypeChoiceChoices[] = { _("Generic"), _("Melee"), _("Ranged"), _("Defensive"), _("Caster"), _("Utility") };
	int playerTypeChoiceNChoices = sizeof(playerTypeChoiceChoices) / sizeof(wxString);
	playerTypeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, playerTypeChoiceNChoices, playerTypeChoiceChoices, 0);
	playerTypeChoice->SetSelection(0);
	bSizer27->Add(playerTypeChoice, 0, wxALL, 5);
	playerTypeChoice->Bind(wxEVT_CHOICE, &PlayerPanelBase::onPlayerTypeChoice, this);

	mainSizer->Add(bSizer27, 0, wxEXPAND, 5);

	wxString strengthIndicatorRadioBoxChoices[] = { _("Party strength in general tab"), _("Actual character's generated level") };
	int strengthIndicatorRadioBoxNChoices = sizeof(strengthIndicatorRadioBoxChoices) / sizeof(wxString);
	strengthIndicatorRadioBox = new wxRadioBox(this, wxID_ANY, _("What defines character strength?"), wxDefaultPosition, wxDefaultSize, strengthIndicatorRadioBoxNChoices, strengthIndicatorRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	strengthIndicatorRadioBox->SetSelection(0);
	mainSizer->Add(strengthIndicatorRadioBox, 0, wxALL, 5);
	strengthIndicatorRadioBox->Bind(wxEVT_RADIOBOX, &PlayerPanelBase::onStrengthIndicatorRadio, this);

	m_notebook2 = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// LEVEL PANEL //
	levelPanel = new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer(wxVERTICAL);

	wxString generateWhatRadioBoxChoices[] = { _("Level"), _("Experience") };
	int generateWhatRadioBoxNChoices = sizeof(generateWhatRadioBoxChoices) / sizeof(wxString);
	generateWhatRadioBox = new wxRadioBox(levelPanel, wxID_ANY, _("Generate"), wxDefaultPosition, wxDefaultSize, generateWhatRadioBoxNChoices, generateWhatRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	generateWhatRadioBox->SetSelection(0);
	bSizer17->Add(generateWhatRadioBox, 0, wxALL, 5);
	generateWhatRadioBox->Bind(wxEVT_RADIOBOX, &PlayerPanelBase::onGenerateWhatRadio, this);

	levelPanel->SetSizer(bSizer17);
	levelPanel->Layout();
	bSizer17->Fit(levelPanel);
	m_notebook2->AddPage(levelPanel, _("Level"), false);

	// ~~LEVEL PANEL~~ //
	
	// CLASS PANEL //

	classSettingsTab = new ClassSettingsTab(m_notebook2, &linkedGenerationData->classes);
	m_notebook2->AddPage(classSettingsTab, _("Class"), true);

	// ~~CLASS PANEL~~ //

	// SKILLS PANEL //

	skillsPanel = new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText111 = new wxStaticText(skillsPanel, wxID_ANY, _("Skill points multiplier (0.1 - 10)"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText111->Wrap(-1);
	bSizer23->Add(m_staticText111, 0, wxALL, 5);

	skillPointsMultiplier = new wxTextCtrl(skillsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	skillPointsMultiplier->Bind(wxEVT_TEXT, &PlayerPanelBase::onSkillPointsMulEnter, this);
	bSizer23->Add(skillPointsMultiplier, 0, wxALL, 5);
	bSizer22->Add(bSizer23, 1, wxEXPAND, 5);


	skillsPanel->SetSizer(bSizer22);
	skillsPanel->Layout();
	bSizer22->Fit(skillsPanel);
	m_notebook2->AddPage(skillsPanel, _("Skills"), false);

	// ~~SKILLS PANEL~~ //

	// ITEMS PANEL //

	itemsPanel = new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxVERTICAL);

	keepCurrentItemsCheckbox = new wxCheckBox(itemsPanel, wxID_ANY, _("Keep current items"), wxDefaultPosition, wxDefaultSize, 0);
	keepCurrentItemsCheckbox->SetToolTip(_("If unset, all items (equipped & backpack) will be removed before generation"));
	keepCurrentItemsCheckbox->Bind(wxEVT_CHECKBOX, &PlayerPanelBase::onKeepCurrentItemsCheck, this);
	bSizer21->Add(keepCurrentItemsCheckbox, 0, wxALL, 5);

	itemsPanel->SetSizer(bSizer21);
	itemsPanel->Layout();
	bSizer21->Fit(itemsPanel);
	m_notebook2->AddPage(itemsPanel, _("Items"), false);

	// ~~ITEMS PANEL~~ //

	// STATS PANEL //

	statsPanel = new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_notebook2->AddPage(statsPanel, _("Stats"), false);
	resistancesPanel = new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer(wxVERTICAL);

	exclusiveResistancesCheckbox = new wxCheckBox(resistancesPanel, wxID_ANY, _("Generate (and show) exclusive resistances"), wxDefaultPosition, wxDefaultSize, 0);
	exclusiveResistancesCheckbox->SetToolTip(_("Normally unobtainable, like light/dark"));
	exclusiveResistancesCheckbox->Bind(wxEVT_CHECKBOX, &PlayerPanelBase::onExclusiveResistancesCheck, this);
	bSizer20->Add(exclusiveResistancesCheckbox, 0, wxALL, 5);


	resistancesPanel->SetSizer(bSizer20);
	resistancesPanel->Layout();
	bSizer20->Fit(resistancesPanel);
	m_notebook2->AddPage(resistancesPanel, _("Resistances"), false);

	// ~~STATS PANEL~~ //

	// SPELLS PANEL //

	spellsPanel = new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer(wxVERTICAL);

	zeroOutTimedSpellsCastsCheckbox = new wxCheckBox(spellsPanel, wxID_ANY, _("Zero out timed spell casts if they're learned"), wxDefaultPosition, wxDefaultSize, 0);
	zeroOutTimedSpellsCastsCheckbox->Bind(wxEVT_CHECKBOX, &PlayerPanelBase::onZeroOutTimedSpellCastsCheck, this);
	bSizer25->Add(zeroOutTimedSpellsCastsCheckbox, 0, wxALL, 5);


	spellsPanel->SetSizer(bSizer25);
	spellsPanel->Layout();
	bSizer25->Fit(spellsPanel);
	m_notebook2->AddPage(spellsPanel, _("Spells"), false);

	// ~~SPELLS PANEL~~ //

	mainSizer->Add(m_notebook2, 1, wxEXPAND | wxALL, 20);


	this->SetSizer(mainSizer);
	this->Layout();
	mainSizer->Fit(this);
}

void PlayerPanelBase::onGenerationEnabledCheck(wxCommandEvent& event)
{
}

void PlayerPanelBase::onPlayerTypeChoice(wxCommandEvent& event)
{
}

void PlayerPanelBase::onStrengthIndicatorRadio(wxCommandEvent& event)
{
}

void PlayerPanelBase::onGenerateWhatRadio(wxCommandEvent& event)
{
}

void PlayerPanelBase::onSkillPointsMulEnter(wxCommandEvent& event)
{
}

void PlayerPanelBase::onKeepCurrentItemsCheck(wxCommandEvent& event)
{
}

void PlayerPanelBase::onExclusiveResistancesCheck(wxCommandEvent& event)
{
}

void PlayerPanelBase::onZeroOutTimedSpellCastsCheck(wxCommandEvent& event)
{
}
