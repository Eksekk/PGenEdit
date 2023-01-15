#pragma once
#include "pch.h"
#include "main.h"
#include <wx/notebook.h>
#include "PlayerPanelBase.h"

class ClassSettingsTab;

class PlayerPanel : public PlayerPanelBase
{
public:

	PlayerPanel(wxWindow* parent, PlayerData* linkedGenerationData);
	wxCheckBox* useDefaultsCheckbox;
};