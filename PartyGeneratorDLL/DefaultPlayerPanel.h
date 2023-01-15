#pragma once
#pragma once
#include "pch.h"
#include "main.h"
#include <wx/notebook.h>
#include "PlayerPanelBase.h"

class ClassSettingsTab;

class DefaultPlayerPanel : public PlayerPanelBase
{
public:

	DefaultPlayerPanel(wxWindow* parent, PlayerData* linkedGenerationData);
};