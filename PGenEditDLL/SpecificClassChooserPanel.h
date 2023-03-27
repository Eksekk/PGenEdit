#pragma once
#include "pch.h"
#include "main.h"
#include <wx/statline.h>
#include "ClassGenerationData.h"
#include "GuaranteedClassDialog.h"

class SpecificClassChooserPanel : public wxPanel
{
private:

protected:
	wxCheckBox* generateSpecificClassCheckbox;
	wxButton* chooseSpecificClassButton;
	wxStaticText* m_staticText56;
	wxStaticText* chosenClassBaseLabel;
	wxStaticText* chosenClassTierLabel;
	wxStaticText* chosenClassAlignmentLabel;
	wxStaticLine* m_staticline7;
	GuaranteedClassDialog* guaranteedClassDialog;

public:

	ClassGenerationData* linkedClassData;

	SpecificClassChooserPanel(wxWindow* parent, ClassGenerationData* linkedClassData);

	~SpecificClassChooserPanel();

	void processClassChange();
	void onGenerateSpecificClassCheck(wxCommandEvent& event);
	void onChooseClick(wxCommandEvent& event);
};

