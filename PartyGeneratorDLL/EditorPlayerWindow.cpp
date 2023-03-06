#include "pch.h"
#include "EditorPlayerWindow.h"
#include <wx/notebook.h>
#include "PlayerStructAccessor.h"
#include "EditorSkillsPanel.h"
#include "EditorMainWindow.h"
#include "GuiApplication.h"

EditorPlayerWindow::EditorPlayerWindow(wxWindow* parent, int playerIndex) : wxFrame(parent, wxID_ANY, "Edit " + playerAccessor->getNameOrDefault(playerIndex),
	wxDefaultPosition, wxSize(770, 670), wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL), playerIndex(playerIndex)
{
	mainWindow = dynamic_cast<EditorMainWindow*>(parent);
	wxASSERT(mainWindow);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetMinSize(wxSize(600, 800));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	updateTimer = new wxTimer(this);
	Bind(wxEVT_TIMER, &EditorPlayerWindow::onUpdateTimer, this);
	updateTimer->Start(350, wxTIMER_CONTINUOUS);

	mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	mainSizer = new wxBoxSizer(wxVERTICAL);
	mainPanel->SetSizer(mainSizer);

	tabs = new wxNotebook(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	static const wxSize tabsImageSize = wxSize(50, 30);
	wxImageList* tabsImages = new wxImageList(tabsImageSize.GetWidth(), tabsImageSize.GetHeight());
	tabs->AssignImageList(tabsImages);
	appearancePanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(appearancePanel, _("Appearance"), false);
	propertiesPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(propertiesPanel, _("Properties"), false);
	statisticsPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(statisticsPanel, _("Statistics"), true);
	skillsPanel = new EditorSkillsPanel(tabs, playerIndex);
	tabs->AddPage(skillsPanel, _("Skills"), false);
	spellsPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(spellsPanel, _("Spells"), false);
	itemsPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(itemsPanel, _("Items"), false);
	conditionsAndBuffsPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(conditionsAndBuffsPanel, _("Conditions/buffs"), false);
	awardsPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	tabs->AddPage(awardsPanel, _("Awards"), false);

	mainSizer->Add(tabs, 1, wxEXPAND | wxALL, 5);

	mainPanel->SetSizer(mainSizer);
	mainPanel->Layout();
	mainSizer->Fit(mainPanel);

	this->Layout();
	this->Centre(wxBOTH);

	Bind(wxEVT_CLOSE_WINDOW, &EditorPlayerWindow::onCloseWindow, this);
}

// TODO: three windows have update timer now. Do one timer with multiple Bind()s?
void EditorPlayerWindow::onUpdateTimer(wxTimerEvent& event)
{
	SetTitle("Edit " + playerAccessor->getNameOrDefault(playerIndex));
}

EditorPlayerWindow::~EditorPlayerWindow()
{
	delete updateTimer;
}

void EditorPlayerWindow::onCloseWindow(wxCloseEvent& event)
{
	mainWindow->playerWindows[playerIndex] = nullptr;
	wxASSERT(Destroy());
	//wxGetApp().ProcessIdle(); // important because otherwise window won't ever be destroyed
	// (lack of "event loop", top level window destruction is done in idle events)
	
	// onWakeUpIdle() crashes process (no event loop!)
	//wxGetApp().ProcessPendingEvents();
	//wxGetApp().DeletePendingObjects();
	//CallAfter([] {wxGetApp().DeletePendingObjects(); });
}