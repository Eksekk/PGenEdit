#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)
namespace mm6
{
	struct Item
	{
	};
}

namespace mm7
{
	struct Item // size: 0x24
	{
		int32_t number;
		int32_t bonus;
		int32_t bonusStrength;
		int32_t bonus2;
		int32_t charges;
		union
		{
			int32_t condition;
			struct
			{
				bool identified : 1;
				bool broken : 1;
				SKIPBITS(1);
				bool temporaryBonus : 1;
				SKIPBITS(4);
				bool stolen : 1;
				bool hardened : 1;
				bool refundable : 1;
			};
		};
		int8_t bodyLocation;
		uint8_t maxCharges;
		int8_t owner;
		SKIP(1);
		int64_t bonusExpireTime;
	};
}

using ItemInternal = mm7::Item; // has all required fields

namespace mm8
{
	struct Item
	{
	};
}
#pragma pack(pop)

/* GENERATE MOST OF STRUCT OFFSETS IN LUA */