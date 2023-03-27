#include "pch.h"
#include "main.h"
#include "ClassSettingsTab.h"
#include "ClassInfoPanel.h"
#include "GameData.h"
#include "ClassGenerationData.h"
#include "ClassWindow.h"

ClassSettingsTab::ClassSettingsTab(wxWindow* parent, ClassGenerationData* data) : wxPanel(parent), linkedClassSettings(data)
{
	classWindow = new ClassWindow(this);
	assert(data);

	mainSizer = new wxBoxSizer(wxVERTICAL);
	possibleAlignmentRadioBox = new AlignmentRadioBox(this, _("Possible alignment (MM7/Merge; overrides all other alignment settings)"));
	possibleAlignmentRadioBox->SetSelection(ALIGNMENT_ANY);
	possibleAlignmentRadioBox->Bind(wxEVT_RADIOBOX, &ClassSettingsTab::onPossibleAlignmentSelectRadio, this);
	mainSizer->Add(possibleAlignmentRadioBox, 0, wxALL, 5);

	specificClassSettingsButton = new wxButton(this, wxID_ANY, "Specific class settings");
	mainSizer->Add(specificClassSettingsButton, 0, wxALL, 5);
	specificClassSettingsButton->Bind(wxEVT_BUTTON, &ClassSettingsTab::onSpecificClassSettingsClick, this);

	this->SetSizer(mainSizer);
	this->Layout();
	mainSizer->Fit(this);
}

void ClassSettingsTab::onSpecificClassSettingsClick(wxCommandEvent& event)
{
	classWindow->Show(true);
}

void ClassSettingsTab::onPossibleAlignmentSelectRadio(wxCommandEvent& event)
{
	linkedClassSettings->possibleAlignment = possibleAlignmentRadioBox->getSelectedAlignment();
}

void ClassSettingsTab::updateSettingsFromLinked()
{
	possibleAlignmentRadioBox->SetSelection(linkedClassSettings->possibleAlignment);
	classWindow->updateSettingsFromLinked();
}