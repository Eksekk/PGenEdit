#include "pch.h"
#include "PlayerPanel.h"
#include "ClassSettingsTab.h"

PlayerPanel::PlayerPanel(wxWindow* parent) : wxPanel(parent)
{
	classSettingsTab = new ClassSettingsTab(this);
}