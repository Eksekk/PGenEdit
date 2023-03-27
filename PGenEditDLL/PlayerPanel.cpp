#include "pch.h"
#include "PlayerPanel.h"

PlayerPanel::PlayerPanel(wxWindow* parent, PlayerData* linkedGenerationData) : PlayerPanelBase(parent, linkedGenerationData)
{
	useDefaultsCheckbox = new wxCheckBox(this, wxID_ANY, _("Use defaults"));
	useDefaultsCheckbox->SetToolTip(_("If set, all settings will be taken from \"default\" tab"));

	mainSizer->Prepend(useDefaultsCheckbox, 0, wxALL, 5);
}