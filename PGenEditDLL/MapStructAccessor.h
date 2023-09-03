#pragma once
#include "pch.h"
#include "main.h"
#include "StructAccessor.h"
#include "LuaFunctions.h"

template<typename Map>
class TemplatedMapStructAccessor;
class MapStructAccessor;
extern MapStructAccessor* mapAccessor;

class MapStructAccessor
{
public:
    // any map
    template<typename Function>
    static void forEachChestDo(void* chestsPtr, int n, Function func)
    {
        if (MMVER == 6)
        {
            TemplatedMapStructAccessor<mm6::GameMap>::forEachChestDo(chestsPtr, n, func);
        }
        else if (MMVER == 7)
        {
            TemplatedMapStructAccessor<mm7::GameMap>::forEachChestDo(chestsPtr, n, func);
        }
        else if (MMVER == 8)
        {
            TemplatedMapStructAccessor<mm8::GameMap>::forEachChestDo(chestsPtr, n, func);
        }
        else
        {
            wxFAIL;
        }
    }

    // current map only
    template<typename Function>
    static void forEachMapChestDo(Function func)
    {
        if (MMVER == 6)
        {
            TemplatedMapStructAccessor<mm6::GameMap>::forEachMapChestDo(func);
        }
        else if (MMVER == 7)
        {
            TemplatedMapStructAccessor<mm7::GameMap>::forEachMapChestDo(func);
        }
        else if (MMVER == 8)
        {
            TemplatedMapStructAccessor<mm8::GameMap>::forEachMapChestDo(func);
        }
    }

    virtual std::string getName() const = 0;
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
};

INSTANTIATE_ACCESSOR_TEMPLATES_MM_GAMES(MapStructAccessor, GameMap);