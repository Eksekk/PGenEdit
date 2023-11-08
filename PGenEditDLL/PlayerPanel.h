#pragma once
#include "main.h"
#include "PlayerPanelBase.h"

class PlayerData;

class PlayerPanel : public PlayerPanelBase
{
public:

	PlayerPanel(wxWindow* parent, PlayerData* linkedGenerationData);
	wxCheckBox* useDefaultsCheckbox;
};