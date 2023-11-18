#include "pch.h"
#include "main.h"
#include "GameData.h"
#include "Utility.h"
#include "globals.h"
#include "GuiApplication.h"
#include "PlayerData.h"
#include "PlayerPanel.h"
#include "ClassSettingsTab.h"
#include "DefaultPlayerPanel.h"
#include "ClassWindow.h"
#include "MainWindow.h"
#include "Tests.h"
#include "LodStructAccessor.h"
#include "LowLevel.h"
#include "dllApi.h"

std::unordered_map<int, PlayerClass> GameData::classes;
std::unordered_map<int, PlayerSkill> GameData::skills;
std::map<int, std::unique_ptr<PlayerPrimaryStat>> GameData::primaryStats;
std::map<int, std::unique_ptr<PlayerResistance>> GameData::resistances;
std::map<int, std::unique_ptr<PlayerItem>> GameData::items;
Json GameData::classDataJson;
Json GameData::skillDataJson;
Json GameData::miscDataJson;
Json GameData::itemDataJson;
std::vector<std::function<void()>> GameData::callbacks;

Json getJsonFromStr(const char* str)
{
    Json json;
    if (inMM)
    {
        json = json.parse(str);
    }
    else
    {
        std::fstream file(str, std::ios::in);
        json = json.parse(file);
        file.close();
    }
    return json;
}

void GameData::addPostProcessCallback(std::function<void()> callback)
{
    callbacks.push_back(callback);
}

bool GameData::allDataReceived = false;
void GameData::postProcess()
{
    // TODO: fill out once I add parsing for other things
    if (!classes.empty() && !skills.empty() && !primaryStats.empty() && !items.empty())
    {
        allDataReceived = true;
        for (auto& callback : callbacks)
        {
            callback();
        }
    }
}

bool GameData::processClassDataJson(const char* str)
{
    Json json = getJsonFromStr(str);
    classDataJson = json;
    
    //wxLogMessage(wxString(to_string(json)));
    if (json.size() == 0)
    {
        wxLogMessage("invalid json: " + wxString(to_string(json)));
        return false;
    }

    // first pass - create entries for all classes to allow setting pointers to them (promotion/base classes)
    try
    {
        auto& entries = GameData::classes;
        for (auto& classEntry : json)
        {
            //wxLogMessage(wxString(classEntry.type_name()));
            //wxLogMessage(wxString(to_string(classEntry)));
            PlayerClass cls;
            int id = classEntry["id"];
            cls.id = id;
            cls.name = classEntry["name"];
            if (classEntry.contains("tier"))
            {
                cls.tier = classEntry["tier"];
            }
            if (classEntry.contains("alignment"))
            {
                std::string str = stringToLower(classEntry["alignment"]);
                auto itr = alignmentStringToId.find(str);
                if (itr != alignmentStringToId.end())
                {
                    cls.alignment = (Alignment)itr->second;
                }
                else
                {
                    wxLogWarning("Invalid value (%s) for class alignment (class %d - %s)", str, cls.id, cls.name);
                }
            }
            if (classEntry.contains("playerTypeAffinity"))
            {
                for (auto& [playerTypeStr, affinity] : classEntry["playerTypeAffinity"].items())
                {
                    auto itr = plTypeEnumStringToId.find(playerTypeStr);
                    if (itr != plTypeEnumStringToId.end())
                    {
                        cls.playerTypeAffinity.emplace(id, affinity);
                    }
                    else
                    {
                        wxLogWarning("Unknown player type %s for class %d", playerTypeStr, cls.id);
                    }

                }
            }
            else
            {
                wxLogWarning("Class entry of id %d doesn't contain player type affinity field", (int)classEntry["id"]);
            }
            if (classEntry.contains("masteries"))
            {
                const auto& vec = classEntry["masteries"].get<std::vector<int>>();
                for (size_t i = 0; i < vec.size(); ++i)
                {
                    // can't have assert that skill exists because skills might not be processed yet
                    cls.maximumSkillMasteries[i] = static_cast<Mastery>(vec[i]);
                }
            }
            else
            {
                wxLogWarning("Class entry of id %d doesn't contain masteries field", (int)classEntry["id"]);
            }
            entries[id] = std::move(cls);
        }

        // second pass - actually set the pointers

        for (auto& classEntry : json)
        {
            if (classEntry.contains("promotionClasses"))
            {
                auto promos = classEntry["promotionClasses"].get<std::vector<int> >();
                for (int id : promos)
                {
                    auto itr = entries.find(id);
                    if (itr != entries.end())
                    {
                        entries[classEntry["id"]].promotionClasses.push_back(&(itr->second));
                    }
                    else
                    {
                        wxLogWarning("Promotion class %d not found", id);
                    }
                }
            }
            else if ((int)classEntry["tier"] < 2)
            {
                wxLogWarning("Class entry of id %d doesn't contain promotion classes field", (int)classEntry["id"]);
            }

            if (classEntry.contains("baseClass"))
            {
                int baseId = classEntry["baseClass"];
                auto itr = entries.find(baseId);
                if (itr != entries.end())
                {
                    entries[classEntry["id"]].baseClass = &(itr->second);
                    // could also set promotion classes at the same time (inverse), but
                    // I like being slightly verbose here with json than implementing it
                }
                else
                {
                    wxLogWarning("Base class %d not found", baseId);
                }
            }
            else if ((int)classEntry["tier"] > 0)
            {
                wxLogWarning("Class entry of id %d doesn't contain base class field", (int)classEntry["id"]);
            }
        }
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogMessage("Exception received! Type: %s\n\nwhat(): %s", typeid(ex).name(), wxString(ex.what()));
        wxLog::FlushActive();
        return false;
    }
    postProcess();
    return true;

    // TODO, set GameData::classes AND call ClassGenerationData::createSettings for global/per player default/per player specific class settings
    // AND call ClassWindow::createPanels AND create default class settings panel
    // a lot of things to do :)

    // TODO 2: masteries
}

bool GameData::processSkillDataJson(const char* str)
{
    try
    {
        Json json = getJsonFromStr(str);
        skillDataJson = json;
        if (json.size() == 0)
        {
            wxLogMessage("invalid json: " + wxString(to_string(json)));
            return false;
        }

        auto& entries = GameData::skills;
        for (auto& skillEntry : json)
        {
            PlayerSkill sk;
            int id = skillEntry["id"];
            sk.id = id;
            sk.name = skillEntry["name"];
            //assert(!sk.name.empty());
            auto maxMasteryByClass = skillEntry["maxMasteryByClass"].get<std::vector<int> >();
            for (size_t i = 0; i < maxMasteryByClass.size(); ++i)
            {
                sk.maxMasteryByClass.emplace(i, (Mastery)maxMasteryByClass[i]);
            }
            for (auto& skillTypeStr : skillEntry["types"].get<std::vector<std::string> >())
            {
                auto itr = skillTypeEnumStringToId.find(skillTypeStr);
                if (itr != skillTypeEnumStringToId.end())
                {
                    sk.types.push_back((SkillType)itr->second);
                }
                else
                {
                    wxLogWarning("Skill type %s for skill %d not found", skillTypeStr, sk.id);
                }
            }
            sk.doNotGenerate = skillEntry.contains("doNotGenerate");
            if (skillEntry.contains("special"))
            {
                auto itr = skillSpecialEnumStringToId.find(skillEntry["special"]);
                if (itr != skillSpecialEnumStringToId.end())
                {
                    sk.special = (SkillSpecial)itr->second;
                }
                else
                {
                    wxLogWarning("Unknown special %s for skill %d", std::string(skillEntry["special"]), sk.id);
                }
            }
            if (skillEntry.contains("category"))
            {
                auto itr = skillCategoryEnumStringToId.find(skillEntry["category"]);
                if (itr != skillCategoryEnumStringToId.end())
                {
                    sk.category = (SkillCategory)itr->second;
                }
                else
                {
                    wxLogWarning("Unknown category %s for skill %d", std::string(skillEntry["category"]), sk.id);
                }
            }
            else
            {
                wxLogError("Missing category for skill %d", sk.id);
            }
            if (skillEntry.contains("trainCost"))
            {
                auto vec = skillEntry["trainCost"].get<std::vector<int>>();
                for (size_t i = 0; i < vec.size(); ++i)
                {
                    int index = MASTERY_NOVICE + i;
                    sk.trainCost.at(index) = vec[i];
                }
                if (vec.size() != MAX_MASTERY)
                {
                    wxLogWarning("Skill %d has %d trainCost[] size - %d expected", sk.id, vec.size(), MAX_MASTERY);
                }
            }
            else
            {
                wxLogError("Missing train cost for skill %d", sk.id);
            }
            for (auto& [plTypeStr, affinity] : skillEntry["affinityByPlayerType"].items())
            {
                auto itr = plTypeEnumStringToId.find(plTypeStr);
                if (itr != plTypeEnumStringToId.end())
                {
                    sk.affinityByPlayerType.emplace(itr->second, affinity);
                }
                else
                {
                    wxLogWarning("Unknown player type \"%s\" skill %d", plTypeStr, sk.id);
                }
            }
            entries[id] = std::move(sk);
        }
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogMessage("Exception received! Type: %s\n\nwhat(): %s", typeid(ex).name(), wxString(ex.what()));
        wxLog::FlushActive();
        return false;
    }
    postProcess();
    return true;
}

bool GameData::processMiscDataJson(const char* str)
{
    try
    {
        Json json = getJsonFromStr(str);
		miscDataJson = json;

		auto stats = json["primaryStats"].get<std::unordered_map<std::string, Json>>();
		for (const auto& [id, data] : stats)
		{
			GameData::primaryStats.emplace(std::stoi(id), std::make_unique<PlayerPrimaryStat>(std::stoi(id), data["name"], data["blackPotionId"]));
		}
		wxASSERT(GameData::primaryStats.size() == 7);

		auto resists = json["resistances"].get<std::unordered_map<std::string, Json>>();
		for (const auto& [id, data] : resists)
		{
			int useId = INVALID_ID;
			if (data.contains("builtinSpecial"))
			{
				wxString str = (std::string)data["builtinSpecial"];
				if (str.CmpNoCase("light"))
				{
					useId = STAT_LIGHT_RESISTANCE;
				}
				else if (str.CmpNoCase("dark"))
				{
					useId = STAT_DARK_RESISTANCE;
				}
				else
				{
					wxFAIL_MSG(wxString::Format("Unknown builtinSpecial: %s", str));
				}
			}
			else
			{
				useId = std::stoi(id);
			}
			// TODO: resistance spells
			GameData::resistances.emplace(useId, std::make_unique<PlayerResistance>(useId, data["name"], data["exclusive"], nullptr, nullptr));
		}
		wxASSERT(GameData::resistances.size() >= (MMVER == 6 ? 5U : 9U));
		postProcess();
    }
    catch (const nlohmann::json::exception& e)
    {
        wxLogError("Json exception while parsing misc data: %s", e.what());
        wxLog::FlushActive();
        return false;
    }
    return true;
}

struct CacheKey
{
    uint8_t* ptr;
    int bitWidth;
    inline bool operator==(const CacheKey& b) const
    {
        return ptr == b.ptr && bitWidth == b.bitWidth;
    }
};

namespace std
{
    template<>
    struct hash<CacheKey>
    {
        size_t operator()(const CacheKey& val) const
        {
            return hash<uint8_t*>()(val.ptr) ^ hash<int>()(val.bitWidth);
        }
    };
}

void GameData::fillInItemImages()
{
    // I considered multiple times to move actual loading code into PlayerItem, but decided against it, because, to be fully decoupled,
    // I would need to iterate over lod once to find out if bitmap was already loaded, load it if not, destroy bitmap and call Cleanup() function **for every item**
    // this is a ton of overhead, and I think putting code here is better
    std::map<std::string, std::vector<int>> imageIdToNameMap;
    // NEED TO UNLOAD BITMAPS, otherwise crash might happen when loading any other from same lod, due to too high loaded bitmap count
    std::unordered_set<std::string> loaded; // store already-loaded bitmaps, to unload only those loaded by me
    LodStructAccessor::forEachLodBitmapDo([&](const AnyLodBitmapStruct auto* bitmapPtr, int i)
        {
            loaded.insert(stringToLower(stringFromArray(bitmapPtr->name)));
        }, BITMAPS_LOD_ICONS);
    std::vector<int> indexesToFree;
    for (auto& [id, item] : items)
    {
        std::string str = stringToLower(item->pictureName);
        if (!loaded.contains(str))
        {
            indexesToFree.push_back(lodAccessor->loadBitmap(str.data(), BITMAPS_LOD_ICONS));
            loaded.insert(str);
        }
        imageIdToNameMap[str].push_back(id);
    }
    struct CacheValue
    {
        std::vector<uint8_t> red, green, blue;
    }; static_assert(std::is_aggregate_v<CacheKey>);
    std::unordered_map<CacheKey, CacheValue/*, pfr::hash<CacheKey>, pfr::equal_to<CacheKey>*/> cache;
    LodStructAccessor::forEachLodBitmapDo([&](const AnyLodBitmapStruct auto* bitmapPtr)
    {
        std::string name = stringToLower(bitmapPtr->name.data());
        int width = bitmapPtr->width, height = bitmapPtr->height;
        if (!imageIdToNameMap.contains(name))
        {
            return;
        }
        uint8_t* _palettePtr;
        int paletteBitWidth; // 16, 24, (32?)
        if (bitmapPtr->palette)
        {
            _palettePtr = (uint8_t*)bitmapPtr->palette;
            paletteBitWidth = 8; // ???
            __debugbreak();
        }
        else if (bitmapPtr->palette24)
        {
            _palettePtr = (uint8_t*)bitmapPtr->palette24;
            paletteBitWidth = 8;
        }
        else if (bitmapPtr->palette16)
        {
            _palettePtr = (uint8_t*)bitmapPtr->palette16;
            paletteBitWidth = 5;
        }
        else
        {
            wxFAIL;
            assert(false);
        }
        const uint8_t* palettePtr = _palettePtr;
        // dump(Game.IconsLod.Bitmaps[Game.IconsLod:LoadBitmap"item001"])
        static uint8_t red[256], blue[256], green[256];
        //auto itr = cache.find(CacheKey{ _palettePtr, paletteBitWidth });
        if (true)//(itr == cache.end())
        {
            // extract palette colors
            // three vectors at index "i" contain constituent RGB colors of palette entry (max 256 entries)
            // each palette color value has "paletteBitWidth" bits to represent the value
            //red.resize(256);
            //blue.resize(256);
            //green.resize(256);

            // couuuld simply read dword from memory, but to be 100% sure no invalid memory access happens, let's use a small buffer
            //uint8_t entry[4];
            const int entrySize = std::ceil(paletteBitWidth * 3 / 8.0);
            const dword_t mask = (1 << paletteBitWidth) - 1;

            // 10110100 01101100
            // r 10110, b 10001, g 10110
            // 01101100 10110100
            // r 01101, b 10010, g 11010
            const int scale = std::max(8 - paletteBitWidth, 0); // scale lower ranges to one byte
            for (int i = 0; i < 256; ++i)
            {
                //uint32_t data = dword(entry);
                dword_t data = dword(palettePtr + i * entrySize);
                //data = byteswap(data);
                // extract bit groups
                blue[i] = (data & mask) << scale;
                red[i] = ((data >> paletteBitWidth) & mask) << scale;
                green[i] = ((data >> (paletteBitWidth * 2)) & mask) << scale;
            }
            //cache[CacheKey{_palettePtr, paletteBitWidth}] = CacheValue{ red, green, blue };
        }
        else
        {
            // NEVER called - console script confirmed each palette has distinct address, I thought they might be shared
            
            //std::tie(red, green, blue) = pfr::structure_to_tuple(itr->second);
        }

        // MALLOC REQUIRED, wxWidgets will take care of deletion
        uint8_t* data = (uint8_t*)malloc(width * height * 3); // RGBRGBRGBRGB... data
        // TODO: wxWidgets supports transparency mask
        uint8_t* alpha = (uint8_t*)malloc(width * height);
        memset(alpha, 255, width * height);
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                dword_t off = (dword_t)data + (y * width + x) * 3;
                dword_t pal = byte(bitmapPtr->image + x + y * width);
                byte(off) = red[pal];
                byte(off + 1) = green[pal];
                byte(off + 2) = blue[pal];
                //img.SetRGB(x, y, red[pal], blue[pal], green[pal]);

                if (pal == 0) // first color in palette is transparency color
                {
                    //img.SetAlpha(x, y, 255);
                    byte((dword_t)alpha + y * width + x) = 0;
                }
            }
        }
        wxImage img(width, height, data, alpha);

        wxBitmap* bmp = nullptr;
        for (int itemId : imageIdToNameMap[name])
        {
            PlayerItem* item = items.at(itemId).get();
            item->inventoryHeight = std::ceil(height / 45.0);
            item->inventoryWidth = std::ceil(width / 45.0);
            if (!bmp)
            {
                bmp = new wxBitmap(img); // actual image-to-bitmap conversion is only performed once
                item->image = bmp;
            }
            else
            {
                item->image = new wxBitmap(*bmp); // all subsequent images use copy constructor
            }
        }
    }, BITMAPS_LOD_ICONS);

    lodAccessor->forLodBitmapIndexesDo([](AnyLodBitmapStruct auto* bmp)
        {
            lodAccessor->destroyBitmap(bmp);
        }, BITMAPS_LOD_ICONS, indexesToFree);
    lodAccessor->cleanupBitmaps(BITMAPS_LOD_ICONS);
}

bool GameData::processItemDataJson(const char* str)
{
    try
    {
        // this is post init, because it requires filled in skill information, and I don't want to depend on loading order
        addPostInitCallback([] {
            int itemIndex = 0;
            itemAccessor->forEachItemTxtDo([&](const AnyItemsTxtItemStruct auto* entry) -> void
                {
                    ++itemIndex; // TODO: pass extra index argument to callback functions
                    if (!GameData::items.contains(itemIndex))
                    {
                        GameData::items[itemIndex] = std::move(std::make_unique<PlayerItem>());
                    }
                    auto& item = GameData::items.at(itemIndex);
                    int skIdx;
                    if constexpr (SAME_BASE_TYPE(entry, mm6::ItemsTxtItem))
                    {
                        //showDeducedType(entry);
                        skIdx = entry->skill[0] - 1; // is an array in this case (custom type)
                    }
                    else
                    {
                        skIdx = entry->skill;
                    }
                    // club has fake skill one higher than normal highest
                    item->skill = skIdx < (int)GameData::skills.size() ? &GameData::skills.at(skIdx) : nullptr;
                    item->pictureName = entry->picture;
                    item->id = itemIndex;
                    item->name = entry->name;
                    item->value = entry->value;
                    // 0 = normal,  1 = artifact,  2 = relic,  3 = special
                    item->isArtifact = entry->material == 1 || entry->material == 2;
                    item->itemTypeActual = entry->equipStat + 1;

                    items.emplace(itemIndex, std::move(item));
                });

            fillInItemImages();
        });
        Json json = getJsonFromStr(str);

        for (const auto& [indexStr, data] : json.get<std::map<std::string, Json>>())
        {
            int itemIndex = stoi(indexStr);
            if (!GameData::items.contains(itemIndex))
            {
                GameData::items[itemIndex] = std::move(std::make_unique<PlayerItem>());
            }
            auto& itemPtr = GameData::items.at(itemIndex);
            // TODO: fill other info
        }

        postProcess();
    }
    catch (const JsonException& ex)
    {
        wxLogError("Exception received: %s", ex.what());
        wxLog::FlushActive();
        return false;
    }
    return true;
}

extern "C" bool checkIsInGame();
void updatePartySizeAndPlayerPtrs(); // defined in dllApi.cpp
void GameData::updateIsInGameAndPartySize()
{
    if (Tests::testingNow) return; // don't overwrite party size with 0 if we're not in game and testing now
	inGame = checkIsInGame();
	if (inGame && MMVER == 8)
	{
		updatePartySizeAndPlayerPtrs();
	}
	else if (inGame)
	{
		CURRENT_PARTY_SIZE = 4;
	}
	else
	{
		CURRENT_PARTY_SIZE = 0;
	}
}
