#include "pch.h"
#include "main.h"
#include "InventoryCtrl.h"
#include "PlayerStructAccessor.h"
#include "ItemStructAccessor.h"
#include "GameData.h"
#include "MapStructAccessor.h"
#include "SaveGameData.h"

const std::string ITEM_LOC_STORED = "stored", ITEM_LOC_CHEST = "chest", ITEM_LOC_PLAYER = "player";

const int InventoryCtrl::CELL_HEIGHT = 40; // TODO
const int InventoryCtrl::CELL_WIDTH = 40; // TODO
const std::string InventoryCtrl::JSON_KEY_INVENTORY = "inventory";

wxSize InventoryCtrl::DoGetBestClientSize() const
{
    return wxSize(CELLS_ROW * CELL_WIDTH, CELLS_COL * CELL_HEIGHT);
}

void InventoryCtrl::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    // inventory border
    wxSize size = DoGetBestClientSize();
    static wxBrush cornerBrush(0x6b6868, wxBRUSHSTYLE_SOLID); // gray
    static wxBrush edgeBrush(0x8c8685, wxBRUSHSTYLE_SOLID);
    // background
    dc.SetBrush(wxBrush(0xe6d0cf, wxBRUSHSTYLE_SOLID));
    dc.DrawRectangle(wxPoint(0, 0), size);
    std::vector<wxRect> drawRects;
    for (int y = 0; y < CELL_HEIGHT + 1; ++y)
    {
        for (int x = 0; x < CELL_WIDTH + 1; ++x)
        {
            // important to draw lines before corners, so they get covered, but I think that's done here
            if (y == 0) // draw top to bottom
            {
                dc.SetBrush(edgeBrush);
                dc.DrawLine(wxPoint(CELL_WIDTH * x, 0), wxPoint(CELL_WIDTH * x, size.GetY()));
            }
            else if (x == 0) // draw left to right
            {
                dc.SetBrush(edgeBrush);
                dc.DrawLine(wxPoint(0, CELL_HEIGHT * y), wxPoint(size.GetX(), CELL_HEIGHT * y));
            }
            drawRects.push_back(wxRect(wxPoint(x * CELL_WIDTH, y * CELL_HEIGHT), wxSize(10, 10)));
        }
    }

    dc.SetBrush(cornerBrush);
    for (const auto& rect : drawRects)
    {
        dc.DrawRectangle(rect);
    }

    for (const auto& elem : elements)
    {
        drawItemAt(dc, elem, elem.pos.x * CELL_WIDTH, elem.pos.y * CELL_HEIGHT);
    }
    /*
     
     
     */
}

template<typename Variant>
bool persistItemLocationVariant(const Variant& loc, Json& json)
{
    try
    {
        std::visit([&](auto& arg)
            {
                arg.persist(json);
            }, loc);
        return true;
    }
    catch (const JsonException& ex)
    {
        wxLogError("Item location variant persist error: '%s'", ex.what());
        return false;
    }
}

template<typename Variant>
bool unpersistItemLocationVariant(Variant& loc, const Json& json)
{
    try 
    {
        std::visit([&](auto& arg)
            {
                arg.unpersist(json);
            }, loc);
        return true;
    }
    catch (const JsonException& ex)
    {
        wxLogError("Item location variant unpersist error: '%s'", ex.what());
        return false;
    }
}

bool ItemStoreElement::persistItem(Json& json) const
{
    try
    {
        json["pos"] =
        {
            {"x", pos.x},
            {"y", pos.y}
        };
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

bool ItemStoreElement::unpersistItem(const Json& json)
{
    try
    {
        const Json& posJson = json["pos"];
        pos.x = posJson["x"];
        pos.y = posJson["y"];
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
        wxLogError("Couldn't persist elem: %s", ex.what());
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
            origin: {
                "type": ITEM_LOC_CHEST,
                "mapName": "d23.blv",
                "chestId": 5
            },
            elem: {
                "number": 20,
                "bonus2": 33,
                "condition": 3,
                // etc...
            }
        },
        {
            // another elem...
        }
     }
     **/

    // only store saved items? actual chest's items will be reloaded anyways
    /*
     "mapChestsStoredItems" = {
     
     }
     **/
    bool hasChest = false, hasPlayerInventory = false; // check that both of these are not true at the same time (can use chest's inventory + stored items or player's inventory + stored items)

    try
    {
        // remove old items belonging to same inventory before adding new
        static enum
        {
            REMOVE_CHEST,
            REMOVE_PLAYER
        } removeMode;
        if (std::holds_alternative<MapChestRef>(inventoryType))
        {
            removeMode = REMOVE_CHEST;
        }
        else if (std::holds_alternative<PlayerInventoryRef>(inventoryType))
        {
            removeMode = REMOVE_PLAYER;
        }
        else
        {
            wxFAIL_MSG("Invalid inventoryType value");
        }
        auto r = std::ranges::remove_if(json, [&](Json& elem) -> bool
            {
                ItemLocationType tmp;
                std::visit([&](auto& loc) { loc.unpersist(elem); }, tmp);
                bool shouldRemove = (removeMode == REMOVE_CHEST && std::holds_alternative<MapChestRef>(tmp)) || (removeMode == REMOVE_PLAYER && std::holds_alternative<PlayerInventoryRef>(tmp));
                return shouldRemove;
            });
        json.erase(r.begin(), json.end());
        for (const auto& elem : elements)
        {
            Json j;
            elem.persist(j);
            json.push_back(std::move(j));
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

bool InventoryCtrl::persist(Json& json) const
{
    Json j = json.value(JSON_KEY_INVENTORY, Json{});
    // not persisting directly in given json, because of potential additions in future which wouldn't classify as inventory
    return persistInventory(j);
}

bool InventoryCtrl::unpersistInventory(const Json& json)
{
    bool hasChest = false, hasPlayerInventory = false;
    try
    {
        for (const Json& entry : json)
        {
            ItemStoreElement elem;
            elem.unpersist(entry);
            hasChest = hasChest || std::holds_alternative<MapChestRef>(elem.origin);
            hasPlayerInventory = hasPlayerInventory || std::holds_alternative<PlayerInventoryRef>(elem.origin);
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

bool InventoryCtrl::unpersist(const Json& json)
{
    if (json.contains(JSON_KEY_INVENTORY))
    {
        return unpersistInventory(json[JSON_KEY_INVENTORY]);
    }
    return false;
}

bool InventoryCtrl::drawItemAt(wxPaintDC& dc, const ItemStoreElement& elem, int x, int y)
{
    dc.DrawBitmap(*GameData::items.at(elem.item.number)->image, x, y);
    return true;
}

bool InventoryCtrl::reloadReferencedItems()
{
    ElementsContainer nextElements; // will be assigned to elements
    std::ranges::copy_if(elements, std::back_inserter(nextElements), [=](const ItemStoreElement& elem)
    {
        return std::holds_alternative<StoredItemRef>(elem.origin);
    });

    if (const MapChestRef* ref = std::get_if<MapChestRef>(&inventoryType))
    {
        // add items from chest
        auto callback = [&](auto itemPtr)
        {
            mm7::Item convertedItem = itemAccessor->forItem(itemPtr)->convertToMM7Item();
            if (convertedItem.number != 0)
            {
                ItemStoreElement elem(convertedItem, { -1, -1 }, StoredItemRef{}, MapChestRef(*ref));
                moveStoredItemToInventory(elem);
                nextElements.push_back(std::move(elem));
            }
        };
        mapAccessor->forEachMapChestDo(callback);
    }
    else if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&inventoryType))
    {
        // add items from player
        auto callback = [&](auto& item)
        {
            mm7::Item convertedItem = itemAccessor->forItem(&item)->convertToMM7Item();
            if (convertedItem.number != 0)
            {
                ItemStoreElement elem(convertedItem, { -1, -1 }, StoredItemRef{}, PlayerInventoryRef(*ref));
                moveStoredItemToInventory(elem);
                nextElements.push_back(std::move(elem));
            }
        };
        void* items = playerAccessor->forPlayerRosterId(ref->rosterIndex)->getItemsPtr();
        if (MMVER == 6)
        {
            dynamic_cast<ItemStructAccessor_6*>(itemAccessor)->forEachItemDo((mm6::Item*)items, playerAccessor->getItemsSize(), callback);
        }
        else if (MMVER == 7)
        {
            dynamic_cast<ItemStructAccessor_7*>(itemAccessor)->forEachItemDo((mm7::Item*)items, playerAccessor->getItemsSize(), callback);
        }
        else if (MMVER == 8)
        {
            dynamic_cast<ItemStructAccessor_8*>(itemAccessor)->forEachItemDo((mm8::Item*)items, playerAccessor->getItemsSize(), callback);
        }
    }
    else
    {
        wxFAIL;
    }
    elements = std::move(nextElements);
    return false;
}

void InventoryCtrl::onClick(wxMouseEvent& event)
{
}

void InventoryCtrl::onRightclick(wxMouseEvent& event)
{
}

bool InventoryCtrl::moveStoredItemToInventory(ItemStoreElement& item, InventoryPosition pos)
{
    wxASSERT_MSG(std::holds_alternative<StoredItemRef>(item.location), "Expected item in storage");
    auto visitor = [&](const auto& ref) {item.location = ref; }; // needed because inventoryType doesn't have stored item ref alternative
    item.pos = findFreePositionForItem(item);
    if (pos.x != -1 || item.pos.x != -1)
    {
        if (pos.x != -1)
        {
            wxASSERT(canItemBePlacedAtPosition(item, pos));
            item.pos = pos;
        }
        std::visit(visitor, inventoryType);
        return true;
    }
    return false;
}

bool InventoryCtrl::moveInventoryItemToStore(ItemStoreElement& item)
{
    wxASSERT_MSG(std::holds_alternative<PlayerInventoryRef>(item.location) || std::holds_alternative<MapChestRef>(item.location), "Expected item in player's or chest's inventory");
    item.pos = { -1, -1 };
    item.location = StoredItemRef{};
    return true;
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
    for (size_t i = 0; i < elements.size(); ++i)
    {
        if (item.isSameExceptPos(elements[i]))
        {
            elements.erase(elements.begin() + i);
            return true;
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
    SetSizeHints(DoGetBestClientSize());
    saveGameData.loadInventoryControl(*this);
}

InventoryCtrl::~InventoryCtrl()
{
    saveGameData.saveInventoryControl(*this);
}

ItemStoreElement::ItemStoreElement() : item{ 0 }, pos{ -1, -1 }, location{ PlayerInventoryRef{} }
{

}

bool ItemStoreElement::persist(Json& json) const
{
    json.clear();
    Json& locationJson = json["location"];
    persistItemLocationVariant(location, locationJson);

    Json& originJson = json["origin"];
    persistItemLocationVariant(origin, originJson);
    persistItem(json);
    return true;
}

bool ItemStoreElement::unpersist(const Json& json)
{
    const Json& locationJson = json.at("location");
    unpersistItemLocationVariant(location, locationJson);
    unpersistItemLocationVariant(origin, json.at("origin"));
    unpersistItem(json);
    return true;
}

ItemStoreElement::ItemStoreElement(const mm7::Item& item, InventoryPosition pos, const ItemLocationType& location, const ItemLocationType& origin)
    : item(item), pos(pos), location(location), origin(origin)
{

}

bool ItemStoreElement::isSameExceptPos(const ItemStoreElement& other) const
{
    // using memcmp, because I'm too lazy to write comparator function; items are mm7 only, so it should work
    if (location.index() == other.location.index())
    {
        return memcmp(&item, &other.item, sizeof(item)) == 0 && location == other.location;
    }
    else
    {
        return false;
    }
}

bool MapChestRef::persist(Json& json) const
{
    auto mapLower = tolowerStr(mapName);
    // not sure yet which storage approach I take (one big array of map chests or tree indexed by map names and chest ids), so store both ways
    // LOCATION (current) -> flat?
    // ORIGIN (initial) -> flat?
    // MAP CHESTS array -> structured?
    // mapChests = 
    // {
    //     "7d05.blv":
    //     {
    //         "chestId" = 5,
    //         "items" = {...}
    //     },
    //     {
    //         ...
    //     }
    // },
    // {
    //     ...
    // }
    json[mapLower][std::to_string(chestId)] =
    {
        {"type", ITEM_LOC_CHEST},
        {"mapName", mapLower},
        {"chestId", chestId},
    };
    return true;
}

bool MapChestRef::unpersist(const Json& json)
{
    mapName = json["mapName"];
    chestId = json["chestId"];
    return true;
}

bool PlayerInventoryRef::persist(Json& json) const
{
    json["type"] = ITEM_LOC_PLAYER;
    json["rosterIndex"] = rosterIndex;
    return true;
}

bool PlayerInventoryRef::unpersist(const Json& json)
{
    rosterIndex = json["rosterIndex"];
    return true;
}

bool StoredItemRef::persist(Json& json) const
{
    json["type"] = ITEM_LOC_STORED;
    return true;
}

bool StoredItemRef::unpersist(const Json& json)
{
    return true;
}

bool operator==(const MapChestRef& lhs, const MapChestRef& rhs)
{
    return lhs.chestId == rhs.chestId && tolowerStr(lhs.mapName) == tolowerStr(rhs.mapName);
}

bool operator==(const PlayerInventoryRef& lhs, const PlayerInventoryRef& rhs)
{
    return lhs.rosterIndex == rhs.rosterIndex;
}

bool operator==(const StoredItemRef& lhs, const StoredItemRef& rhs)
{
    return true;
}