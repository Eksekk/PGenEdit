#include "pch.h"
#include "main.h"
#include "SaveGameData.h"
#include <GuiApplication.h>
#include "EditorMainWindow.h"
#include "EditorPlayerWindow.h"
#include "PlayerPanel.h"
#include <MainWindow.h>

SaveGameData saveGameData;

static const std::string EDITOR_KEY = "editorJson", GENERATOR_KEY = "generator", PLAYERS_KEY = "playersJson", PLAYER_WINDOW_KEY = "window", PLAYER_PANELS_KEY = "panelsJson";

bool SaveGameData::saveEditorPlayerPanelData(const EditorPlayerPanel& panel)
{
    // {"editorJson": {"playersJson": {"1": {<...window data...>, "panelsJson": {...}}}}}
    Json& editorJson = data[EDITOR_KEY]; // implicitly created
    if (wxGetApp().editorMainWindow)
    {
        auto playerKey = std::to_string(panel.getRosterIndex());
        Json& playerJson = editorJson[PLAYERS_KEY][playerKey];
        if (dynamic_cast<const EditorPlayerWindow*>(&panel))
        {
            if (!panel.persist(playerJson))
            {
                wxLogError("Player window %s persist error", playerKey);
                return false;
            }
        }
        else
        {
            Json& panelsJson = playerJson[PLAYER_PANELS_KEY];
            if (!panel.persist(panelsJson[panel.getJsonPersistKey()]))
            {
                wxLogError("Player panel %s persist error", playerKey);
                return false;
            }
        }
    }
    return true;
}

bool SaveGameData::loadEditorPlayerPanelData(EditorPlayerPanel& panel)
{
    Json& editorJson = data[EDITOR_KEY];
    if (wxGetApp().editorMainWindow)
    {
        Json& playersJson = editorJson[PLAYERS_KEY];
        auto playerKey = std::to_string(panel.getRosterIndex());
        if (dynamic_cast<EditorPlayerWindow*>(&panel))
        {
            if (playersJson.contains(playerKey) && !panel.unpersist(playersJson[playerKey]))
            {
                wxLogError("Player window %s unpersist error", playerKey);
                return false;
            }
        }
        else
        {
            if (playersJson.contains(playerKey) && playersJson[playerKey].contains(PLAYER_PANELS_KEY))
            {
                Json& panelsJson = playersJson[playerKey][PLAYER_PANELS_KEY];
                if (panelsJson.contains(panel.getJsonPersistKey()) && !panel.unpersist(panelsJson[panel.getJsonPersistKey()]))
                {
                    wxLogError("Player panel %s unpersist error", playerKey);
                    return false;
                }
            }
        }
    }
    return true;
}

void SaveGameData::resetPlayerCustomData(int playerIndex, int rosterIndex)
{

}

std::string SaveGameData::saveAllToString()
{
    return data.dump();
}

bool SaveGameData::saveAllToJson(Json& json)
{
    // NO copy constructor, because our data might not be updated - need to query all existing windows etc.
    return false;
}

bool SaveGameData::saveAllToFile(const std::string& path)
{
    return false;
}

bool SaveGameData::saveAllToSaveFile()
{
    return false;
}

bool SaveGameData::loadAllFromString(const std::string& str)
{
    // TODO: proper exception handling etc.
    Json copy = data;
    try
    {
        data = Json::parse(str);
        return true;
    }
    catch (const nlohmann::json::exception& e)
    {
        wxLogError("Parsing json failed: %s", e.what());
        wxLog::FlushActive();
        return false;
    }
}

bool SaveGameData::loadAllFromJson(const Json& json)
{
    return false;
}

bool SaveGameData::loadAllFromFile(const std::string& path)
{
    return false;
}

bool SaveGameData::loadAllFromSaveFile()
{
    return false;
}

bool SaveGameData::updateAllFromUpdatedData()
{
    /*// {"editorJson": {"playersJson": {"1": {"panels": {...}}}}}
    Json& editorJson = data[EDITOR_KEY]; // implicitly created
    if (wxGetApp().editorMainWindow)
    {
        EditorMainWindow* win = wxGetApp().editorMainWindow;
        Json& playersJson = editorJson[PLAYERS_KEY];
        for (auto& playerWindow : win->playerWindows)
        {
            if (playerWindow)
            {
                if (dynamic_cast<EditorPlayerWindow*>(&panel))
                {
                    if (playersJson.contains(PLAYER_WINDOW_KEY))
                    {
                        if
                    }
                }
                auto playerKey = std::to_string(playerWindow->getRosterIndex());
                if (playersJson.contains(playerKey) && playersJson[playerKey].contains(PLAYER_PANELS_KEY))
                {
                    Json& panels = playersJson[playerKey][PLAYER_PANELS_KEY];
                    if (!playerWindow->unpersist(panels[playerKey]))
                    {
                        wxLogError("Player panel %s unpersist error", playerKey);
                    }
                }
            }
        }
    }*/
    Json& generator = data["generator"]; // implicitly created
    if (wxGetApp().mainWindow)
    {
        MainWindow* win = wxGetApp().mainWindow;
        Json& panels = generator["playerPanels"];
        for (auto& playerPanel : win->playerPanels)
        {
            /*auto playerKey = std::to_string(playerWindow->);
            if (playerWindow && panelsJson.contains(playerKey))
            {
                if (!playerWindow->unpersist(panelsJson[playerKey]))
                {
                    wxLogError("Player panel %s unpersist error", playerKey);
                }
            }*/
        }
    }
    // existing panelsJson etc.
    return true;
}