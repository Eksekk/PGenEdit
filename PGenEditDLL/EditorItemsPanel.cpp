#include "pch.h"
#include "EditorItemsPanel.h"
#include "SaveGameData.h"

EditorItemsPanel::EditorItemsPanel(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements, int playerIndex, int rosterIndex)
    : wxPanel(parent), EditorPlayerPanel(playerIndex, rosterIndex)
{
    Freeze();
    Bind(wxEVT_ACTIVATE, &EditorItemsPanel::onActivateWindow, this);
    inventoryManagerCtrl = new InventoryManagerCtrl(this, CELLS_ROW, CELLS_COL, std::forward<InventoryType>(inventoryType), elements);
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