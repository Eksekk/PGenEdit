#pragma once
#include "pch.h"
#include "PersistablePlayerPanel.h"
class EditorPlayerPanel : public PersistablePlayerPanel
{
protected:
    int rosterIndex;
public:
    int getRosterIndex();
    virtual int setRosterIndex() = 0;
    const int playerIndex;

    EditorPlayerPanel() = delete;
    EditorPlayerPanel(int playerIndex, int rosterIndex);
    virtual void setDefaultCustomSettings() = 0; // if no saved for given player&panel
};

