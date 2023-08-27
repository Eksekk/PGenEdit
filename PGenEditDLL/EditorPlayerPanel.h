#pragma once
#include "pch.h"

class EditorPlayerPanel
{
protected:
    int rosterIndex;
public:
    int getRosterIndex() const;
    virtual int setRosterIndex() = 0;
    const int playerIndex;

    EditorPlayerPanel() = delete;
    EditorPlayerPanel(int playerIndex, int rosterIndex);
    virtual void setDefaultCustomSettings() = 0; // if no saved for given player&panel
    virtual std::string getJsonPersistKey() const = 0;
    virtual bool persist(Json& json) const = 0;
    virtual bool unpersist(const Json& json) = 0;
};

