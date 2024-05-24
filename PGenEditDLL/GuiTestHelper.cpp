#include "pch.h"
#include "GuiTestHelper.h"
#include <wx/uiaction.h>
#include "Asserter.h"
#include "GuiApplication.h"
#include <wx/spinctrl.h>

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
		if (s->AcceptsFocus() && s->CanAcceptFocus())
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
			if (s->AcceptsFocus() && s->CanAcceptFocus())
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

template<typename T>
concept hasClear = requires(T * t) { t->Clear(); };

template<typename T>
concept hasSetValueText = requires(T * t) { t->SetValue(""); };

template<typename T>
concept hasSetValueInteger = requires(T * t) { t->SetValue(0); };

// template<typename T>
// 	requires hasClear<T>
// void tryClearTextFor(T* t)
// {
// 	if (t)
// 	{
// 		t.Clear();
// 	}
// }

template<typename T>
	requires hasSetValueText<T>
void tryClearTextFor(T* t)
{
	if (t)
	{
		t->SetValue("");

		// manually send events for supported control types, because windows messages are sent, but they apparently don't trigger internal value change and old value is kept after adding text via ui action simulator
		if constexpr (SAME(T, wxSpinCtrl))
		{
			wxCommandEvent event(wxEVT_SPINCTRL, t->GetId());
			event.SetEventObject(t);
			t->ProcessWindowEvent(event);
		}
		else if constexpr (SAME(T, wxTextCtrl))
		{
			wxCommandEvent event(wxEVT_TEXT);
			event.SetEventObject(t);
			t->ProcessWindowEvent(event);
		}
		else if constexpr (SAME(T, wxComboBox))
		{
			wxCommandEvent event(wxEVT_COMBOBOX);
			event.SetEventObject(t);
			t->ProcessWindowEvent(event);
		}
		else
		{
			COMPILE_TIME_CONSTEXPR_IF_ERROR();
		}
	}
}

// template<typename T>
// 	requires hasSetValueInteger<T>
// void tryClearTextFor(T* t)
// {
// 	if (t)
// 	{
// 		t->SetValue(0);
// 	}
// }

void GuiTestHelper::autoText(wxWindow* target, const wxString& text)
{
	scrollIntoView(target);
	target->SetFocus();
	// I don't know how to better do trying to clear value of different types without making this a template function, which might be inconvenient
	tryClearTextFor(dynamic_cast<wxTextCtrl*>(target));
	tryClearTextFor(dynamic_cast<wxComboBox*>(target));
	tryClearTextFor(dynamic_cast<wxSpinCtrl*>(target));

	// NO MESSAGES TO PROCESS HERE
	wxYield();
	dispatchWindowMessages();
	target->SetFocus();
	wxASSERT(target->HasFocus());
	wxASSERT_MSG(sim.Text(text), text);
	dispatchWindowMessages();
	wxYield();
	getNearestFocusableSibling(target)->SetFocus();
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