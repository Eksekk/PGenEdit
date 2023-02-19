#include "pch.h"
#include "EditorPlayerWindow.h"
#include <wx/notebook.h>

EditorPlayerWindow::EditorPlayerWindow(wxWindow* parent, int playerIndex) : wxFrame(parent, wxID_ANY, wxString::Format("Edit player %d", playerIndex + 1),
	wxDefaultPosition, wxSize(770, 670), (wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) & ~wxRESIZE_BORDER), playerIndex(playerIndex)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

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
	skillsPanel = new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
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

EditorPlayerWindow::~EditorPlayerWindow()
{
}

void EditorPlayerWindow::onCloseWindow(wxCloseEvent& event)
{
	if (event.CanVeto())
	{
		event.Veto();
		Show(false);
		return;
	}
	Destroy();
}