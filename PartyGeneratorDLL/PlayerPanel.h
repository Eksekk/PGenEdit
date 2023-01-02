#pragma once
#include "pch.h"
#include "main.h"

class ClassWindow;

class PlayerPanel : public wxPanel
{
public:
	ClassWindow* classWindow;

	PlayerPanel(wxWindow* parent);
};

