#include "pch.h"
#include "ItemStructAccessor.h"

ItemStructAccessor* itemAccessor;

ItemStructAccessor* ItemStructAccessor::forItem(void* item)
{
    itemPtr = item;
    index = 0;
    return this;
}

ItemStructAccessor* ItemStructAccessor::nextItem()
{
    ++index;
    return this;
}

ItemStructAccessor::~ItemStructAccessor()
{

}