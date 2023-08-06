#include "pch.h"
#include "GuiTestHelper.h"
#include <wx/uiaction.h>
#include "Asserter.h"
#include "GuiApplication.h"

void GuiTestHelper::scrollIntoView(wxWindow* window)
{
	int scrollRateY = 0;
	scrolled.GetScrollPixelsPerUnit(nullptr, &scrollRateY);

	const wxPoint windowPos = scrolled.CalcUnscrolledPosition(window->GetPosition());
	scrolled.Scroll(0, windowPos.y / scrollRateY);
}

wxWindow* GuiTestHelper::getNearestFocusableSibling(wxWindow* origin)
{
	bool end = false;
	wxWindow* s = origin;
	while ((s = s->GetPrevSibling()) != nullptr)
	{
		if (s->AcceptsFocus())
		{
			end = true;
			break;
		}
	}
	if (!end)
	{
		s = origin;
		while ((s = s->GetNextSibling()) != nullptr)
		{
			if (s->AcceptsFocus())
			{
				end = true;
				break;
			}
		}
	}
	assert(end);
	return s;
}

GuiTestHelper::GuiTestHelper::GuiTestHelper(wxScrolledWindow& scrolled, wxUIActionSimulator& sim, Asserter& asserter)
	: scrolled(scrolled), sim(sim), myasserter(asserter), tmpLoop(new FakeEventLoop) {}

GuiTestHelper::~GuiTestHelper()
{
	delete tmpLoop;
}

void GuiTestHelper::autoClick(wxWindow* window)
{
	scrollIntoView(window);
	sim.MouseMove(window->GetScreenPosition() + wxPoint(5, 5));
	sim.MouseClick();
	dispatchWindowMessages();
}

void GuiTestHelper::autoText(wxWindow* target, const wxString& text)
{
	scrollIntoView(target);
	target->SetFocus();
	dispatchWindowMessages();
	wxASSERT_MSG(sim.Text(text), text);
	getNearestFocusableSibling(target)->SetFocus();
	dispatchWindowMessages();
	wxYield();
}

// NOT WORKING
// keybd_event doesn't generate "arrow up pressed" window message
void GuiTestHelper::autoSelect(wxChoice* target, const wxString& text)
{
	scrollIntoView(target);
	target->SetFocus();
	dispatchWindowMessages();
	//wxMessageBox("Set breakpoint in wxYield() now");
	// a hack, but temporary event loop is needed for wxwidgets
	wxEventLoop::SetActive(tmpLoop);
	// IMPORTANT
	// I conditionally revert selection to old with skill choosers, and simulator first sets selection to 0, then increments it
	// with reverting that won't work
	target->SetSelection(0);
	wxASSERT_MSG(sim.Select(text), text);
	wxEventLoop::SetActive(nullptr);
	getNearestFocusableSibling(target)->SetFocus();
	dispatchWindowMessages();
	wxYield();
}

void GuiTestHelper::dispatchWindowMessages()
{
	// temporary message loop to fix wxYield() not working due to no direct event loop
	// for my dll
	MSG msg;
	while (PeekMessageA(&msg, 0, 0, 0, true))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

bool FakeEventLoop::YieldFor(long eventsToProcess)
{
	GuiTestHelper::dispatchWindowMessages();
	return wxEventLoop::YieldFor(eventsToProcess);
}