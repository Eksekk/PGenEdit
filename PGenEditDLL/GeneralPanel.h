#pragma once
#include "main.h"
#include <wx/statline.h>
#include "wx/spinctrl.h"

class GeneralPanel : public wxPanel
{
public:
	wxStaticText* m_staticText10;
	wxSlider* partyStrengthSlider;
	wxStaticLine* m_staticline3;
	wxCheckBox* miscSkillsOnePlayerCheckbox;
	wxStaticLine* m_staticline1;
	wxCheckBox* generateArtifactsCheckbox;
	wxCheckBox* clearFoundArtifactsCheckbox;
	wxCheckBox* markArtifactsAsFoundCheckbox;
	wxStaticLine* m_staticline2;
	wxCheckBox* generateGoldCheckbox;
	wxStaticText* m_staticText1;
	wxTextCtrl* goldMin;
	wxStaticText* m_staticText2;
	wxTextCtrl* goldMax;
	wxCheckBox* clearBankGoldCheckbox;
	wxCheckBox* removeFineCheckbox;
	wxCheckBox* generateFoodCheckbox;
	wxStaticText* m_staticText11;
	wxSpinCtrl* foodMin;
	wxStaticText* m_staticText21;
	wxSpinCtrl* foodMax;
	wxCheckBox* clearConditionsCheckbox;
	wxCheckBox* fullHpSpCheckbox;
	wxCheckBox* dispelPartyCheckbox;
	wxRadioBox* interfaceColorRadioBox;

	GeneralPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(843, 479),
		long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL, const wxString& title = _("Classes"));
};

