#include "pch.h"
#include "main.h"
#include "GameData.h"
#include "Utility.h"
#include "Generator.h"
#include "globals.h"
#include "GuiApplication.h"
#include "PlayerData.h"
#include "PlayerPanel.h"
#include "wx/notebook.h"
#include "ClassSettingsTab.h"
#include "DefaultPlayerPanel.h"
#include "ClassWindow.h"
#include "MainWindow.h"

std::unordered_map<int, PlayerClass> GameData::classes;
std::unordered_map<int, PlayerSkill> GameData::skills;
Json GameData::classDataJson;
Json GameData::skillDataJson;

bool GameData::allDataReceived = false;
void GameData::postProcess()
{
    // TODO: fill out once I add parsing for other things
    if (!classes.empty() && !skills.empty())
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

        for (auto& pdata : generator->playerData)
        {
            pdata->classes.createSettings();
        }

        generator->defaultPlayerData.classes.createSettings();
        assert((wxGetApp().mainWindow->tabs->GetPageCount() == MAX_PLAYERS + MainWindow::FIRST_PLAYER_PAGE) && wxString::Format("Invalid notebook tab count %d, expected %d", wxGetApp().mainWindow->tabs->GetPageCount(), MAX_PLAYERS + MainWindow::FIRST_PLAYER_PAGE).ToStdString().c_str());
        for (int i = MainWindow::FIRST_PLAYER_PAGE; i < wxGetApp().mainWindow->tabs->GetPageCount(); ++i)
        {
            auto page = static_cast<PlayerPanel*>(wxGetApp().mainWindow->tabs->GetPage(i));
            auto tab = page->classSettingsTab;
            tab->classWindow->createPanels(page->linkedGenerationData->classes.defaultSettings, page->linkedGenerationData->classes.settings);
            ++i;
        }
        auto page = static_cast<DefaultPlayerPanel*>(wxGetApp().mainWindow->tabs->GetPage(MainWindow::DEFAULT_PLAYER_PAGE));
        auto tab = page->classSettingsTab;
        tab->classWindow->createPanels(page->linkedGenerationData->classes.defaultSettings, page->linkedGenerationData->classes.settings);
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
                    int index = NOVICE + i;
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

void GameData::reparse(const char* data[DATA_TYPE_COUNT])
{
    throw std::runtime_error("Not supported");
}