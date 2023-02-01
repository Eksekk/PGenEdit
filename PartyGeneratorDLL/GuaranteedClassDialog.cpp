#include "pch.h"
#include "GuaranteedClassDialog.h"
#include <wx/gbsizer.h>
#include "GameData.h"
#include "globals.h"
#include "Utility.h"

GuaranteedClassDialog::GuaranteedClassDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer(0, 0);
	gbSizer2->SetFlexibleDirection(wxBOTH);
	gbSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText26 = new wxStaticText(this, wxID_ANY, _("Filters:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText26->Wrap(-1);
	gbSizer2->Add(m_staticText26, wxGBPosition(0, 0), wxGBSpan(2, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_staticText27 = new wxStaticText(this, wxID_ANY, _("Base class"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText27->Wrap(-1);
	gbSizer2->Add(m_staticText27, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxString tierRadioBoxChoices[] = { _("Any"), _("0"), _("1"), _("2") };
	int tierRadioBoxNChoices = sizeof(tierRadioBoxChoices) / sizeof(wxString);
	tierRadioBox = new wxRadioBox(this, wxID_ANY, _("Tier"), wxDefaultPosition, wxDefaultSize, tierRadioBoxNChoices, tierRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
	tierRadioBox->SetSelection(0);
	gbSizer2->Add(tierRadioBox, wxGBPosition(0, 2), wxGBSpan(2, 1), wxALL, 5);
	tierRadioBox->Bind(wxEVT_RADIOBOX, &GuaranteedClassDialog::onFilterChange, this);

	classChoiceEntries.Add("Any");
	choicesToClassIds[0] = INVALID_ID;
	classChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, classChoiceEntries, 0);
	classChoice->SetSelection(0);
	classChoice->Bind(wxEVT_CHOICE, &GuaranteedClassDialog::onFilterChange, this);
	gbSizer2->Add(classChoice, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL, 5);

	wxString alignmentRadioBoxChoices[] = { _("Any"), _("Neutral"), _("Light"), _("Dark") };
	int alignmentRadioBoxNChoices = sizeof(alignmentRadioBoxChoices) / sizeof(wxString);
	alignmentRadioBox = new AlignmentRadioBox(this, _("Alignment"));
	alignmentRadioBox->SetSelection(ALIGNMENT_ANY);
	gbSizer2->Add(alignmentRadioBox, wxGBPosition(0, 3), wxGBSpan(2, 1), wxALL, 5);
	alignmentRadioBox->Bind(wxEVT_RADIOBOX, &GuaranteedClassDialog::onFilterChange, this);


	mainSizer->Add(gbSizer2, 0, wxEXPAND, 5);

	classTable = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES | wxDV_ROW_LINES | wxDV_SINGLE | wxDV_VARIABLE_LINE_HEIGHT);
	classTableIdColumn = classTable->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
	classTableNameColumn = classTable->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
	classTableTierColumn = classTable->AppendTextColumn(_("Tier"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
	classTableAlignmentColumn = classTable->AppendTextColumn(_("Alignment"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
	mainSizer->Add(classTable, 0, wxALL | wxEXPAND, 5);

	m_staticline6 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline6, 0, wxEXPAND | wxALL, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer(wxVERTICAL);


	mainSizer->Add(bSizer46, 1, wxEXPAND, 5);

	buttonsSizer = new wxStdDialogButtonSizer();
	buttonsSizerSave = new wxButton(this, wxID_SAVE);
	buttonsSizer->AddButton(buttonsSizerSave);
	buttonsSizerCancel = new wxButton(this, wxID_CANCEL);
	buttonsSizer->AddButton(buttonsSizerCancel);
	buttonsSizer->Realize();

	mainSizer->Add(buttonsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);


	this->SetSizer(mainSizer);
	this->Layout();

	this->Centre(wxBOTH);
}

GuaranteedClassDialog::~GuaranteedClassDialog()
{
}

void GuaranteedClassDialog::fillOutTable()
{
	assert(classTable->GetStore()->GetItemCount() == 0);
	int i = 0;
	wxVector<wxVariant> data;
	for (auto& [id, clas] : GameData::classes)
	{
		classIdsToTableIndexes[id] = i++;
		data.clear();
		data.push_back(wxVariant(id));
		data.push_back(wxVariant(clas.name));
		data.push_back(wxVariant(clas.getFormattedTier()));
		data.push_back(wxVariant(clas.getFormattedAlignment()));
		classTable->AppendItem(data, (wxUIntPtr) &clas);
		/*classTable = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES | wxDV_ROW_LINES | wxDV_SINGLE | wxDV_VARIABLE_LINE_HEIGHT);
		classTableIdColumn = classTable->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
		classTableNameColumn = classTable->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
		classTableTierColumn = classTable->AppendTextColumn(_("Tier"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
		classTableAlignmentColumn = classTable->AppendTextColumn(_("Alignment"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);*/
	}
	classTable->SelectRow(0);
}

void GuaranteedClassDialog::fillOutClassChoice()
{
	assert(classIdsToChoices.size() == 1); // don't fill out twice
	auto& classes = GameData::classes;
	int n = classChoiceEntries.size();
	for (auto& [id, clas] : classes)
	{
		if (clas.tier == 0)
		{
			classChoiceEntries.Add(clas.name);
			choicesToClassIds[n++] = clas.id;
		}
	}
	classIdsToChoices = invertMap(choicesToClassIds);
}

void GuaranteedClassDialog::readFromJson(const Json& json)
{
	int classId = json["baseClass"];
	auto itr = GameData::classes.find(classId);
	if (classId == INVALID_ID)
	{
		classChoice->SetSelection(0);
	}
	if (itr == GameData::classes.end())
	{
		wxLogWarning("Couldn't find class %d from json, using default", classId);
		classChoice->SetSelection(0);
	}
	else
	{
		classChoice->SetSelection(classIdsToChoices.at(itr->second.id));
	}
	// TODO
	applyFilters();
}

void GuaranteedClassDialog::writeToJson(Json& json)
{
}

Json GuaranteedClassDialog::writeToJsonR(Json& json)
{
	Json j;
	writeToJson(j);
	return j;
}

void GuaranteedClassDialog::applyFilters()
{
	auto store = classTable->GetStore();
	int n = store->GetItemCount();

	for (int i = 0; i < n; ++i)
	{
		wxDataViewItem item = store->GetItem(i);
		PlayerClass* clas = (PlayerClass*)item.GetID();
		if (clas->alignment != alignmentRadioBox->getSelectedAlignment() && alignmentRadioBox->getSelectedAlignment() != ALIGNMENT_ANY)
		{
			//store->
		}
	}
}

void GuaranteedClassDialog::onFilterChange(wxCommandEvent& event)
{
	applyFilters();
}

void ClassTableViewModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ClassTableViewModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col)
{
	throw std::logic_error("The method or operation is not implemented.");
}

wxDataViewItem ClassTableViewModel::GetParent(const wxDataViewItem& item) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ClassTableViewModel::IsContainer(const wxDataViewItem& item) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

unsigned int ClassTableViewModel::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ClassTableViewModel::createRows()
{
}
