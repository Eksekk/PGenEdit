#pragma once
#include "pch.h"
#include "main.h"

class ClassWindow;
class ClassSettingsTab : public wxPanel
{
public:

	ClassSettingsTab(wxWindow* parent);
	ClassWindow* classWindow;

	/*int id = INVALID_ID; // not used in general settings
	int weight;
	std::vector<int> tierWeights;
	Alignment alignment;
	bool disabled; // not used in general settings
	bool equalChances;*/
};

