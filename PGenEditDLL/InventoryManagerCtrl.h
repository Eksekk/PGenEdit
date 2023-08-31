#pragma once
#include "pch.h"
#include "main.h"
#include "InventoryCtrl.h"

class wxDataViewListCtrl;
class wxDataViewColumn;

class InventoryManagerCtrl : public wxScrolledWindow
{
    // not instance and not smart pointer, because wxWidgets auto-deletes all windows and so it'd be deleted twice
    InventoryCtrl* inventoryCtrl;

    wxButton* addButton;
    wxButton* deleteButton;
    wxButton* modifyButton;
    wxButton* storeButton;
    wxButton* restoreButton;
    wxDataViewListCtrl* m_dataViewListCtrl3;
    wxDataViewColumn* numberCol;
    wxDataViewColumn* m_dataViewListColumn14;
    wxDataViewColumn* m_dataViewListColumn15;
    wxDataViewColumn* m_dataViewListColumn16;
    wxDataViewColumn* m_dataViewListColumn17;
    wxDataViewColumn* m_dataViewListColumn18;

    void onAddPress(wxCommandEvent& event);
    void onDeletePress(wxCommandEvent& event);
    void onModifyPress(wxCommandEvent& event);
    void onStorePress(wxCommandEvent& event);
    void onRestorePress(wxCommandEvent& event);

public:
    InventoryManagerCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements = ElementsContainer());
    ~InventoryManagerCtrl();
};
