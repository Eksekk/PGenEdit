#pragma once
#include "pch.h"
#include "main.h"

class GUI_tests
{
public:
	template<typename Player, typename Game>
	static std::vector<wxString> testGui();

	static std::vector<wxString> testAlignmentRadioBox();

	template<typename Player, typename Game>
	static std::vector<wxString> testEditorSkillsPanel();
};