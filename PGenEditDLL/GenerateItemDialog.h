#pragma once

// TODO: add count field!
class GenerateItemDialog : public wxDialog
{
private:

protected:
	wxStaticText* labelItemType;
	wxChoice* choiceItemType;
	wxStaticText* labelItemStrength;
	wxChoice* choiceItemStrength;
	wxCheckBox* checkboxAlwaysEnchant;
	wxStdDialogButtonSizer* sizerDialogButtons;
	wxButton* sizerDialogButtonsOK;
	wxButton* sizerDialogButtonsCancel;

public:
	// save settings between panel openings
	void persistToJson(Json& json) const;
	void restoreFromJson(const Json& json);

	mm7::Item generate(bool close = true);

	GenerateItemDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generate random item"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE);

	~GenerateItemDialog();

};

