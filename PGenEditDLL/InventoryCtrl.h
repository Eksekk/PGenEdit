#pragma once
#include "pch.h"
#include "main.h"

extern const std::string ITEM_LOC_STORED, ITEM_LOC_CHEST, ITEM_LOC_PLAYER;

struct MapChestRef
{
    std::string mapName;
    int chestId;

    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};

struct PlayerInventoryRef
{
    int rosterIndex;

    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};

struct StoredItemRef
{
    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};

static bool operator==(const MapChestRef& lhs, const MapChestRef& rhs);
static bool operator==(const PlayerInventoryRef& lhs, const PlayerInventoryRef& rhs);
static bool operator==(const StoredItemRef& lhs, const StoredItemRef& rhs);

struct InventoryPosition
{
    int x, y;
};

using ItemLocationType = std::variant<StoredItemRef, MapChestRef, PlayerInventoryRef>;
using InventoryType = std::variant<MapChestRef, PlayerInventoryRef>;

struct ItemStoreElement
{
    mm7::Item item; // mm7 item, because it has all required fields
    InventoryPosition pos;
    // TODO: automatically calculate cell width

    ItemLocationType location; // first is when item is only stored (doesn't exist in any inventory)
    ItemLocationType origin; // stores whether item was taken from player's inventory, chest or added artificially (to not duplicate inventory items when reloading)

    ItemStoreElement();
    ItemStoreElement(const mm7::Item& item, InventoryPosition pos, const ItemLocationType& location, const ItemLocationType& origin);

    bool isSameExceptPos(const ItemStoreElement& other) const;
};

using ElementsContainer = std::vector<ItemStoreElement>;
using ItemsVariant = std::variant<mm6::Item*, mm7::Item*, mm8::Item*>;

class InventoryCtrl : public wxControl
{
    static const int CELL_WIDTH, CELL_HEIGHT;
    ElementsContainer elements;
    
    // wx stuff
    virtual wxSize DoGetBestSize() const;
    void OnPaint(wxPaintEvent& event);
public:
    InventoryType inventoryType;
    const ElementsContainer& getElements() const;
    const int CELLS_ROW, CELLS_COL;

    bool persistInventory(Json& json) const;
    bool unpersistInventory(const Json& json);

    // delete all player inventory / map chest items, and readd them, if possible on old positions
    bool reloadReferencedItems();

    // event handlers
    void onClick(wxMouseEvent& event);
    void onRightclick(wxMouseEvent& event);

    bool moveStoredItemToInventory(const ItemStoreElement& item); // MODIFIES original inventory (chest's or player's)
    bool moveInventoryItemToStore(const ItemStoreElement& item); // same as above
    ItemStoreElement* getMouseoverItem(); // pointer to allow null value (no item at mouse position) | FIXMEEEE: vector reallocation will cause problems if code holds valid pointer for long
    ItemStoreElement* chooseItemWithMouse(bool allowNone = true); // enters item selecting mode, after clicking returns clicked item
    bool addItem(const ItemStoreElement& item);
    bool removeItem(const ItemStoreElement& item);
    bool modifyItem(const ItemStoreElement& itemToModify, const ItemStoreElement& newItem);

    InventoryPosition findFreePositionForItem(const ItemStoreElement& elem);
    bool canItemBePlacedAtPosition(const ItemStoreElement& elem, InventoryPosition pos);

    InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements = ElementsContainer());

    InventoryCtrl() = delete;
    InventoryCtrl(const InventoryCtrl&) = delete;
    bool operator=(const InventoryCtrl&) = delete;
    InventoryCtrl(InventoryCtrl&&) = default;
};

