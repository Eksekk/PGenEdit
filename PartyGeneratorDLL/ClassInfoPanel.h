#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include "AlignmentRadioBox.h"

class ClassGenerationSettings;

class ClassInfoPanel : public wxPanel
{
private:

	wxBoxSizer* checkboxesSizer;
	wxCheckBox* useDefaultsCheckbox;
	wxStaticBoxSizer* tierSettings_sbs;
protected:
	

public:
	wxStaticLine* m_staticline4;
	wxStaticText* classNameLabel;
	wxCheckBox* disabledCheckbox;
	wxStaticText* classWeightText;
	wxSpinCtrl* weightText;
	wxRadioButton* equalWeightsRadio;
	wxRadioButton* manualWeightsRadio;
	wxSpinCtrl* tierWeightTexts[3];
	AlignmentRadioBox* alignmentRadioBox;

	ClassGenerationSettings* linkedClassSettings;

	static const int TIER_ZERO_ID = 10, TIER_ONE_ID = 11, TIER_TWO_ID = 12;
	static const int TIER_IDS[3];

	void onDisabledCheck(wxCommandEvent& event);
	void onUseDefaultsCheck(wxCommandEvent& event);
	void onWeightTextChange(wxCommandEvent& event);
	void onEqualWeightsRadio(wxCommandEvent& event);
	void onManualWeightsRadio(wxCommandEvent& event);
	void onTierWeightTextChange(wxCommandEvent& event);
	void onAlignmentRadioBoxSelect(wxCommandEvent& event);

	ClassInfoPanel(wxWindow* parent, ClassGenerationSettings* linkedClassSettings);

	bool isDefault();
	void setClassName(const wxString& name);

	~ClassInfoPanel();
	void updateSettingsFromLinked();
	void setEnabledStateBecauseUseDefaultsChanged(bool enabled);
};

