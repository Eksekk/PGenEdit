#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct ObjectRef // size: 0x4
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type | 0x0 (0 decimal)
			uint16_t value; // 0x0 (0 decimal) | MMExt info: Raw value. In inventory screen this is item index, in other screens it equals !Lua[[Kind + Index*8]].
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | 0x0 (0 decimal)
			};
		};
		int16_t ZBuf; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm6::ObjectRef) == 0x4, "Invalid \"mm6::ObjectRef\" structure size");
	static_assert(offsetof(mm6::ObjectRef, ZBuf) == 2);



	struct ObjectRef2 // size: 0x2
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type | 0x0 (0 decimal)
			uint16_t value; // 0x0 (0 decimal) | MMExt info: Raw value. In inventory screen this is item index, in other screens it equals !Lua[[Kind + Index*8]].
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | 0x0 (0 decimal)
			};
		};
	};
	static_assert(sizeof(mm6::ObjectRef2) == 0x2, "Invalid \"mm6::ObjectRef2\" structure size");



	struct Item // size: 0x1C
	{
		int32_t number; // 0x0 (0 decimal)
		int32_t bonus; // 0x4 (4 decimal) | MMExt info: From STDITEMS.TXT. You can use #const.Stats:#, just add 1 to a supported value from it.
		int32_t bonusStrength; // 0x8 (8 decimal)
		int32_t bonus2; // 0xC (12 decimal) | MMExt info: From SPCITEMS.TXT. Value in case of gold.
		int32_t charges; // 0x10 (16 decimal)
		union
		{
			int32_t condition; // 0x14 (20 decimal)
			struct
			{
				bool identified : 1; // 0x14 (20 decimal), bit index 7
				bool broken : 1; // 0x14 (20 decimal), bit index 6
				SKIPBITS(1);
				bool temporaryBonus : 1; // 0x14 (20 decimal), bit index 4
				SKIPBITS(4);
				bool stolen : 1; // 0x15 (21 decimal), bit index 7
				bool hardened : 1; // 0x15 (21 decimal), bit index 6
				bool refundable : 1; // 0x15 (21 decimal), bit index 5 | MMExt info: Added in patch v2.5.4. Used internally to remove artifacts generated in unopened chests from #ArtifactsFound:structs.GameParty.ArtifactsFound# upon map refill.
			};
		};
		int8_t bodyLocation; // 0x18 (24 decimal)
		uint8_t maxCharges; // 0x19 (25 decimal)
		int8_t owner; // 0x1A (26 decimal)
		SKIP(1);
		char* __thiscall getIdentifiedName(); // address: 0x448680 | defaults: (this)
		int __thiscall generateArtifact(); // address: 0x44A6B0 | defaults: (this)
		int __thiscall getValue(); // address: 0x448610 | defaults: (this)
		char* __thiscall getName(); // address: 0x448660 | defaults: (this)
	};
	static_assert(sizeof(mm6::Item) == 0x1C, "Invalid \"mm6::Item\" structure size");
	static_assert(offsetof(mm6::Item, bonus) == 4);
	static_assert(offsetof(mm6::Item, bonusStrength) == 8);
	static_assert(offsetof(mm6::Item, bonus2) == 12);
	static_assert(offsetof(mm6::Item, charges) == 16);
	static_assert(offsetof(mm6::Item, condition) == 20);
	static_assert(offsetof(mm6::Item, bodyLocation) == 24);
	static_assert(offsetof(mm6::Item, maxCharges) == 25);
	static_assert(offsetof(mm6::Item, owner) == 26);



	struct SpellBuff // size: 0x10
	{
		int64_t expireTime; // 0x0 (0 decimal)
		int16_t power; // 0x8 (8 decimal)
		int16_t skill; // 0xA (10 decimal)
		int16_t overlayId; // 0xC (12 decimal)
		uint8_t caster; // 0xE (14 decimal)
		uint8_t bits; // 0xF (15 decimal)
	};
	static_assert(sizeof(mm6::SpellBuff) == 0x10, "Invalid \"mm6::SpellBuff\" structure size");
	static_assert(offsetof(mm6::SpellBuff, power) == 8);
	static_assert(offsetof(mm6::SpellBuff, skill) == 10);
	static_assert(offsetof(mm6::SpellBuff, overlayId) == 12);
	static_assert(offsetof(mm6::SpellBuff, caster) == 14);
	static_assert(offsetof(mm6::SpellBuff, bits) == 15);
}
namespace mm7
{
	struct StartStat // size: 0x4
	{
		int8_t base; // 0x0 (0 decimal)
		int8_t max; // 0x1 (1 decimal)
		int8_t spend; // 0x2 (2 decimal) | MMExt info: how much you spend on it to add a point
		int8_t add; // 0x3 (3 decimal) | MMExt info: how much is added when you spend a point
	};
	static_assert(sizeof(mm7::StartStat) == 0x4, "Invalid \"mm7::StartStat\" structure size");
	static_assert(offsetof(mm7::StartStat, max) == 1);
	static_assert(offsetof(mm7::StartStat, spend) == 2);
	static_assert(offsetof(mm7::StartStat, add) == 3);



	struct ObjectRef // size: 0x4
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type | 0x0 (0 decimal)
			uint16_t value; // 0x0 (0 decimal) | MMExt info: Raw value. In inventory screen this is item index, in other screens it equals !Lua[[Kind + Index*8]].
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | 0x0 (0 decimal)
			};
		};
		int16_t ZBuf; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm7::ObjectRef) == 0x4, "Invalid \"mm7::ObjectRef\" structure size");
	static_assert(offsetof(mm7::ObjectRef, ZBuf) == 2);



	struct FloatVector // size: 0xC
	{
		union
		{
			float x; // 0x0 (0 decimal)
			float _1; // 0x0 (0 decimal)
		};
		union
		{
			float y; // 0x4 (4 decimal)
			float _2; // 0x4 (4 decimal)
		};
		union
		{
			float z; // 0x8 (8 decimal)
			float _3; // 0x8 (8 decimal)
		};
	};
	static_assert(sizeof(mm7::FloatVector) == 0xC, "Invalid \"mm7::FloatVector\" structure size");
	static_assert(offsetof(mm7::FloatVector, y) == 4);
	static_assert(offsetof(mm7::FloatVector, _2) == 4);
	static_assert(offsetof(mm7::FloatVector, z) == 8);
	static_assert(offsetof(mm7::FloatVector, _3) == 8);



	struct SpellEffect; // 0-size struct, declaration only



	struct ObjectRef2 // size: 0x2
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type | 0x0 (0 decimal)
			uint16_t value; // 0x0 (0 decimal) | MMExt info: Raw value. In inventory screen this is item index, in other screens it equals !Lua[[Kind + Index*8]].
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | 0x0 (0 decimal)
			};
		};
	};
	static_assert(sizeof(mm7::ObjectRef2) == 0x2, "Invalid \"mm7::ObjectRef2\" structure size");



	struct SpellBuff // size: 0x10
	{
		int64_t expireTime; // 0x0 (0 decimal)
		int16_t power; // 0x8 (8 decimal)
		int16_t skill; // 0xA (10 decimal)
		int16_t overlayId; // 0xC (12 decimal)
		uint8_t caster; // 0xE (14 decimal)
		uint8_t bits; // 0xF (15 decimal)
	};
	static_assert(sizeof(mm7::SpellBuff) == 0x10, "Invalid \"mm7::SpellBuff\" structure size");
	static_assert(offsetof(mm7::SpellBuff, power) == 8);
	static_assert(offsetof(mm7::SpellBuff, skill) == 10);
	static_assert(offsetof(mm7::SpellBuff, overlayId) == 12);
	static_assert(offsetof(mm7::SpellBuff, caster) == 14);
	static_assert(offsetof(mm7::SpellBuff, bits) == 15);



	struct Item // size: 0x24
	{
		int32_t number; // 0x0 (0 decimal)
		int32_t bonus; // 0x4 (4 decimal) | MMExt info: From STDITEMS.TXT. You can use #const.Stats:#, just add 1 to a supported value from it.
		int32_t bonusStrength; // 0x8 (8 decimal)
		int32_t bonus2; // 0xC (12 decimal) | MMExt info: From SPCITEMS.TXT. Value in case of gold.
		int32_t charges; // 0x10 (16 decimal)
		union
		{
			int32_t condition; // 0x14 (20 decimal)
			struct
			{
				bool identified : 1; // 0x14 (20 decimal), bit index 7
				bool broken : 1; // 0x14 (20 decimal), bit index 6
				SKIPBITS(1);
				bool temporaryBonus : 1; // 0x14 (20 decimal), bit index 4
				SKIPBITS(4);
				bool stolen : 1; // 0x15 (21 decimal), bit index 7
				bool hardened : 1; // 0x15 (21 decimal), bit index 6
				bool refundable : 1; // 0x15 (21 decimal), bit index 5 | MMExt info: Added in patch v2.5.4. Used internally to remove artifacts generated in unopened chests from #ArtifactsFound:structs.GameParty.ArtifactsFound# upon map refill.
			};
		};
		int8_t bodyLocation; // 0x18 (24 decimal)
		uint8_t maxCharges; // 0x19 (25 decimal)
		int8_t owner; // 0x1A (26 decimal)
		SKIP(1);
		int64_t bonusExpireTime; // 0x1C (28 decimal)
		int __thiscall generateArtifact(); // address: 0x4505F8 | defaults: (this)
		int __thiscall getValue(); // address: 0x45646E | defaults: (this)
		char* __thiscall getName(); // address: 0x4564C5 | defaults: (this)
		char* __thiscall getIdentifiedName(); // address: 0x4564DF | defaults: (this)
	};
	static_assert(sizeof(mm7::Item) == 0x24, "Invalid \"mm7::Item\" structure size");
	static_assert(offsetof(mm7::Item, bonus) == 4);
	static_assert(offsetof(mm7::Item, bonusStrength) == 8);
	static_assert(offsetof(mm7::Item, bonus2) == 12);
	static_assert(offsetof(mm7::Item, charges) == 16);
	static_assert(offsetof(mm7::Item, condition) == 20);
	static_assert(offsetof(mm7::Item, bodyLocation) == 24);
	static_assert(offsetof(mm7::Item, maxCharges) == 25);
	static_assert(offsetof(mm7::Item, owner) == 26);
	static_assert(offsetof(mm7::Item, bonusExpireTime) == 28);
}
namespace mm8
{
	struct ObjectRef // size: 0x4
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type | 0x0 (0 decimal)
			uint16_t value; // 0x0 (0 decimal) | MMExt info: Raw value. In inventory screen this is item index, in other screens it equals !Lua[[Kind + Index*8]].
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | 0x0 (0 decimal)
			};
		};
		int16_t ZBuf; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::ObjectRef) == 0x4, "Invalid \"mm8::ObjectRef\" structure size");
	static_assert(offsetof(mm8::ObjectRef, ZBuf) == 2);



	struct FloatVector // size: 0xC
	{
		union
		{
			float x; // 0x0 (0 decimal)
			float _1; // 0x0 (0 decimal)
		};
		union
		{
			float y; // 0x4 (4 decimal)
			float _2; // 0x4 (4 decimal)
		};
		union
		{
			float z; // 0x8 (8 decimal)
			float _3; // 0x8 (8 decimal)
		};
	};
	static_assert(sizeof(mm8::FloatVector) == 0xC, "Invalid \"mm8::FloatVector\" structure size");
	static_assert(offsetof(mm8::FloatVector, y) == 4);
	static_assert(offsetof(mm8::FloatVector, _2) == 4);
	static_assert(offsetof(mm8::FloatVector, z) == 8);
	static_assert(offsetof(mm8::FloatVector, _3) == 8);



	struct SpellEffect; // 0-size struct, declaration only



	struct ObjectRef2 // size: 0x2
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type | 0x0 (0 decimal)
			uint16_t value; // 0x0 (0 decimal) | MMExt info: Raw value. In inventory screen this is item index, in other screens it equals !Lua[[Kind + Index*8]].
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | 0x0 (0 decimal)
			};
		};
	};
	static_assert(sizeof(mm8::ObjectRef2) == 0x2, "Invalid \"mm8::ObjectRef2\" structure size");



	struct SpellBuff // size: 0x10
	{
		int64_t expireTime; // 0x0 (0 decimal)
		int16_t power; // 0x8 (8 decimal)
		int16_t skill; // 0xA (10 decimal)
		int16_t overlayId; // 0xC (12 decimal)
		uint8_t caster; // 0xE (14 decimal)
		uint8_t bits; // 0xF (15 decimal)
	};
	static_assert(sizeof(mm8::SpellBuff) == 0x10, "Invalid \"mm8::SpellBuff\" structure size");
	static_assert(offsetof(mm8::SpellBuff, power) == 8);
	static_assert(offsetof(mm8::SpellBuff, skill) == 10);
	static_assert(offsetof(mm8::SpellBuff, overlayId) == 12);
	static_assert(offsetof(mm8::SpellBuff, caster) == 14);
	static_assert(offsetof(mm8::SpellBuff, bits) == 15);



	struct Item // size: 0x24
	{
		int32_t number; // 0x0 (0 decimal)
		int32_t bonus; // 0x4 (4 decimal) | MMExt info: From STDITEMS.TXT. You can use #const.Stats:#, just add 1 to a supported value from it.
		int32_t bonusStrength; // 0x8 (8 decimal)
		int32_t bonus2; // 0xC (12 decimal) | MMExt info: From SPCITEMS.TXT. Value in case of gold.
		int32_t charges; // 0x10 (16 decimal)
		union
		{
			int32_t condition; // 0x14 (20 decimal)
			struct
			{
				bool identified : 1; // 0x14 (20 decimal), bit index 7
				bool broken : 1; // 0x14 (20 decimal), bit index 6
				SKIPBITS(1);
				bool temporaryBonus : 1; // 0x14 (20 decimal), bit index 4
				SKIPBITS(4);
				bool stolen : 1; // 0x15 (21 decimal), bit index 7
				bool hardened : 1; // 0x15 (21 decimal), bit index 6
				bool refundable : 1; // 0x15 (21 decimal), bit index 5 | MMExt info: Added in patch v2.5.4. Used internally to remove artifacts generated in unopened chests from #ArtifactsFound:structs.GameParty.ArtifactsFound# upon map refill.
			};
		};
		int8_t bodyLocation; // 0x18 (24 decimal)
		uint8_t maxCharges; // 0x19 (25 decimal)
		int8_t owner; // 0x1A (26 decimal)
		SKIP(1);
		int64_t bonusExpireTime; // 0x1C (28 decimal)
		char* __thiscall getIdentifiedName(); // address: 0x453D58 | defaults: (this)
		char* __thiscall getName(); // address: 0x453D3E | defaults: (this)
		int __thiscall getValue(); // address: 0x453CE7 | defaults: (this)
		int __thiscall generateArtifact(); // address: 0x44DD43 | defaults: (this)
	};
	static_assert(sizeof(mm8::Item) == 0x24, "Invalid \"mm8::Item\" structure size");
	static_assert(offsetof(mm8::Item, bonus) == 4);
	static_assert(offsetof(mm8::Item, bonusStrength) == 8);
	static_assert(offsetof(mm8::Item, bonus2) == 12);
	static_assert(offsetof(mm8::Item, charges) == 16);
	static_assert(offsetof(mm8::Item, condition) == 20);
	static_assert(offsetof(mm8::Item, bodyLocation) == 24);
	static_assert(offsetof(mm8::Item, maxCharges) == 25);
	static_assert(offsetof(mm8::Item, owner) == 26);
	static_assert(offsetof(mm8::Item, bonusExpireTime) == 28);



	struct StartStat // size: 0x4
	{
		int8_t base; // 0x0 (0 decimal)
		int8_t max; // 0x1 (1 decimal)
		int8_t spend; // 0x2 (2 decimal) | MMExt info: how much you spend on it to add a point
		int8_t add; // 0x3 (3 decimal) | MMExt info: how much is added when you spend a point
	};
	static_assert(sizeof(mm8::StartStat) == 0x4, "Invalid \"mm8::StartStat\" structure size");
	static_assert(offsetof(mm8::StartStat, max) == 1);
	static_assert(offsetof(mm8::StartStat, spend) == 2);
	static_assert(offsetof(mm8::StartStat, add) == 3);
}

#pragma pack(pop)