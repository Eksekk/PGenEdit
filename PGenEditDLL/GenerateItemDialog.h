#pragma once

// TODO: add count field!
class GenerateItemDialog : public wxDialog
{
private:
	std::unordered_map<int, int> itemTypeIdToChoiceIndexMap;
	std::unordered_map<int, int> choiceIndexToItemTypeIdMap;

	void onGenerateClick(wxCommandEvent& event);
	void onCloseButtonClick(wxCommandEvent& event);
	void onClose(wxCloseEvent& event);
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

	std::optional<mm7::Item> generate();

	GenerateItemDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generate random item"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE);

	~GenerateItemDialog();

};

