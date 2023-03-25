#include "pch.h"
#include "SpecificClassChooserPanel.h"
#include "GameData.h"

SpecificClassChooserPanel::SpecificClassChooserPanel(wxWindow* parent, ClassGenerationData* linkedClassData) : wxPanel(parent), linkedClassData(linkedClassData)
{
	guaranteedClassDialog = new GuaranteedClassDialog(this);
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* actionSizer;
	actionSizer = new wxBoxSizer(wxHORIZONTAL);

	generateSpecificClassCheckbox = new wxCheckBox(this, wxID_ANY, _("Generate specific class"));
	generateSpecificClassCheckbox->SetToolTip(_("Always the same, no randomization involved. Overrides all other options."));

	actionSizer->Add(generateSpecificClassCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	chooseSpecificClassButton = new wxButton(this, wxID_ANY, _("Choose..."));
	actionSizer->Add(chooseSpecificClassButton, 0, wxALL, 5);

	mainSizer->Add(actionSizer, 0, wxEXPAND, 5);

	wxStaticBoxSizer* classDetailsSizer;
	classDetailsSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Chosen class details")), wxHORIZONTAL);

	m_staticText56 = new wxStaticText(classDetailsSizer->GetStaticBox(), wxID_ANY, _("Base class:"));
	m_staticText56->Wrap(-1);
	classDetailsSizer->Add(m_staticText56, 0, wxALL, 5);

	chosenClassBaseLabel = new wxStaticText(classDetailsSizer->GetStaticBox(), wxID_ANY, _("N/A"));
	chosenClassBaseLabel->Wrap(-1);
	classDetailsSizer->Add(chosenClassBaseLabel, 0, wxALL, 5);

	classDetailsSizer->Add(20, 0, 0, wxEXPAND, 5);

	chosenClassTierLabel = new wxStaticText(classDetailsSizer->GetStaticBox(), wxID_ANY, _("Tier:"));
	chosenClassTierLabel->Wrap(-1);
	classDetailsSizer->Add(chosenClassTierLabel, 0, wxALL, 5);

	chosenClassTierLabel = new wxStaticText(classDetailsSizer->GetStaticBox(), wxID_ANY, _("N/A"));
	chosenClassTierLabel->Wrap(-1);
	classDetailsSizer->Add(chosenClassTierLabel, 0, wxALL, 5);


	classDetailsSizer->Add(20, 0, 0, wxALL, 5);

	chosenClassAlignmentLabel = new wxStaticText(classDetailsSizer->GetStaticBox(), wxID_ANY, _("Alignment:"));
	chosenClassAlignmentLabel->Wrap(-1);
	classDetailsSizer->Add(chosenClassAlignmentLabel, 0, wxALL, 5);

	chosenClassAlignmentLabel = new wxStaticText(classDetailsSizer->GetStaticBox(), wxID_ANY, _("N/A"));
	chosenClassAlignmentLabel->Wrap(-1);
	classDetailsSizer->Add(chosenClassAlignmentLabel, 0, wxALL, 5);


	classDetailsSizer->Add(20, 0, 0, wxEXPAND, 5);


	mainSizer->Add(classDetailsSizer, 0, wxEXPAND, 5);

	m_staticline7 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline7, 0, wxEXPAND | wxALL, 5);


	this->SetSizer(mainSizer);
	this->Layout();
}

SpecificClassChooserPanel::~SpecificClassChooserPanel()
{
}

void SpecificClassChooserPanel::processClassChange()
{
	static const wxString NA = "N/A";
	PlayerClass* clas = linkedClassData->guaranteedClass;
	if (clas)
	{
		chosenClassAlignmentLabel->SetLabel(linkedClassData->guaranteedClass->getFormattedAlignment());
		chosenClassBaseLabel->SetLabel(linkedClassData->guaranteedClass->name);
		chosenClassTierLabel->SetLabel(linkedClassData->guaranteedClass->getFormattedTier());
	}
	else
	{
		chosenClassAlignmentLabel->SetLabel(NA);
		chosenClassBaseLabel->SetLabel(NA);
		chosenClassTierLabel->SetLabel(NA);
	}
	bool enable = linkedClassData->useGuaranteedClass;
	chosenClassTierLabel->Enable(enable);
	chosenClassBaseLabel->Enable(enable);
	chosenClassAlignmentLabel->Enable(enable);
}

void SpecificClassChooserPanel::onGenerateSpecificClassCheck(wxCommandEvent& event)
{
	if (event.IsChecked() && !linkedClassData->guaranteedClass)
	{
		linkedClassData->guaranteedClass = &GameData::classes.begin()->second;
		linkedClassData->useGuaranteedClass = true;
	}
	processClassChange();
}

void SpecificClassChooserPanel::onChooseClick(wxCommandEvent& event)
{
	guaranteedClassDialog->Show(true);
}