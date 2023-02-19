#include "pch.h"
#include "ControlPanel.h"
#include "GuiApplication.h"
#include "MainWindow.h"
#include "EditorMainWindow.h"
#include "Tests.h"
#include "Game.h"

ControlPanel::ControlPanel(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	mainPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	mainPanel->SetScrollRate(35, 35);
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* windowButtonsSizer;
	windowButtonsSizer = new wxBoxSizer(wxHORIZONTAL);

	showPartyGeneratorWindowButton = new wxButton(mainPanel, wxID_ANY, _("Party generator"), wxDefaultPosition, wxSize(150, 40), 0);
	windowButtonsSizer->Add(showPartyGeneratorWindowButton, 0, wxALL, 5);
	showPartyGeneratorWindowButton->Bind(wxEVT_BUTTON, &ControlPanel::onPartyGeneratorButtonClick, this);

	showGameStateEditorWindowButton = new wxButton(mainPanel, wxID_ANY, _("Game state editor"), wxDefaultPosition, wxSize(150, 40), 0);
	windowButtonsSizer->Add(showGameStateEditorWindowButton, 0, wxALL, 5);
	showGameStateEditorWindowButton->Bind(wxEVT_BUTTON, &ControlPanel::onGameStateEditorButtonClick, this);

	mainSizer->Add(windowButtonsSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	mainSizer->Add(0, 50, 0, 0, 5); // spacer

	runTestsButton = new wxButton(mainPanel, wxID_ANY, _("Run tests"), wxDefaultPosition, wxSize(150, 40), 0);
	mainSizer->Add(runTestsButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	runTestsButton->Bind(wxEVT_BUTTON, &ControlPanel::onRunTestsClick, this);

	mainPanel->SetSizer(mainSizer);

	this->Layout();
	this->Centre(wxBOTH);
	Bind(wxEVT_CLOSE_WINDOW, &ControlPanel::onCloseWindow, this);
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::onCloseWindow(wxCloseEvent& event)
{
	if (event.CanVeto())
	{
		event.Veto();
		Show(false);
		return;
	}
	Destroy();
}

extern "C" void __stdcall displayMainWindow(bool visible); // defined in dllApi.cpp
void ControlPanel::onPartyGeneratorButtonClick(wxCommandEvent& event)
{
	displayMainWindow(true);
}

extern "C" void __stdcall displayEditorMainWindow(bool visible); // defined in dllApi.cpp
void ControlPanel::onGameStateEditorButtonClick(wxCommandEvent& event)
{
	displayEditorMainWindow(true);
}

extern "C" void __stdcall runTests(); // defined in dllApi.cpp
void ControlPanel::onRunTestsClick(wxCommandEvent& event)
{
	int answer = wxMessageBox("Run tests again? (that can be slow)", "Confirm", wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_QUESTION | wxCENTRE, this);
	if (answer == wxOK)
	{
		runTests();
	}
}