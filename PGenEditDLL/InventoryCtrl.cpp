#include "pch.h"
#include "main.h"
#include "InventoryCtrl.h"
#include "PlayerStructAccessor.h"
#include "ItemStructAccessor.h"
#include "GameData.h"

const std::string ITEM_LOC_STORED = "stored", ITEM_LOC_CHEST = "chest", ITEM_LOC_PLAYER = "player";

const int InventoryCtrl::CELL_HEIGHT = 40; // TODO
const int InventoryCtrl::CELL_WIDTH = 40; // TODO

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
    std::visit([&](auto& arg)
    {
        arg.persist(json);
    }, loc);
    return true;
}

template<typename Variant>
bool unpersistItemLocationVariant(Variant& loc, const Json& json)
{
    try
    {
        std::string type = tolowerStr(json["type"]);
        if (type == ITEM_LOC_CHEST)
        {
            MapChestRef ref;
            ref.unpersist(json);
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

bool persistItem(const ItemStoreElement& elem, Json& json)
{
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
    bool hasChest = false, hasPlayerInventory = false; // check that both of these are not true at the same time (can use chest's inventory + stored items or player's inventory + stored items)
    try
    {
        for (const auto& elem : elements)
        {
            Json entryJson;
            Json& locationJson = entryJson["location"];
            // using ifs there, because I want to make sure there aren't items both from player and chest
            if (const MapChestRef* ref = std::get_if<MapChestRef>(&elem.location))
            {
                ref->persist(locationJson);
                hasChest = true;
            }
            else if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&elem.location))
            {
                ref->persist(locationJson);
                hasPlayerInventory = true;
            }
            else if (const StoredItemRef* ref = std::get_if<StoredItemRef>(&elem.location))
            {
                ref->persist(locationJson);
            }
            else
            {
                wxFAIL;
                return false;
            }

            Json& originJson = entryJson["origin"];
            persistItemLocationVariant(elem.origin, originJson);
            Json itemJson;
            persistItem(elem, itemJson);
            entryJson["elem"] = std::move(itemJson);
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

bool InventoryCtrl::persist(Json& json) const
{
    return persistInventory(json["inventory"]);
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
            std::string type = tolowerStr(location["type"]);
            if (type == ITEM_LOC_CHEST)
            {
                MapChestRef ref;
                ref.unpersist(location);
                elem.location = std::move(ref);
                hasChest = true;
            }
            else if (type == ITEM_LOC_PLAYER)
            {
                PlayerInventoryRef ref;
                ref.unpersist(location);
                elem.location = std::move(ref);
                hasPlayerInventory = true;
            }
            else if (type == ITEM_LOC_STORED)
            {
                StoredItemRef ref;
                ref.unpersist(location);
                elem.location = std::move(ref);
            }
            else
            {
                wxFAIL;
                return false;
            }
            unpersistItemLocationVariant(elem.origin, json["origin"]);
            unpersistItem(elem, entry["elem"]);
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
    if (json.contains("inventory"))
    {
        return unpersistInventory(json["inventory"]);
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
    ElementsContainer storedOnly;
    std::ranges::copy_if(elements, std::back_inserter(storedOnly), [=](const ItemStoreElement& elem)
    {
        return std::holds_alternative<StoredItemRef>(elem.location);
    });

    if (const MapChestRef* ref = std::get_if<MapChestRef>(&inventoryType))
    {
        // add items from chest
        //auto addItems = [](auto& )
    }
    else if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&inventoryType))
    {
        // add items from player
        auto callback = [&](auto& item)
        {
            mm7::Item convertedItem = itemAccessor->forItem(&item)->convertToMM7Item();
            if (item.number != 0)
            {
                ItemStoreElement elem(convertedItem, { -1, -1 }, StoredItemRef{}, PlayerInventoryRef{ref->rosterIndex});
                InventoryPosition pos = findFreePositionForItem(elem);
                if (pos.x != -1)
                {
                    elem.pos = pos;
                    elem.location = PlayerInventoryRef{ ref->rosterIndex };
                }
                elements.push_back(std::move(elem));
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
    elements = std::move(storedOnly);
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
    auto visitor = [&](const auto& ref) {item.location = ref; };
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
    // TODO: unpersist
}

InventoryCtrl::~InventoryCtrl()
{
    // TODO: persist
}

ItemStoreElement::ItemStoreElement() : item{ 0 }, pos{ -1, -1 }, location{ PlayerInventoryRef{} }
{

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
    json["type"] = ITEM_LOC_CHEST;
    json["mapName"] = mapName;
    json["chestId"] = chestId;
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