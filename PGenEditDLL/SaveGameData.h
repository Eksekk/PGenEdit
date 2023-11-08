#pragma once
#include "main.h"
#include "EditorPlayerPanel.h"

struct SaveGameData;
extern SaveGameData saveGameData;
class InventoryCtrl;

struct SaveGameData
{
    bool saveEditorPlayerPanelData(const EditorPlayerPanel& panel);
    bool loadEditorPlayerPanelData(EditorPlayerPanel& panel);
    bool saveInventoryControl(const InventoryCtrl& ctrl);
    bool loadInventoryControl(InventoryCtrl& ctrl);
    void resetPlayerCustomData(int playerIndex, int rosterIndex); // for use in situations like if mercenary is generated in merge

    Json data;

    std::string saveAllToString();
    bool saveAllToJson(Json& json);
    bool saveAllToFile(const std::string& path);
    bool saveAllToSaveFile();

    bool loadAllFromString(const std::string& str);
    bool loadAllFromJson(const Json& json);
    bool loadAllFromFile(const std::string& path);
    bool loadAllFromSaveFile();

    // updates everything that might need updating with new data
    bool updateAllFromUpdatedData();
};
