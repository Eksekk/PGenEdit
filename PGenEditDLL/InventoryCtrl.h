#pragma once
#include "pch.h"
#include "main.h"

struct ItemStoreElement
{
    mm7::Item item; // mm7 item, because it has all required fields
    int x, y;
    std::variant<std::monostate, MapChestRef, PlayerInventoryRef> location; // first is when item is only stored (doesn't exist in any inventory)
};

struct MapChestRef
{
    std::string mapName;
    int chestId;
};

struct PlayerInventoryRef
{
    int rosterIndex;
};

class InventoryCtrl : public wxControl
{
    static const int CELL_WIDTH, CELL_HEIGHT;
public:
    const int CELLS_ROW, CELLS_COL;
    std::vector<ItemStoreElement> elements;

    bool persistAllStoredItems(Json& json) const;
    bool unpersistAllStoredItems(const Json& json);

    // delete all player inventory / map chest items, and readd them, if possible on old positions
    bool reloadReferencedItems();

    // event handlers
    void onClick(wxMouseEvent& event);
    void onRightclick(wxMouseEvent& event);
    void onPaint(wxPaintEvent& event);

    InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, std::vector<ItemStoreElement> elements = std::vector<ItemStoreElement>());

    InventoryCtrl() = delete;
    InventoryCtrl(const InventoryCtrl&) = delete;
    bool operator=(const InventoryCtrl&) = delete;
    InventoryCtrl(InventoryCtrl&&) = default;
};

