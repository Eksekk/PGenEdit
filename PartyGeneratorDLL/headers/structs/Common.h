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
			std::array<uint8_t, 2> index; // Unknown type
			uint16_t value;
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
		int16_t ZBuf;
	};
	static_assert(sizeof(mm6::ObjectRef) == 0x4, "Invalid \"mm6::ObjectRef\" structure size");
	static_assert(offsetof(mm6::ObjectRef, ZBuf) == 2);



	struct ObjectRef2 // size: 0x2
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type
			uint16_t value;
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
	};
	static_assert(sizeof(mm6::ObjectRef2) == 0x2, "Invalid \"mm6::ObjectRef2\" structure size");



	struct Item // size: 0x1C
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
		int64_t expireTime;
		int16_t power;
		int16_t skill;
		int16_t overlayId;
		uint8_t caster;
		uint8_t bits;
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
	struct SpellEffect; // 0-size struct, declaration only



	struct FloatVector // size: 0xC
	{
		union
		{
			float _1;
			float x;
		};
		union
		{
			float y;
			float _2;
		};
		union
		{
			float z;
			float _3;
		};
	};
	static_assert(sizeof(mm7::FloatVector) == 0xC, "Invalid \"mm7::FloatVector\" structure size");
	static_assert(offsetof(mm7::FloatVector, y) == 4);
	static_assert(offsetof(mm7::FloatVector, _2) == 4);
	static_assert(offsetof(mm7::FloatVector, z) == 8);
	static_assert(offsetof(mm7::FloatVector, _3) == 8);



	struct SpellBuff // size: 0x10
	{
		int64_t expireTime;
		int16_t power;
		int16_t skill;
		int16_t overlayId;
		uint8_t caster;
		uint8_t bits;
	};
	static_assert(sizeof(mm7::SpellBuff) == 0x10, "Invalid \"mm7::SpellBuff\" structure size");
	static_assert(offsetof(mm7::SpellBuff, power) == 8);
	static_assert(offsetof(mm7::SpellBuff, skill) == 10);
	static_assert(offsetof(mm7::SpellBuff, overlayId) == 12);
	static_assert(offsetof(mm7::SpellBuff, caster) == 14);
	static_assert(offsetof(mm7::SpellBuff, bits) == 15);



	struct ObjectRef2 // size: 0x2
	{
		union
		{
			uint16_t value;
			std::array<uint8_t, 2> index; // Unknown type
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
	};
	static_assert(sizeof(mm7::ObjectRef2) == 0x2, "Invalid \"mm7::ObjectRef2\" structure size");



	struct StartStat // size: 0x4
	{
		int8_t base;
		int8_t max;
		int8_t spend;
		int8_t add;
	};
	static_assert(sizeof(mm7::StartStat) == 0x4, "Invalid \"mm7::StartStat\" structure size");
	static_assert(offsetof(mm7::StartStat, max) == 1);
	static_assert(offsetof(mm7::StartStat, spend) == 2);
	static_assert(offsetof(mm7::StartStat, add) == 3);



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



	struct ObjectRef // size: 0x4
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type
			uint16_t value;
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
		int16_t ZBuf;
	};
	static_assert(sizeof(mm7::ObjectRef) == 0x4, "Invalid \"mm7::ObjectRef\" structure size");
	static_assert(offsetof(mm7::ObjectRef, ZBuf) == 2);
}
namespace mm8
{
	struct SpellEffect; // 0-size struct, declaration only



	struct ObjectRef // size: 0x4
	{
		union
		{
			uint16_t value;
			std::array<uint8_t, 2> index; // Unknown type
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
		int16_t ZBuf;
	};
	static_assert(sizeof(mm8::ObjectRef) == 0x4, "Invalid \"mm8::ObjectRef\" structure size");
	static_assert(offsetof(mm8::ObjectRef, ZBuf) == 2);



	struct StartStat // size: 0x4
	{
		int8_t base;
		int8_t max;
		int8_t spend;
		int8_t add;
	};
	static_assert(sizeof(mm8::StartStat) == 0x4, "Invalid \"mm8::StartStat\" structure size");
	static_assert(offsetof(mm8::StartStat, max) == 1);
	static_assert(offsetof(mm8::StartStat, spend) == 2);
	static_assert(offsetof(mm8::StartStat, add) == 3);



	struct ObjectRef2 // size: 0x2
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type
			uint16_t value;
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
	};
	static_assert(sizeof(mm8::ObjectRef2) == 0x2, "Invalid \"mm8::ObjectRef2\" structure size");



	struct FloatVector // size: 0xC
	{
		union
		{
			float _1;
			float x;
		};
		union
		{
			float _2;
			float y;
		};
		union
		{
			float _3;
			float z;
		};
	};
	static_assert(sizeof(mm8::FloatVector) == 0xC, "Invalid \"mm8::FloatVector\" structure size");
	static_assert(offsetof(mm8::FloatVector, _2) == 4);
	static_assert(offsetof(mm8::FloatVector, y) == 4);
	static_assert(offsetof(mm8::FloatVector, _3) == 8);
	static_assert(offsetof(mm8::FloatVector, z) == 8);



	struct SpellBuff // size: 0x10
	{
		int64_t expireTime;
		int16_t power;
		int16_t skill;
		int16_t overlayId;
		uint8_t caster;
		uint8_t bits;
	};
	static_assert(sizeof(mm8::SpellBuff) == 0x10, "Invalid \"mm8::SpellBuff\" structure size");
	static_assert(offsetof(mm8::SpellBuff, power) == 8);
	static_assert(offsetof(mm8::SpellBuff, skill) == 10);
	static_assert(offsetof(mm8::SpellBuff, overlayId) == 12);
	static_assert(offsetof(mm8::SpellBuff, caster) == 14);
	static_assert(offsetof(mm8::SpellBuff, bits) == 15);



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
}

#pragma pack(pop)