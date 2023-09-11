#include "pch.h"
#include "EditorItemsPanel.h"
#include "SaveGameData.h"

EditorItemsPanel::EditorItemsPanel(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements, int playerIndex, int rosterIndex)
    : wxScrolledWindow(parent), EditorPlayerPanel(playerIndex, rosterIndex)
{
    Freeze();
    SetScrollRate(10, 10);
    SetSizeHints(1024, 768);
    Bind(wxEVT_ACTIVATE, &EditorItemsPanel::onActivateWindow, this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);
    inventoryManagerCtrl = new InventoryManagerCtrl(this, CELLS_ROW, CELLS_COL, std::forward<InventoryType>(inventoryType), elements);
    sizer->Add(inventoryManagerCtrl, wxSizerFlags(0).Expand().Border(wxALL, 5));

    Layout();
    Thaw();
}

EditorItemsPanel::~EditorItemsPanel()
{
}

int EditorItemsPanel::setRosterIndex()
{
    return 0;
}

void EditorItemsPanel::setDefaultCustomSettings()
{
}

std::string EditorItemsPanel::getJsonPersistKey() const
{
    return "items";
}

bool EditorItemsPanel::persist(Json& json) const
{
    json = json.is_null() ? Json{} : json;
    return inventoryManagerCtrl->persist(json);
}

bool EditorItemsPanel::unpersist(const Json& json)
{
    return inventoryManagerCtrl->unpersist(json);
}

void EditorItemsPanel::updateFromPlayerData()
{
    inventoryManagerCtrl->inventoryCtrl->reloadReferencedItems();
}

void EditorItemsPanel::onActivateWindow(wxActivateEvent& event)
{
    if (event.GetActive())
    {
        saveGameData.loadEditorPlayerPanelData(*this);
        updateFromPlayerData();
    }
    else
    {
        saveGameData.saveEditorPlayerPanelData(*this);
    }
}