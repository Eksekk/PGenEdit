#pragma once
#include "main.h"
#include "Utility.h"

extern const std::string ITEM_LOC_STORED, ITEM_LOC_CHEST, ITEM_LOC_PLAYER;
class PlayerItem;

struct ItemRefMapChest
{
    std::string mapName;
    int chestId;
    int itemArrayIndex;

    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};

struct ItemRefPlayerInventory
{
    int rosterIndex;
    int itemArrayIndex;

    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};

struct ItemRefStored
{
    bool persist(Json& json) const;
    bool unpersist(const Json& json);
};

static bool operator==(const ItemRefMapChest& lhs, const ItemRefMapChest& rhs);
static bool operator==(const ItemRefPlayerInventory& lhs, const ItemRefPlayerInventory& rhs);
static bool operator==(const ItemRefStored& lhs, const ItemRefStored& rhs);

struct InventoryPosition
{
    int x, y;
    inline bool isInvalid()
    {
        return x == -1 || y == -1;
    }
    inline bool isValid()
    {
        return !isInvalid();
    }
    static inline InventoryPosition invalid()
    {
        return { -1, -1 };
    }
};

using ItemLocationType = std::variant<ItemRefStored, ItemRefMapChest, ItemRefPlayerInventory>;
using InventoryType = std::variant<ItemRefMapChest, ItemRefPlayerInventory>;

struct ItemStoreElement
{
    // TODO: automatically calculate cell width

    ItemLocationType location; // first is when item is only stored (doesn't exist in any inventory), second and third mean it's inside control's inventory
    ItemLocationType origin; // stores whether item was taken from player's inventory, chest or added artificially (to not duplicate inventory items when reloading); also stores array index when applicable

    bool persistItem(Json& json) const;
    bool unpersistItem(const Json& json);

    bool persist(Json& json) const;
    bool unpersist(const Json& json);

    PlayerItem* getItemData() const;

    const mm7::Item& getItem() const;
    bool changeItem(const mm7::Item& item);
    InventoryPosition getPos() const;
    bool changePos(InventoryPosition pos);

    bool isSameExceptPos(const ItemStoreElement& other) const;
    // exact equality
    friend bool operator==(const ItemStoreElement& a, const ItemStoreElement& b);
    ItemStoreElement();
    ItemStoreElement(const mm7::Item& item, const ItemLocationType& origin = ItemRefStored{}, const ItemLocationType& location = ItemRefStored{}, InventoryPosition pos = InventoryPosition::invalid());
private:
    mm7::Item item; // mm7 item, because it has all required fields
    InventoryPosition pos;

    friend class InventoryCtrl;
};

// hash specializations for unordered_set of highlighted elements
namespace std
{
    template<>
    struct hash<ItemRefStored>
    {
        size_t operator()(const ItemRefStored& elem) const noexcept
        {
            return 1;
        }
    };
    template<>
    struct hash<ItemRefMapChest>
    {
        size_t operator()(const ItemRefMapChest& elem) const noexcept
        {
            return hash<std::string>()(elem.mapName) ^ hash<int>()(elem.chestId);
        }
    };
    template<>
    struct hash<ItemRefPlayerInventory>
    {
        size_t operator()(const ItemRefPlayerInventory& elem) const noexcept
        {
            return hash<int>()(elem.rosterIndex);
        }
    };
    template<>
    struct hash<ItemStoreElement>
    {
        size_t operator()(const ItemStoreElement& elem) const noexcept
        {
            return 1;
        }
    };
    template<typename T>
    struct hash<std::reference_wrapper<T>>
    {
        size_t operator()(const std::reference_wrapper<T>& elem) const noexcept
        {
            return hash<std::remove_cvref_t<T>>()(elem.get());
        }
    };
}

// REALLOCATION OF ELEMENTS IN VECTOR CRASHES TABLE VIEW MODEL
// different container and/or notifying table model about changes?
using ElementsContainer = std::unordered_set<std::unique_ptr<ItemStoreElement>>;
using ItemsVariant = std::variant<mm6::Item*, mm7::Item*, mm8::Item*>;
using ItemStoreElementPtr = std::unique_ptr<ItemStoreElement>;

class InventoryCtrl : public wxWindow
{
    // FIXME: all these methods modify chest's or player's items array, but inventory positions are not modified
    static const int CELL_WIDTH, CELL_HEIGHT;
    ElementsContainer elements;
    
    // wx stuff
    virtual wxSize DoGetBestClientSize() const override;
    void OnPaint(wxPaintEvent& event);

    std::unordered_set<std::reference_wrapper<const ItemStoreElement>> highlighted;

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
    ItemStoreElement* getMouseoverItem(); // pointer to allow null value (no item at mouse position) | FIXME: vector reallocation will cause problems if code holds valid pointer for long
    ItemStoreElement* chooseItemWithMouse(bool allowNone = true); // enters item selecting mode, after clicking returns clicked item
    ItemStoreElement* addItem(const mm7::Item& item, const ItemLocationType& origin = ItemRefStored{}, const ItemLocationType& location = ItemRefStored{}, InventoryPosition pos = { -1, -1 });
    bool removeItem(ItemStoreElement&& item);
    bool modifyItem(const ItemStoreElement& itemToModify, ItemStoreElement&& newItem);
    bool setHighlightForItem(const ItemStoreElement& item, bool highlight = true);

    InventoryPosition findFreePositionForItem(const ItemStoreElement& elem);
    bool canItemBePlacedAtPosition(const ItemStoreElement& elem, InventoryPosition pos);

    InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType);
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
            ItemRefMapChest ref;
            ref.unpersist(json, std::get<ItemRefMapChest>(inventoryType));
            loc = ref;
        }
        else if (type == ITEM_LOC_PLAYER)
        {
            ItemRefPlayerInventory ref;
            ref.unpersist(json);
            loc = ref;
        }
        else if (type == ITEM_LOC_STORED)
        {
            // to have consistent code
            ItemRefStored ref;
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