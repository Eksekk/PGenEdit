#pragma once
#include "pch.h"
#include "main.h"
#include "ClassGenerationData.h"
#include "AlignmentRadioBox.h"

class ClassWindow;
class ClassGenerationData;
class ClassInfoPanel;

class ClassSettingsTab : public wxPanel
{
public:
	ClassGenerationData* linkedClassSettings;
	wxBoxSizer* mainSizer;
	AlignmentRadioBox* possibleAlignmentRadioBox;
	ClassWindow* classWindow;

	ClassSettingsTab(wxWindow* parent, ClassGenerationData* data);
	void updateSettingsFromLinked();
private:
	void onSpecificClassSettingsClick(wxCommandEvent& event);
	void onPossibleAlignmentSelectRadio(wxCommandEvent& event);
	wxButton* specificClassSettingsButton;
};

