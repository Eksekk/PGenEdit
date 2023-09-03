#pragma once
#include "pch.h"
#include "main.h"
#include "EditorPlayerPanel.h"
#include "InventoryManagerCtrl.h"

class InventoryManagerCtrl;

class EditorItemsPanel : public EditorPlayerPanel, public wxScrolledWindow
{
    void onActivateWindow(wxActivateEvent& event);
public:
    InventoryManagerCtrl* inventoryManagerCtrl;

    EditorItemsPanel(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements, int playerIndex, int rosterIndex);
    ~EditorItemsPanel();

    // Inherited via EditorPlayerPanel
    virtual int setRosterIndex() override;
    virtual void setDefaultCustomSettings() override;
    virtual std::string getJsonPersistKey() const override;
    virtual bool persist(Json& json) const override;
    virtual bool unpersist(const Json& json) override;
    virtual void updateFromPlayerData() override;
};

