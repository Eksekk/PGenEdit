#include "pch.h"
#include "main.h"
#include "ClassSettingsTab.h"
#include "ClassWindow.h"

ClassSettingsTab::ClassSettingsTab(wxWindow* parent) : wxPanel(parent)
{
	classWindow = new ClassWindow(this);
}
