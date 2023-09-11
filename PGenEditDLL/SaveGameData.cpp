#include "pch.h"
#include "main.h"
#include "SaveGameData.h"
#include <GuiApplication.h>
#include "EditorMainWindow.h"
#include "EditorPlayerWindow.h"
#include "PlayerPanel.h"
#include <MainWindow.h>
#include "HookParams.h"
#include "InventoryCtrl.h"

SaveGameData saveGameData;

static const std::string JSON_KEY_EDITOR = "editorJson", JSON_KEY_GENERATOR = "generator", JSON_KEY_PLAYERS = "playersJson", JSON_KEY_PLAYER_WINDOW = "window", JSON_KEY_PLAYER_PANELS = "panelsJson";
static const std::string JSON_KEY_INVENTORY_CONTROLS = "inventoryControls", JSON_KEY_MAP_CHESTS = "mapChests";

bool SaveGameData::saveEditorPlayerPanelData(const EditorPlayerPanel& panel)
{
    // {"editorJson": {"playersJson": {"1": {<...window data...>, "panelsJson": {...}}}}}
    Json& editorJson = data[JSON_KEY_EDITOR]; // implicitly created
    if (wxGetApp().editorMainWindow)
    {
        auto playerKey = std::to_string(panel.getRosterIndex());
        Json& playerJson = editorJson[JSON_KEY_PLAYERS][playerKey];
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
            Json& panelsJson = playerJson[JSON_KEY_PLAYER_PANELS];
            // operator[] used as getter assigns NULL if key is not present, not object
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
    Json& editorJson = data[JSON_KEY_EDITOR];
    if (wxGetApp().editorMainWindow)
    {
        Json& playersJson = editorJson[JSON_KEY_PLAYERS];
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
            if (playersJson.contains(playerKey) && playersJson[playerKey].contains(JSON_KEY_PLAYER_PANELS))
            {
                Json& panelsJson = playersJson[playerKey][JSON_KEY_PLAYER_PANELS];
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

bool SaveGameData::saveInventoryControl(const InventoryCtrl& ctrl)
{
    // TODO: won't work for generator, invalid json path
    try
    {
        Json& dest = data[JSON_KEY_EDITOR][JSON_KEY_INVENTORY_CONTROLS];
        if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&ctrl.inventoryType))
        {
            Json& invCtrlJson = dest[JSON_KEY_PLAYERS][std::to_string(ref->rosterIndex)];
            ctrl.persist(invCtrlJson);
        }
        else if (const MapChestRef* ref = std::get_if<MapChestRef>(&ctrl.inventoryType))
        {
            Json& invCtrlJson = dest[JSON_KEY_MAP_CHESTS][tolowerStr(ref->mapName)][ref->chestId];
            ctrl.persist(invCtrlJson);
        }
        else
        {
            wxFAIL;
        }
    }
    catch (const JsonException& ex)
    {
        wxLogError("Inventory control persist error: '%s'", ex.what());
    }
    return false;
}

bool SaveGameData::loadInventoryControl(InventoryCtrl& ctrl)
{
    try
    {
        const Json& src = data[JSON_KEY_EDITOR][JSON_KEY_INVENTORY_CONTROLS];
        if (const PlayerInventoryRef* ref = std::get_if<PlayerInventoryRef>(&ctrl.inventoryType))
        {
            std::string pointer = wxString::Format("%s/%s", JSON_KEY_PLAYERS, std::to_string(ref->rosterIndex)).ToStdString();
            if (src.contains(pointer))
            {
                ctrl.unpersist(src.at(pointer));
            }
            return true;
        }
        else if (const MapChestRef* ref = std::get_if<MapChestRef>(&ctrl.inventoryType))
        {
            std::string pointer = wxString::Format("%s/%s/%s", JSON_KEY_MAP_CHESTS, tolowerStr(ref->mapName), std::to_string(ref->chestId)).ToStdString();
            if (src.contains(pointer))
            {
                ctrl.unpersist(src.at(pointer));
            }
            return true;
        }
        else
        {
            wxFAIL;
        }
    }
    catch (const JsonException& ex)
    {
        wxLogError("Inventory control unpersist error: '%s'", ex.what());
    }
    return false;
}

void SaveGameData::resetPlayerCustomData(int playerIndex, int rosterIndex)
{

}

std::string SaveGameData::saveAllToString()
{
    saveAllToJson(data);
    return data.dump();
}

bool SaveGameData::saveAllToJson(Json& json)
{
    json.clear();
    HookParams::persist(json["hookParams"]);
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
        data = copy;
        return false;
    }
}

bool SaveGameData::loadAllFromJson(const Json& json)
{
    HookParams::unpersist(json["hookParams"]);
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
    Json& editorJson = data[JSON_KEY_EDITOR]; // implicitly created
    if (wxGetApp().editorMainWindow)
    {
        EditorMainWindow* win = wxGetApp().editorMainWindow;
        Json& playersJson = editorJson[JSON_KEY_PLAYERS];
        for (auto& playerWindow : win->playerWindows)
        {
            if (playerWindow)
            {
                if (dynamic_cast<EditorPlayerWindow*>(&panel))
                {
                    if (playersJson.contains(JSON_KEY_PLAYER_WINDOW))
                    {
                        if
                    }
                }
                auto playerKey = std::to_string(playerWindow->getRosterIndex());
                if (playersJson.contains(playerKey) && playersJson[playerKey].contains(JSON_KEY_PLAYER_PANELS))
                {
                    Json& panels = playersJson[playerKey][JSON_KEY_PLAYER_PANELS];
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