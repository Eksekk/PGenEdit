#include "pch.h"
#include "main.h"
#include "ClassSettingsTab.h"
#include "ClassWindow.h"

ClassSettingsTab::ClassSettingsTab(wxWindow* parent, ClassGenerationData* data) : wxPanel(parent), data(data)
{
	assert(data);
	classWindow = new ClassWindow(this);

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer(wxHORIZONTAL);
	wxString possibleAlignmentRadioBoxChoices[] = { _("Any"), _("Light only"), _("Dark only") };
	int possibleAlignmentRadioBoxNChoices = sizeof(possibleAlignmentRadioBoxChoices) / sizeof(wxString);
	possibleAlignmentRadioBox = new wxRadioBox(this, wxID_ANY, _("Possible alignment (MM7/Merge; overrides all other alignment settings)"), wxDefaultPosition, wxDefaultSize, possibleAlignmentRadioBoxNChoices, possibleAlignmentRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	possibleAlignmentRadioBox->SetSelection(0);
	possibleAlignmentRadioBox->Bind(wxEVT_RADIOBOX, &ClassSettingsTab::onPossibleAlignmentSelectRadio, this);
	bSizer28->Add(possibleAlignmentRadioBox, 0, wxALL, 5);


	this->SetSizer(bSizer28);
	this->Layout();
	bSizer28->Fit(this);
}

void ClassSettingsTab::onPossibleAlignmentSelectRadio(wxCommandEvent& event)
{
}
