#include "pch.h"
#include "EditorPlayerPanel.h"
#include "PlayerStructAccessor.h"

int EditorPlayerPanel::getRosterIndex() const
{
    return rosterIndex;
}

// base class for editor player panels, contains common stuff for them, mainly to ease managing some settings persistence (those which are my addition)
EditorPlayerPanel::EditorPlayerPanel(int playerIndex, int rosterIndex) : playerIndex(playerIndex), rosterIndex(rosterIndex)
{
    wxASSERT_MSG(playerAccessor->forPlayer(playerIndex)->getRosterIndex() == rosterIndex, wxString::Format("Player index (%d) and roster id (%d) don't match", playerIndex, rosterIndex));
}