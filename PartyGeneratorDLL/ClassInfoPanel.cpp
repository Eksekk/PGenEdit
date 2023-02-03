#include "pch.h"
#include "ClassInfoPanel.h"
#include "ClassGenerationData.h"

const int ClassInfoPanel::TIER_IDS[3] = { TIER_ZERO_ID, TIER_ONE_ID, TIER_TWO_ID };

ClassInfoPanel::ClassInfoPanel(wxWindow* parent, ClassGenerationSettings* linkedClassSettings) : wxPanel(parent), linkedClassSettings(linkedClassSettings)//, resetButton(nullptr)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	m_staticline4 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline4, 0, wxEXPAND | wxALL, 5);

	classNameLabel = new wxStaticText(this, wxID_ANY, _("Class name"), wxDefaultPosition, wxDefaultSize, 0);
	classNameLabel->Wrap(-1);
	classNameLabel->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));

	mainSizer->Add(classNameLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	checkboxesSizer = new wxBoxSizer(wxHORIZONTAL);

	disabledCheckbox = new wxCheckBox(this, wxID_ANY, _("Disabled"), wxDefaultPosition, wxDefaultSize, 0);
	disabledCheckbox->SetToolTip(_("Excludes this class from generation"));
	disabledCheckbox->Bind(wxEVT_CHECKBOX, &ClassInfoPanel::onDisabledCheck, this);
	checkboxesSizer->Add(disabledCheckbox, 0, wxALL, 5);

	useDefaultsCheckbox = new wxCheckBox(this, wxID_ANY, _("Use defaults"));
	useDefaultsCheckbox->SetToolTip(isDefault() ? "Check to use global defaults where player-specific default would be used" : "Check to use default settings above");
	useDefaultsCheckbox->Bind(wxEVT_CHECKBOX, &ClassInfoPanel::onUseDefaultsCheck, this);
	checkboxesSizer->Add(useDefaultsCheckbox, 0, wxALL, 5);

	mainSizer->Add(checkboxesSizer, 0, wxALL, 5);

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer(wxHORIZONTAL);

	classWeightText = new wxStaticText(this, wxID_ANY, _("Class weight:"), wxDefaultPosition, wxDefaultSize, 0);
	classWeightText->Wrap(-1);
	bSizer40->Add(classWeightText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	weightText = new wxSpinCtrl(this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP, 0, 99999, 1);
	weightText->Bind(wxEVT_SPINCTRL, &ClassInfoPanel::onWeightTextChange, this);
	bSizer40->Add(weightText, 0, wxALL, 5);


	mainSizer->Add(bSizer40, 0, wxEXPAND, 5);

	tierSettings_sbs = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Tier settings")), wxHORIZONTAL);

	equalWeightsRadio = new wxRadioButton(tierSettings_sbs->GetStaticBox(), wxID_ANY, _("Equal weights"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	tierSettings_sbs->Add(equalWeightsRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	equalWeightsRadio->Bind(wxEVT_RADIOBUTTON, &ClassInfoPanel::onEqualWeightsRadio, this);
	manualWeightsRadio = new wxRadioButton(tierSettings_sbs->GetStaticBox(), wxID_ANY, _("Specific weights:"), wxDefaultPosition, wxDefaultSize, 0);
	manualWeightsRadio->SetToolTip(_("Tier 0, 1, 2"));
	manualWeightsRadio->Bind(wxEVT_RADIOBUTTON, &ClassInfoPanel::onManualWeightsRadio, this);
	tierSettings_sbs->Add(manualWeightsRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	for (int i = 0; i < 3; ++i)
	{
		tierWeightTexts[i] = new wxSpinCtrl(tierSettings_sbs->GetStaticBox(), TIER_IDS[i], "1", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP, 0, 99999, 1);
		tierSettings_sbs->Add(tierWeightTexts[i], 0, wxALL, 5);
		tierWeightTexts[i]->Bind(wxEVT_SPINCTRL, &ClassInfoPanel::onWeightTextChange, this);
	}

	mainSizer->Add(tierSettings_sbs, 0, wxEXPAND, 5);

	alignmentRadioBox = new AlignmentRadioBox(this, _("Alignment"));
	alignmentRadioBox->SetSelection(ALIGNMENT_ANY);
	mainSizer->Add(alignmentRadioBox, 0, wxALL, 5);
	alignmentRadioBox->Bind(wxEVT_RADIOBOX, &ClassInfoPanel::onAlignmentRadioBoxSelect, this);

	this->SetSizer(mainSizer);
	this->Layout();
	mainSizer->Fit(this);

	if (linkedClassSettings->useDefaults)
	{
		useDefaultsCheckbox->SetValue(true);
		setEnabledStateBecauseUseDefaultsChanged(false);
	}

	//sizer->Add(sizer, 0, 0, 5); // INFINITE RECURSION, RETAINED FOR LAUGHS - I SPENT 1.5H ON THIS :(((
}

bool ClassInfoPanel::isDefault()
{
	return linkedClassSettings->id == DEFAULT_SETTINGS_INDEX;
}

void ClassInfoPanel::setClassName(const wxString& name)
{
	classNameLabel->SetLabel(name);
}

ClassInfoPanel::~ClassInfoPanel()
{
}

void ClassInfoPanel::updateSettingsFromLinked()
{
	disabledCheckbox->SetValue(linkedClassSettings->disabled);
	useDefaultsCheckbox->SetValue(linkedClassSettings->useDefaults);
	weightText->SetValue(linkedClassSettings->weight);
	if (linkedClassSettings->equalChances)
	{
		equalWeightsRadio->SetValue(true);
	}
	else
	{
		manualWeightsRadio->SetValue(true);
	}
	for (int i = 0; i < 3; ++i)
	{
		tierWeightTexts[i]->SetValue(linkedClassSettings->tierWeights[i]);
	}
	alignmentRadioBox->SetSelection(linkedClassSettings->alignment);
	useDefaultsCheckbox->SetValue(linkedClassSettings->useDefaults);

	useDefaultsCheckbox->Enable(linkedClassSettings->disabled);

	bool enableRest = !linkedClassSettings->disabled && !linkedClassSettings->useDefaults;
	setEnabledStateBecauseUseDefaultsChanged(enableRest);
}

void ClassInfoPanel::setEnabledStateBecauseUseDefaultsChanged(bool enabled)
{
	classWeightText->Enable(enabled);
	tierSettings_sbs->GetStaticBox()->Enable(enabled);
	weightText->Enable(enabled);
	equalWeightsRadio->Enable(enabled);
	manualWeightsRadio->Enable(enabled);
	bool enableTierWeights = enabled && manualWeightsRadio->GetValue();
	for (auto ptr : tierWeightTexts)
	{
		ptr->Enable(enableTierWeights);
	}
	alignmentRadioBox->Enable(enabled);
}

void ClassInfoPanel::onDisabledCheck(wxCommandEvent& event)
{
	linkedClassSettings->disabled = event.IsChecked();
	bool enabled = !event.IsChecked();
	if (!enabled)
	{
		setEnabledStateBecauseUseDefaultsChanged(false);
	}
	else if (!useDefaultsCheckbox->IsChecked())
	{
		setEnabledStateBecauseUseDefaultsChanged(true);
	}
	useDefaultsCheckbox->Enable(enabled);
}

void ClassInfoPanel::onUseDefaultsCheck(wxCommandEvent& event)
{
	linkedClassSettings->useDefaults = event.IsChecked();
	setEnabledStateBecauseUseDefaultsChanged(!event.IsChecked());
}

void ClassInfoPanel::onWeightTextChange(wxCommandEvent& event)
{
	linkedClassSettings->weight = weightText->GetValue();
}

void ClassInfoPanel::onEqualWeightsRadio(wxCommandEvent& event)
{
	linkedClassSettings->equalChances = true;
	for (int i = 0; i < 3; ++i)
	{
		tierWeightTexts[i]->Disable();
	}
}

void ClassInfoPanel::onManualWeightsRadio(wxCommandEvent& event)
{
	linkedClassSettings->equalChances = false;
	for (int i = 0; i < 3; ++i)
	{
		tierWeightTexts[i]->Enable();
	}
}

void ClassInfoPanel::onTierWeightTextChange(wxCommandEvent& event)
{
	const int index = event.GetId() - TIER_ZERO_ID;
	linkedClassSettings->tierWeights[index] = tierWeightTexts[index]->GetValue();
}

void ClassInfoPanel::onAlignmentRadioBoxSelect(wxCommandEvent& event)
{
	linkedClassSettings->alignment = alignmentRadioBox->getSelectedAlignment();
}