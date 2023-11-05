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
}

void InventoryManagerCtrl::onRestorePress(wxCommandEvent& event)
{
}

void InventoryManagerCtrl::addItem()
{
    CreateItemDialog dialog(this);
    mm7::Item item = dialog.getNewItemModal();
    // item store element ownership problem
    inventoryCtrl->addItem(item);
}

mm7::Item InventoryManagerCtrl::modifyItem(const mm7::Item& item)
{
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

    m_dataViewListCtrl3 = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    numberCol = m_dataViewListCtrl3->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn13 = m_dataViewListCtrl3->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn14 = m_dataViewListCtrl3->AppendTextColumn(_("Type"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn15 = m_dataViewListCtrl3->AppendTextColumn(_("Skill"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn16 = m_dataViewListCtrl3->AppendTextColumn(_("Stats"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn17 = m_dataViewListCtrl3->AppendTextColumn(_("Value"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn18 = m_dataViewListCtrl3->AppendTextColumn(_("Condition"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn19 = m_dataViewListCtrl3->AppendTextColumn(_("Bonus" /* aggregate str */), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    itemsMainSizer->Add(m_dataViewListCtrl3, 0, wxALL | wxEXPAND, 5);

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
#if 0
    numberCol = m_dataViewListCtrl3->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn14 = m_dataViewListCtrl3->AppendTextColumn(_("Type" /* aggregate str */), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn15 = m_dataViewListCtrl3->AppendTextColumn(_("Skill"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn16 = m_dataViewListCtrl3->AppendTextColumn(_("Stats"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn17 = m_dataViewListCtrl3->AppendTextColumn(_("Value"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn18 = m_dataViewListCtrl3->AppendTextColumn(_("Condition"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn19 = m_dataViewListCtrl3->AppendTextColumn(_("Bonus"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
#endif
    const ItemStoreElement* const elem = reinterpret_cast<const ItemStoreElement*>(&dataItem);
    const mm7::Item* const item = &elem->item;
    const PlayerItem* const itemData = GameData::items.at(item->number).get();
    switch (col)
    {
    case 0: // id
        variant = (long)itemData->id;
        break;
    case 1: // name
        variant = itemData->name;
        break;
    case 2: // type
        variant = ENUM_TO_STRING_ITEM_TYPE.at(itemData->id);
        break;
    case 3: // skill name
    {
        PlayerSkill* sk = itemData->skill;
        if (sk)
        {
            variant = sk->name;
        }
        else
        {
            variant = "None";
        }
        break;
    }
    case 4: // stats (+5 AC etc.)
        variant = playerItem->getItemTypeName();
        break;
    case 5: // value
        variant = ""; // TODO
        break;
    case 6: // condition (broken etc.)
        variant = (long)playerItem->forItemTxtDo([](auto itemTxt) { return itemTxt->material; });
        break;
    case 7: // Bonus (complex string like +5 might)
        variant = ""; // TODO
        break;
    }
}

bool InventoryItemTableViewModel::SetValue(const wxVariant& variant, const wxDataViewItem& dataItem, unsigned int col)
{
    return false;
}

wxDataViewItem InventoryItemTableViewModel::GetParent(const wxDataViewItem& dataItem) const
{
    return wxDataViewItem();
}

bool InventoryItemTableViewModel::IsContainer(const wxDataViewItem& dataItem) const
{
    return false;
}

unsigned int InventoryItemTableViewModel::GetChildren(const wxDataViewItem& dataItem, wxDataViewItemArray& children) const
{
    //itemAccessor->for
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
