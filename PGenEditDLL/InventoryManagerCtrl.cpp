#include "pch.h"
#include "main.h"
#include "InventoryManagerCtrl.h"
#include <wx/dataview.h>

void InventoryManagerCtrl::onAddPress(wxCommandEvent& event)
{
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

// PASSING RVALUE REFERENCES REQUIRES std::forward
InventoryManagerCtrl::InventoryManagerCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements)
    : wxScrolledWindow(parent), inventoryCtrl(new InventoryCtrl(this, CELLS_ROW, CELLS_COL, std::forward<InventoryType>(inventoryType), elements))
{
    SetScrollRate(35, 35);
    wxBoxSizer* itemsMainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(itemsMainSizer);

    wxBoxSizer* inventoryAndActionsSizer;
    inventoryAndActionsSizer = new wxBoxSizer(wxHORIZONTAL);

    inventoryAndActionsSizer->Add(inventoryCtrl, 0, 0, 5);

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


    inventoryAndActionsSizer->Add(buttonsSizer, 1, wxEXPAND, 5);


    itemsMainSizer->Add(inventoryAndActionsSizer, 0, wxEXPAND, 5);

    m_dataViewListCtrl3 = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    numberCol = m_dataViewListCtrl3->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn14 = m_dataViewListCtrl3->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn15 = m_dataViewListCtrl3->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn16 = m_dataViewListCtrl3->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn17 = m_dataViewListCtrl3->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    m_dataViewListColumn18 = m_dataViewListCtrl3->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    itemsMainSizer->Add(m_dataViewListCtrl3, 0, wxALL | wxEXPAND, 5);

    this->Layout();
}

InventoryManagerCtrl::~InventoryManagerCtrl()
{
}
