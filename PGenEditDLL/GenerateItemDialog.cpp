#include "pch.h"
#include "GenerateItemDialog.h"
#include "Utility.h"
#include "ItemStructAccessor.h"

namespace
{
	enum class GenerateReturn
	{
		CANCEL,
		GENERATE
	};
}

void GenerateItemDialog::onGenerateClick(wxCommandEvent& event)
{
	EndModal(static_cast<int>(GenerateReturn::GENERATE));
}

void GenerateItemDialog::onCloseButtonClick(wxCommandEvent& event)
{
	EndModal(static_cast<int>(GenerateReturn::CANCEL));
	// TODO: persist
}

void GenerateItemDialog::onClose(wxCloseEvent& event)
{
	EndModal(static_cast<int>(GenerateReturn::CANCEL));
}

void GenerateItemDialog::persistToJson(Json& json) const
{
	json["itemType"] = choiceItemType->GetSelection();
	json["itemStrength"] = choiceItemStrength->GetSelection();
	json["alwaysEnchant"] = checkboxAlwaysEnchant->GetValue();
}

void GenerateItemDialog::restoreFromJson(const Json& json)
{
	int strength = json["itemStrength"];
	static const std::array<int, 7> validItemStrengths = { 1, 2, 3, 4, 5, 6, 7 };
	if (!util::container::existsInContainer(validItemStrengths, strength))
	{
		wxLogWarning("Invalid item strength %d", strength);
		strength = 1;
	}
	choiceItemStrength->SetSelection(strength);
	int type = json["itemType"];
	if (!util::container::existsInContainer(consts::ITEM_TYPE_ALL, type) || !choiceIndexToItemTypeIdMap.contains(type) || type == consts::ITEM_TYPE_ANY)
	{
		wxLogWarning("Invalid item type %d", type);
		type = consts::ITEM_TYPE_ARMOR;
	}
	choiceItemType->SetSelection(choiceIndexToItemTypeIdMap.at(type));
	checkboxAlwaysEnchant->SetValue(json["alwaysEnchant"]);
}

std::optional<mm7::Item> GenerateItemDialog::generate()
{
	GenerateReturn ret = static_cast<GenerateReturn>(ShowModal());
	if (ret == GenerateReturn::CANCEL)
	{
		return std::nullopt;
	}
	else if (ret != GenerateReturn::GENERATE)
	{
		wxLogError("Invalid return value %d", ret);
		return std::nullopt;
	}
	int strength;
	wxString strengthVal = choiceItemStrength->GetString(choiceItemStrength->GetSelection());
	if (!strengthVal.ToInt(&strength))
	{
		wxLogError("Invalid non-integer item strength %s", strengthVal);
		strength = 1;
	}
	int sel = choiceItemType->GetSelection();
	int type;
	if (!util::container::existsInContainer(consts::ITEM_TYPE_ALL, sel) || !itemTypeIdToChoiceIndexMap.contains(sel))
	{
		wxLogError("Invalid selection %d", sel);
		type = consts::ITEM_TYPE_ARMOR;
	}
	else
	{
		type = itemTypeIdToChoiceIndexMap.at(sel);
	}
	auto item = ItemStructAccessor::generateRandomItem(strength, type, checkboxAlwaysEnchant->GetValue());
	return item;
}

GenerateItemDialog::GenerateItemDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* sizerMain;
	sizerMain = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerGenerationProperties;
	sizerGenerationProperties = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerItemType;
	sizerItemType = new wxBoxSizer(wxHORIZONTAL);

	labelItemType = new wxStaticText(this, wxID_ANY, _("Item strength:"), wxDefaultPosition, wxDefaultSize, 0);
	labelItemType->Wrap(-1);
	sizerItemType->Add(labelItemType, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	choiceItemType = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	for (int type: util::container::sorted(consts::ITEM_TYPE_ALL))
	{
		choiceItemType->Append(consts::ENUM_TO_STRING_ITEM_TYPE.at(type));
		itemTypeIdToChoiceIndexMap[choiceItemType->GetCount() - 1] = type;
	}
	choiceIndexToItemTypeIdMap = util::container::invertMap(itemTypeIdToChoiceIndexMap);
	choiceItemType->SetSelection(0);
	sizerItemType->Add(choiceItemType, 0, wxALL, 5);


	sizerGenerationProperties->Add(sizerItemType, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);

	wxBoxSizer* sizerItemStrength;
	sizerItemStrength = new wxBoxSizer(wxHORIZONTAL);

	labelItemStrength = new wxStaticText(this, wxID_ANY, _("Item strength:"), wxDefaultPosition, wxDefaultSize, 0);
	labelItemStrength->Wrap(-1);
	sizerItemStrength->Add(labelItemStrength, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	static const wxString choiceItemStrengthChoices[] = {"1", "2", "3", "4", "5", "6", "7"};
	choiceItemStrength = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 7, choiceItemStrengthChoices, 0);
	choiceItemStrength->SetSelection(0);
	sizerItemStrength->Add(choiceItemStrength, 0, wxALL, 5);


	sizerGenerationProperties->Add(sizerItemStrength, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);

	wxBoxSizer* sizerAlwaysEnchant;
	sizerAlwaysEnchant = new wxBoxSizer(wxHORIZONTAL);

	checkboxAlwaysEnchant = new wxCheckBox(this, wxID_ANY, _("Always enchant"), wxDefaultPosition, wxDefaultSize, 0);
	sizerAlwaysEnchant->Add(checkboxAlwaysEnchant, 0, wxALL, 5);


	sizerGenerationProperties->Add(sizerAlwaysEnchant, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);


	sizerMain->Add(sizerGenerationProperties, 0, wxEXPAND, 5);

	sizerDialogButtons = new wxStdDialogButtonSizer();
	sizerDialogButtonsOK = new wxButton(this, wxID_OK);
	sizerDialogButtonsOK->Bind(wxEVT_BUTTON, &GenerateItemDialog::onGenerateClick, this, wxID_OK);
	sizerDialogButtons->AddButton(sizerDialogButtonsOK);
	sizerDialogButtonsCancel = new wxButton(this, wxID_CANCEL);
	sizerDialogButtonsCancel->Bind(wxEVT_BUTTON, &GenerateItemDialog::onCloseButtonClick, this, wxID_CANCEL);
	sizerDialogButtons->AddButton(sizerDialogButtonsCancel);
	sizerDialogButtons->Realize();

	sizerMain->Add(sizerDialogButtons, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 15);


	this->SetSizer(sizerMain);
	this->Layout();
	sizerMain->Fit(this);

	this->Centre(wxBOTH);

	this->Bind(wxEVT_CLOSE_WINDOW, &GenerateItemDialog::onClose, this);

	// TODO: unpersist
}

GenerateItemDialog::~GenerateItemDialog()
{
}