#include "pch.h"
#include "main.h"
#include "InventoryCtrl.h"
#include "PlayerStructAccessor.h"
#include "ItemStructAccessor.h"
#include "GameData.h"
#include "MapStructAccessor.h"
#include "SaveGameData.h"
#include "PlayerItem.h"
#include "wx/dataview.h"
#include "MapChestStructAccessor.h"

const std::string ITEM_LOC_STORED = "stored", ITEM_LOC_CHEST = "chest", ITEM_LOC_PLAYER = "player";

const int InventoryCtrl::CELL_HEIGHT = 40; // TODO
const int InventoryCtrl::CELL_WIDTH = 40; // TODO
const std::string InventoryCtrl::JSON_KEY_INVENTORY = "inventory";

wxDEFINE_EVENT(EVT_INVENTORY_ITEM_DELETED, wxCommandEvent);
wxDEFINE_EVENT(EVT_INVENTORY_ITEM_ADDED, wxCommandEvent);
wxDEFINE_EVENT(EVT_INVENTORY_ITEMS_ADDED, wxCommandEvent);
wxDEFINE_EVENT(EVT_INVENTORY_ITEMS_DELETED, wxCommandEvent);
wxDEFINE_EVENT(EVT_INVENTORY_ALL_ITEMS_CHANGED, wxCommandEvent);

wxSize InventoryCtrl::DoGetBestClientSize() const
{
    return wxSize(CELLS_ROW * CELL_WIDTH, CELLS_COL * CELL_HEIGHT);
}

void InventoryCtrl::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    // inventory border
    wxSize windowSize = DoGetBestClientSize();
    static wxBrush cornerBrush(0x6b6868, wxBRUSHSTYLE_SOLID); // gray
    static wxBrush edgeBrush(0x8c8685, wxBRUSHSTYLE_SOLID);
    const wxPen& oldPen = dc.GetPen();
    dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
    static const int cornerSize = 10;
    // background
    dc.SetBrush(wxBrush(0xe6d0cf, wxBRUSHSTYLE_SOLID));
    dc.DrawRectangle(wxPoint(0, 0), windowSize);
    std::vector<wxRect> drawRects;
    for (int y = 0; y < CELLS_COL + 1; ++y)
    {
        for (int x = 0; x < CELLS_ROW + 1; ++x)
        {
            // important to draw lines before corners, so they get covered
            if (y == 0) // draw top to bottom
            {
                dc.SetBrush(edgeBrush);
                dc.DrawLine(wxPoint(CELL_WIDTH * x, 0), wxPoint(CELL_WIDTH * x, windowSize.GetY()));
            }
            else if (x == 0) // draw left to right
            {
                dc.SetBrush(edgeBrush);
                dc.DrawLine(wxPoint(0, CELL_HEIGHT * y), wxPoint(windowSize.GetX(), CELL_HEIGHT * y));
            }

            // corners
            wxPoint center(x * CELL_WIDTH - cornerSize / 2, y * CELL_HEIGHT - cornerSize / 2);
            wxSize size(cornerSize, cornerSize);
            // take care of points outside window borders
            int newX = std::clamp(center.x, 0, windowSize.GetWidth());
            int newY = std::clamp(center.y, 0, windowSize.GetHeight());
            size.SetWidth(size.GetWidth() - std::abs(center.x - newX));
            size.SetHeight(size.GetHeight() - std::abs(center.y - newY));
            center = wxPoint(newX, newY);
            drawRects.push_back(wxRect(center, size));
        }
    }

    dc.SetPen(oldPen);
    dc.SetBrush(cornerBrush);
    for (const auto& rect : drawRects)
    {
        dc.DrawRectangle(rect);
    }

    for (const auto& elem : elements)
    {
        if (elem->pos.isValid()) // draw only items actually placed in the inventory
        {
            drawItemAt(dc, *elem, elem->pos.x * CELL_WIDTH, elem->pos.y * CELL_HEIGHT);
        }
    }
}

template<typename Variant>
bool persistItemLocationVariant(const Variant& loc, Json& json)
{
    jsonEnsureIsObject(json);
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
    jsonEnsureIsArray(json);
    bool hasChest = false, hasPlayerInventory = false; // check that both of these are not true at the same time (can use chest's inventory + stored items or player's inventory + stored items)

    try
    {
        // remove old items belonging to same inventory before adding new
        static enum
        {
            REMOVE_CHEST,
            REMOVE_PLAYER
        } removeMode;
        if (std::holds_alternative<ItemRefMapChest>(inventoryType))
        {
            removeMode = REMOVE_CHEST;
        }
        else if (std::holds_alternative<ItemRefPlayerInventory>(inventoryType))
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
                bool shouldRemove = (removeMode == REMOVE_CHEST && std::holds_alternative<ItemRefMapChest>(tmp)) || (removeMode == REMOVE_PLAYER && std::holds_alternative<ItemRefPlayerInventory>(tmp));
                return shouldRemove;
            });
        json.erase(r.begin(), json.end());
        for (const auto& elem : elements)
        {
            Json j;
            elem->persist(j);
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
    jsonEnsureIsObject(json);
    // not persisting directly in given json, because of potential additions in future which wouldn't classify as inventory
    return persistInventory(json);
}

bool InventoryCtrl::unpersistInventory(const Json& json)
{
    bool hasChest = false, hasPlayerInventory = false;
    try
    {
        for (const Json& entry : json)
        {
            auto elem = std::make_unique<ItemStoreElement>();
            elem->unpersist(entry);
            hasChest = hasChest || std::holds_alternative<ItemRefMapChest>(elem->origin);
            hasPlayerInventory = hasPlayerInventory || std::holds_alternative<ItemRefPlayerInventory>(elem->origin);
            elements.insert(std::move(elem));
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
    return true;
}

bool InventoryCtrl::drawItemAt(wxPaintDC& dc, const ItemStoreElement& elem, int x, int y)
{
    dc.DrawBitmap(*GameData::items.at(elem.item.number)->image, x, y);
    return true;
}

bool InventoryCtrl::reloadReferencedItems()
{
    // COME BACK LATER, BREAKS CODE
    // delete all player inventory / map chest items, and readd them, if possible on old positions
    for (auto itr = elements.begin(); itr != elements.end(); )
    {
        if (!std::holds_alternative<ItemRefStored>((*itr)->origin))
		{
            // !!! IMPORTANT: first run event, THEN delete, because otherwise unique_ptr would delete the item before event is run
// 			wxCommandEvent event(EVT_INVENTORY_ITEM_DELETED);
// 			event.SetEventObject(this);
// 			event.SetClientData(itr->get());
// 			ProcessWindowEvent(event);
            itr = elements.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

    if (const ItemRefMapChest* ref = std::get_if<ItemRefMapChest>(&inventoryType))
    {
        // add items from chest
        int arrayIndex = 0;
        auto callback = [&](AnyItemStruct auto* itemPtr)
        {
            mm7::Item convertedItem = itemAccessor->forItem(itemPtr)->convertToMM7Item();
            if (convertedItem.number != 0)
            {
                ItemRefMapChest origin(*ref);
                origin.itemsArrayIndex = arrayIndex;
                // for make_unique need to explicitly specify InventoryPosition type, since it doesn't know that it's not an initializer list
                auto elem = std::make_unique<ItemStoreElement>(convertedItem, origin, ItemRefStored{}, InventoryPosition{ -1, -1 });
                // try at old position first
                auto pos = playerAccessor->getItemInventoryPosition(itemPtr);
                // this needs to return true, each item should fit, since stored items are not in inventory
                moveStoredItemToInventory(*elem, pos, false);
                elements.insert(std::move(elem));
            }
            ++arrayIndex;
        };
        MapStructAccessor::forMapChestIndexItemsDo(ref->chestId, callback);
    }
    else if (const ItemRefPlayerInventory* ref = std::get_if<ItemRefPlayerInventory>(&inventoryType))
    {
        // need to take item ptr and player/chest ptr
        // also know which game's structs to use
        
        // add items from player
        int arrayIndex = 0;
        auto callback = [&](AnyItemStruct auto* item)
        {
            mm7::Item convertedItem = itemAccessor->forItem(item)->convertToMM7Item();
            if (convertedItem.number != 0)
            {
                // FIXME: need to separate moveStoredItemInInventory into two functions: one which changes this control's state, and other which changes player's inventory. Here we need to call it, but don't want to move items in player inventory since they're already here, and we're just loading them into the control.
                ItemRefPlayerInventory origin(*ref);
                origin.itemsArrayIndex = arrayIndex;
                auto elem = std::make_unique<ItemStoreElement>(convertedItem, origin, ItemRefStored{}, InventoryPosition{ -1, -1 });
                auto pos = playerAccessor->getItemInventoryPosition(item);
                wxASSERT(moveStoredItemToInventory(*elem, pos, false));
                elements.insert(std::move(elem));
            }
            ++arrayIndex;
        };
        void* items = playerAccessor->forPlayerRosterId(ref->rosterIndex)->getItemsPtr();
        int count = playerAccessor->getItemsSize();
        itemAccessor->forEachItemDo(items, count, callback);
    }
    else
    {
        wxFAIL;
    }
    wxCommandEvent allChangedEvent(EVT_INVENTORY_ALL_ITEMS_CHANGED);
    allChangedEvent.SetEventObject(this);
    ProcessWindowEvent(allChangedEvent);
    return false;
}

void InventoryCtrl::onClick(wxMouseEvent& event)
{
}

void InventoryCtrl::onRightclick(wxMouseEvent& event)
{
}

bool InventoryCtrl::moveStoredItemToInventory(ItemStoreElement& item, InventoryPosition pos, bool affectGameInventory)
{
    // TODO: safeguard against restoring items already drawn on the control here or during button press? or both?
    wxASSERT_MSG(std::holds_alternative<ItemRefStored>(item.location), "Expected item in storage");
    auto visitor = [&](const auto& ref) {item.location = ref; }; // needed because inventoryType doesn't have stored item ref alternative

    // compute real position, trying first to place item at given position, then at any free position
    // and update control's own state
    item.pos = findFreePositionForItem(item);
    bool ret = false;
    if (pos.x != -1 || item.pos.x != -1)
    {
        if (pos.x != -1)
        {
            wxASSERT(canItemBePlacedAtPosition(item, pos));
            item.pos = pos;
        }
        std::visit(visitor, inventoryType);
        ret = true;
    }

    if (pos.isValid())
    {
        wxASSERT(canItemBePlacedAtPosition(item, pos));
        item.pos = pos;
        std::visit(visitor, inventoryType);
        ret = true;
    }
    else
    {
        auto pos2 = findFreePositionForItem(item);
        if (pos2.isValid())
        {
            wxASSERT(canItemBePlacedAtPosition(item, pos2));
            item.pos = pos2;
            std::visit(visitor, inventoryType);
            ret = true;
        }
    }
    // FIXME: the above can run and below can fail, leaving control in inconsistent state
    // actually move the item to player's/chest's inventory
    if (!affectGameInventory)
    {
        return true;
    }
    if (std::holds_alternative<ItemRefPlayerInventory>(inventoryType))
    {
        std::optional<ItemInInventoryData> inventoryDataOpt = playerAccessor->forPlayerRosterId(std::get<ItemRefPlayerInventory>(inventoryType).rosterIndex)->addItemToInventory(item.getItem());
        if (inventoryDataOpt.has_value())
        {
			std::get<ItemRefPlayerInventory>(item.location).itemsArrayIndex = inventoryDataOpt.value().itemsArrayIndex;
            if (!playerAccessor->moveItemToInventoryPosition(inventoryDataOpt.value().itemsArrayIndex, item.pos))
            {
				wxMessageBox("Couldn't move item to inventory", "Error", wxICON_ERROR);
				return false;
			}
        }
        else
        {
			wxMessageBox("Couldn't add item to inventory", "Error", wxICON_ERROR);
			return false;
		}
    }
    else if (std::holds_alternative<ItemRefMapChest>(inventoryType))
    {
		std::optional<ItemInInventoryData> inventoryDataOpt = mapAccessor->addItemToChest(std::get<ItemRefMapChest>(inventoryType).chestId, item.getItem());
        if (inventoryDataOpt.has_value())
        {
            std::get<ItemRefMapChest>(item.location).itemsArrayIndex = inventoryDataOpt.value().itemsArrayIndex;
            throw new std::logic_error("Not implemented");
			if (!chestAccessor->forMapChestIndex(std::get<ItemRefMapChest>(inventoryType).chestId)->moveItemToInventoryPosition(inventoryDataOpt.value().itemsArrayIndex, item.pos))
			{ }
        }
    }
    return ret;
}

bool InventoryCtrl::moveInventoryItemToStore(ItemStoreElement& item)
{
    wxASSERT_MSG(std::holds_alternative<ItemRefPlayerInventory>(item.location) || std::holds_alternative<ItemRefMapChest>(item.location), "Expected item in player's or chest's inventory");
    item.pos = { -1, -1 };
    item.location = ItemRefStored{};
    throw new std::logic_error("Not implemented (boolean to affect game inventory is missing)");
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

// location is used here to tell where item should be placed after adding it
ItemStoreElement* InventoryCtrl::addItem(const mm7::Item& item, const ItemLocationType& origin, const ItemLocationType& location, InventoryPosition pos)
{
    auto elem = std::make_unique<ItemStoreElement>(item, origin, location, pos);
    ItemStoreElement* ptr = elem.get();
    auto newLoc = location;
    if (ItemRefMapChest* ref = std::get_if<ItemRefMapChest>(&newLoc))
	{
		// add to chest
        auto inventoryDataOpt = mapAccessor->addItemToChest(ref->chestId, item);
        if (!inventoryDataOpt.has_value())
		{
			wxMessageBox("Couldn't add item to chest", "Error", wxICON_ERROR);
			ref->itemsArrayIndex = -1;
            return nullptr;
		}
		else
		{
			ref->itemsArrayIndex = inventoryDataOpt.value().itemsArrayIndex;
			elements.insert(std::move(elem));
		}
	}
	else if (ItemRefPlayerInventory* ref = std::get_if<ItemRefPlayerInventory>(&newLoc))
	{
		// add to player
		auto inventoryDataOpt = playerAccessor->forPlayerRosterId(ref->rosterIndex)->addItemToInventory(item);
        if (!inventoryDataOpt.has_value())
        {
            wxMessageBox("Couldn't add item to inventory", "Error", wxICON_ERROR);
            ref->itemsArrayIndex = -1;
            return nullptr;
        }
        else
        {
			ref->itemsArrayIndex = inventoryDataOpt.value().itemsArrayIndex;
            elements.insert(std::move(elem));
        }
	}
	else
	{
		elements.insert(std::move(elem));
	}
    return ptr;
}

ItemStoreElement* InventoryCtrl::addNewItem(const mm7::Item& item, const ItemLocationType& loc, InventoryPosition pos /*= { -1, -1 }*/)
{
    return addItem(item, ItemRefStored{}, loc, pos);
}

bool InventoryCtrl::removeItem(ItemStoreElement&& item)
{
    for (auto itr = elements.begin(); itr != elements.end(); ++itr)
    {
        if (**itr == item)
        {
            elements.erase(itr);
            return true;
        }
    }
    return false;
}

bool InventoryCtrl::modifyItem(const ItemStoreElement& itemToModify, ItemStoreElement&& newItem)
{
    return false;
}

bool InventoryCtrl::setHighlightForItem(const ItemStoreElement& item, bool highlight /*= true*/)
{
    if (highlight)
    {
    }
    else
    {
        // premature delete from erase???
        highlighted.erase(std::ref(item));
    }
    return false;
}

int test(char c)
{
    return c + 23;
}

InventoryPosition InventoryCtrl::findFreePositionForItem(const ItemStoreElement& elem)
{
    // mm7+/mm6 with Grayface patch placing order (prefer left side, not top)
    auto taken = std::vector<std::vector<byte_t>>(CELLS_COL, std::vector<byte_t>(CELLS_ROW, 0));
    for (const auto& existing : elements)
    {
        if (std::holds_alternative<ItemRefStored>(existing->location))
        {
            const PlayerItem* const data = existing->getItemData();
            if (data)
            {
                if (existing->pos.isInvalid())
                {
                    // not stored in inventory, skip
                    continue;
                }
                int startx = existing->pos.x, starty = existing->pos.y, w = data->inventoryWidth, h = data->inventoryHeight;
                wxASSERT_MSG(startx + w <= CELLS_ROW && starty + h <= CELLS_COL,
                    wxString::Format("Detected invalid item at row %d col %d (width %d, height %d)", starty, startx, w, h));
                for (int x = startx; x < startx + w; ++x)
                {
                    for (int y = starty; y < starty + h; ++y)
                    {
                        taken[y][x] = true;
                    }
                }
            }
        }
    }
    const PlayerItem* const data = elem.getItemData();
    if (data)
    {
        int w = data->inventoryWidth, h = data->inventoryHeight;
        for (int x = 0; x + w < CELLS_ROW; ++x)
        {
            for (int y = 0; y + h < CELLS_COL; ++y)
            {
                bool free = true;
                for (int itemX = x; itemX < x + w; ++itemX)
                {
                    for (int itemY = y; itemY < y + h; ++itemY)
                    {
                        if (taken[itemY][itemX])
                        {
                            free = false;
                            goto exit;
                        }
                    }
                }
                exit:
                if (free)
                {
                    return InventoryPosition{ x, y };
                }
            }
        }
    }
    return InventoryPosition::invalid();
}

bool InventoryCtrl::canItemBePlacedAtPosition(const ItemStoreElement& elem, InventoryPosition pos)
{
    return true;
}

InventoryCtrl::InventoryCtrl(wxWindow* parent, int CELLS_ROW, int CELLS_COL, InventoryType&& inventoryType)
    : wxWindow(parent, wxID_ANY), CELLS_ROW(CELLS_ROW), CELLS_COL(CELLS_COL), inventoryType(inventoryType)
{
    Bind(wxEVT_PAINT, &InventoryCtrl::OnPaint, this);
    SetSizeHints(DoGetBestClientSize());
    saveGameData.loadInventoryControl(*this);
    reloadReferencedItems();
}

InventoryCtrl::~InventoryCtrl()
{
    saveGameData.saveInventoryControl(*this);
}

ItemStoreElement::ItemStoreElement() : item{ 0 }, pos{ -1, -1 }, location{ ItemRefStored{} }
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

PlayerItem* ItemStoreElement::getItemData() const
{
    if (item.number != 0)
    {
        return GameData::items.at(item.number).get();
    }
    return nullptr;
}

const mm7::Item& ItemStoreElement::getItem() const
{
    return item;
}

bool ItemStoreElement::changeItem(const mm7::Item& item)
{
    wxFAIL;
    return false;
}

InventoryPosition ItemStoreElement::getPos() const
{
    return pos;
}

bool ItemStoreElement::changePos(InventoryPosition pos)
{
    wxFAIL;
    return false;
}

ItemStoreElement::ItemStoreElement(const mm7::Item& item, const ItemLocationType& origin, const ItemLocationType& location, InventoryPosition pos)
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

bool operator==(const ItemStoreElement& a, const ItemStoreElement& b)
{
    return a.isSameExceptPos(b) && pfr::eq_fields<InventoryPosition, InventoryPosition>(a.getPos(), b.getPos());
}

bool ItemRefMapChest::persist(Json& json) const
{
    jsonEnsureIsObject(json);
    auto mapLower = stringToLower(mapName);
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
        {"itemsArrayIndex", itemsArrayIndex}
    };
    return true;
}

bool ItemRefMapChest::unpersist(const Json& json)
{
    mapName = json["mapName"];
    chestId = json["chestId"];
    itemsArrayIndex = json["itemsArrayIndex"];
    return true;
}

void* ItemRefMapChest::getItemsPtr() const
{
	auto current = mapAccessor->getName();
	if (current != mapName)
	{
		wxLogFatalError("ItemRefMapChest::getItemsPtr: operating on maps other than current one is not supported yet (current: %s, requested: %s)", current, mapName);
	}
	//return mapAccessor->
	return nullptr;
}

bool ItemRefPlayerInventory::persist(Json& json) const
{
    jsonEnsureIsObject(json);
    json["type"] = ITEM_LOC_PLAYER;
    json["rosterIndex"] = rosterIndex;
    json["itemsArrayIndex"] = itemsArrayIndex;
    return true;
}

bool ItemRefPlayerInventory::unpersist(const Json& json)
{
    rosterIndex = json["rosterIndex"];
    itemsArrayIndex = json["itemsArrayIndex"];
    return true;
}

void* ItemRefPlayerInventory::getItemsPtr() const
{
	throw std::logic_error("ItemRefPlayerInventory::getItemsPtr: not implemented");
}

bool ItemRefStored::persist(Json& json) const
{
    jsonEnsureIsObject(json);
    json["type"] = ITEM_LOC_STORED;
    return true;
}

bool ItemRefStored::unpersist(const Json& json)
{
    return true;
}

bool operator==(const ItemRefMapChest& lhs, const ItemRefMapChest& rhs)
{
    return lhs.chestId == rhs.chestId && stringToLower(lhs.mapName) == stringToLower(rhs.mapName) && lhs.itemsArrayIndex == rhs.itemsArrayIndex;
}

bool operator==(const ItemRefPlayerInventory& lhs, const ItemRefPlayerInventory& rhs)
{
    return lhs.rosterIndex == rhs.rosterIndex && lhs.itemsArrayIndex == rhs.itemsArrayIndex;
}

bool operator==(const ItemRefStored& lhs, const ItemRefStored& rhs)
{
    return true;
}

RTTR_REGISTRATION
{
    using namespace rttr;
registration::class_<InventoryCtrl>("InventoryCtrl").method("addItem", &InventoryCtrl::addItem);

registerExtra<InventoryCtrl>();
registerExtra<ItemStoreElement>();
registerExtra<ItemRefMapChest>();
registerExtra<ItemRefPlayerInventory>();
registerExtra<ItemRefStored>();
}
