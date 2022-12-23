#include "pch.h"
#include "main.h"
#include "MainWindow.h"
#include "Application.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	statusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

	setupMenus();

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	this->SetSizer(bSizer6);
	this->Layout();

	this->Centre(wxBOTH);

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::onClose, this);
}

void MainWindow::setupMenus()
{
	menuBar = new wxMenuBar(0);
	settingsMenu = new wxMenu();
	wxMenuItem* NewMenuItem;
	NewMenuItem = new wxMenuItem(settingsMenu, wxID_ANY, wxString(_("New")), _("Load default settings"), wxITEM_NORMAL);
	settingsMenu->Append(NewMenuItem);

	settingsMenu->AppendSeparator();

	wxMenuItem* loadMenuItem;
	loadMenuItem = new wxMenuItem(settingsMenu, wxID_ANY, wxString(_("Load")), _("Load settings or part of them from another file"), wxITEM_NORMAL);
	settingsMenu->Append(loadMenuItem);

	wxMenuItem* saveMenuItem;
	saveMenuItem = new wxMenuItem(settingsMenu, wxID_ANY, wxString(_("Save")), _("Save settings or part of them to another file"), wxITEM_NORMAL);
	settingsMenu->Append(saveMenuItem);

	menuBar->Append(settingsMenu, _("Settings"));

	editMenu = new wxMenu();
	menuBar->Append(editMenu, _("Edit"));

	helpMenu = new wxMenu();
	wxMenuItem* randomizationMechanicsMenuItem;
	randomizationMechanicsMenuItem = new wxMenuItem(helpMenu, wxID_ANY, wxString(_("Randomization mechanics")), wxEmptyString, wxITEM_NORMAL);
	helpMenu->Append(randomizationMechanicsMenuItem);

	wxMenuItem* aboutMenuItem;
	aboutMenuItem = new wxMenuItem(helpMenu, wxID_ANY, wxString(_("About")), wxEmptyString, wxITEM_NORMAL);
	helpMenu->Append(aboutMenuItem);

	menuBar->Append(helpMenu, _("Help"));

	this->SetMenuBar(menuBar);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClose(wxCloseEvent& event)
{
	if (event.CanVeto())
	{
		// don't delete frame unless needed, just hide window
		event.Veto();
		Show(false);
		return;
	}
	Destroy();
	wxGetApp().mainWindow = nullptr;
}