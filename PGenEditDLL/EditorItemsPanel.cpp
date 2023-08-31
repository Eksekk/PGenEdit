#include "pch.h"
#include "EditorItemsPanel.h"
#include "InventoryManagerCtrl.h"

EditorItemsPanel::EditorItemsPanel(wxWindow* parent, InventoryManagerCtrl* inventoryManagerCtrl, int playerIndex, int rosterIndex)
    : wxPanel(parent), EditorPlayerPanel(playerIndex, rosterIndex), inventoryManagerCtrl(inventoryManagerCtrl)
{
    Layout();
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
    return std::string();
}

bool EditorItemsPanel::persist(Json& json) const
{
    return false;
}

bool EditorItemsPanel::unpersist(const Json& json)
{
    return false;
}

void EditorItemsPanel::updateFromPlayerData()
{
}
