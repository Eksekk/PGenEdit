#pragma once
#include "pch.h"
#include "main.h"
#include "StructAccessor.h"

class MapStructAccessor
{
};

template<typename Map>
class TemplatedMapStructAccessor : public MapStructAccessor, public StructAccessor<Map, mm6::GameMap, mm7::GameMap, mm8::GameMap>
{
    
};