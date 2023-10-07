#pragma once
#include "pch.h"
#include "main.h"
#include "Utility.h"

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

    bool persistItem(Json& json) const;
    bool unpersistItem(const Json& json);
    ItemStoreElement();
    ItemStoreElement(const mm7::Item& item, InventoryPosition pos, const ItemLocationType& location, const ItemLocationType& origin);

    bool persist(Json& json) const;
    bool unpersist(const Json& json);

    bool isSameExceptPos(const ItemStoreElement& other) const;
};

using ElementsContainer = std::vector<ItemStoreElement>;
using ItemsVariant = std::variant<mm6::Item*, mm7::Item*, mm8::Item*>;

class InventoryCtrl : public wxWindow
{
    // FIXME: all these methods modify chest's or player's items array, but inventory positions are not modified
    static const int CELL_WIDTH, CELL_HEIGHT;
    ElementsContainer elements;
    
    // wx stuff
    virtual wxSize DoGetBestClientSize() const override;
    void OnPaint(wxPaintEvent& event);

    template<typename Variant> bool unpersistItemLocationVariant(Variant& loc, const Json& json);
    // event handlers
    void onClick(wxMouseEvent& event);
    void onRightclick(wxMouseEvent& event);
public:
    InventoryType inventoryType;
    const ElementsContainer& getElements() const;
    const int CELLS_ROW, CELLS_COL;
    static const std::string JSON_KEY_INVENTORY;

    bool persistInventory(Json& json) const;
    bool unpersistInventory(const Json& json);
    bool persist(Json& json) const;
    bool unpersist(const Json& json);

    bool drawItemAt(wxPaintDC& dc, const ItemStoreElement& elem, int x, int y);

    // delete all player inventory / map chest items, and readd them, if possible on old positions
    bool reloadReferencedItems();

    bool moveStoredItemToInventory(ItemStoreElement& item, InventoryPosition pos = { -1, -1 }); // MODIFIES original inventory (chest's or player's)
    bool moveInventoryItemToStore(ItemStoreElement& item); // same as above
    ItemStoreElement* getMouseoverItem(); // pointer to allow null value (no item at mouse position) | FIXMEEEE: vector reallocation will cause problems if code holds valid pointer for long
    ItemStoreElement* chooseItemWithMouse(bool allowNone = true); // enters item selecting mode, after clicking returns clicked item
    bool addItem(const ItemStoreElement& item);
    bool removeItem(const ItemStoreElement& item);
    bool modifyItem(const ItemStoreElement& itemToModify, const ItemStoreElement& newItem);

    InventoryPosition findFreePositionForItem(const ItemStoreElement& elem);
    bool canItemBePlacedAtPosition(const ItemStoreElement& elem, InventoryPosition pos);

    InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements = ElementsContainer());
    ~InventoryCtrl();

    InventoryCtrl() = delete;
    InventoryCtrl(const InventoryCtrl&) = delete;
    bool operator=(const InventoryCtrl&) = delete;
    InventoryCtrl(InventoryCtrl&&) = default;
};

template<typename Variant> bool InventoryCtrl::unpersistItemLocationVariant(Variant& loc, const Json& json)
{
    try
    {
        std::string type = stringToLower(json["type"]);
        if (type == ITEM_LOC_CHEST)
        {
            MapChestRef ref;
            ref.unpersist(json, std::get<MapChestRef>(inventoryType));
            loc = ref;
        }
        else if (type == ITEM_LOC_PLAYER)
        {
            PlayerInventoryRef ref;
            ref.unpersist(json);
            loc = ref;
        }
        else if (type == ITEM_LOC_STORED)
        {
            // to have consistent code
            StoredItemRef ref;
            ref.unpersist(json);
            loc = ref;
        }
        else
        {
            wxLogError("Item location unpersist error: unknown item location type '%s'", type);
            return false;
        }
        return true;
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogError("Json error: %s", ex.what());
        return false;
    }
}