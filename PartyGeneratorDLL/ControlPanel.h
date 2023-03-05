#pragma once
#include "pch.h"
#include "main.h"
class ControlPanel : public wxFrame
{
private:

protected:
	wxScrolledWindow* mainPanel;
	wxButton* showPartyGeneratorWindowButton;
	wxButton* showGameStateEditorWindowButton;
	wxButton* runTestsButton;
	wxButton* flushLogsButton;

public:

	ControlPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Control panel"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~ControlPanel();

	void onCloseWindow(wxCloseEvent& event);
	void onPartyGeneratorButtonClick(wxCommandEvent& event);
	void onGameStateEditorButtonClick(wxCommandEvent& event);
	void onRunTestsClick(wxCommandEvent& event);

	void onFlushLogsClick(wxCommandEvent& event);
	friend class Tests; // to allow ProcessEvent()
};

