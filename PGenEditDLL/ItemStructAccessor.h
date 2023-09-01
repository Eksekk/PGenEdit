#pragma once
#include "pch.h"
#include "main.h"

class ItemStructAccessor;
extern ItemStructAccessor* itemAccessor;

class ItemStructAccessor
{
protected:
    void* itemPtr;
    int index;

public:
    ItemStructAccessor* forItem(void* item);
    ItemStructAccessor* nextItem();
    [[nodiscard]] virtual mm7::Item convertToMM7Item() = 0;
    virtual ~ItemStructAccessor();

    // pure virtual function forEachItemDo(void* items, Callback callback)
    // template instantiations override it to cast to game version item type and execute callback
    // callback (usually polymorphic lambda) receives correct type
    // PROBLEM: can't have both virtual function and templated Callback
    // if I added std::function<void(void*)>, callback wouldn't know what it received
    
    virtual void forEachItemDo2(void* items, int n, std::function<void(std::variant<mm6::Item*, mm7::Item*, mm8::Item*> variant)> callback) = 0;
};

template<typename Item>
class TemplatedItemStructAccessor : public ItemStructAccessor
{
    [[nodiscard]] Item* getItemToAffect();
public:
    [[nodiscard]] virtual mm7::Item convertToMM7Item() override
    {
        Item* item = getItemToAffect();
        if constexpr (SAME(Item, mm7::Item))
        {
            return *item;
        }
        else
        {
            mm7::Item changed;
            changed.number = item->number;
            changed.bonus = item->bonus;
            changed.bonus2 = item->bonus2;
            changed.bodyLocation = item->bodyLocation;
            changed.bonusStrength = item->bonusStrength;
            changed.condition = item->condition;
            changed.charges = item->charges;
            changed.maxCharges = item->maxCharges;
            changed.owner = item->owner;
            if constexpr (!SAME(Item, mm6::Item))
            {
                changed.bonusExpireTime = item->bonusExpireTime;
            }
            return changed;
        }
    }

    template<typename Container, typename Callback>
    void forEachItemDo(Container& container, Callback callback);

    template<typename Callback>
    void forEachItemDo(Item* item, int n, Callback callback);

    void forEachItemDo2(void* items, int n, std::function<void(std::variant<mm6::Item*, mm7::Item*, mm8::Item*> variant)> callback);
};

template<typename Item>
void TemplatedItemStructAccessor<Item>::forEachItemDo2(void* items, int n, std::function<void(std::variant<mm6::Item*, mm7::Item*, mm8::Item*> variant)> callback)
{
    for (int i = 0; i < n; ++i)
    {
        callback(reinterpret_cast<Item*>(items) + i);
    }
}

void ff();

template<typename Item>
template<typename Callback>
void TemplatedItemStructAccessor<Item>::forEachItemDo(Item* item, int n, Callback callback)
{
    for (int i = 0; i < n; ++i)
    {
        callback(item[i]);
    }
}

template<typename Item>
template<typename Container, typename Callback>
void TemplatedItemStructAccessor<Item>::forEachItemDo(Container& container, Callback callback)
{
    for (Item& item : container)
    {
        callback(item);
    }
}

template<typename Item>
Item* TemplatedItemStructAccessor<Item>::getItemToAffect()
{
    Item* item = reinterpret_cast<Item*>(itemPtr);
    return item + index;
}

INSTANTIATE_CLASS_TEMPLATES_MM_GAMES(TemplatedItemStructAccessor, Item);

using ItemStructAccessor_6 = TemplatedItemStructAccessor<mm6::Item>;
using ItemStructAccessor_7 = TemplatedItemStructAccessor<mm7::Item>;
using ItemStructAccessor_8 = TemplatedItemStructAccessor<mm8::Item>;