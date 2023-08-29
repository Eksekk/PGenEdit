#pragma once
#include "pch.h"
#include "main.h"

extern const std::string ITEM_LOC_STORED, ITEM_LOC_CHEST, ITEM_LOC_PLAYER;

struct MapChestRef
{
    std::string mapName;
    int chestId;
};

struct PlayerInventoryRef
{
    int rosterIndex;
};

struct ItemStoreElement
{
    mm7::Item item; // mm7 item, because it has all required fields
    int x, y;

    // decided to use tagged union because IMO code required is 
    std::variant<std::monostate, MapChestRef, PlayerInventoryRef> location; // first is when item is only stored (doesn't exist in any inventory)
};

class InventoryCtrl : public wxControl
{
    static const int CELL_WIDTH, CELL_HEIGHT;
    std::vector<ItemStoreElement> elements;
    
    virtual wxSize DoGetBestSize() const;
    void OnPaint(wxPaintEvent& event);
public:
    const int CELLS_ROW, CELLS_COL;

    bool persistInventory(Json& json) const;
    bool unpersistInventory(const Json& json);

    // delete all player inventory / map chest items, and readd them, if possible on old positions
    bool reloadReferencedItems();

    // event handlers
    void onClick(wxMouseEvent& event);
    void onRightclick(wxMouseEvent& event);

    bool moveStoredItemToInventory(const ItemStoreElement& item);
    bool moveInventoryItemToStore(const ItemStoreElement& item);
    ItemStoreElement* getMouseoverItem(); // pointer to allow null value (no item at mouse position)
    ItemStoreElement* chooseItemWithMouse(bool allowNull = true); // enters item selecting mode, after clicking returns clicked item
    bool addItem(const ItemStoreElement& item);
    bool removeItem(const ItemStoreElement& item);
    bool modifyItem(const ItemStoreElement& itemToModify, const ItemStoreElement& newItem);

    InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, const std::vector<ItemStoreElement>& elements = std::vector<ItemStoreElement>());

    InventoryCtrl() = delete;
    InventoryCtrl(const InventoryCtrl&) = delete;
    bool operator=(const InventoryCtrl&) = delete;
    InventoryCtrl(InventoryCtrl&&) = default;
};

