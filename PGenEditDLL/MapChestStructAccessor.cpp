#include "pch.h"
#include "MapChestStructAccessor.h"
#include "MapStructAccessor.h"

MapChestStructAccessor* chestAccessor;

MapChestStructAccessor* MapChestStructAccessor::forMapChestIndex(int index)
{
	chest = mapAccessor->getMapChestsArrayData().nthElementPtr(index);
	return this;
}
