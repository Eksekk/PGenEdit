#pragma once
#include "pch.h"
#include "main.h"
#include "EditorPlayerPanel.h"

struct SaveGameData;
extern SaveGameData saveGameData;

struct SaveGameData
{
    bool saveEditorPlayerPanelData(const EditorPlayerPanel& panel);
    bool loadEditorPlayerPanelData(EditorPlayerPanel& panel);
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
