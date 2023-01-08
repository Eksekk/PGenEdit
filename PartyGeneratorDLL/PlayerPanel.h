#pragma once
#include "pch.h"
#include "main.h"

class ClassSettingsTab;

class PlayerPanel : public wxPanel
{
public:
	ClassSettingsTab* classSettingsTab;

	PlayerPanel(wxWindow* parent);
};

