#pragma once
#include "pch.h"
#include "main.h"

namespace mm7
{
	struct MapMonster // size: 0x344
	{
		SKIP(32);
		int16_t NPC_ID;
		SKIP(2);
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1;
				SKIPBITS(4);
				bool showOnMap : 1;
				bool invisible : 1;
				bool noFlee : 1;
				SKIPBITS(1);
				bool hostile : 1;
				bool onAlertMap : 1;
				SKIPBITS(2);
				bool treasureGenerated : 1;
				bool showAsHostile : 1;
			};
		};
		union
		{
			int16_t hitPoints;
			int16_t HP;
		};
		SKIP(10);
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm7::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm7::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0;
				uint8_t _1;
				uint8_t _2;
				uint8_t _3;
				uint8_t _7;
				uint8_t _6;
				uint8_t _8;
				uint8_t _9;
				uint8_t _10;
				uint8_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t airResistance;
				uint8_t waterResistance;
				uint8_t earthResistance;
				uint8_t mindResistance;
				uint8_t spiritResistance;
				uint8_t bodyResistance;
				uint8_t lightResistance;
				uint8_t darkResistance;
				uint8_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		SKIP(2);
		union
		{
			int32_t fullHP;
			int32_t fullHitPoints;
		};
		int32_t armorClass;
		union
		{
			int32_t experience;
			int32_t exp;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x1, MMExt union
				{
					bool knight : 1;
					bool paladin : 1;
					bool archer : 1;
					bool druid : 1;
					bool cleric : 1;
					bool sorcerer : 1;
					bool ranger : 1;
					bool thief : 1;
					bool monk : 1;
					bool male : 1;
					bool female : 1;
					bool human : 1;
					bool elf : 1;
					bool dwarf : 1;
					bool goblin : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x1, "Invalid \"prefers\" structure size");
			};
		};
		int16_t rangeAttack;
		int16_t id2;
		int16_t bodyRadius;
		int16_t bodyHeight;
		int16_t velocity;
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		int16_t velocityX;
		int16_t velocityY;
		int16_t velocityZ;
		int16_t direction;
		int16_t lookAngle;
		int16_t room;
		int16_t currentActionLength;
		int16_t startX;
		int16_t startY;
		int16_t startZ;
		int16_t guardX;
		int16_t guardY;
		int16_t guardZ;
		int16_t guardRadius;
		int16_t AIState;
		int16_t graphicState;
		int16_t item;
		SKIP(2);
		int32_t currentActionStep;
		union
		{
			std::array<int16_t, 8> frames;
			struct
			{
				int16_t framesStand;
				int16_t framesWalk;
				int16_t framesAttack;
				int16_t framesShoot;
				int16_t framesStun;
				int16_t framesGotHit;
				int16_t framesDie;
				int16_t framesDead;
				int16_t framesFidget;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				int16_t soundGotHit;
				int16_t soundGetHit;
				int16_t soundFidget;
			};
		};
		std::array<mm7::SpellBuff, 22> spellBuffs;
		std::array<mm7::Item, 4> items;
		int32_t group;
		int32_t ally;
		std::array<mm7::MonsterSchedule, 8> schedules;
		int32_t summoner;
		int32_t lastAttacker;
		int32_t nameId;
		SKIP(12);
	};
	static_assert(sizeof(mm7::MapMonster) == 0x344, "Invalid \"mm7::MapMonster\" structure size");

	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t _1;
			int16_t x;
		};
		union
		{
			int16_t y;
			int16_t _2;
		};
		union
		{
			int16_t _3;
			int16_t z;
		};
	};
	static_assert(sizeof(mm7::MapVertex) == 0x6, "Invalid \"mm7::MapVertex\" structure size");

	struct SpawnPoint // size: 0x18
	{
		union
		{
			std::array<int32_t, 3> pos;
			struct
			{
				int32_t x;
				int32_t y;
				int32_t z;
			};
		};
		int16_t radius;
		int16_t kind;
		int16_t index;
		union
		{
			uint16_t bits;
			struct
			{
				bool onAlertMap : 1;
			};
		};
		int32_t group;
	};
	static_assert(sizeof(mm7::SpawnPoint) == 0x18, "Invalid \"mm7::SpawnPoint\" structure size");

	struct MapFacet // size: 0x60
	{
		union
		{
			std::array<float, 3> normalF;
			struct
			{
				float normalFX;
				float normalFY;
				float normalFZ;
			};
		};
		float normalFDistance;
		union
		{
			std::array<int32_t, 3> normal;
			struct
			{
				int32_t normalX;
				int32_t normalY;
				int32_t normalZ;
			};
		};
		int32_t normalDistance;
		int32_t ZCalc1;
		int32_t ZCalc2;
		int32_t ZCalc3;
		union
		{
			uint32_t bits;
			struct
			{
				bool isPortal : 1;
				bool isSecret : 1;
				bool scrollDown : 1;
				bool alignTop : 1;
				bool isWater : 1;
				bool scrollUp : 1;
				bool scrollLeft : 1;
				SKIPBITS(1);
				bool projectToXY : 1;
				bool projectToXZ : 1;
				bool projectToYZ : 1;
				bool scrollRight : 1;
				bool alignLeft : 1;
				bool invisible : 1;
				bool animatedTFT : 1;
				bool alignRight : 1;
				SKIPBITS(1);
				bool alignBottom : 1;
				bool moveByDoor : 1;
				SKIPBITS(1);
				bool isEventJustHint : 1;
				bool alternativeSound : 1;
				bool isSky : 1;
				bool flipU : 1;
				bool flipV : 1;
				bool triggerByClick : 1;
				bool triggerByStep : 1;
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
				bool untouchable : 1;
				bool isLava : 1;
				bool hasData : 1;
			};
		};
		(*uint16_t)[] vertexIds; // AccessBeyondLength is active (???) | size offset is 0x5D
		(*int16_t)[] XInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x5D
		(*int16_t)[] YInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x5D
		(*int16_t)[] ZInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x5D
		(*int16_t)[] UList; // AccessBeyondLength is active (???) | size offset is 0x5D
		(*int16_t)[] VList; // AccessBeyondLength is active (???) | size offset is 0x5D
		uint16_t dataIndex;
		int16_t bitmapId;
		int16_t room;
		int16_t roomBehind;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
		uint8_t polygonType;
		union
		{
			uint8_t ZInterceptDisplacement_size;
			uint8_t YInterceptDisplacement_size;
			uint8_t vertexIds_size;
			uint8_t VList_size;
			uint8_t vertexesCount;
			uint8_t XInterceptDisplacement_size;
			uint8_t UList_size;
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapFacet) == 0x60, "Invalid \"mm7::MapFacet\" structure size");

	struct MapChest // size: 0x14CC
	{
		int16_t chestPicture;
		union
		{
			uint16_t bits;
			struct
			{
				bool trapped : 1;
				bool itemsPlaced : 1;
				bool identified : 1;
			};
		};
		std::array<mm7::Item, 140> items; // MMExt: 1..140, here 0..139
		std::array<int16_t, 140> inventory;
	};
	static_assert(sizeof(mm7::MapChest) == 0x14CC, "Invalid \"mm7::MapChest\" structure size");

	struct MapRoom // size: 0x74
	{
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1;
				bool hasBSP : 1;
			};
		};
		uint16_t floors_size;
		SKIP(2);
		(*int16_t)[] floors; // size offset is 0x4
		uint16_t walls_size;
		SKIP(2);
		(*int16_t)[] walls; // size offset is 0xC
		uint16_t ceils_size;
		SKIP(2);
		(*int16_t)[] ceils; // size offset is 0x14
		uint16_t fluids_size;
		SKIP(2);
		(*int16_t)[] fluids; // size offset is 0x1C
		uint16_t portals_size;
		SKIP(2);
		(*int16_t)[] portals; // size offset is 0x24
		uint16_t drawFacets_size;
		int16_t nonBSPDrawFacetsCount;
		(*int16_t)[] drawFacets; // size offset is 0x2C
		SKIP(8);
		uint16_t cogs_size;
		SKIP(2);
		(*int16_t)[] cogs; // size offset is 0x3C
		uint16_t sprites_size;
		SKIP(2);
		(*int16_t)[] sprites; // size offset is 0x44
		uint16_t markers_size;
		SKIP(2);
		(*int16_t)[] markers; // size offset is 0x4C
		uint16_t lights_size;
		SKIP(2);
		(*int16_t)[] lights; // size offset is 0x54
		SKIP(6);
		int16_t darkness;
		int16_t firstBSPNode;
		SKIP(1);
		uint8_t exitTag;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
	};
	static_assert(sizeof(mm7::MapRoom) == 0x74, "Invalid \"mm7::MapRoom\" structure size");

	struct BaseLight // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		int16_t radius;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t type;
	};
	static_assert(sizeof(mm7::BaseLight) == 0xC, "Invalid \"mm7::BaseLight\" structure size");

	struct MapLight // size: 0x10
	{
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		int16_t radius;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t type;
		union
		{
			uint16_t bits;
			struct
			{
				SKIPBITS(3);
				bool off : 1;
			};
		};
		int16_t brightness;
	};
	static_assert(sizeof(mm7::MapLight) == 0x10, "Invalid \"mm7::MapLight\" structure size");

	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits;
			struct
			{
				bool startState2 : 1;
				bool silentMove : 1;
				bool noSound : 1;
				bool stopped : 1;
			};
		};
		int32_t id;
		int32_t timeStep;
		union
		{
			std::array<int32_t, 3> direction;
			struct
			{
				int32_t directionX;
				int32_t directionY;
				int32_t directionZ;
			};
		};
		int32_t moveLength;
		union
		{
			int32_t openSpeed;
			int32_t speed2;
		};
		union
		{
			int32_t closeSpeed;
			int32_t speed1;
		};
		(*int16_t)[] vertexIds; // size offset is 0x44
		(*int16_t)[] facetIds; // size offset is 0x46
		(*int16_t)[] roomIds; // size offset is 0x48
		(*int16_t)[] facetStartU; // size offset is 0x46
		(*int16_t)[] facetStartV; // size offset is 0x46
		(*int16_t)[] vertexStartX; // size offset is 0x4A
		(*int16_t)[] vertexStartY; // size offset is 0x4A
		(*int16_t)[] vertexStartZ; // size offset is 0x4A
		uint16_t vertexIds_size;
		union
		{
			uint16_t facetIds_size;
			uint16_t facetStartU_size;
			uint16_t facetStartV_size;
		};
		uint16_t roomIds_size;
		union
		{
			uint16_t vertexStartY_size;
			uint16_t vertexStartZ_size;
			uint16_t vertexStartX_size;
		};
		int16_t state;
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapDoor) == 0x50, "Invalid \"mm7::MapDoor\" structure size");

	struct OdmHeader // size: 0xB0
	{
		std::array<char, 32> name; // requires null terminator
		std::array<char, 32> fileName; // requires null terminator
		std::array<char, 31> versionStr; // requires null terminator
		SKIP(65);
		std::array<mm7::TilesetDef, 4> tilesets;
	};
	static_assert(sizeof(mm7::OdmHeader) == 0xB0, "Invalid \"mm7::OdmHeader\" structure size");

	struct TilesetDef // size: 0x4
	{
		std::array<uint8_t, 2> group; // Unknown type
		int16_t offset;
	};
	static_assert(sizeof(mm7::TilesetDef) == 0x4, "Invalid \"mm7::TilesetDef\" structure size");

	struct MapObject // size: 0x70
	{
		int16_t type;
		int16_t typeIndex;
		union
		{
			std::array<int32_t, 3> pos;
			struct
			{
				int32_t x;
				int32_t y;
				int32_t z;
			};
		};
		union
		{
			std::array<int16_t, 3> velocity;
			struct
			{
				int16_t velocityX;
				int16_t velocityY;
				int16_t velocityZ;
			};
		};
		int16_t direction;
		int16_t lookAngle;
		union
		{
			uint16_t bits;
			struct
			{
				bool visible : 1;
				bool temporary : 1;
				bool haltTurnBased : 1;
				bool droppedByPlayer : 1;
				bool ignoreRange : 1;
				bool noZBuffer : 1;
				bool skipAFrame : 1;
				bool attachToHead : 1;
				bool missile : 1;
				bool removed : 1;
			};
		};
		int16_t room;
		int16_t age;
		int16_t maxAge;
		int16_t lightMultiplier;
		mm7::Item item;
		union
		{
			int32_t spell;
			int32_t spellType;
		};
		int32_t spellSkill;
		union
		{
			int32_t spellLevel;
			int32_t spellMastery;
		};
		mm7::SpellEffect* spellEffect;
		int32_t owner;
		int32_t target;
		uint8_t range;
		uint8_t attackType;
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos;
			struct
			{
				int32_t startX;
				int32_t startY;
				int32_t startZ;
			};
		};
	};
	static_assert(sizeof(mm7::MapObject) == 0x70, "Invalid \"mm7::MapObject\" structure size");

	struct MapOutlines // size: 0x14824
	{
		SKIP(4);
		std::array<mm7::MapOutline, 7000> items;
	};
	static_assert(sizeof(mm7::MapOutlines) == 0x14824, "Invalid \"mm7::MapOutlines\" structure size");

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
			float _3;
			float z;
		};
	};
	static_assert(sizeof(mm7::FloatVector) == 0xC, "Invalid \"mm7::FloatVector\" structure size");

	struct MapSprite // size: 0x20
	{
		union
		{
			int16_t decListId;
			std::array<uint8_t, 2> decName; // Unknown type
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool triggerByTouch : 1;
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
				bool showOnMap : 1;
				bool isChest : 1;
				bool invisible : 1;
				bool isObeliskChest : 1;
			};
		};
		union
		{
			std::array<int32_t, 3> pos;
			struct
			{
				int32_t x;
				int32_t y;
				int32_t z;
			};
		};
		int32_t direction;
		int16_t id;
		int16_t event;
		int16_t triggerRadius;
		int16_t directionDegrees;
		int16_t eventVariable;
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapSprite) == 0x20, "Invalid \"mm7::MapSprite\" structure size");

	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // requires null terminator
		std::array<char, 32> name2; // requires null terminator
		union
		{
			uint32_t bits;
			struct
			{
				bool showOnMap : 1;
			};
		};
		uint32_t vertexes_size;
		(*mm7::ModelVertex)[] vertexes; // size offset is 0x44
		union
		{
			uint32_t facets_size;
			uint32_t ordering_size;
		};
		int16_t convexFacetsCount;
		SKIP(2);
		(*mm7::ModelFacet)[] facets; // size offset is 0x4C
		(*int16_t)[] ordering; // size offset is 0x4C
		uint32_t BSPNodes_size;
		(*mm7::BSPNode)[] BSPNodes; // size offset is 0x5C
		SKIP(4);
		int32_t gridX;
		int32_t gridY;
		union
		{
			std::array<int32_t, 3> pos;
			struct
			{
				int32_t x;
				int32_t y;
				int32_t z;
			};
		};
		int32_t minX;
		int32_t minY;
		int32_t minZ;
		int32_t maxX;
		int32_t maxY;
		int32_t maxZ;
		int32_t BFMinX;
		int32_t BFMinY;
		int32_t BFMinZ;
		int32_t BFMaxX;
		int32_t BFMaxY;
		int32_t BFMaxZ;
		int32_t boxCenterX;
		int32_t boxCenterY;
		int32_t boxCenterZ;
		int32_t boundingRadius;
	};
	static_assert(sizeof(mm7::MapModel) == 0xBC, "Invalid \"mm7::MapModel\" structure size");

	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime;
		std::array<char, 12> skyBitmap; // requires null terminator
		union
		{
			uint32_t dayBits;
			struct
			{
				bool foggy : 1;
			};
		};
		int32_t fogRange1;
		int32_t fogRange2;
		SKIP(8);
		uint32_t lastWeeklyTimer;
		uint32_t lastMonthlyTimer;
		uint32_t lastYearlyTimer;
		uint32_t lastDailyTimer;
	};
	static_assert(sizeof(mm7::MapExtra) == 0x38, "Invalid \"mm7::MapExtra\" structure size");

	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex;
		int16_t bitmapIndex;
		int16_t TFTIndex;
		SKIP(2);
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t id;
		int16_t event;
		SKIP(8);
	};
	static_assert(sizeof(mm7::FacetData) == 0x24, "Invalid \"mm7::FacetData\" structure size");

	struct ObjectRef2 // size: 0x2
	{
		union
		{
			uint16_t value;
			std::array<uint8_t, 2> index; // Unknown type
			struct
			{
				std::array<uint8_t, 1> kind; // real size is 0 | Unknown type
			};
		};
	};
	static_assert(sizeof(mm7::ObjectRef2) == 0x2, "Invalid \"mm7::ObjectRef2\" structure size");

	struct BSPNode // size: 0x8
	{
		int16_t frontNode;
		int16_t backNode;
		int16_t coplanarOffset;
		int16_t coplanarSize;
	};
	static_assert(sizeof(mm7::BSPNode) == 0x8, "Invalid \"mm7::BSPNode\" structure size");

	struct BlvHeader // size: 0x88
	{
		SKIP(4);
		std::array<char, 60> name; // requires null terminator
		SKIP(40);
		int32_t facetDataSize;
		int32_t roomDataSize;
		int32_t roomLightDataSize;
		int32_t doorDataSize;
		SKIP(16);
	};
	static_assert(sizeof(mm7::BlvHeader) == 0x88, "Invalid \"mm7::BlvHeader\" structure size");

	struct GameMap // size: 0x76D398
	{
		SKIP(5342836);
		std::array<mm7::BaseLight, 400> spriteLights;
		SKIP(831964);
		std::array<uint8_t, 200> vars;
		SKIP(1016);
		std::array<mm7::MapChest, 20> chests;
		SKIP(24);
		std::array<mm7::MapMonster, 500> monsters;
		SKIP(8);
		std::array<mm7::MapObject, 1000> objects;
		SKIP(8);
		std::array<int32_t, 10> soundSprites;
		SKIP(12016);
		std::array<mm7::MapSprite, 3000> sprites;
		SKIP(24608);
		union
		{
			mm7::OdmHeader outdoorHeader;
			struct
			{
				SKIP(160);
				std::array<mm7::TilesetDef, 4> tilesets;
			};
		};
		uint32_t models_size;
		std::array<std::array<uint8_t, 128>, 128>* heightMap;
		std::array<std::array<uint8_t, 128>, 128>* tileMap;
		std::array<std::array<uint8_t, 128>, 128>* unknownMap;
		SKIP(24);
		(*mm7::MapModel)[] models; // size offset is 0x6A0D20
		uint32_t IDList_size;
		(*mm7::ObjectRef2)[] IDList; // size offset is 0x6A0D4C
		std::array<std::array<int32_t, 128>, 128>* IDOffsets;
		int32_t loadedSkyBitmap;
		SKIP(980);
		uint32_t outdoorSpawns_size;
		(*mm7::SpawnPoint)[] outdoorSpawns; // size offset is 0x6A1130
		int32_t outdoorRefillCount;
		uint32_t outdoorLastRefillDay;
		int32_t outdoorReputation;
		SKIP(4);
		int32_t outdoorSanityFacetsCount;
		int32_t outdoorSanitySpritesCount;
		int32_t sanityModelsCount;
		SKIP(12);
		union
		{
			mm7::MapExtra outdoorExtra;
			struct
			{
				int64_t outdoorLastVisitTime;
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual)
		SKIP(116372);
		int32_t mapStatsIndex;
		SKIP(516);
		std::array<uint8_t, 20> name; // Unknown type
		SKIP(8);
		uint32_t indoorOrOutdoor;
		SKIP(97);
		bool noNPC;
		SKIP(490);
		mm7::BlvHeader indoorHeader;
		uint32_t vertexes_size;
		(*mm7::MapVertex)[] vertexes; // size offset is 0x6BE4B8
		uint32_t facets_size;
		(*mm7::MapFacet)[] facets; // size offset is 0x6BE4C0
		uint32_t facetData_size;
		(*mm7::FacetData)[] facetData; // size offset is 0x6BE4C8
		uint32_t rooms_size;
		(*mm7::MapRoom)[] rooms; // size offset is 0x6BE4D0
		uint32_t lights_size;
		(*mm7::MapLight)[] lights; // size offset is 0x6BE4D8
		uint32_t doors_size;
		std::array<mm7::MapDoor, 200>* doors; // size offset is 0x6BE4E0
		uint32_t BSPNodes_size;
		(*mm7::BSPNode)[] BSPNodes; // size offset is 0x6BE4E8
		mm7::MapOutlines* outlines;
		SKIP(16);
		uint32_t indoorSpawns_size;
		(*mm7::SpawnPoint)[] indoorSpawns; // size offset is 0x6BE504
		int32_t indoorRefillCount;
		uint32_t indoorLastRefillDay;
		int32_t indoorReputation;
		SKIP(4);
		int32_t indoorSanityFacetsCount;
		int32_t indoorSanitySpritesCount;
		std::array<uint8_t, 4> sanityDoorDataSize; // Unknown type
		union
		{
			std::array<uint8_t, 1> spawns; // real size is 0 | Unknown type
			std::array<uint8_t, 1> lastVisitTime; // real size is 0 | Unknown type
			std::array<uint8_t, 1> refillCount; // real size is 0 | Unknown type
			std::array<uint8_t, 1> sanityFacetsCount; // real size is 0 | Unknown type
			std::array<uint8_t, 1> sanitySpritesCount; // real size is 0 | Unknown type
			std::array<uint8_t, 1> lastRefillDay; // real size is 0 | Unknown type
			std::array<uint8_t, 1> reputation; // real size is 0 | Unknown type
		};
		SKIP(11);
		union
		{
			mm7::MapExtra indoorExtra;
			struct
			{
				int64_t indoorLastVisitTime;
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual)
		SKIP(518841);
		uint32_t terNorm_size;
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist;
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId;
		(*mm7::FloatVector)[] terNorm; // size offset is 0x73D390
	};
	static_assert(sizeof(mm7::GameMap) == 0x76D398, "Invalid \"mm7::GameMap\" structure size");
}