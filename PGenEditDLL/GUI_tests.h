#pragma once
#include "main.h"

class wxUIActionSimulator;
class Asserter;

class GUI_tests
{
public:
	template<typename Player, typename Game>
	static std::vector<wxString> testGui();

	static std::vector<wxString> testAlignmentRadioBox();

	template<typename Player, typename Game>
	static std::vector<wxString> testEditorSkillsPanel();
	template<typename Player, typename Game>
	static std::vector<wxString> testEditorStatisticsPanel();
};