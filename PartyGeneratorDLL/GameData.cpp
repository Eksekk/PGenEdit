#include "pch.h"
#include "main.h"
#include "GameData.h"
#include "Utility.h"
#include "Generator.h"
#include "globals.h"
#include <cassert>
#include "Application.h"
#include "PlayerData.h"
#include "PlayerPanel.h"
#include "wx/notebook.h"
#include "ClassSettingsTab.h"

std::unordered_map<int, PlayerClass> GameData::classes;
std::unordered_map<int, PlayerSkill> GameData::skills;

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
    Json json = Json::parse(str);
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
            pdata.classes.createSettings();
        }

        int i = 0;

        generator->createClassSettings();
        assert((wxGetApp().mainWindow->tabs->GetPageCount() == MAX_PLAYERS) && wxString::Format("Invalid notebook tab count %d, expected %d", wxGetApp().mainWindow->tabs->GetPageCount(), MAX_PLAYERS).ToStdString().c_str());
        for (int i = 0; i < wxGetApp().mainWindow->tabs->GetPageCount(); ++i)
        {
            auto tab = static_cast<PlayerPanel*>(wxGetApp().mainWindow->tabs->GetPage(i))->classSettingsTab;
            tab->classWindow->createPanels(generator->playerData[i].classes.defaultSettings, generator->playerData[i].classes.settings);
            ++i;
        }
        wxGetApp().mainWindow->generalClassWindow->createPanels(generator->defaultGlobalClassSettings, generator->globalClassSettings);
    }
    catch (const nlohmann::json::exception& ex)
    {
        wxLogMessage("Exception received! Type: %s\n\nwhat(): %s", typeid(ex).name(), wxString(ex.what()));
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
        Json json = Json::parse(str);
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
        return false;
    }
    postProcess();
    return true;
}
