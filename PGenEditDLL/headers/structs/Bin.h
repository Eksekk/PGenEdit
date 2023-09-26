#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int16_t id; // 0x10 (16 decimal)
		int16_t bitmap; // 0x12 (18 decimal)
		int16_t tileSet; // 0x14 (20 decimal)
		int16_t section; // 0x16 (22 decimal)
		union
		{
			uint16_t bits; // 0x18 (24 decimal)
			struct
			{
				bool burn : 1; // 0x18 (24 decimal), bit index 7
				bool water : 1; // 0x18 (24 decimal), bit index 6
				bool block : 1; // 0x18 (24 decimal), bit index 5
				bool repulse : 1; // 0x18 (24 decimal), bit index 4
				bool flat : 1; // 0x18 (24 decimal), bit index 3
				bool wave : 1; // 0x18 (24 decimal), bit index 2
				bool noDraw : 1; // 0x18 (24 decimal), bit index 1
				SKIPBITS(1);
				bool waterTransition : 1; // 0x19 (25 decimal), bit index 7
				bool transition : 1; // 0x19 (25 decimal), bit index 6
				bool scrollDown : 1; // 0x19 (25 decimal), bit index 5
				bool scrollUp : 1; // 0x19 (25 decimal), bit index 4
				bool scrollLeft : 1; // 0x19 (25 decimal), bit index 3
				bool scrollRight : 1; // 0x19 (25 decimal), bit index 2
			};
		};
	};
	static_assert(sizeof(mm6::TileItem) == 0x1A, "Invalid \"mm6::TileItem\" structure size");
	static_assert(offsetof(mm6::TileItem, id) == 16);
	static_assert(offsetof(mm6::TileItem, bitmap) == 18);
	static_assert(offsetof(mm6::TileItem, tileSet) == 20);
	static_assert(offsetof(mm6::TileItem, section) == 22);
	static_assert(offsetof(mm6::TileItem, bits) == 24);



	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: texture name
		int16_t index; // 0xC (12 decimal) | MMExt info: index in bitmaps.lod
		int16_t time; // 0xE (14 decimal) | MMExt info: time for this frame in 1/32 of a second
		int16_t totalTime; // 0x10 (16 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x12 (18 decimal), bit index 7
				bool groupStart : 1; // 0x12 (18 decimal), bit index 6
			};
		};
	};
	static_assert(sizeof(mm6::TFTItem) == 0x14, "Invalid \"mm6::TFTItem\" structure size");
	static_assert(offsetof(mm6::TFTItem, index) == 12);
	static_assert(offsetof(mm6::TFTItem, time) == 14);
	static_assert(offsetof(mm6::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm6::TFTItem, bits) == 18);



	struct SoundsItem // size: 0x70
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: name of sound file
		int32_t id; // 0x20 (32 decimal)
		// MMExt info: type of sound
		// 0 = (0)      level specific sound, load during level initialization
		// 1 = (system) system sound, always loaded
		// 2 = (swap)   level specific sound, that gets loaded and flushed
		// 3 = (?)
		// 4 = (lock)   delete sound only when game ends
		int32_t type; // 0x24 (36 decimal)
		union
		{
			uint32_t bits; // 0x28 (40 decimal)
			struct
			{
				bool locked : 1; // 0x28 (40 decimal), bit index 7
			};
		};
		std::array<uint32_t, 17> data; // 0x2C (44 decimal) | MMExt info: data pointer
	};
	static_assert(sizeof(mm6::SoundsItem) == 0x70, "Invalid \"mm6::SoundsItem\" structure size");
	static_assert(offsetof(mm6::SoundsItem, id) == 32);
	static_assert(offsetof(mm6::SoundsItem, type) == 36);
	static_assert(offsetof(mm6::SoundsItem, bits) == 40);
	static_assert(offsetof(mm6::SoundsItem, data) == 44);



	struct SFTItem // size: 0x38
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 12> spriteName; // fixed size string, requires null terminator | 0xC (12 decimal)
		std::array<int16_t, 8> spriteIndex; // 0x18 (24 decimal) | MMExt info: loaded from sprite list at runtime, chosen based on sprite orientation
		int32_t scale; // 0x28 (40 decimal)
		union
		{
			uint16_t bits; // 0x2C (44 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x2C (44 decimal), bit index 7
				bool luminous : 1; // 0x2C (44 decimal), bit index 6
				bool groupStart : 1; // 0x2C (44 decimal), bit index 5
				SKIPBITS(1);
				bool image1 : 1; // 0x2C (44 decimal), bit index 3 | MMExt info: has 1 image (not 8 for different angles)
				bool center : 1; // 0x2C (44 decimal), bit index 2 | MMExt info: center sprite
				bool fidget : 1; // 0x2C (44 decimal), bit index 1 | MMExt info: part of monster figet sequence
				bool loaded : 1; // 0x2C (44 decimal), bit index 0 | MMExt info: group is loaded
				bool mirror0 : 1; // 0x2D (45 decimal), bit index 7
				bool mirror1 : 1; // 0x2D (45 decimal), bit index 6
				bool mirror2 : 1; // 0x2D (45 decimal), bit index 5
				bool mirror3 : 1; // 0x2D (45 decimal), bit index 4
				bool mirror4 : 1; // 0x2D (45 decimal), bit index 3
				bool mirror5 : 1; // 0x2D (45 decimal), bit index 2
				bool mirror6 : 1; // 0x2D (45 decimal), bit index 1
				bool mirror7 : 1; // 0x2D (45 decimal), bit index 0
			};
		};
		int16_t lightRadius; // 0x2E (46 decimal)
		int16_t paletteId; // 0x30 (48 decimal)
		int16_t paletteIndex; // 0x32 (50 decimal) | MMExt info: palette index (0 if not loaded)
		int16_t time; // 0x34 (52 decimal) | MMExt info: time for this frame in 1/32 of a second
		int16_t totalTime; // 0x36 (54 decimal) | MMExt info: total time for this group
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
		uint32_t frames_size; // 0x0 (0 decimal)
		union
		{
			uint32_t groupIndex_size; // 0x4 (4 decimal)
			uint32_t groups_size; // 0x4 (4 decimal)
		};
		int32_t matchIndex; // 0x8 (8 decimal) | MMExt info: used when searching for a group by name
		mm6::SFTItem* frames; // size field offset is 0x0 | 0xC (12 decimal)
		mm6::SFTItem** groups; // size field offset is 0x4 | 0x10 (16 decimal) | MMExt info: sorted by name
		int16_t* groupIndex; // size field offset is 0x4 | 0x14 (20 decimal)
		int __thiscall findGroup(); // address: 0x444020 | defaults: (this), ""
		int __thiscall loadGroup(); // address: 0x443CE0 | defaults: (this)
	};
	static_assert(sizeof(mm6::SFT) == 0x18, "Invalid \"mm6::SFT\" structure size");
	static_assert(offsetof(mm6::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm6::SFT, groups_size) == 4);
	static_assert(offsetof(mm6::SFT, matchIndex) == 8);
	static_assert(offsetof(mm6::SFT, frames) == 12);
	static_assert(offsetof(mm6::SFT, groups) == 16);
	static_assert(offsetof(mm6::SFT, groupIndex) == 20);



	struct PFTItem // size: 0xA
	{
		uint16_t groupId; // 0x0 (0 decimal)
		uint16_t frameIndex; // 0x2 (2 decimal)
		uint16_t time; // 0x4 (4 decimal) | MMExt info: time for this frame in 1/32 of a second
		uint16_t totalTime; // 0x6 (6 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x8 (8 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x8 (8 decimal), bit index 7
				SKIPBITS(1);
				bool groupStart : 1; // 0x8 (8 decimal), bit index 5
			};
		};
	};
	static_assert(sizeof(mm6::PFTItem) == 0xA, "Invalid \"mm6::PFTItem\" structure size");
	static_assert(offsetof(mm6::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm6::PFTItem, time) == 4);
	static_assert(offsetof(mm6::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm6::PFTItem, bits) == 8);



	struct OverlayItem // size: 0x8
	{
		int16_t id; // 0x0 (0 decimal)
		int16_t type; // 0x2 (2 decimal)
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x4 (4 decimal)
			int16_t SFTIndex; // 0x4 (4 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm6::OverlayItem) == 0x8, "Invalid \"mm6::OverlayItem\" structure size");
	static_assert(offsetof(mm6::OverlayItem, type) == 2);
	static_assert(offsetof(mm6::OverlayItem, SFTGroup) == 4);
	static_assert(offsetof(mm6::OverlayItem, SFTIndex) == 4);



	struct ObjListItem // size: 0x34
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int16_t id; // 0x20 (32 decimal)
		int16_t radius; // 0x22 (34 decimal)
		int16_t height; // 0x24 (36 decimal)
		union
		{
			uint16_t bits; // 0x26 (38 decimal)
			struct
			{
				bool invisible : 1; // 0x26 (38 decimal), bit index 7
				bool untouchable : 1; // 0x26 (38 decimal), bit index 6
				bool temporary : 1; // 0x26 (38 decimal), bit index 5
				bool lifetimeInSFT : 1; // 0x26 (38 decimal), bit index 4
				bool noPickup : 1; // 0x26 (38 decimal), bit index 3
				bool noGravity : 1; // 0x26 (38 decimal), bit index 2
				bool interceptAction : 1; // 0x26 (38 decimal), bit index 1
				bool bounce : 1; // 0x26 (38 decimal), bit index 0
				bool trailParticles : 1; // 0x27 (39 decimal), bit index 7
				bool trailFire : 1; // 0x27 (39 decimal), bit index 6
				bool trailLine : 1; // 0x27 (39 decimal), bit index 5
			};
		};
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x28 (40 decimal)
			int16_t SFTIndex; // 0x28 (40 decimal)
		};
		int16_t lifeTime; // 0x2A (42 decimal)
		uint16_t loadedParticlesColor; // 0x2C (44 decimal) | MMExt info: munged 16-bit color
		uint16_t speed; // 0x2E (46 decimal) | MMExt info: default speed of object
		union
		{
			std::array<uint8_t, 4> particlesColor; // 0x30 (48 decimal) | MMExt info: color for particles
			struct
			{
				uint8_t particleR; // 0x30 (48 decimal)
				uint8_t particleG; // 0x31 (49 decimal)
				uint8_t particleB; // 0x32 (50 decimal)
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



	struct MonListItem // size: 0x94
	{
		int16_t height; // 0x0 (0 decimal)
		int16_t radius; // 0x2 (2 decimal) | MMExt info: overall monster radius
		int16_t velocity; // 0x4 (4 decimal)
		SKIP(2);
		union
		{
			std::array<int16_t, 4> sounds; // 0x8 (8 decimal)
			struct
			{
				int16_t soundAttack; // 0x8 (8 decimal)
				int16_t soundDie; // 0xA (10 decimal)
				int16_t soundGetHit; // 0xC (12 decimal)
				int16_t soundFidget; // 0xE (14 decimal)
			};
		};
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x10 (16 decimal)
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator | 0x30 (48 decimal)
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator | 0x30 (48 decimal)
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator | 0x3A (58 decimal)
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator | 0x44 (68 decimal)
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator | 0x4E (78 decimal)
				std::array<char, 10> framesStun; // fixed size string, requires null terminator | 0x58 (88 decimal)
				std::array<char, 10> framesDie; // fixed size string, requires null terminator | 0x62 (98 decimal)
				std::array<char, 10> framesDead; // fixed size string, requires null terminator | 0x6C (108 decimal)
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator | 0x76 (118 decimal)
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



	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: animation name
		std::array<char, 12> iconName; // fixed size string, requires null terminator | 0xC (12 decimal) | MMExt info: image name in icons.lod
		uint16_t time; // 0x18 (24 decimal) | MMExt info: time for this frame, units in 1/16 of a second
		uint16_t totalTime; // 0x1A (26 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x1C (28 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x1C (28 decimal), bit index 7
				SKIPBITS(1);
				bool groupStart : 1; // 0x1C (28 decimal), bit index 5
			};
		};
		uint16_t iconIndex; // 0x1E (30 decimal)
	};
	static_assert(sizeof(mm6::IFTItem) == 0x20, "Invalid \"mm6::IFTItem\" structure size");
	static_assert(offsetof(mm6::IFTItem, iconName) == 12);
	static_assert(offsetof(mm6::IFTItem, time) == 24);
	static_assert(offsetof(mm6::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm6::IFTItem, bits) == 28);
	static_assert(offsetof(mm6::IFTItem, iconIndex) == 30);



	struct DecListItem // size: 0x50
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> gameName; // fixed size string, requires null terminator | 0x20 (32 decimal)
		int16_t type; // 0x40 (64 decimal)
		int16_t height; // 0x42 (66 decimal)
		int16_t radius; // 0x44 (68 decimal)
		int16_t lightRadius; // 0x46 (70 decimal)
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x48 (72 decimal)
			int16_t SFTIndex; // 0x48 (72 decimal)
		};
		union
		{
			uint16_t bits; // 0x4A (74 decimal)
			struct
			{
				bool noBlockMovement : 1; // 0x4A (74 decimal), bit index 7
				bool noDraw : 1; // 0x4A (74 decimal), bit index 6
				bool flickerSlow : 1; // 0x4A (74 decimal), bit index 5
				bool flickerMedium : 1; // 0x4A (74 decimal), bit index 4
				bool flickerFast : 1; // 0x4A (74 decimal), bit index 3
				bool marker : 1; // 0x4A (74 decimal), bit index 2
				bool slowLoop : 1; // 0x4A (74 decimal), bit index 1
				bool emitFire : 1; // 0x4A (74 decimal), bit index 0
				bool soundOnDawn : 1; // 0x4B (75 decimal), bit index 7
				bool soundOnDusk : 1; // 0x4B (75 decimal), bit index 6
				bool emitSmoke : 1; // 0x4B (75 decimal), bit index 5
			};
		};
		int16_t soundId; // 0x4C (76 decimal)
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



	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		uint8_t width; // 0x20 (32 decimal)
		uint8_t height; // 0x21 (33 decimal)
		int16_t imageIndex; // 0x22 (34 decimal)
	};
	static_assert(sizeof(mm6::DChestItem) == 0x24, "Invalid \"mm6::DChestItem\" structure size");
	static_assert(offsetof(mm6::DChestItem, width) == 32);
	static_assert(offsetof(mm6::DChestItem, height) == 33);
	static_assert(offsetof(mm6::DChestItem, imageIndex) == 34);
}
namespace mm7
{
	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int16_t id; // 0x10 (16 decimal)
		int16_t bitmap; // 0x12 (18 decimal)
		int16_t tileSet; // 0x14 (20 decimal)
		int16_t section; // 0x16 (22 decimal)
		union
		{
			uint16_t bits; // 0x18 (24 decimal)
			struct
			{
				bool burn : 1; // 0x18 (24 decimal), bit index 7
				bool water : 1; // 0x18 (24 decimal), bit index 6
				bool block : 1; // 0x18 (24 decimal), bit index 5
				bool repulse : 1; // 0x18 (24 decimal), bit index 4
				bool flat : 1; // 0x18 (24 decimal), bit index 3
				bool wave : 1; // 0x18 (24 decimal), bit index 2
				bool noDraw : 1; // 0x18 (24 decimal), bit index 1
				SKIPBITS(1);
				bool waterTransition : 1; // 0x19 (25 decimal), bit index 7
				bool transition : 1; // 0x19 (25 decimal), bit index 6
				bool scrollDown : 1; // 0x19 (25 decimal), bit index 5
				bool scrollUp : 1; // 0x19 (25 decimal), bit index 4
				bool scrollLeft : 1; // 0x19 (25 decimal), bit index 3
				bool scrollRight : 1; // 0x19 (25 decimal), bit index 2
			};
		};
	};
	static_assert(sizeof(mm7::TileItem) == 0x1A, "Invalid \"mm7::TileItem\" structure size");
	static_assert(offsetof(mm7::TileItem, id) == 16);
	static_assert(offsetof(mm7::TileItem, bitmap) == 18);
	static_assert(offsetof(mm7::TileItem, tileSet) == 20);
	static_assert(offsetof(mm7::TileItem, section) == 22);
	static_assert(offsetof(mm7::TileItem, bits) == 24);



	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: texture name
		int16_t index; // 0xC (12 decimal) | MMExt info: index in bitmaps.lod
		int16_t time; // 0xE (14 decimal) | MMExt info: time for this frame in 1/32 of a second
		int16_t totalTime; // 0x10 (16 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x12 (18 decimal), bit index 7
				bool groupStart : 1; // 0x12 (18 decimal), bit index 6
			};
		};
	};
	static_assert(sizeof(mm7::TFTItem) == 0x14, "Invalid \"mm7::TFTItem\" structure size");
	static_assert(offsetof(mm7::TFTItem, index) == 12);
	static_assert(offsetof(mm7::TFTItem, time) == 14);
	static_assert(offsetof(mm7::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm7::TFTItem, bits) == 18);



	struct SoundsItem // size: 0x78
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: name of sound file
		int32_t id; // 0x20 (32 decimal)
		// MMExt info: type of sound
		// 0 = (0)      level specific sound, load during level initialization
		// 1 = (system) system sound, always loaded
		// 2 = (swap)   level specific sound, that gets loaded and flushed
		// 3 = (?)
		// 4 = (lock)   delete sound only when game ends
		int32_t type; // 0x24 (36 decimal)
		union
		{
			uint32_t bits; // 0x28 (40 decimal)
			struct
			{
				bool locked : 1; // 0x28 (40 decimal), bit index 7
				bool is3D : 1; // 0x28 (40 decimal), bit index 6
			};
		};
		std::array<uint32_t, 17> data; // 0x2C (44 decimal) | MMExt info: data pointer
		uint32_t data3D; // 0x70 (112 decimal) | MMExt info: 3d data pointer
		uint32_t decompressed; // 4-byte boolean | 0x74 (116 decimal) | MMExt info: true if decompressed and needs to be freed separately
	};
	static_assert(sizeof(mm7::SoundsItem) == 0x78, "Invalid \"mm7::SoundsItem\" structure size");
	static_assert(offsetof(mm7::SoundsItem, id) == 32);
	static_assert(offsetof(mm7::SoundsItem, type) == 36);
	static_assert(offsetof(mm7::SoundsItem, bits) == 40);
	static_assert(offsetof(mm7::SoundsItem, data) == 44);
	static_assert(offsetof(mm7::SoundsItem, data3D) == 112);
	static_assert(offsetof(mm7::SoundsItem, decompressed) == 116);



	struct SFTItem // size: 0x3C
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 12> spriteName; // fixed size string, requires null terminator | 0xC (12 decimal)
		std::array<int16_t, 8> spriteIndex; // 0x18 (24 decimal) | MMExt info: loaded from sprite list at runtime, chosen based on sprite orientation
		int32_t scale; // 0x28 (40 decimal)
		union
		{
			uint32_t bits; // 0x2C (44 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x2C (44 decimal), bit index 7
				bool luminous : 1; // 0x2C (44 decimal), bit index 6
				bool groupStart : 1; // 0x2C (44 decimal), bit index 5
				SKIPBITS(1);
				bool image1 : 1; // 0x2C (44 decimal), bit index 3 | MMExt info: has 1 image (not 8 for different angles)
				bool center : 1; // 0x2C (44 decimal), bit index 2 | MMExt info: center sprite
				bool fidget : 1; // 0x2C (44 decimal), bit index 1 | MMExt info: part of monster figet sequence
				bool loaded : 1; // 0x2C (44 decimal), bit index 0 | MMExt info: group is loaded
				bool mirror0 : 1; // 0x2D (45 decimal), bit index 7
				bool mirror1 : 1; // 0x2D (45 decimal), bit index 6
				bool mirror2 : 1; // 0x2D (45 decimal), bit index 5
				bool mirror3 : 1; // 0x2D (45 decimal), bit index 4
				bool mirror4 : 1; // 0x2D (45 decimal), bit index 3
				bool mirror5 : 1; // 0x2D (45 decimal), bit index 2
				bool mirror6 : 1; // 0x2D (45 decimal), bit index 1
				bool mirror7 : 1; // 0x2D (45 decimal), bit index 0
				bool images3 : 1; // 0x2E (46 decimal), bit index 7 | MMExt info: only views 0,2,4 exist (mirrored)
				bool glow : 1; // 0x2E (46 decimal), bit index 6
				bool transparent : 1; // 0x2E (46 decimal), bit index 5
			};
		};
		int16_t lightRadius; // 0x30 (48 decimal)
		int16_t paletteId; // 0x32 (50 decimal)
		int16_t paletteIndex; // 0x34 (52 decimal) | MMExt info: palette index (0 if not loaded)
		int16_t time; // 0x36 (54 decimal) | MMExt info: time for this frame in 1/32 of a second
		int16_t totalTime; // 0x38 (56 decimal) | MMExt info: total time for this group
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
		uint32_t frames_size; // 0x0 (0 decimal)
		union
		{
			uint32_t groupIndex_size; // 0x4 (4 decimal)
			uint32_t groups_size; // 0x4 (4 decimal)
		};
		int32_t matchIndex; // 0x8 (8 decimal) | MMExt info: used when searching for a group by name
		mm7::SFTItem* frames; // size field offset is 0x0 | 0xC (12 decimal)
		mm7::SFTItem** groups; // size field offset is 0x4 | 0x10 (16 decimal) | MMExt info: sorted by name
		int16_t* groupIndex; // size field offset is 0x4 | 0x14 (20 decimal)
		int __thiscall loadGroup(); // address: 0x44D53F | defaults: (this)
		int __thiscall findGroup(); // address: 0x44D83F | defaults: (this), ""
	};
	static_assert(sizeof(mm7::SFT) == 0x18, "Invalid \"mm7::SFT\" structure size");
	static_assert(offsetof(mm7::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm7::SFT, groups_size) == 4);
	static_assert(offsetof(mm7::SFT, matchIndex) == 8);
	static_assert(offsetof(mm7::SFT, frames) == 12);
	static_assert(offsetof(mm7::SFT, groups) == 16);
	static_assert(offsetof(mm7::SFT, groupIndex) == 20);



	struct PFTItem // size: 0xA
	{
		uint16_t groupId; // 0x0 (0 decimal)
		uint16_t frameIndex; // 0x2 (2 decimal)
		uint16_t time; // 0x4 (4 decimal) | MMExt info: time for this frame in 1/32 of a second
		uint16_t totalTime; // 0x6 (6 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x8 (8 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x8 (8 decimal), bit index 7
				SKIPBITS(1);
				bool groupStart : 1; // 0x8 (8 decimal), bit index 5
			};
		};
	};
	static_assert(sizeof(mm7::PFTItem) == 0xA, "Invalid \"mm7::PFTItem\" structure size");
	static_assert(offsetof(mm7::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm7::PFTItem, time) == 4);
	static_assert(offsetof(mm7::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm7::PFTItem, bits) == 8);



	struct OverlayItem // size: 0x8
	{
		int16_t id; // 0x0 (0 decimal)
		int16_t type; // 0x2 (2 decimal)
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x4 (4 decimal)
			int16_t SFTIndex; // 0x4 (4 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::OverlayItem) == 0x8, "Invalid \"mm7::OverlayItem\" structure size");
	static_assert(offsetof(mm7::OverlayItem, type) == 2);
	static_assert(offsetof(mm7::OverlayItem, SFTGroup) == 4);
	static_assert(offsetof(mm7::OverlayItem, SFTIndex) == 4);



	struct ObjListItem // size: 0x38
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int16_t id; // 0x20 (32 decimal)
		int16_t radius; // 0x22 (34 decimal)
		int16_t height; // 0x24 (36 decimal)
		union
		{
			uint16_t bits; // 0x26 (38 decimal)
			struct
			{
				bool invisible : 1; // 0x26 (38 decimal), bit index 7
				bool untouchable : 1; // 0x26 (38 decimal), bit index 6
				bool temporary : 1; // 0x26 (38 decimal), bit index 5
				bool lifetimeInSFT : 1; // 0x26 (38 decimal), bit index 4
				bool noPickup : 1; // 0x26 (38 decimal), bit index 3
				bool noGravity : 1; // 0x26 (38 decimal), bit index 2
				bool interceptAction : 1; // 0x26 (38 decimal), bit index 1
				bool bounce : 1; // 0x26 (38 decimal), bit index 0
				bool trailParticles : 1; // 0x27 (39 decimal), bit index 7
				bool trailFire : 1; // 0x27 (39 decimal), bit index 6
				bool trailLine : 1; // 0x27 (39 decimal), bit index 5
			};
		};
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x28 (40 decimal)
			int16_t SFTIndex; // 0x28 (40 decimal)
		};
		int16_t lifeTime; // 0x2A (42 decimal)
		uint32_t loadedParticlesColor; // 0x2C (44 decimal) | MMExt info: RGBA color with R and B swapped
		uint16_t speed; // 0x30 (48 decimal) | MMExt info: default speed of object
		union
		{
			std::array<uint8_t, 4> particlesColor; // 0x32 (50 decimal) | MMExt info: color for particles
			struct
			{
				uint8_t particleR; // 0x32 (50 decimal)
				uint8_t particleG; // 0x33 (51 decimal)
				uint8_t particleB; // 0x34 (52 decimal)
				uint8_t particleA; // 0x35 (53 decimal)
			};
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::ObjListItem) == 0x38, "Invalid \"mm7::ObjListItem\" structure size");
	static_assert(offsetof(mm7::ObjListItem, id) == 32);
	static_assert(offsetof(mm7::ObjListItem, radius) == 34);
	static_assert(offsetof(mm7::ObjListItem, height) == 36);
	static_assert(offsetof(mm7::ObjListItem, bits) == 38);
	static_assert(offsetof(mm7::ObjListItem, SFTGroup) == 40);
	static_assert(offsetof(mm7::ObjListItem, SFTIndex) == 40);
	static_assert(offsetof(mm7::ObjListItem, lifeTime) == 42);
	static_assert(offsetof(mm7::ObjListItem, loadedParticlesColor) == 44);
	static_assert(offsetof(mm7::ObjListItem, speed) == 48);
	static_assert(offsetof(mm7::ObjListItem, particlesColor) == 50);
	static_assert(offsetof(mm7::ObjListItem, particleR) == 50);
	static_assert(offsetof(mm7::ObjListItem, particleG) == 51);
	static_assert(offsetof(mm7::ObjListItem, particleB) == 52);
	static_assert(offsetof(mm7::ObjListItem, particleA) == 53);



	struct MonListItem // size: 0x98
	{
		int16_t height; // 0x0 (0 decimal)
		int16_t radius; // 0x2 (2 decimal) | MMExt info: overall monster radius
		int16_t velocity; // 0x4 (4 decimal)
		int16_t radius2; // 0x6 (6 decimal) | MMExt info: monster radius for "to-hit" purposes
		union
		{
			int32_t tint; // 0x8 (8 decimal) | MMExt info: tint color for graphic
			struct
			{
				uint8_t tintB; // 0x8 (8 decimal)
				uint8_t tintG; // 0x9 (9 decimal)
				uint8_t tintR; // 0xA (10 decimal)
				uint8_t tintA; // 0xB (11 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // 0xC (12 decimal)
			struct
			{
				int16_t soundAttack; // 0xC (12 decimal)
				int16_t soundDie; // 0xE (14 decimal)
				int16_t soundGetHit; // 0x10 (16 decimal)
				int16_t soundFidget; // 0x12 (18 decimal)
			};
		};
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x14 (20 decimal)
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator | 0x34 (52 decimal)
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator | 0x34 (52 decimal)
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator | 0x3E (62 decimal)
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator | 0x48 (72 decimal)
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator | 0x52 (82 decimal)
				std::array<char, 10> framesStun; // fixed size string, requires null terminator | 0x5C (92 decimal)
				std::array<char, 10> framesDie; // fixed size string, requires null terminator | 0x66 (102 decimal)
				std::array<char, 10> framesDead; // fixed size string, requires null terminator | 0x70 (112 decimal)
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator | 0x7A (122 decimal)
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



	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: animation name
		std::array<char, 12> iconName; // fixed size string, requires null terminator | 0xC (12 decimal) | MMExt info: image name in icons.lod
		uint16_t time; // 0x18 (24 decimal) | MMExt info: time for this frame, units in 1/16 of a second
		uint16_t totalTime; // 0x1A (26 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x1C (28 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x1C (28 decimal), bit index 7
				SKIPBITS(1);
				bool groupStart : 1; // 0x1C (28 decimal), bit index 5
			};
		};
		uint16_t iconIndex; // 0x1E (30 decimal)
	};
	static_assert(sizeof(mm7::IFTItem) == 0x20, "Invalid \"mm7::IFTItem\" structure size");
	static_assert(offsetof(mm7::IFTItem, iconName) == 12);
	static_assert(offsetof(mm7::IFTItem, time) == 24);
	static_assert(offsetof(mm7::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm7::IFTItem, bits) == 28);
	static_assert(offsetof(mm7::IFTItem, iconIndex) == 30);



	struct DecListItem // size: 0x54
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> gameName; // fixed size string, requires null terminator | 0x20 (32 decimal)
		int16_t type; // 0x40 (64 decimal)
		int16_t height; // 0x42 (66 decimal)
		int16_t radius; // 0x44 (68 decimal)
		int16_t lightRadius; // 0x46 (70 decimal)
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x48 (72 decimal)
			int16_t SFTIndex; // 0x48 (72 decimal)
		};
		union
		{
			uint16_t bits; // 0x4A (74 decimal)
			struct
			{
				bool noBlockMovement : 1; // 0x4A (74 decimal), bit index 7
				bool noDraw : 1; // 0x4A (74 decimal), bit index 6
				bool flickerSlow : 1; // 0x4A (74 decimal), bit index 5
				bool flickerMedium : 1; // 0x4A (74 decimal), bit index 4
				bool flickerFast : 1; // 0x4A (74 decimal), bit index 3
				bool marker : 1; // 0x4A (74 decimal), bit index 2
				bool slowLoop : 1; // 0x4A (74 decimal), bit index 1
				bool emitFire : 1; // 0x4A (74 decimal), bit index 0
				bool soundOnDawn : 1; // 0x4B (75 decimal), bit index 7
				bool soundOnDusk : 1; // 0x4B (75 decimal), bit index 6
				bool emitSmoke : 1; // 0x4B (75 decimal), bit index 5
			};
		};
		int16_t soundId; // 0x4C (76 decimal)
		SKIP(2);
		uint8_t red; // 0x50 (80 decimal)
		uint8_t green; // 0x51 (81 decimal)
		uint8_t blue; // 0x52 (82 decimal)
		SKIP(1);
	};
	static_assert(sizeof(mm7::DecListItem) == 0x54, "Invalid \"mm7::DecListItem\" structure size");
	static_assert(offsetof(mm7::DecListItem, gameName) == 32);
	static_assert(offsetof(mm7::DecListItem, type) == 64);
	static_assert(offsetof(mm7::DecListItem, height) == 66);
	static_assert(offsetof(mm7::DecListItem, radius) == 68);
	static_assert(offsetof(mm7::DecListItem, lightRadius) == 70);
	static_assert(offsetof(mm7::DecListItem, SFTGroup) == 72);
	static_assert(offsetof(mm7::DecListItem, SFTIndex) == 72);
	static_assert(offsetof(mm7::DecListItem, bits) == 74);
	static_assert(offsetof(mm7::DecListItem, soundId) == 76);
	static_assert(offsetof(mm7::DecListItem, red) == 80);
	static_assert(offsetof(mm7::DecListItem, green) == 81);
	static_assert(offsetof(mm7::DecListItem, blue) == 82);



	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		uint8_t width; // 0x20 (32 decimal)
		uint8_t height; // 0x21 (33 decimal)
		int16_t imageIndex; // 0x22 (34 decimal)
	};
	static_assert(sizeof(mm7::DChestItem) == 0x24, "Invalid \"mm7::DChestItem\" structure size");
	static_assert(offsetof(mm7::DChestItem, width) == 32);
	static_assert(offsetof(mm7::DChestItem, height) == 33);
	static_assert(offsetof(mm7::DChestItem, imageIndex) == 34);
}
namespace mm8
{
	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: texture name
		int16_t index; // 0xC (12 decimal) | MMExt info: index in bitmaps.lod
		int16_t time; // 0xE (14 decimal) | MMExt info: time for this frame in 1/32 of a second
		int16_t totalTime; // 0x10 (16 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x12 (18 decimal), bit index 7
				bool groupStart : 1; // 0x12 (18 decimal), bit index 6
			};
		};
	};
	static_assert(sizeof(mm8::TFTItem) == 0x14, "Invalid \"mm8::TFTItem\" structure size");
	static_assert(offsetof(mm8::TFTItem, index) == 12);
	static_assert(offsetof(mm8::TFTItem, time) == 14);
	static_assert(offsetof(mm8::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm8::TFTItem, bits) == 18);



	struct SoundsItem // size: 0x98
	{
		std::array<char, 64> name; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: name of sound file
		int32_t id; // 0x40 (64 decimal)
		// MMExt info: type of sound
		// 0 = (0)      level specific sound, load during level initialization
		// 1 = (system) system sound, always loaded
		// 2 = (swap)   level specific sound, that gets loaded and flushed
		// 3 = (?)
		// 4 = (lock)   delete sound only when game ends
		int32_t type; // 0x44 (68 decimal)
		union
		{
			uint32_t bits; // 0x48 (72 decimal)
			struct
			{
				bool locked : 1; // 0x48 (72 decimal), bit index 7
				bool is3D : 1; // 0x48 (72 decimal), bit index 6
			};
		};
		std::array<uint32_t, 17> data; // 0x4C (76 decimal) | MMExt info: data pointer
		uint32_t data3D; // 0x90 (144 decimal) | MMExt info: 3d data pointer
		uint32_t decompressed; // 4-byte boolean | 0x94 (148 decimal) | MMExt info: true if decompressed and needs to be freed separately
	};
	static_assert(sizeof(mm8::SoundsItem) == 0x98, "Invalid \"mm8::SoundsItem\" structure size");
	static_assert(offsetof(mm8::SoundsItem, id) == 64);
	static_assert(offsetof(mm8::SoundsItem, type) == 68);
	static_assert(offsetof(mm8::SoundsItem, bits) == 72);
	static_assert(offsetof(mm8::SoundsItem, data) == 76);
	static_assert(offsetof(mm8::SoundsItem, data3D) == 144);
	static_assert(offsetof(mm8::SoundsItem, decompressed) == 148);



	struct SFTItem // size: 0x3C
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 12> spriteName; // fixed size string, requires null terminator | 0xC (12 decimal)
		std::array<int16_t, 8> spriteIndex; // 0x18 (24 decimal) | MMExt info: loaded from sprite list at runtime, chosen based on sprite orientation
		int32_t scale; // 0x28 (40 decimal)
		union
		{
			uint32_t bits; // 0x2C (44 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x2C (44 decimal), bit index 7
				bool luminous : 1; // 0x2C (44 decimal), bit index 6
				bool groupStart : 1; // 0x2C (44 decimal), bit index 5
				SKIPBITS(1);
				bool image1 : 1; // 0x2C (44 decimal), bit index 3 | MMExt info: has 1 image (not 8 for different angles)
				bool center : 1; // 0x2D (45 decimal), bit index 2 | MMExt info: center sprite
				bool fidget : 1; // 0x2D (45 decimal), bit index 1 | MMExt info: part of monster figet sequence
				bool loaded : 1; // 0x2D (45 decimal), bit index 0 | MMExt info: group is loaded
				bool mirror0 : 1; // 0x2D (45 decimal), bit index 7
				bool mirror1 : 1; // 0x2D (45 decimal), bit index 6
				bool mirror2 : 1; // 0x2D (45 decimal), bit index 5
				bool mirror3 : 1; // 0x2D (45 decimal), bit index 4
				bool mirror4 : 1; // 0x2E (46 decimal), bit index 3
				bool mirror5 : 1; // 0x2E (46 decimal), bit index 2
				bool mirror6 : 1; // 0x2E (46 decimal), bit index 1
				bool mirror7 : 1; // 0x2E (46 decimal), bit index 0
				bool images3 : 1; // 0x2E (46 decimal), bit index 7 | MMExt info: only views 0,2,4 exist (mirrored)
				bool glow : 1; // 0x2E (46 decimal), bit index 6
				bool transparent : 1; // 0x2E (46 decimal), bit index 5
			};
		};
		int16_t lightRadius; // 0x30 (48 decimal)
		int16_t paletteId; // 0x32 (50 decimal)
		int16_t paletteIndex; // 0x34 (52 decimal) | MMExt info: palette index (0 if not loaded)
		int16_t time; // 0x36 (54 decimal) | MMExt info: time for this frame in 1/32 of a second
		int16_t totalTime; // 0x38 (56 decimal) | MMExt info: total time for this group
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
		uint32_t frames_size; // 0x0 (0 decimal)
		union
		{
			uint32_t groupIndex_size; // 0x4 (4 decimal)
			uint32_t groups_size; // 0x4 (4 decimal)
		};
		int32_t matchIndex; // 0x8 (8 decimal) | MMExt info: used when searching for a group by name
		mm8::SFTItem* frames; // size field offset is 0x0 | 0xC (12 decimal)
		mm8::SFTItem** groups; // size field offset is 0x4 | 0x10 (16 decimal) | MMExt info: sorted by name
		int16_t* groupIndex; // size field offset is 0x4 | 0x14 (20 decimal)
		int __thiscall loadGroup(); // address: 0x44AC21 | defaults: (this)
		int __thiscall findGroup(); // address: 0x44AF24 | defaults: (this), ""
	};
	static_assert(sizeof(mm8::SFT) == 0x18, "Invalid \"mm8::SFT\" structure size");
	static_assert(offsetof(mm8::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm8::SFT, groups_size) == 4);
	static_assert(offsetof(mm8::SFT, matchIndex) == 8);
	static_assert(offsetof(mm8::SFT, frames) == 12);
	static_assert(offsetof(mm8::SFT, groups) == 16);
	static_assert(offsetof(mm8::SFT, groupIndex) == 20);



	struct PFTItem // size: 0xA
	{
		uint16_t groupId; // 0x0 (0 decimal)
		uint16_t frameIndex; // 0x2 (2 decimal)
		uint16_t time; // 0x4 (4 decimal) | MMExt info: time for this frame in 1/32 of a second
		uint16_t totalTime; // 0x6 (6 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x8 (8 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x8 (8 decimal), bit index 7
				SKIPBITS(1);
				bool groupStart : 1; // 0x8 (8 decimal), bit index 5
			};
		};
	};
	static_assert(sizeof(mm8::PFTItem) == 0xA, "Invalid \"mm8::PFTItem\" structure size");
	static_assert(offsetof(mm8::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm8::PFTItem, time) == 4);
	static_assert(offsetof(mm8::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm8::PFTItem, bits) == 8);



	struct OverlayItem // size: 0x8
	{
		int16_t id; // 0x0 (0 decimal)
		int16_t type; // 0x2 (2 decimal)
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x4 (4 decimal)
			int16_t SFTIndex; // 0x4 (4 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::OverlayItem) == 0x8, "Invalid \"mm8::OverlayItem\" structure size");
	static_assert(offsetof(mm8::OverlayItem, type) == 2);
	static_assert(offsetof(mm8::OverlayItem, SFTGroup) == 4);
	static_assert(offsetof(mm8::OverlayItem, SFTIndex) == 4);



	struct ObjListItem // size: 0x38
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int16_t id; // 0x20 (32 decimal)
		int16_t radius; // 0x22 (34 decimal)
		int16_t height; // 0x24 (36 decimal)
		union
		{
			uint16_t bits; // 0x26 (38 decimal)
			struct
			{
				bool invisible : 1; // 0x26 (38 decimal), bit index 7
				bool untouchable : 1; // 0x26 (38 decimal), bit index 6
				bool temporary : 1; // 0x26 (38 decimal), bit index 5
				bool lifetimeInSFT : 1; // 0x26 (38 decimal), bit index 4
				bool noPickup : 1; // 0x26 (38 decimal), bit index 3
				bool noGravity : 1; // 0x27 (39 decimal), bit index 2
				bool interceptAction : 1; // 0x27 (39 decimal), bit index 1
				bool bounce : 1; // 0x27 (39 decimal), bit index 0
				bool trailParticles : 1; // 0x27 (39 decimal), bit index 7
				bool trailFire : 1; // 0x27 (39 decimal), bit index 6
				bool trailLine : 1; // 0x27 (39 decimal), bit index 5
			};
		};
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x28 (40 decimal)
			int16_t SFTIndex; // 0x28 (40 decimal)
		};
		int16_t lifeTime; // 0x2A (42 decimal)
		uint32_t loadedParticlesColor; // 0x2C (44 decimal) | MMExt info: RGBA color with R and B swapped
		uint16_t speed; // 0x30 (48 decimal) | MMExt info: default speed of object
		union
		{
			std::array<uint8_t, 4> particlesColor; // 0x32 (50 decimal) | MMExt info: color for particles
			struct
			{
				uint8_t particleR; // 0x32 (50 decimal)
				uint8_t particleG; // 0x33 (51 decimal)
				uint8_t particleB; // 0x34 (52 decimal)
				uint8_t particleA; // 0x35 (53 decimal)
			};
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::ObjListItem) == 0x38, "Invalid \"mm8::ObjListItem\" structure size");
	static_assert(offsetof(mm8::ObjListItem, id) == 32);
	static_assert(offsetof(mm8::ObjListItem, radius) == 34);
	static_assert(offsetof(mm8::ObjListItem, height) == 36);
	static_assert(offsetof(mm8::ObjListItem, bits) == 38);
	static_assert(offsetof(mm8::ObjListItem, SFTGroup) == 40);
	static_assert(offsetof(mm8::ObjListItem, SFTIndex) == 40);
	static_assert(offsetof(mm8::ObjListItem, lifeTime) == 42);
	static_assert(offsetof(mm8::ObjListItem, loadedParticlesColor) == 44);
	static_assert(offsetof(mm8::ObjListItem, speed) == 48);
	static_assert(offsetof(mm8::ObjListItem, particlesColor) == 50);
	static_assert(offsetof(mm8::ObjListItem, particleR) == 50);
	static_assert(offsetof(mm8::ObjListItem, particleG) == 51);
	static_assert(offsetof(mm8::ObjListItem, particleB) == 52);
	static_assert(offsetof(mm8::ObjListItem, particleA) == 53);



	struct MonListItem // size: 0xB8
	{
		int16_t height; // 0x0 (0 decimal)
		int16_t radius; // 0x2 (2 decimal) | MMExt info: overall monster radius
		int16_t velocity; // 0x4 (4 decimal)
		int16_t radius2; // 0x6 (6 decimal) | MMExt info: monster radius for "to-hit" purposes
		union
		{
			int32_t tint; // 0x8 (8 decimal) | MMExt info: tint color for graphic
			struct
			{
				uint8_t tintB; // 0x8 (8 decimal)
				uint8_t tintG; // 0x9 (9 decimal)
				uint8_t tintR; // 0xA (10 decimal)
				uint8_t tintA; // 0xB (11 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // 0xC (12 decimal)
			struct
			{
				int16_t soundAttack; // 0xC (12 decimal)
				int16_t soundDie; // 0xE (14 decimal)
				int16_t soundGetHit; // 0x10 (16 decimal)
				int16_t soundFidget; // 0x12 (18 decimal)
			};
		};
		std::array<char, 64> name; // fixed size string, requires null terminator | 0x14 (20 decimal)
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator | 0x54 (84 decimal)
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator | 0x54 (84 decimal)
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator | 0x5E (94 decimal)
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator | 0x68 (104 decimal)
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator | 0x72 (114 decimal)
				std::array<char, 10> framesStun; // fixed size string, requires null terminator | 0x7C (124 decimal)
				std::array<char, 10> framesDie; // fixed size string, requires null terminator | 0x86 (134 decimal)
				std::array<char, 10> framesDead; // fixed size string, requires null terminator | 0x90 (144 decimal)
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator | 0x9A (154 decimal)
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



	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator | 0x0 (0 decimal) | MMExt info: animation name
		std::array<char, 12> iconName; // fixed size string, requires null terminator | 0xC (12 decimal) | MMExt info: image name in icons.lod
		uint16_t time; // 0x18 (24 decimal) | MMExt info: time for this frame, units in 1/16 of a second
		uint16_t totalTime; // 0x1A (26 decimal) | MMExt info: total time for this group
		union
		{
			uint16_t bits; // 0x1C (28 decimal)
			struct
			{
				bool notGroupEnd : 1; // 0x1C (28 decimal), bit index 7
				SKIPBITS(1);
				bool groupStart : 1; // 0x1C (28 decimal), bit index 5
			};
		};
		uint16_t iconIndex; // 0x1E (30 decimal)
	};
	static_assert(sizeof(mm8::IFTItem) == 0x20, "Invalid \"mm8::IFTItem\" structure size");
	static_assert(offsetof(mm8::IFTItem, iconName) == 12);
	static_assert(offsetof(mm8::IFTItem, time) == 24);
	static_assert(offsetof(mm8::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm8::IFTItem, bits) == 28);
	static_assert(offsetof(mm8::IFTItem, iconIndex) == 30);



	struct DecListItem // size: 0x54
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> gameName; // fixed size string, requires null terminator | 0x20 (32 decimal)
		int16_t type; // 0x40 (64 decimal)
		int16_t height; // 0x42 (66 decimal)
		int16_t radius; // 0x44 (68 decimal)
		int16_t lightRadius; // 0x46 (70 decimal)
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | 0x48 (72 decimal)
			int16_t SFTIndex; // 0x48 (72 decimal)
		};
		union
		{
			uint16_t bits; // 0x4A (74 decimal)
			struct
			{
				bool noBlockMovement : 1; // 0x4A (74 decimal), bit index 7
				bool noDraw : 1; // 0x4A (74 decimal), bit index 6
				bool flickerSlow : 1; // 0x4A (74 decimal), bit index 5
				bool flickerMedium : 1; // 0x4A (74 decimal), bit index 4
				bool flickerFast : 1; // 0x4A (74 decimal), bit index 3
				bool marker : 1; // 0x4B (75 decimal), bit index 2
				bool slowLoop : 1; // 0x4B (75 decimal), bit index 1
				bool emitFire : 1; // 0x4B (75 decimal), bit index 0
				bool soundOnDawn : 1; // 0x4B (75 decimal), bit index 7
				bool soundOnDusk : 1; // 0x4B (75 decimal), bit index 6
				bool emitSmoke : 1; // 0x4B (75 decimal), bit index 5
			};
		};
		int16_t soundId; // 0x4C (76 decimal)
		SKIP(2);
		uint8_t red; // 0x50 (80 decimal)
		uint8_t green; // 0x51 (81 decimal)
		uint8_t blue; // 0x52 (82 decimal)
		SKIP(1);
	};
	static_assert(sizeof(mm8::DecListItem) == 0x54, "Invalid \"mm8::DecListItem\" structure size");
	static_assert(offsetof(mm8::DecListItem, gameName) == 32);
	static_assert(offsetof(mm8::DecListItem, type) == 64);
	static_assert(offsetof(mm8::DecListItem, height) == 66);
	static_assert(offsetof(mm8::DecListItem, radius) == 68);
	static_assert(offsetof(mm8::DecListItem, lightRadius) == 70);
	static_assert(offsetof(mm8::DecListItem, SFTGroup) == 72);
	static_assert(offsetof(mm8::DecListItem, SFTIndex) == 72);
	static_assert(offsetof(mm8::DecListItem, bits) == 74);
	static_assert(offsetof(mm8::DecListItem, soundId) == 76);
	static_assert(offsetof(mm8::DecListItem, red) == 80);
	static_assert(offsetof(mm8::DecListItem, green) == 81);
	static_assert(offsetof(mm8::DecListItem, blue) == 82);



	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int16_t id; // 0x10 (16 decimal)
		int16_t bitmap; // 0x12 (18 decimal)
		int16_t tileSet; // 0x14 (20 decimal)
		int16_t section; // 0x16 (22 decimal)
		union
		{
			uint16_t bits; // 0x18 (24 decimal)
			struct
			{
				bool burn : 1; // 0x18 (24 decimal), bit index 7
				bool water : 1; // 0x18 (24 decimal), bit index 6
				bool block : 1; // 0x18 (24 decimal), bit index 5
				bool repulse : 1; // 0x18 (24 decimal), bit index 4
				bool flat : 1; // 0x18 (24 decimal), bit index 3
				bool wave : 1; // 0x19 (25 decimal), bit index 2
				bool noDraw : 1; // 0x19 (25 decimal), bit index 1
				SKIPBITS(1);
				bool waterTransition : 1; // 0x19 (25 decimal), bit index 7
				bool transition : 1; // 0x19 (25 decimal), bit index 6
				bool scrollDown : 1; // 0x19 (25 decimal), bit index 5
				bool scrollUp : 1; // 0x19 (25 decimal), bit index 4
				bool scrollLeft : 1; // 0x1A (26 decimal), bit index 3
				bool scrollRight : 1; // 0x1A (26 decimal), bit index 2
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
		uint32_t items_size; // 0x0 (0 decimal)
		mm8::TileItem* items; // size field offset is 0x0 | 0x4 (4 decimal)
	};
	static_assert(sizeof(mm8::CurrentTileBin) == 0x8, "Invalid \"mm8::CurrentTileBin\" structure size");
	static_assert(offsetof(mm8::CurrentTileBin, items) == 4);



	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		uint8_t width; // 0x20 (32 decimal)
		uint8_t height; // 0x21 (33 decimal)
		int16_t imageIndex; // 0x22 (34 decimal)
	};
	static_assert(sizeof(mm8::DChestItem) == 0x24, "Invalid \"mm8::DChestItem\" structure size");
	static_assert(offsetof(mm8::DChestItem, width) == 32);
	static_assert(offsetof(mm8::DChestItem, height) == 33);
	static_assert(offsetof(mm8::DChestItem, imageIndex) == 34);
}

#pragma pack(pop)