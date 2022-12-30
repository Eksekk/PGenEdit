#pragma once
#include "pch.h"
#include "main.h"
#include "Generator.h"

struct ClassGenerationSettings;

class ClassInfoPanel : public wxPanel
{
private:

protected:
	

public:
	wxCheckBox* equalChancesCheckbox;
	wxTextCtrl* tierZeroWeight;
	wxTextCtrl* tierOneWeight;
	wxTextCtrl* tierTwoWeight;
	wxRadioBox* alignment;
	wxButton* resetButton;
	wxBoxSizer* sizer;
	ClassGenerationSettings* linkedClassSettings;

	ClassInfoPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(843, 479),
		long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL, const wxString& title = _("Classes"));

	~ClassInfoPanel();
	void updateSettingsFromLinked();
};

