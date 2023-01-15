#pragma once
#include "pch.h"
#include "main.h"

class ClassWindow;
class ClassGenerationData;

class ClassSettingsTab : public wxPanel
{
public:

	ClassGenerationData* data;
	ClassSettingsTab(wxWindow* parent, ClassGenerationData* data);
	ClassWindow* classWindow;

	wxRadioBox* possibleAlignmentRadioBox;

	void onPossibleAlignmentSelectRadio(wxCommandEvent& event);
};

