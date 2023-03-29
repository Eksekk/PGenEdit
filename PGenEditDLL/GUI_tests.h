#pragma once
#include "pch.h"
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

	static void dispatchWindowMessages();
	static void scrollIntoView(wxScrolledWindow* scrolled, wxWindow* window);

	class GuiTestHelper
	{
		wxUIActionSimulator& sim;
		wxScrolledWindow& scrolled;
		Asserter& myasserter;
	public:
		GuiTestHelper() = delete;
		GuiTestHelper(wxScrolledWindow& scrolled, wxUIActionSimulator& sim, Asserter& asserter);
		void autoClick(wxWindow* window);
		void autoText(wxWindow* target, const wxString& text);
		void autoSelect(wxChoice* target, const wxString& text);
// 		template<typename Player, typename FieldType>
// 		void testLinkedSpinCtrl(wxSpinCtrl* ctrl, FieldType Player::* fieldPointer);
	};
};