#pragma once
#include "main.h"
#include "InventoryCtrl.h"
#include "wx/dataview.h"

class wxDataViewListCtrl;
class wxDataViewColumn;

class InventoryItemTableViewModel;

class InventoryManagerCtrl : public wxPanel
{
    wxButton* addAdvancedButton;
    wxButton* addSimpleButton;
    wxButton* deleteButton;
    wxButton* modifyButton;
    wxButton* storeButton;
    wxButton* restoreButton;
    wxDataViewCtrl* tableItems;

    void onAddAdvancedPress(wxCommandEvent& event);
    void onAddSimplePress(wxCommandEvent& event);
    void onDeletePress(wxCommandEvent& event);
    void onModifyPress(wxCommandEvent& event);
    void onStorePress(wxCommandEvent& event);
    void onRestorePress(wxCommandEvent& event);

    // item was deleted by the control itself due to various reasons, not by manager
    void onItemDeleted(wxCommandEvent& event);
    // all items might have changed/been added/been removed, rebuild the item table
    void onAllItemsChanged(wxCommandEvent& event);

    void addItemAdvanced();
    void addItemSimple();
    mm7::Item modifyItem(const mm7::Item& item);

public:
    // not instance and not smart pointer, because wxWidgets auto-deletes all windows and so it'd be deleted twice
    InventoryCtrl* const inventoryCtrl;

    InventoryManagerCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType);
    ~InventoryManagerCtrl();

    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};


class InventoryItemTableViewModel : public wxDataViewModel
{
private:
    wxVector<wxVector<wxVariant>> data;
public:
    static const int COLUMN_INDEX_ID = 0, COLUMN_INDEX_NAME = 1, COLUMN_INDEX_TYPE = 2, COLUMN_INDEX_SKILL = 3, COLUMN_INDEX_STATS = 4,
        COLUMN_INDEX_BONUS = 5, COLUMN_INDEX_CONDITION = 6, COLUMN_INDEX_VALUE = 7;

    void GetValue(wxVariant& variant, const wxDataViewItem& dataItem, unsigned int col) const override;

    bool SetValue(const wxVariant& variant, const wxDataViewItem& dataItem, unsigned int col) override;

    wxDataViewItem GetParent(const wxDataViewItem& dataItem) const override;

    bool IsContainer(const wxDataViewItem& dataItem) const override;

    unsigned int GetChildren(const wxDataViewItem& dataItem, wxDataViewItemArray& children) const override;

    unsigned int GetColumnCount() const override;
    wxString GetColumnType(unsigned int col) const override;
    InventoryManagerCtrl& inventoryManagerCtrl;

    InventoryItemTableViewModel(InventoryManagerCtrl& dialog);
};