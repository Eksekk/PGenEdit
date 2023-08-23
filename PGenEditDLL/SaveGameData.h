#pragma once
#include "pch.h"
#include "main.h"
#include "EditorPlayerPanel.h"

struct SaveGameData
{
    void saveEditorPlayerPanelData(const EditorPlayerPanel& panel);
    bool loadEditorPlayerPanelData(EditorPlayerPanel& panel);
    void resetPlayerCustomData(int playerIndex, int rosterIndex); // for use in situations like if mercenary is generated in merge
};