#pragma once
#include "main.h"
#include "StructAccessor.h"
#include "LuaFunctions.h"
#include "ItemStructAccessor.h"
#include "MapChestStructAccessor.h"

template<typename Map>
class TemplatedMapStructAccessor;
class MapStructAccessor;
extern MapStructAccessor* mapAccessor;

class MapStructAccessor : public StructAccessorGenericFor
{
public:
    // any map
    template<typename Function>
    static void forEachChestDo(void* chestsPtr, int n, Function&& func)
    {
        if (MMVER == 6)
        {
            TemplatedMapStructAccessor<mm6::GameMap>::forEachChestDo(chestsPtr, n, std::forward<Function>(func));
        }
        else if (MMVER == 7)
        {
            TemplatedMapStructAccessor<mm7::GameMap>::forEachChestDo(chestsPtr, n, std::forward<Function>(func));
        }
        else if (MMVER == 8)
        {
            TemplatedMapStructAccessor<mm8::GameMap>::forEachChestDo(chestsPtr, n, std::forward<Function>(func));
        }
        else
        {
            wxFAIL;
        }
    }

    template<typename Function>
    static void forChestDo(void* chestsPtr, Function&& func)
    {
        return forEachChestDo(chestsPtr, 1, std::forward<Function>(func));
    }

    template<typename Function>
    static void forEachChestItemDo(void* chestsPtr, int n, Function&& func)
    {
        auto funcWrapper = [&](auto* chestPtr)
            {
                itemAccessor->forEachItemDo(chestPtr->items, n, std::forward<Function>(func));
            };
        
        forEachChestDo(chestsPtr, n, funcWrapper);
    }

    // current map only
    template<typename Function>
    static void forEachMapChestDo(Function&& func)
    {
        if (MMVER == 6)
        {
            TemplatedMapStructAccessor<mm6::GameMap>::forEachMapChestDo(std::forward<Function>(func));
        }
        else if (MMVER == 7)
        {
            TemplatedMapStructAccessor<mm7::GameMap>::forEachMapChestDo(std::forward<Function>(func));
        }
        else if (MMVER == 8)
        {
            TemplatedMapStructAccessor<mm8::GameMap>::forEachMapChestDo(std::forward<Function>(func));
        }
    }

    template<typename Function>
    static void forEachMapChestItemDo(Function&& func)
    {
        auto funcWrapper = [&](auto* chestPtr)
            {
                itemAccessor->forEachItemDo(chestPtr->items, chestPtr->items.size(), std::forward<Function>(func));
            };

        forEachMapChestDo(funcWrapper);
    }
    
    template<typename Function>
    static void forMapChestIndexDo(int index, Function&& func)
    {
        ArrayData data = mapAccessor->getMapChestsArrayData();
        StructAccessorGenericFor::genericForSingleArrayIndexExecute<Function, mm6::MapChest, mm7::MapChest, mm8::MapChest>(data.ptr(), index, std::forward<Function>(func));
    }

    // FIXME: allow loading data of any map
    template<typename Function>
    static void forMapChestIndexItemsDo(int index, Function&& func)
    {
        auto wrapperFunc = [&](AnyMapChestStruct auto* chestPtr)
            {
                itemAccessor->forEachItemDo(chestPtr, chestPtr->items.size(), std::forward<Function>(func));
            };
        forMapChestIndexDo(index, wrapperFunc);
    }

    virtual std::string getName() const = 0;
    virtual ArrayData getMapChestsArrayData() = 0;
    virtual ArrayData getMapMonstersArrayData() = 0;

    virtual std::optional<ItemInInventoryData> addItemToChest(int chestIndex, const mm7::Item& item) = 0;

	PGENEDIT_FOR_EACH_DEF(MapMonster)
    //PGENEDIT_FOR_EACH_STATIC_ARRAY_DEF(MapMonster)
    PGENEDIT_FOR_EACH_STATIC_ARRAY_DECL(MapMonster, TemplatedMapStructAccessor)
public:

    virtual ~MapStructAccessor();
};

template<typename Map>
class TemplatedMapStructAccessor : public MapStructAccessor, public StructAccessor<Map, mm6::GameMap, mm7::GameMap, mm8::GameMap>
{
public:
    template<typename Function>
    static void forEachChestDo(void* chestsPtr, int n, Function func)
    {
        auto chests = (decltype(Map::chests.data()))chestsPtr;
        for (int i = 0; i < n; ++i)
        {
            func(chests + i);
        }
    }

    // otherwise weird error - game is accessible (first declared), but all others (including if game is removed) nope
    using AccessorType = StructAccessor<Map, mm6::GameMap, mm7::GameMap, mm8::GameMap>;
    using AccessorType::game;
    using AccessorType::map;
    using AccessorType::party;
    using AccessorType::mouse;
    using AccessorType::screen;

    template<typename Function>
    static void forEachMapChestDo(Function func)
    {
        forEachChestDo(map->chests.data(), map->chests_size, func);
    }

    PGENEDIT_FOR_EACH_STATIC_ARRAY_DEF(MapMonster, map->monsters.data(), map->monsters_size)

    // Inherited via MapStructAccessor
    virtual std::string getName() const override
    {
        lua_getfield(Lua, LUA_REGISTRYINDEX, "MapName");
        int type = lua_type(Lua, -1);
        if (type == LUA_TSTRING)
        {
            std::string str = lua_tostring(Lua, -1);
            lua_pop(Lua, 1);
            return str;
        }
        lua_pop(Lua, 1);
        return (const char*)map->name.data();
    }

    // Inherited via MapStructAccessor
    ArrayData getMapChestsArrayData() override
    {
        return ArrayData(map->chests.data(), map->chests.size());
    }
    ArrayData getMapMonstersArrayData() override
    {
        return ArrayData(map->monsters);
	}

	void* getChestIndexPtr(int n)
	{
		return getMapChestsArrayData().nthElementPtr(n);
	}

private:
    inline void checkMapChestIndex(int index)
    {
        if (index < 0 || index > 19)
        {
            wxFAIL_MSG(wxString::Format("Invalid map chest index %d", index));
        }
    }

	std::optional<ItemInInventoryData> addItemToChest(int chestIndex, const mm7::Item& item) override
	{
        checkMapChestIndex(chestIndex);
        void* old = chestAccessor->getCurrentChestPtr();
        auto ret = chestAccessor->forChest(getChestIndexPtr(chestIndex))->addItemToInventory(item);
        (void)chestAccessor->forChest(old);
        return ret;
	}
};

INSTANTIATE_ACCESSOR_TEMPLATES_MM_GAMES(MapStructAccessor, GameMap);