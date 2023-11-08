#pragma once
#include "main.h"
#include <wx/evtloop.h>

class wxUIActionSimulator;
class Asserter;
class wxScrolledWindow;

class FakeEventLoop : public wxEventLoop
{
public:
	bool YieldFor(long eventsToProcess) override;
};

class GuiTestHelper
{
	wxUIActionSimulator& sim;
	wxScrolledWindow& scrolled;
	Asserter& myasserter;
	wxWindow* getNearestFocusableSibling(wxWindow* origin);
	FakeEventLoop* tmpLoop;
public:
	GuiTestHelper() = delete;
	GuiTestHelper(wxScrolledWindow& scrolled, wxUIActionSimulator& sim, Asserter& asserter);
	~GuiTestHelper();
	void autoClick(wxWindow* window);
	void autoText(wxWindow* target, const wxString& text);
	void autoSelect(wxChoice* target, const wxString& text);

	static void dispatchWindowMessages();
	void scrollIntoView(wxWindow* window);
};