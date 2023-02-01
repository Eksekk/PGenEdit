#pragma once
#include "pch.h"
#include "main.h"
#include <wx/dataview.h>
#include <wx/statline.h>
#include "AlignmentRadioBox.h"

class ClassTableViewModel : public wxDataViewModel
{

public:
	void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;

	bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;

	wxDataViewItem GetParent(const wxDataViewItem& item) const override;

	bool IsContainer(const wxDataViewItem& item) const override;

	unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;

	void createRows();

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
	wxDataViewListCtrl* classTable;
	wxDataViewColumn* classTableIdColumn;
	wxDataViewColumn* classTableNameColumn;
	wxDataViewColumn* classTableTierColumn;
	wxDataViewColumn* classTableAlignmentColumn;
	wxStaticLine* m_staticline6;
	wxStdDialogButtonSizer* buttonsSizer;
	wxButton* buttonsSizerSave;
	wxButton* buttonsSizerCancel;

	GuaranteedClassDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(681, 244), long style = wxDEFAULT_DIALOG_STYLE);

	~GuaranteedClassDialog();

	void fillOutTable();

	void fillOutClassChoice();
	void readFromJson(const Json& json);
	void writeToJson(Json& json);
	Json writeToJsonR(Json& json);
private:
	std::unordered_map<int, int> choicesToClassIds;
	std::unordered_map<int, int> classIdsToChoices;
	std::unordered_map<int, int> classIdsToTableIndexes;
	wxArrayString classChoiceEntries;

	void applyFilters();
	void onFilterChange(wxCommandEvent& event);
};

