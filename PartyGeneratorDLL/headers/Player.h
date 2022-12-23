#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)
namespace mm6
{
    struct Player
    {
        int items[5];
    };
}

namespace mm7
{
    struct Player
    {
        int items[6];
    };
}

namespace mm8
{
    struct Player
    {
        int items[7];
    };
}

#pragma pack(pop)