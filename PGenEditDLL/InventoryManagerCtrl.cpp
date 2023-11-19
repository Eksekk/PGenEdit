#include "pch.h"
#include "main.h"
#include "InventoryManagerCtrl.h"
#include <wx/dataview.h>
#include "ItemDialogBase.h"
#include "CreateItemDialog.h"
#include "PlayerItem.h"
#include "GameData.h"

void InventoryManagerCtrl::onAddPress(wxCommandEvent& event)
{
    addItem();
}

void InventoryManagerCtrl::onDeletePress(wxCommandEvent& event)
{
}

void InventoryManagerCtrl::onModifyPress(wxCommandEvent& event)
{
}

void InventoryManagerCtrl::onStorePress(wxCommandEvent& event)
{
    auto sel = tableItems->GetSelection();
    if (sel.IsOk())
    {
        ItemStoreElement* item = reinterpret_cast<ItemStoreElement*>(sel.GetID());
        if (!inventoryCtrl->moveInventoryItemToStore(*item))
        {
            wxMessageBox("Failed to move item in inventory to store", "Error", wxOK_DEFAULT | wxICON_ERROR, this); // should this really be "this", and not like parent wxFrame?
        }
    }
}

void InventoryManagerCtrl::onRestorePress(wxCommandEvent& event)
{
    auto sel = tableItems->GetSelection();
    if (sel.IsOk())
    {
        ItemStoreElement* item = reinterpret_cast<ItemStoreElement*>(sel.GetID());
        if (!inventoryCtrl->moveStoredItemToInventory(*item))
        {
            wxMessageBox("Failed to move stored item to inventory", "Error", wxOK_DEFAULT | wxICON_ERROR, this); // should this really be "this", and not like parent wxFrame?
        }
    }
}

void InventoryManagerCtrl::addItem()
{
    CreateItemDialog dialog(this);
    std::optional<mm7::Item> item = dialog.getNewItemModal();
    // item store element ownership problem
    if (item.has_value())
    {
        auto* elem = inventoryCtrl->addItem(item.value());
        tableItems->GetModel()->ItemAdded(wxDataViewItem(nullptr), wxDataViewItem(reinterpret_cast<void*>(elem)));
    }
}

mm7::Item InventoryManagerCtrl::modifyItem(const mm7::Item& item)
{
    //tableItems->GetModel()->ItemChanged(wxDataViewItem(nullptr), wxDataViewItem(nullptr)); // TODO
    return mm7::Item();
}

// PASSING RVALUE REFERENCES REQUIRES std::forward
InventoryManagerCtrl::InventoryManagerCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType)
    : wxPanel(parent), inventoryCtrl(new InventoryCtrl(this, CELLS_ROW, CELLS_COL, std::forward<InventoryType>(inventoryType)))
{
    wxBoxSizer* itemsMainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(itemsMainSizer);

    wxBoxSizer* inventoryAndActionsSizer;
    inventoryAndActionsSizer = new wxBoxSizer(wxHORIZONTAL);

    inventoryAndActionsSizer->Add(inventoryCtrl, wxSizerFlags(0).Border(wxALL, 5));

    wxBoxSizer* buttonsSizer;
    buttonsSizer = new wxBoxSizer(wxVERTICAL);

    addButton = new wxButton(this, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(100, 30), 0);
    addButton->Bind(wxEVT_BUTTON, &InventoryManagerCtrl::onAddPress, this);
    buttonsSizer->Add(addButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    deleteButton = new wxButton(this, wxID_ANY, _("Delete"), wxDefaultPosition, wxSize(100, 30), 0);
    deleteButton->Bind(wxEVT_BUTTON, &InventoryManagerCtrl::onDeletePress, this);
    deleteButton->SetToolTip(_("Fully removes item"));

    buttonsSizer->Add(deleteButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    modifyButton = new wxButton(this, wxID_ANY, _("Modify"), wxDefaultPosition, wxSize(100, 30), 0);
    modifyButton->Bind(wxEVT_BUTTON, &InventoryManagerCtrl::onModifyPress, this);
    buttonsSizer->Add(modifyButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    storeButton = new wxButton(this, wxID_ANY, _("Store"), wxDefaultPosition, wxSize(100, 30), 0);
    storeButton->Bind(wxEVT_BUTTON, &InventoryManagerCtrl::onStorePress, this);
    storeButton->SetToolTip(_("Moves item from inventory to inactive, persistent storage"));

    buttonsSizer->Add(storeButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    restoreButton = new wxButton(this, wxID_ANY, _("Restore"), wxDefaultPosition, wxSize(100, 30), 0);
    restoreButton->Bind(wxEVT_BUTTON, &InventoryManagerCtrl::onRestorePress, this);
    restoreButton->SetToolTip(_("Moves item from storage to inventory"));

    buttonsSizer->Add(restoreButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


    inventoryAndActionsSizer->Add(buttonsSizer, 1, wxEXPAND | wxALL, 5);


    itemsMainSizer->Add(inventoryAndActionsSizer, 0, wxEXPAND, 5);

    auto renderer = [] { return new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT, wxALIGN_LEFT); };

    tableItems = new wxDataViewCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    tableItems->AppendColumn(new wxDataViewColumn("#", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_ID));
    tableItems->AppendColumn(new wxDataViewColumn("Name", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_NAME));
    tableItems->AppendColumn(new wxDataViewColumn("Type", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_TYPE));
    tableItems->AppendColumn(new wxDataViewColumn("Skill", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_SKILL));
    tableItems->AppendColumn(new wxDataViewColumn("Stats", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_STATS));
    tableItems->AppendColumn(new wxDataViewColumn("Bonus", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_BONUS));
    tableItems->AppendColumn(new wxDataViewColumn("Condition", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_CONDITION));
    tableItems->AppendColumn(new wxDataViewColumn("Value", renderer(), InventoryItemTableViewModel::COLUMN_INDEX_VALUE));

    tableItems->AssociateModel(new InventoryItemTableViewModel(*this));
    
    itemsMainSizer->Add(tableItems, 0, wxALL | wxEXPAND, 5);

    Fit();
    this->Layout();
}

InventoryManagerCtrl::~InventoryManagerCtrl()
{
}

bool InventoryManagerCtrl::persist(Json& json) const
{
    return inventoryCtrl->persist(json);
}

bool InventoryManagerCtrl::unpersist(const Json& json)
{
    return inventoryCtrl->unpersist(json);
}

void InventoryItemTableViewModel::GetValue(wxVariant& variant, const wxDataViewItem& dataItem, unsigned int col) const
{
    const ItemStoreElement* const elem = reinterpret_cast<ItemStoreElement*>(dataItem.GetID());
    const mm7::Item& item = elem->getItem();
    const PlayerItem* const itemData = GameData::items.at(item.number).get();
    switch (col)
    {
    case COLUMN_INDEX_ID:
        variant = (long)itemData->id;
        break;
    case COLUMN_INDEX_NAME:
        variant = itemData->name;
        break;
    case COLUMN_INDEX_TYPE:
        variant = ENUM_TO_STRING_ITEM_TYPE.at(itemData->itemTypeActual);
        break;
    case COLUMN_INDEX_SKILL: // skill name
    {
        variant = itemData->getSkillString();
        break;
    }
    case COLUMN_INDEX_STATS: // stats (+5 AC etc.)
        variant = itemData->getStatsString();
        break;
    case COLUMN_INDEX_BONUS: // Bonus (complex string like +5 might)
    {
        auto opt = PlayerItem::getEnchantmentsString(item);
        variant = opt.value_or(""); // TODO
        break;
    }
    case COLUMN_INDEX_CONDITION: // condition (broken etc.)
    {
        std::vector<std::string> v{item.identified ? "Identified" : "Not identified", item.broken ? "Broken" : "Not broken"};
        if (MMVER > 6)
        {
            v.push_back(item.hardened ? "Hardened" : "Not hardened");
            v.push_back(item.stolen ? "Stolen" : "Not stolen");
        }
        variant = stringConcat(v, "; ");
        break;

    }
    case COLUMN_INDEX_VALUE: // value
        variant = (long)itemData->value;
        break;
    default:
        wxLogFatalError("Unknown column id %d", col);
    }
}

bool InventoryItemTableViewModel::SetValue(const wxVariant& variant, const wxDataViewItem& dataItem, unsigned int col)
{
    wxFAIL;
    return false;
}

wxDataViewItem InventoryItemTableViewModel::GetParent(const wxDataViewItem& dataItem) const
{
    return wxDataViewItem();
}

bool InventoryItemTableViewModel::IsContainer(const wxDataViewItem& dataItem) const
{
    return !dataItem.IsOk();
}

unsigned int InventoryItemTableViewModel::GetChildren(const wxDataViewItem& dataItem, wxDataViewItemArray& children) const
{
    if (!dataItem.IsOk()) // get top level items
    {
        int n = 0;
        for (const auto& elem : inventoryManagerCtrl.inventoryCtrl->getElements())
        {
            if (std::holds_alternative<ItemRefPlayerInventory>(elem->location) || std::holds_alternative<ItemRefMapChest>(elem->location))
            {
                children.Add(wxDataViewItem(elem.get()));
                ++n;
            }
        }
        return n;
    }
    return 0;
}

unsigned int InventoryItemTableViewModel::GetColumnCount() const
{
    // NOT NEEDED, is not called because of deprecation
    return 8;
}

wxString InventoryItemTableViewModel::GetColumnType(unsigned int col) const
{
    // NOT NEEDED, is not called because of deprecation
    return wxString();
}

InventoryItemTableViewModel::InventoryItemTableViewModel(InventoryManagerCtrl& inventoryManagerCtrl) : inventoryManagerCtrl(inventoryManagerCtrl)
{
}
