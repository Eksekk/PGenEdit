#include "pch.h"
#include "main.h"
#include "InventoryCtrl.h"
#include "PlayerStructAccessor.h"

const std::string ITEM_LOC_STORED = "stored", ITEM_LOC_CHEST = "chest", ITEM_LOC_PLAYER = "player";

const int InventoryCtrl::CELL_HEIGHT = 40; // TODO
const int InventoryCtrl::CELL_WIDTH = 40; // TODO

wxSize InventoryCtrl::DoGetBestSize() const
{
    return wxSize(CELLS_ROW * CELL_WIDTH, CELLS_COL * CELL_HEIGHT);
}

void InventoryCtrl::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
}

bool persistItem(const ItemStoreElement& elem, Json& json)
{
    /*
     *struct Item // size: 0x24
    {
        int32_t number;
        int32_t bonus;
        int32_t bonusStrength;
        int32_t bonus2;
        int32_t charges;
        union
        {
            int32_t condition;
            struct
            {
                bool identified : 1;
                bool broken : 1;
                SKIPBITS(1);
                bool temporaryBonus : 1;
                SKIPBITS(4);
                bool stolen : 1;
                bool hardened : 1;
                bool refundable : 1;
            };
        };
        int8_t bodyLocation;
        uint8_t maxCharges;
        int8_t owner;
        SKIP(1);
        int64_t bonusExpireTime;
    };*/
    try
    {
        json["pos"] =
        {
            {"x", elem.pos.x},
            {"y", elem.pos.y}
        };
        const mm7::Item& item = elem.item;
        Json& itemJson = json["item"];
        // don't care about SKIP-ped field?
        itemJson["number"] = item.number;
        itemJson["bonus"] = item.bonus;
        itemJson["bonusStrength"] = item.bonusStrength;
        itemJson["bonus2"] = item.bonus2;
        itemJson["charges"] = item.charges;
        itemJson["condition"] = item.condition;
        itemJson["bodyLocation"] = item.bodyLocation;
        itemJson["maxCharges"] = item.maxCharges;
        itemJson["owner"] = item.owner;
        itemJson["bonusExpireTime"] = item.bonusExpireTime;
        return true;
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogError("Couldn't persist item: %s", ex.what());
        return false;
    }
}

bool unpersistItem(ItemStoreElement& elem, const Json& json)
{
    try
    {
        const Json& pos = json["pos"];
        elem.pos.x = pos["x"];
        elem.pos.y = pos["y"];
        mm7::Item& item = elem.item;
        const Json& itemJson = json["item"];
        // don't care about SKIP-ped field?
        item.number = itemJson["number"];
        item.bonus = itemJson["bonus"];
        item.bonusStrength = itemJson["bonusStrength"];
        item.bonus2 = itemJson["bonus2"];
        item.charges = itemJson["charges"];
        item.condition = itemJson["condition"];
        item.bodyLocation = itemJson["bodyLocation"];
        item.maxCharges = itemJson["maxCharges"];
        item.owner = itemJson["owner"];
        item.bonusExpireTime = itemJson["bonusExpireTime"];
        return true;
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogError("Couldn't persist item: %s", ex.what());
        return false;
    }
}

const ElementsContainer& InventoryCtrl::getElements() const
{
    return elements;
}

bool InventoryCtrl::persistInventory(Json& json) const
{
    /*
     "items": {
        {
            location: {
                "type": ITEM_LOC_CHEST,
                "mapName": "d23.blv",
                "chestId": 5
            },
            item: {
                "number": 20,
                "bonus2": 33,
                "condition": 3,
                // etc...
            }
        },
        {
            // another item...
        }
     }
     **/
    bool hasChest = false, hasPlayerInventory = false; // check that both of these are not true at the same time (can use chest's inventory + stored items or player's inventory + stored items)
    try
    {
        for (const auto& elem : elements)
        {
            Json entryJson;
            Json& location = entryJson["location"];
            if (const MapChestRef* ref = std::get_if<MapChestRef>(&elem.location))
            {
                location["type"] = ITEM_LOC_CHEST;
                location["mapName"] = ref->mapName;
                location["chestId"] = ref->chestId;
                hasChest = true;
            }
            else if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&elem.location))
            {
                location["type"] = ITEM_LOC_PLAYER;
                location["rosterIndex"] = ref->rosterIndex;
                hasPlayerInventory = true;
            }
            else if (const std::monostate* ref = std::get_if<std::monostate>(&elem.location))
            {
                location["type"] = ITEM_LOC_STORED;
            }
            else
            {
                wxFAIL;
                return false;
            }
            Json itemJson;
            persistItem(elem, itemJson);
            entryJson["item"] = std::move(itemJson);
            json.push_back(std::move(entryJson));
        }
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogError("Couldn't unpersist inventory: %s", ex.what());
        return false;
    }
    
    if (hasChest && hasPlayerInventory)
    {
        wxFAIL_MSG("InventoryCtrl has items both from chest and player inventory");
        return false;
    }
    return true;
}

bool InventoryCtrl::unpersistInventory(const Json& json)
{
    bool hasChest = false, hasPlayerInventory = false;
    try
    {
        for (const Json& entry : json)
        {
            ItemStoreElement elem;
            const Json& location = entry["location"];
            std::string type = location["type"];
            std::ranges::transform(type, type.begin(), [](char c) {return std::tolower(c); });
            if (type == ITEM_LOC_CHEST)
            {
                elem.location = MapChestRef{
                    .mapName = location["mapName"],
                    .chestId = location["chestId"]
                };
                hasChest = true;
            }
            else if (type == ITEM_LOC_PLAYER)
            {
                elem.location = PlayerInventoryRef{
                    .rosterIndex = location["rosterIndex"]
                };
                hasPlayerInventory = true;
            }
            else if (type == ITEM_LOC_STORED)
            {
                elem.location = std::monostate();
            }
            else
            {
                wxFAIL;
                return false;
            }
            unpersistItem(elem, entry["item"]);
            elements.push_back(std::move(elem));
        }
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogError("Couldn't unpersist inventory: %s", ex.what());
        return false;
    }
    
    if (hasChest && hasPlayerInventory)
    {
        wxFAIL_MSG("InventoryCtrl has items both from chest and player inventory");
        return false;
    }
    return true;
}
template <int i>
struct types {};

template <>
struct types<1>
{
    typedef int type;
};

template <>
struct types<2>
{
    typedef long type;
};

bool InventoryCtrl::reloadReferencedItems()
{
    ElementsContainer storedOnly;
    std::ranges::copy_if(elements, std::back_inserter(storedOnly), [=](const ItemStoreElement& elem)
    {
        return std::holds_alternative<std::monostate>(elem.location);
    });

    if (const MapChestRef* ref = std::get_if<MapChestRef>(&inventoryType))
    {
        // add items from chest
        //auto addItems = [](auto& )
    }
    else if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&inventoryType))
    {
        // add items from player
        gameVersionDispatchItem(playerAccessor->forPlayerRosterId(ref->rosterIndex)->getItemsPtr(), [&](auto item)
            {

            });
    }
    else
    {
        wxFAIL;
    }
    elements = std::move(storedOnly);
    return false;
}

void InventoryCtrl::onClick(wxMouseEvent& event)
{
}

void InventoryCtrl::onRightclick(wxMouseEvent& event)
{
}

bool InventoryCtrl::moveStoredItemToInventory(const ItemStoreElement& item)
{
    return false;
}

bool InventoryCtrl::moveInventoryItemToStore(const ItemStoreElement& item)
{
    return false;
}

ItemStoreElement* InventoryCtrl::getMouseoverItem()
{
    return nullptr;
}

ItemStoreElement* InventoryCtrl::chooseItemWithMouse(bool allowNone)
{
    return nullptr;
}

bool InventoryCtrl::addItem(const ItemStoreElement& item)
{
    elements.push_back(item);
    return true;
}

bool InventoryCtrl::removeItem(const ItemStoreElement& item)
{
    for (const auto& item2 : elements)
    {
        if (item.isSameExceptPos(item2))
        {

        }
    }
    return false;
}

bool InventoryCtrl::modifyItem(const ItemStoreElement& itemToModify, const ItemStoreElement& newItem)
{
    return false;
}

InventoryPosition InventoryCtrl::findFreePositionForItem(const ItemStoreElement& elem)
{
    return {-1, -1};
}

bool InventoryCtrl::canItemBePlacedAtPosition(const ItemStoreElement& elem, InventoryPosition pos)
{
    return true;
}

InventoryCtrl::InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType, const ElementsContainer& elements)
    : wxControl(parent, wxID_ANY), CELLS_ROW(CELLS_ROW), CELLS_COL(CELLS_COL), inventoryType(inventoryType), elements(elements)
{
}

ItemStoreElement::ItemStoreElement() : item{0}, pos{-1, -1}, location{std::monostate()}
{

}

bool ItemStoreElement::isSameExceptPos(const ItemStoreElement& other) const
{
    // using memcmp, because I'm too lazy to write comparator function
    //if (memcmp(&item, &other.item, sizeof(item)) == 0 && x)
    {

    }
    return false;
}