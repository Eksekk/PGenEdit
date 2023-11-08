#pragma once
#include "main.h"
#include <wx/dataview.h>
#include <wx/statline.h>
#include "AlignmentRadioBox.h"

class GuaranteedClassDialog;
class SpecificClassChooserPanel;

class ClassTableViewModel : public wxDataViewModel
{
private:
	wxVector<wxVector<wxVariant>> data;
public:
	void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;

	bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;

	wxDataViewItem GetParent(const wxDataViewItem& item) const override;

	bool IsContainer(const wxDataViewItem& item) const override;

	unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;

	unsigned int GetColumnCount() const override;
	wxString GetColumnType(unsigned int col) const override;
	GuaranteedClassDialog& dialog;

	std::unordered_map<int, int> classIdsToTableIndexes;
	ClassTableViewModel(GuaranteedClassDialog& dialog);
};

class GuaranteedClassDialog : public wxDialog
{
private:

protected:

public:
	wxStaticText* m_staticText26;
	wxStaticText* m_staticText27;
	wxRadioBox* tierRadioBox;
	wxChoice* classChoice;
	AlignmentRadioBox* alignmentRadioBox;
	wxDataViewCtrl* classTable;
	wxStaticLine* m_staticline6;
	wxStdDialogButtonSizer* buttonsSizer;
	wxButton* saveButton;
	wxButton* cancelButton;
	SpecificClassChooserPanel* specificClassChooserPanel;

	GuaranteedClassDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(681, 244), long style = wxDEFAULT_DIALOG_STYLE);

	~GuaranteedClassDialog();

	void fillOutClassChoice();
	void readFromJson(const Json& json);
	void writeToJson(Json& json);
	Json writeToJsonR(Json& json);
private:
	std::unordered_map<int, int> choicesToClassIds;
	std::unordered_map<int, int> classIdsToChoices;
	wxArrayString classChoiceEntries;

	void applyFilters();
	void onFilterChange(wxCommandEvent& event);

	void onSavePress(wxCommandEvent& event);
	void onCancelPress(wxCommandEvent& event);
	friend class ClassTableViewModel;
};

