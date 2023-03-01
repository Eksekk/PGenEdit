#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int16_t index;
		int16_t time;
		int16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm6::TFTItem) == 0x14, "Invalid \"mm6::TFTItem\" structure size");
	static_assert(offsetof(mm6::TFTItem, index) == 12);
	static_assert(offsetof(mm6::TFTItem, time) == 14);
	static_assert(offsetof(mm6::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm6::TFTItem, bits) == 18);



	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t bitmap;
		int16_t tileSet;
		int16_t section;
		union
		{
			uint16_t bits;
			struct
			{
				bool burn : 1;
				bool water : 1;
				bool block : 1;
				bool repulse : 1;
				bool flat : 1;
				bool wave : 1;
				bool noDraw : 1;
				SKIPBITS(1);
				bool waterTransition : 1;
				bool transition : 1;
				bool scrollDown : 1;
				bool scrollUp : 1;
				bool scrollLeft : 1;
				bool scrollRight : 1;
			};
		};
	};
	static_assert(sizeof(mm6::TileItem) == 0x1A, "Invalid \"mm6::TileItem\" structure size");
	static_assert(offsetof(mm6::TileItem, id) == 16);
	static_assert(offsetof(mm6::TileItem, bitmap) == 18);
	static_assert(offsetof(mm6::TileItem, tileSet) == 20);
	static_assert(offsetof(mm6::TileItem, section) == 22);
	static_assert(offsetof(mm6::TileItem, bits) == 24);



	struct SoundsItem // size: 0x70
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int32_t id;
		int32_t type;
		union
		{
			uint32_t bits;
			struct
			{
				bool locked : 1;
			};
		};
		std::array<uint32_t, 17> data;
	};
	static_assert(sizeof(mm6::SoundsItem) == 0x70, "Invalid \"mm6::SoundsItem\" structure size");
	static_assert(offsetof(mm6::SoundsItem, id) == 32);
	static_assert(offsetof(mm6::SoundsItem, type) == 36);
	static_assert(offsetof(mm6::SoundsItem, bits) == 40);
	static_assert(offsetof(mm6::SoundsItem, data) == 44);



	struct MonListItem // size: 0x94
	{
		int16_t height;
		int16_t radius;
		int16_t velocity;
		SKIP(2);
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				int16_t soundGetHit;
				int16_t soundFidget;
			};
		};
		std::array<char, 32> name; // fixed size string, requires null terminator
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator
				std::array<char, 10> framesStun; // fixed size string, requires null terminator
				std::array<char, 10> framesDie; // fixed size string, requires null terminator
				std::array<char, 10> framesDead; // fixed size string, requires null terminator
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator
			};
		};
	};
	static_assert(sizeof(mm6::MonListItem) == 0x94, "Invalid \"mm6::MonListItem\" structure size");
	static_assert(offsetof(mm6::MonListItem, radius) == 2);
	static_assert(offsetof(mm6::MonListItem, velocity) == 4);
	static_assert(offsetof(mm6::MonListItem, sounds) == 8);
	static_assert(offsetof(mm6::MonListItem, soundAttack) == 8);
	static_assert(offsetof(mm6::MonListItem, soundDie) == 10);
	static_assert(offsetof(mm6::MonListItem, soundGetHit) == 12);
	static_assert(offsetof(mm6::MonListItem, soundFidget) == 14);
	static_assert(offsetof(mm6::MonListItem, name) == 16);
	static_assert(offsetof(mm6::MonListItem, frameNames) == 48);
	static_assert(offsetof(mm6::MonListItem, framesStand) == 48);
	static_assert(offsetof(mm6::MonListItem, framesWalk) == 58);
	static_assert(offsetof(mm6::MonListItem, framesAttack) == 68);
	static_assert(offsetof(mm6::MonListItem, framesShoot) == 78);
	static_assert(offsetof(mm6::MonListItem, framesStun) == 88);
	static_assert(offsetof(mm6::MonListItem, framesDie) == 98);
	static_assert(offsetof(mm6::MonListItem, framesDead) == 108);
	static_assert(offsetof(mm6::MonListItem, framesFidget) == 118);



	struct ObjListItem // size: 0x34
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t radius;
		int16_t height;
		union
		{
			uint16_t bits;
			struct
			{
				bool invisible : 1;
				bool untouchable : 1;
				bool temporary : 1;
				bool lifetimeInSFT : 1;
				bool noPickup : 1;
				bool noGravity : 1;
				bool interceptAction : 1;
				bool bounce : 1;
				bool trailParticles : 1;
				bool trailFire : 1;
				bool trailLine : 1;
			};
		};
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type
			int16_t SFTIndex;
		};
		int16_t lifeTime;
		uint16_t loadedParticlesColor;
		uint16_t speed;
		union
		{
			std::array<uint8_t, 4> particlesColor;
			struct
			{
				uint8_t particleR;
				uint8_t particleG;
				uint8_t particleB;
			};
		};
	};
	static_assert(sizeof(mm6::ObjListItem) == 0x34, "Invalid \"mm6::ObjListItem\" structure size");
	static_assert(offsetof(mm6::ObjListItem, id) == 32);
	static_assert(offsetof(mm6::ObjListItem, radius) == 34);
	static_assert(offsetof(mm6::ObjListItem, height) == 36);
	static_assert(offsetof(mm6::ObjListItem, bits) == 38);
	static_assert(offsetof(mm6::ObjListItem, SFTGroup) == 40);
	static_assert(offsetof(mm6::ObjListItem, SFTIndex) == 40);
	static_assert(offsetof(mm6::ObjListItem, lifeTime) == 42);
	static_assert(offsetof(mm6::ObjListItem, loadedParticlesColor) == 44);
	static_assert(offsetof(mm6::ObjListItem, speed) == 46);
	static_assert(offsetof(mm6::ObjListItem, particlesColor) == 48);
	static_assert(offsetof(mm6::ObjListItem, particleR) == 48);
	static_assert(offsetof(mm6::ObjListItem, particleG) == 49);
	static_assert(offsetof(mm6::ObjListItem, particleB) == 50);



	struct OverlayItem // size: 0x8
	{
		int16_t id;
		int16_t type;
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		SKIP(2);
	};
	static_assert(sizeof(mm6::OverlayItem) == 0x8, "Invalid \"mm6::OverlayItem\" structure size");
	static_assert(offsetof(mm6::OverlayItem, type) == 2);
	static_assert(offsetof(mm6::OverlayItem, SFTIndex) == 4);
	static_assert(offsetof(mm6::OverlayItem, SFTGroup) == 4);



	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		uint8_t width;
		uint8_t height;
		int16_t imageIndex;
	};
	static_assert(sizeof(mm6::DChestItem) == 0x24, "Invalid \"mm6::DChestItem\" structure size");
	static_assert(offsetof(mm6::DChestItem, width) == 32);
	static_assert(offsetof(mm6::DChestItem, height) == 33);
	static_assert(offsetof(mm6::DChestItem, imageIndex) == 34);



	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> iconName; // fixed size string, requires null terminator
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
		uint16_t iconIndex;
	};
	static_assert(sizeof(mm6::IFTItem) == 0x20, "Invalid \"mm6::IFTItem\" structure size");
	static_assert(offsetof(mm6::IFTItem, iconName) == 12);
	static_assert(offsetof(mm6::IFTItem, time) == 24);
	static_assert(offsetof(mm6::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm6::IFTItem, bits) == 28);
	static_assert(offsetof(mm6::IFTItem, iconIndex) == 30);



	struct PFTItem // size: 0xA
	{
		uint16_t groupId;
		uint16_t frameIndex;
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm6::PFTItem) == 0xA, "Invalid \"mm6::PFTItem\" structure size");
	static_assert(offsetof(mm6::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm6::PFTItem, time) == 4);
	static_assert(offsetof(mm6::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm6::PFTItem, bits) == 8);



	struct DecListItem // size: 0x50
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> gameName; // fixed size string, requires null terminator
		int16_t type;
		int16_t height;
		int16_t radius;
		int16_t lightRadius;
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type
			int16_t SFTIndex;
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool noBlockMovement : 1;
				bool noDraw : 1;
				bool flickerSlow : 1;
				bool flickerMedium : 1;
				bool flickerFast : 1;
				bool marker : 1;
				bool slowLoop : 1;
				bool emitFire : 1;
				bool soundOnDawn : 1;
				bool soundOnDusk : 1;
				bool emitSmoke : 1;
			};
		};
		int16_t soundId;
		SKIP(2);
	};
	static_assert(sizeof(mm6::DecListItem) == 0x50, "Invalid \"mm6::DecListItem\" structure size");
	static_assert(offsetof(mm6::DecListItem, gameName) == 32);
	static_assert(offsetof(mm6::DecListItem, type) == 64);
	static_assert(offsetof(mm6::DecListItem, height) == 66);
	static_assert(offsetof(mm6::DecListItem, radius) == 68);
	static_assert(offsetof(mm6::DecListItem, lightRadius) == 70);
	static_assert(offsetof(mm6::DecListItem, SFTGroup) == 72);
	static_assert(offsetof(mm6::DecListItem, SFTIndex) == 72);
	static_assert(offsetof(mm6::DecListItem, bits) == 74);
	static_assert(offsetof(mm6::DecListItem, soundId) == 76);



	struct SFTItem // size: 0x38
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> spriteName; // fixed size string, requires null terminator
		std::array<int16_t, 8> spriteIndex;
		int32_t scale;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool luminous : 1;
				bool groupStart : 1;
				SKIPBITS(1);
				bool image1 : 1;
				bool center : 1;
				bool fidget : 1;
				bool loaded : 1;
				bool mirror0 : 1;
				bool mirror1 : 1;
				bool mirror2 : 1;
				bool mirror3 : 1;
				bool mirror4 : 1;
				bool mirror5 : 1;
				bool mirror6 : 1;
				bool mirror7 : 1;
			};
		};
		int16_t lightRadius;
		int16_t paletteId;
		int16_t paletteIndex;
		int16_t time;
		int16_t totalTime;
	};
	static_assert(sizeof(mm6::SFTItem) == 0x38, "Invalid \"mm6::SFTItem\" structure size");
	static_assert(offsetof(mm6::SFTItem, spriteName) == 12);
	static_assert(offsetof(mm6::SFTItem, spriteIndex) == 24);
	static_assert(offsetof(mm6::SFTItem, scale) == 40);
	static_assert(offsetof(mm6::SFTItem, bits) == 44);
	static_assert(offsetof(mm6::SFTItem, lightRadius) == 46);
	static_assert(offsetof(mm6::SFTItem, paletteId) == 48);
	static_assert(offsetof(mm6::SFTItem, paletteIndex) == 50);
	static_assert(offsetof(mm6::SFTItem, time) == 52);
	static_assert(offsetof(mm6::SFTItem, totalTime) == 54);



	struct SFT // size: 0x18
	{
		uint32_t frames_size;
		union
		{
			uint32_t groupIndex_size;
			uint32_t groups_size;
		};
		int32_t matchIndex;
		mm6::SFTItem* frames; // size field offset is 0x0
		mm6::SFTItem** groups; // size field offset is 0x4
		int16_t* groupIndex; // size field offset is 0x4
	};
	static_assert(sizeof(mm6::SFT) == 0x18, "Invalid \"mm6::SFT\" structure size");
	static_assert(offsetof(mm6::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm6::SFT, groups_size) == 4);
	static_assert(offsetof(mm6::SFT, matchIndex) == 8);
	static_assert(offsetof(mm6::SFT, frames) == 12);
	static_assert(offsetof(mm6::SFT, groups) == 16);
	static_assert(offsetof(mm6::SFT, groupIndex) == 20);
}
namespace mm7
{
	struct SFTItem // size: 0x3C
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> spriteName; // fixed size string, requires null terminator
		std::array<int16_t, 8> spriteIndex;
		int32_t scale;
		union
		{
			uint32_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool luminous : 1;
				bool groupStart : 1;
				SKIPBITS(1);
				bool image1 : 1;
				bool center : 1;
				bool fidget : 1;
				bool loaded : 1;
				bool mirror0 : 1;
				bool mirror1 : 1;
				bool mirror2 : 1;
				bool mirror3 : 1;
				bool mirror4 : 1;
				bool mirror5 : 1;
				bool mirror6 : 1;
				bool mirror7 : 1;
				bool images3 : 1;
				bool glow : 1;
				bool transparent : 1;
			};
		};
		int16_t lightRadius;
		int16_t paletteId;
		int16_t paletteIndex;
		int16_t time;
		int16_t totalTime;
		SKIP(2);
	};
	static_assert(sizeof(mm7::SFTItem) == 0x3C, "Invalid \"mm7::SFTItem\" structure size");
	static_assert(offsetof(mm7::SFTItem, spriteName) == 12);
	static_assert(offsetof(mm7::SFTItem, spriteIndex) == 24);
	static_assert(offsetof(mm7::SFTItem, scale) == 40);
	static_assert(offsetof(mm7::SFTItem, bits) == 44);
	static_assert(offsetof(mm7::SFTItem, lightRadius) == 48);
	static_assert(offsetof(mm7::SFTItem, paletteId) == 50);
	static_assert(offsetof(mm7::SFTItem, paletteIndex) == 52);
	static_assert(offsetof(mm7::SFTItem, time) == 54);
	static_assert(offsetof(mm7::SFTItem, totalTime) == 56);



	struct SFT // size: 0x18
	{
		uint32_t frames_size;
		union
		{
			uint32_t groupIndex_size;
			uint32_t groups_size;
		};
		int32_t matchIndex;
		mm7::SFTItem* frames; // size field offset is 0x0
		mm7::SFTItem** groups; // size field offset is 0x4
		int16_t* groupIndex; // size field offset is 0x4
	};
	static_assert(sizeof(mm7::SFT) == 0x18, "Invalid \"mm7::SFT\" structure size");
	static_assert(offsetof(mm7::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm7::SFT, groups_size) == 4);
	static_assert(offsetof(mm7::SFT, matchIndex) == 8);
	static_assert(offsetof(mm7::SFT, frames) == 12);
	static_assert(offsetof(mm7::SFT, groups) == 16);
	static_assert(offsetof(mm7::SFT, groupIndex) == 20);



	struct OverlayItem // size: 0x8
	{
		int16_t id;
		int16_t type;
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type
			int16_t SFTIndex;
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::OverlayItem) == 0x8, "Invalid \"mm7::OverlayItem\" structure size");
	static_assert(offsetof(mm7::OverlayItem, type) == 2);
	static_assert(offsetof(mm7::OverlayItem, SFTGroup) == 4);
	static_assert(offsetof(mm7::OverlayItem, SFTIndex) == 4);



	struct SoundsItem // size: 0x78
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int32_t id;
		int32_t type;
		union
		{
			uint32_t bits;
			struct
			{
				bool locked : 1;
				bool is3D : 1;
			};
		};
		std::array<uint32_t, 17> data;
		uint32_t data3D;
		uint32_t decompressed; // 4-byte boolean
	};
	static_assert(sizeof(mm7::SoundsItem) == 0x78, "Invalid \"mm7::SoundsItem\" structure size");
	static_assert(offsetof(mm7::SoundsItem, id) == 32);
	static_assert(offsetof(mm7::SoundsItem, type) == 36);
	static_assert(offsetof(mm7::SoundsItem, bits) == 40);
	static_assert(offsetof(mm7::SoundsItem, data) == 44);
	static_assert(offsetof(mm7::SoundsItem, data3D) == 112);
	static_assert(offsetof(mm7::SoundsItem, decompressed) == 116);



	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t bitmap;
		int16_t tileSet;
		int16_t section;
		union
		{
			uint16_t bits;
			struct
			{
				bool burn : 1;
				bool water : 1;
				bool block : 1;
				bool repulse : 1;
				bool flat : 1;
				bool wave : 1;
				bool noDraw : 1;
				SKIPBITS(1);
				bool waterTransition : 1;
				bool transition : 1;
				bool scrollDown : 1;
				bool scrollUp : 1;
				bool scrollLeft : 1;
				bool scrollRight : 1;
			};
		};
	};
	static_assert(sizeof(mm7::TileItem) == 0x1A, "Invalid \"mm7::TileItem\" structure size");
	static_assert(offsetof(mm7::TileItem, id) == 16);
	static_assert(offsetof(mm7::TileItem, bitmap) == 18);
	static_assert(offsetof(mm7::TileItem, tileSet) == 20);
	static_assert(offsetof(mm7::TileItem, section) == 22);
	static_assert(offsetof(mm7::TileItem, bits) == 24);



	struct MonListItem // size: 0x98
	{
		int16_t height;
		int16_t radius;
		int16_t velocity;
		int16_t radius2;
		union
		{
			int32_t tint;
			struct
			{
				uint8_t tintB;
				uint8_t tintG;
				uint8_t tintR;
				uint8_t tintA;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				int16_t soundGetHit;
				int16_t soundFidget;
			};
		};
		std::array<char, 32> name; // fixed size string, requires null terminator
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator
				std::array<char, 10> framesStun; // fixed size string, requires null terminator
				std::array<char, 10> framesDie; // fixed size string, requires null terminator
				std::array<char, 10> framesDead; // fixed size string, requires null terminator
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator
			};
		};
	};
	static_assert(sizeof(mm7::MonListItem) == 0x98, "Invalid \"mm7::MonListItem\" structure size");
	static_assert(offsetof(mm7::MonListItem, radius) == 2);
	static_assert(offsetof(mm7::MonListItem, velocity) == 4);
	static_assert(offsetof(mm7::MonListItem, radius2) == 6);
	static_assert(offsetof(mm7::MonListItem, tint) == 8);
	static_assert(offsetof(mm7::MonListItem, tintB) == 8);
	static_assert(offsetof(mm7::MonListItem, tintG) == 9);
	static_assert(offsetof(mm7::MonListItem, tintR) == 10);
	static_assert(offsetof(mm7::MonListItem, tintA) == 11);
	static_assert(offsetof(mm7::MonListItem, sounds) == 12);
	static_assert(offsetof(mm7::MonListItem, soundAttack) == 12);
	static_assert(offsetof(mm7::MonListItem, soundDie) == 14);
	static_assert(offsetof(mm7::MonListItem, soundGetHit) == 16);
	static_assert(offsetof(mm7::MonListItem, soundFidget) == 18);
	static_assert(offsetof(mm7::MonListItem, name) == 20);
	static_assert(offsetof(mm7::MonListItem, frameNames) == 52);
	static_assert(offsetof(mm7::MonListItem, framesStand) == 52);
	static_assert(offsetof(mm7::MonListItem, framesWalk) == 62);
	static_assert(offsetof(mm7::MonListItem, framesAttack) == 72);
	static_assert(offsetof(mm7::MonListItem, framesShoot) == 82);
	static_assert(offsetof(mm7::MonListItem, framesStun) == 92);
	static_assert(offsetof(mm7::MonListItem, framesDie) == 102);
	static_assert(offsetof(mm7::MonListItem, framesDead) == 112);
	static_assert(offsetof(mm7::MonListItem, framesFidget) == 122);



	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		uint8_t width;
		uint8_t height;
		int16_t imageIndex;
	};
	static_assert(sizeof(mm7::DChestItem) == 0x24, "Invalid \"mm7::DChestItem\" structure size");
	static_assert(offsetof(mm7::DChestItem, width) == 32);
	static_assert(offsetof(mm7::DChestItem, height) == 33);
	static_assert(offsetof(mm7::DChestItem, imageIndex) == 34);



	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int16_t index;
		int16_t time;
		int16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm7::TFTItem) == 0x14, "Invalid \"mm7::TFTItem\" structure size");
	static_assert(offsetof(mm7::TFTItem, index) == 12);
	static_assert(offsetof(mm7::TFTItem, time) == 14);
	static_assert(offsetof(mm7::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm7::TFTItem, bits) == 18);



	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> iconName; // fixed size string, requires null terminator
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
		uint16_t iconIndex;
	};
	static_assert(sizeof(mm7::IFTItem) == 0x20, "Invalid \"mm7::IFTItem\" structure size");
	static_assert(offsetof(mm7::IFTItem, iconName) == 12);
	static_assert(offsetof(mm7::IFTItem, time) == 24);
	static_assert(offsetof(mm7::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm7::IFTItem, bits) == 28);
	static_assert(offsetof(mm7::IFTItem, iconIndex) == 30);



	struct PFTItem // size: 0xA
	{
		uint16_t groupId;
		uint16_t frameIndex;
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm7::PFTItem) == 0xA, "Invalid \"mm7::PFTItem\" structure size");
	static_assert(offsetof(mm7::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm7::PFTItem, time) == 4);
	static_assert(offsetof(mm7::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm7::PFTItem, bits) == 8);



	struct DecListItem // size: 0x54
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> gameName; // fixed size string, requires null terminator
		int16_t type;
		int16_t height;
		int16_t radius;
		int16_t lightRadius;
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool noBlockMovement : 1;
				bool noDraw : 1;
				bool flickerSlow : 1;
				bool flickerMedium : 1;
				bool flickerFast : 1;
				bool marker : 1;
				bool slowLoop : 1;
				bool emitFire : 1;
				bool soundOnDawn : 1;
				bool soundOnDusk : 1;
				bool emitSmoke : 1;
			};
		};
		int16_t soundId;
		SKIP(2);
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		SKIP(1);
	};
	static_assert(sizeof(mm7::DecListItem) == 0x54, "Invalid \"mm7::DecListItem\" structure size");
	static_assert(offsetof(mm7::DecListItem, gameName) == 32);
	static_assert(offsetof(mm7::DecListItem, type) == 64);
	static_assert(offsetof(mm7::DecListItem, height) == 66);
	static_assert(offsetof(mm7::DecListItem, radius) == 68);
	static_assert(offsetof(mm7::DecListItem, lightRadius) == 70);
	static_assert(offsetof(mm7::DecListItem, SFTIndex) == 72);
	static_assert(offsetof(mm7::DecListItem, SFTGroup) == 72);
	static_assert(offsetof(mm7::DecListItem, bits) == 74);
	static_assert(offsetof(mm7::DecListItem, soundId) == 76);
	static_assert(offsetof(mm7::DecListItem, red) == 80);
	static_assert(offsetof(mm7::DecListItem, green) == 81);
	static_assert(offsetof(mm7::DecListItem, blue) == 82);



	struct ObjListItem // size: 0x38
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t radius;
		int16_t height;
		union
		{
			uint16_t bits;
			struct
			{
				bool invisible : 1;
				bool untouchable : 1;
				bool temporary : 1;
				bool lifetimeInSFT : 1;
				bool noPickup : 1;
				bool noGravity : 1;
				bool interceptAction : 1;
				bool bounce : 1;
				bool trailParticles : 1;
				bool trailFire : 1;
				bool trailLine : 1;
			};
		};
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		int16_t lifeTime;
		uint32_t loadedParticlesColor;
		uint16_t speed;
		union
		{
			std::array<uint8_t, 4> particlesColor;
			struct
			{
				uint8_t particleR;
				uint8_t particleG;
				uint8_t particleB;
				uint8_t particleA;
			};
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::ObjListItem) == 0x38, "Invalid \"mm7::ObjListItem\" structure size");
	static_assert(offsetof(mm7::ObjListItem, id) == 32);
	static_assert(offsetof(mm7::ObjListItem, radius) == 34);
	static_assert(offsetof(mm7::ObjListItem, height) == 36);
	static_assert(offsetof(mm7::ObjListItem, bits) == 38);
	static_assert(offsetof(mm7::ObjListItem, SFTIndex) == 40);
	static_assert(offsetof(mm7::ObjListItem, SFTGroup) == 40);
	static_assert(offsetof(mm7::ObjListItem, lifeTime) == 42);
	static_assert(offsetof(mm7::ObjListItem, loadedParticlesColor) == 44);
	static_assert(offsetof(mm7::ObjListItem, speed) == 48);
	static_assert(offsetof(mm7::ObjListItem, particlesColor) == 50);
	static_assert(offsetof(mm7::ObjListItem, particleR) == 50);
	static_assert(offsetof(mm7::ObjListItem, particleG) == 51);
	static_assert(offsetof(mm7::ObjListItem, particleB) == 52);
	static_assert(offsetof(mm7::ObjListItem, particleA) == 53);
}
namespace mm8
{
	struct PFTItem // size: 0xA
	{
		uint16_t groupId;
		uint16_t frameIndex;
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm8::PFTItem) == 0xA, "Invalid \"mm8::PFTItem\" structure size");
	static_assert(offsetof(mm8::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm8::PFTItem, time) == 4);
	static_assert(offsetof(mm8::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm8::PFTItem, bits) == 8);



	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> iconName; // fixed size string, requires null terminator
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
		uint16_t iconIndex;
	};
	static_assert(sizeof(mm8::IFTItem) == 0x20, "Invalid \"mm8::IFTItem\" structure size");
	static_assert(offsetof(mm8::IFTItem, iconName) == 12);
	static_assert(offsetof(mm8::IFTItem, time) == 24);
	static_assert(offsetof(mm8::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm8::IFTItem, bits) == 28);
	static_assert(offsetof(mm8::IFTItem, iconIndex) == 30);



	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int16_t index;
		int16_t time;
		int16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm8::TFTItem) == 0x14, "Invalid \"mm8::TFTItem\" structure size");
	static_assert(offsetof(mm8::TFTItem, index) == 12);
	static_assert(offsetof(mm8::TFTItem, time) == 14);
	static_assert(offsetof(mm8::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm8::TFTItem, bits) == 18);



	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		uint8_t width;
		uint8_t height;
		int16_t imageIndex;
	};
	static_assert(sizeof(mm8::DChestItem) == 0x24, "Invalid \"mm8::DChestItem\" structure size");
	static_assert(offsetof(mm8::DChestItem, width) == 32);
	static_assert(offsetof(mm8::DChestItem, height) == 33);
	static_assert(offsetof(mm8::DChestItem, imageIndex) == 34);



	struct OverlayItem // size: 0x8
	{
		int16_t id;
		int16_t type;
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::OverlayItem) == 0x8, "Invalid \"mm8::OverlayItem\" structure size");
	static_assert(offsetof(mm8::OverlayItem, type) == 2);
	static_assert(offsetof(mm8::OverlayItem, SFTIndex) == 4);
	static_assert(offsetof(mm8::OverlayItem, SFTGroup) == 4);



	struct SoundsItem // size: 0x98
	{
		std::array<char, 64> name; // fixed size string, requires null terminator
		int32_t id;
		int32_t type;
		union
		{
			uint32_t bits;
			struct
			{
				bool locked : 1;
				bool is3D : 1;
			};
		};
		std::array<uint32_t, 17> data;
		uint32_t data3D;
		uint32_t decompressed; // 4-byte boolean
	};
	static_assert(sizeof(mm8::SoundsItem) == 0x98, "Invalid \"mm8::SoundsItem\" structure size");
	static_assert(offsetof(mm8::SoundsItem, id) == 64);
	static_assert(offsetof(mm8::SoundsItem, type) == 68);
	static_assert(offsetof(mm8::SoundsItem, bits) == 72);
	static_assert(offsetof(mm8::SoundsItem, data) == 76);
	static_assert(offsetof(mm8::SoundsItem, data3D) == 144);
	static_assert(offsetof(mm8::SoundsItem, decompressed) == 148);



	struct MonListItem // size: 0xB8
	{
		int16_t height;
		int16_t radius;
		int16_t velocity;
		int16_t radius2;
		union
		{
			int32_t tint;
			struct
			{
				uint8_t tintB;
				uint8_t tintG;
				uint8_t tintR;
				uint8_t tintA;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				int16_t soundGetHit;
				int16_t soundFidget;
			};
		};
		std::array<char, 64> name; // fixed size string, requires null terminator
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator
				std::array<char, 10> framesStun; // fixed size string, requires null terminator
				std::array<char, 10> framesDie; // fixed size string, requires null terminator
				std::array<char, 10> framesDead; // fixed size string, requires null terminator
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator
			};
		};
	};
	static_assert(sizeof(mm8::MonListItem) == 0xB8, "Invalid \"mm8::MonListItem\" structure size");
	static_assert(offsetof(mm8::MonListItem, radius) == 2);
	static_assert(offsetof(mm8::MonListItem, velocity) == 4);
	static_assert(offsetof(mm8::MonListItem, radius2) == 6);
	static_assert(offsetof(mm8::MonListItem, tint) == 8);
	static_assert(offsetof(mm8::MonListItem, tintB) == 8);
	static_assert(offsetof(mm8::MonListItem, tintG) == 9);
	static_assert(offsetof(mm8::MonListItem, tintR) == 10);
	static_assert(offsetof(mm8::MonListItem, tintA) == 11);
	static_assert(offsetof(mm8::MonListItem, sounds) == 12);
	static_assert(offsetof(mm8::MonListItem, soundAttack) == 12);
	static_assert(offsetof(mm8::MonListItem, soundDie) == 14);
	static_assert(offsetof(mm8::MonListItem, soundGetHit) == 16);
	static_assert(offsetof(mm8::MonListItem, soundFidget) == 18);
	static_assert(offsetof(mm8::MonListItem, name) == 20);
	static_assert(offsetof(mm8::MonListItem, frameNames) == 84);
	static_assert(offsetof(mm8::MonListItem, framesStand) == 84);
	static_assert(offsetof(mm8::MonListItem, framesWalk) == 94);
	static_assert(offsetof(mm8::MonListItem, framesAttack) == 104);
	static_assert(offsetof(mm8::MonListItem, framesShoot) == 114);
	static_assert(offsetof(mm8::MonListItem, framesStun) == 124);
	static_assert(offsetof(mm8::MonListItem, framesDie) == 134);
	static_assert(offsetof(mm8::MonListItem, framesDead) == 144);
	static_assert(offsetof(mm8::MonListItem, framesFidget) == 154);



	struct ObjListItem // size: 0x38
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t radius;
		int16_t height;
		union
		{
			uint16_t bits;
			struct
			{
				bool invisible : 1;
				bool untouchable : 1;
				bool temporary : 1;
				bool lifetimeInSFT : 1;
				bool noPickup : 1;
				bool noGravity : 1;
				bool interceptAction : 1;
				bool bounce : 1;
				bool trailParticles : 1;
				bool trailFire : 1;
				bool trailLine : 1;
			};
		};
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		int16_t lifeTime;
		uint32_t loadedParticlesColor;
		uint16_t speed;
		union
		{
			std::array<uint8_t, 4> particlesColor;
			struct
			{
				uint8_t particleR;
				uint8_t particleG;
				uint8_t particleB;
				uint8_t particleA;
			};
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::ObjListItem) == 0x38, "Invalid \"mm8::ObjListItem\" structure size");
	static_assert(offsetof(mm8::ObjListItem, id) == 32);
	static_assert(offsetof(mm8::ObjListItem, radius) == 34);
	static_assert(offsetof(mm8::ObjListItem, height) == 36);
	static_assert(offsetof(mm8::ObjListItem, bits) == 38);
	static_assert(offsetof(mm8::ObjListItem, SFTIndex) == 40);
	static_assert(offsetof(mm8::ObjListItem, SFTGroup) == 40);
	static_assert(offsetof(mm8::ObjListItem, lifeTime) == 42);
	static_assert(offsetof(mm8::ObjListItem, loadedParticlesColor) == 44);
	static_assert(offsetof(mm8::ObjListItem, speed) == 48);
	static_assert(offsetof(mm8::ObjListItem, particlesColor) == 50);
	static_assert(offsetof(mm8::ObjListItem, particleR) == 50);
	static_assert(offsetof(mm8::ObjListItem, particleG) == 51);
	static_assert(offsetof(mm8::ObjListItem, particleB) == 52);
	static_assert(offsetof(mm8::ObjListItem, particleA) == 53);



	struct SFTItem // size: 0x3C
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> spriteName; // fixed size string, requires null terminator
		std::array<int16_t, 8> spriteIndex;
		int32_t scale;
		union
		{
			uint32_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool luminous : 1;
				bool groupStart : 1;
				SKIPBITS(1);
				bool image1 : 1;
				bool center : 1;
				bool fidget : 1;
				bool loaded : 1;
				bool mirror0 : 1;
				bool mirror1 : 1;
				bool mirror2 : 1;
				bool mirror3 : 1;
				bool mirror4 : 1;
				bool mirror5 : 1;
				bool mirror6 : 1;
				bool mirror7 : 1;
				bool images3 : 1;
				bool glow : 1;
				bool transparent : 1;
			};
		};
		int16_t lightRadius;
		int16_t paletteId;
		int16_t paletteIndex;
		int16_t time;
		int16_t totalTime;
		SKIP(2);
	};
	static_assert(sizeof(mm8::SFTItem) == 0x3C, "Invalid \"mm8::SFTItem\" structure size");
	static_assert(offsetof(mm8::SFTItem, spriteName) == 12);
	static_assert(offsetof(mm8::SFTItem, spriteIndex) == 24);
	static_assert(offsetof(mm8::SFTItem, scale) == 40);
	static_assert(offsetof(mm8::SFTItem, bits) == 44);
	static_assert(offsetof(mm8::SFTItem, lightRadius) == 48);
	static_assert(offsetof(mm8::SFTItem, paletteId) == 50);
	static_assert(offsetof(mm8::SFTItem, paletteIndex) == 52);
	static_assert(offsetof(mm8::SFTItem, time) == 54);
	static_assert(offsetof(mm8::SFTItem, totalTime) == 56);



	struct SFT // size: 0x18
	{
		uint32_t frames_size;
		union
		{
			uint32_t groups_size;
			uint32_t groupIndex_size;
		};
		int32_t matchIndex;
		mm8::SFTItem* frames; // size field offset is 0x0
		mm8::SFTItem** groups; // size field offset is 0x4
		int16_t* groupIndex; // size field offset is 0x4
	};
	static_assert(sizeof(mm8::SFT) == 0x18, "Invalid \"mm8::SFT\" structure size");
	static_assert(offsetof(mm8::SFT, groups_size) == 4);
	static_assert(offsetof(mm8::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm8::SFT, matchIndex) == 8);
	static_assert(offsetof(mm8::SFT, frames) == 12);
	static_assert(offsetof(mm8::SFT, groups) == 16);
	static_assert(offsetof(mm8::SFT, groupIndex) == 20);



	struct DecListItem // size: 0x54
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> gameName; // fixed size string, requires null terminator
		int16_t type;
		int16_t height;
		int16_t radius;
		int16_t lightRadius;
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool noBlockMovement : 1;
				bool noDraw : 1;
				bool flickerSlow : 1;
				bool flickerMedium : 1;
				bool flickerFast : 1;
				bool marker : 1;
				bool slowLoop : 1;
				bool emitFire : 1;
				bool soundOnDawn : 1;
				bool soundOnDusk : 1;
				bool emitSmoke : 1;
			};
		};
		int16_t soundId;
		SKIP(2);
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		SKIP(1);
	};
	static_assert(sizeof(mm8::DecListItem) == 0x54, "Invalid \"mm8::DecListItem\" structure size");
	static_assert(offsetof(mm8::DecListItem, gameName) == 32);
	static_assert(offsetof(mm8::DecListItem, type) == 64);
	static_assert(offsetof(mm8::DecListItem, height) == 66);
	static_assert(offsetof(mm8::DecListItem, radius) == 68);
	static_assert(offsetof(mm8::DecListItem, lightRadius) == 70);
	static_assert(offsetof(mm8::DecListItem, SFTIndex) == 72);
	static_assert(offsetof(mm8::DecListItem, SFTGroup) == 72);
	static_assert(offsetof(mm8::DecListItem, bits) == 74);
	static_assert(offsetof(mm8::DecListItem, soundId) == 76);
	static_assert(offsetof(mm8::DecListItem, red) == 80);
	static_assert(offsetof(mm8::DecListItem, green) == 81);
	static_assert(offsetof(mm8::DecListItem, blue) == 82);



	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t bitmap;
		int16_t tileSet;
		int16_t section;
		union
		{
			uint16_t bits;
			struct
			{
				bool burn : 1;
				bool water : 1;
				bool block : 1;
				bool repulse : 1;
				bool flat : 1;
				bool wave : 1;
				bool noDraw : 1;
				SKIPBITS(1);
				bool waterTransition : 1;
				bool transition : 1;
				bool scrollDown : 1;
				bool scrollUp : 1;
				bool scrollLeft : 1;
				bool scrollRight : 1;
			};
		};
	};
	static_assert(sizeof(mm8::TileItem) == 0x1A, "Invalid \"mm8::TileItem\" structure size");
	static_assert(offsetof(mm8::TileItem, id) == 16);
	static_assert(offsetof(mm8::TileItem, bitmap) == 18);
	static_assert(offsetof(mm8::TileItem, tileSet) == 20);
	static_assert(offsetof(mm8::TileItem, section) == 22);
	static_assert(offsetof(mm8::TileItem, bits) == 24);



	struct CurrentTileBin // size: 0x8
	{
		uint32_t items_size;
		mm8::TileItem* items; // size field offset is 0x0
	};
	static_assert(sizeof(mm8::CurrentTileBin) == 0x8, "Invalid \"mm8::CurrentTileBin\" structure size");
	static_assert(offsetof(mm8::CurrentTileBin, items) == 4);
}

#pragma pack(pop)