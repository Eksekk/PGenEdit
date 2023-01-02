#include "pch.h"
#include "PlayerPanel.h"
#include "ClassWindow.h"

PlayerPanel::PlayerPanel(wxWindow* parent) : wxPanel(parent)
{
	classWindow = new ClassWindow(this, wxID_ANY);
}