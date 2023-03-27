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

std::unordered_map<int, PlayerClass> GameData::classes;
std::unordered_map<int, PlayerSkill> GameData::skills;
std::map<int, std::unique_ptr<PlayerPrimaryStat>> GameData::primaryStats;
std::map<int, std::unique_ptr<PlayerResistance>> GameData::resistances;
Json GameData::classDataJson;
Json GameData::skillDataJson;
Json GameData::miscDataJson;

bool GameData::allDataReceived = false;
void GameData::postProcess()
{
    // TODO: fill out once I add parsing for other things
    if (!classes.empty() && !skills.empty() && !primaryStats.empty())
    {
        allDataReceived = true;
    }
}

bool GameData::processClassDataJson(const char* str)
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
                std::string str = tolowerStr(classEntry["alignment"]);
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
                for (int i = 0; i < vec.size(); ++i)
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
            for (int i = 0; i < maxMasteryByClass.size(); ++i)
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
                for (int i = 0; i < vec.size(); ++i)
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
		wxASSERT(GameData::resistances.size() >= (MMVER == 6 ? 5 : 9));
		postProcess();
    }
    catch (nlohmann::json::exception& e)
    {
        wxLogError("Json exception while parsing misc data: %s", e.what());
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
