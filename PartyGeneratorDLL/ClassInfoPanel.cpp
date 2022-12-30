#include "pch.h"
#include "ClassInfoPanel.h"
#include "ClassGenerationData.h"

ClassInfoPanel::ClassInfoPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& title) : wxPanel(parent, id, pos, size, style, title)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	linkedClassSettings = nullptr;

	sizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer* tierSizer;
	tierSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Tier")), wxHORIZONTAL);

	equalChancesCheckbox = new wxCheckBox(tierSizer->GetStaticBox(), wxID_ANY, _("Equal chances"), wxDefaultPosition, wxDefaultSize, 0);
	equalChancesCheckbox->SetToolTip(_("If enabled, each tier will have equal chance of generating"));

	tierSizer->Add(equalChancesCheckbox, 0, wxALIGN_CENTER | wxALL, 5);

	wxStaticBoxSizer* weights_sbs;
	weights_sbs = new wxStaticBoxSizer(new wxStaticBox(tierSizer->GetStaticBox(), wxID_ANY, _("Weights (tier 0/1/2)")), wxHORIZONTAL);

	tierZeroWeight = new wxTextCtrl(weights_sbs->GetStaticBox(), wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0);
	weights_sbs->Add(tierZeroWeight, 0, wxALL, 5);

	tierOneWeight = new wxTextCtrl(weights_sbs->GetStaticBox(), wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0);
	weights_sbs->Add(tierOneWeight, 0, wxALL, 5);

	tierTwoWeight = new wxTextCtrl(weights_sbs->GetStaticBox(), wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0);
	weights_sbs->Add(tierTwoWeight, 0, wxALL, 5);


	tierSizer->Add(weights_sbs, 1, wxEXPAND, 5);


	sizer->Add(tierSizer, 0, wxEXPAND, 5);


	sizer->Add(30, 0, 1, wxEXPAND, 5);

	wxString alignmentChoices[] = { ("Both"), _("Light"), _("Dark") }; // TODO: properly set order from enum values
	int alignmentNChoices = sizeof(alignmentChoices) / sizeof(wxString);
	alignment = new wxRadioBox(this, wxID_ANY, _("Alignment"), wxDefaultPosition, wxDefaultSize, alignmentNChoices, alignmentChoices, 1, wxRA_SPECIFY_ROWS);
	alignment->SetSelection(1);
	sizer->Add(alignment, 0, wxBOTTOM | wxEXPAND, 5);


	sizer->Add(sizer, 0, 0, 5);


	sizer->Add(0, 20, 0, wxEXPAND, 5);

	/*wxStaticBoxSizer* specificClasses;
	specificClasses = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Specific classes")), wxVERTICAL);

	resetButton = new wxButton(specificClasses->GetStaticBox(), wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0);
	specificClasses->Add(resetButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);


	sizer->Add(specificClasses, 1, wxEXPAND, 5);*/


	this->SetSizer(sizer);
	this->Layout();

	this->Centre(wxBOTH);
}

ClassInfoPanel::~ClassInfoPanel()
{
}

void ClassInfoPanel::updateSettingsFromLinked()
{
	tierZeroWeight->ChangeValue(wxString::Format(wxT("%i"), linkedClassSettings->tierWeights[0]));
	tierOneWeight->ChangeValue(wxString::Format(wxT("%i"), linkedClassSettings->tierWeights[1]));
	tierTwoWeight->ChangeValue(wxString::Format(wxT("%i"), linkedClassSettings->tierWeights[2]));
	equalChancesCheckbox->SetValue(linkedClassSettings->equalChances);
	alignment->SetSelection((int)linkedClassSettings->alignment);
}