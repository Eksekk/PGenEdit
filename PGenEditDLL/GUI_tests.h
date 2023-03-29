#pragma once
#include "pch.h"
#include "main.h"

class wxUIActionSimulator;
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

	// this function retrieves messages
	static void processOnlyDllMessages();
	static void processWindowMessages();
	static void scrollIntoView(wxScrolledWindow* scrolled, wxWindow* window);

	class AutoClicker
	{
		wxUIActionSimulator& sim;
		wxScrolledWindow& scrolled;
	public:
		AutoClicker() = delete;
		AutoClicker(wxScrolledWindow& scrolled, wxUIActionSimulator& sim);
		void operator()(wxWindow* window);
	};
};