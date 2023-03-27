#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include "AlignmentRadioBox.h"
#include "GeneratorGuiBase.h"

class ClassGenerationSettings;

class ClassInfoPanel : public wxPanel, public GeneratorGuiBase
{
private:

	wxBoxSizer* checkboxesSizer;
	wxCheckBox* useDefaultsCheckbox;
	wxStaticBoxSizer* tierSettings_sbs;

	static const int TIER_ZERO_ID = 10, TIER_ONE_ID = 11, TIER_TWO_ID = 12;
	static const int TIER_IDS[3];

	void onDisabledCheck(wxCommandEvent& event);
	void onUseDefaultsCheck(wxCommandEvent& event);
	void onWeightChange(wxCommandEvent& event);
	void onEqualWeightsRadio(wxCommandEvent& event);
	void onManualWeightsRadio(wxCommandEvent& event);
	void onTierWeightChange(wxCommandEvent& event);
	void onAlignmentRadioBoxSelect(wxCommandEvent& event);

	void setEnabledStateBecauseUseDefaultsChanged(bool enabled);
protected:
	

public:
	wxStaticLine* m_staticline4;
	wxStaticText* classNameLabel;
	wxCheckBox* disabledCheckbox;
	wxStaticText* classWeightText;
	wxSpinCtrl* weight;
	wxRadioButton* equalWeightsRadio;
	wxRadioButton* manualWeightsRadio;
	wxSpinCtrl* tierWeights[3];
	AlignmentRadioBox* alignmentRadioBox;

	ClassGenerationSettings* linkedClassSettings;

	ClassInfoPanel(wxWindow* parent, ClassGenerationSettings* linkedClassSettings);

	bool isDefault();
	void setClassName(const wxString& name);

	~ClassInfoPanel();
	void updateSettingsFromLinked();
	bool readFromJson(const Json& json) override;
	bool writeToJson(Json& json) const override;
	void copyFrom(const GeneratorGuiBase& source) override;
	bool hasSameSettingsAs(const GeneratorGuiBase& other) const override;
	void updateLinkedSettings() override;
};

