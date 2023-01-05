#include "pch.h"
#include "main.h"
#include "MainWindow.h"
#include "Application.h"
#include "Generator.h"
#include "PlayerPanel.h"
#include "ClassWindow.h"
#include <wx/notebook.h>
#include "Player.h"
#include "Generator.h"

///////////////////////////////////////////////////////////////////////////

extern int MAX_PLAYERS;
extern int MMVER;
extern Generator* generator;

template<typename Player>
void MainWindow::updatePlayerNames(wxShowEvent& event)
{
	auto names = getPlayerNames<Player>();
	for (int i = 0; i < tabs->GetPageCount(); ++i)
	{
		tabs->SetPageText(i, names[i]);
	}
}

template<typename Player>
std::vector<wxString> MainWindow::getPlayerNames()
{
	std::vector<wxString> names;
	if (generator->players) // setPlayerPointers() was called
	{
		for (int i = 0; i < MAX_PLAYERS; ++i)
		{
			names.push_back(reinterpret_cast<Player*>(generator->players[i])->name);
		}
	}
	else
	{
		for (int i = 0; i < MAX_PLAYERS; ++i)
		{
			names.push_back(wxString::Format("Player %d", i + 1));
		}
	}
	
	return names;
}

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	assert(MAX_PLAYERS >= 4);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	statusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

	setupMenus();

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);
	
	this->SetSizer(bSizer6);

	this->Centre(wxBOTH);

	tabs = new wxNotebook(this, wxID_ANY, pos, size, wxNB_TOP | wxNB_FIXEDWIDTH);
	std::vector<wxString> playerNames;
	if (MMVER == 6)
	{
		//Bind(wxEVT_SHOW, &MainWindow::updatePlayerNames<mm6::Player>, this);
		//playerNames = getPlayerNames<mm6::Player>();
	}
	else if (MMVER == 7)
	{
		Bind(wxEVT_SHOW, &MainWindow::updatePlayerNames<mm7::Player>, this);
		playerNames = getPlayerNames<mm7::Player>();
	}
	else if (MMVER == 8)
	{
		//Bind(wxEVT_SHOW, &MainWindow::updatePlayerNames<mm8::Player>, this);
		//playerNames = getPlayerNames<mm8::Player>();
	}

	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		tabs->AddPage(new PlayerPanel(tabs), playerNames[i], i == 0 ? true : false);
	}

	generalClassWindow = new ClassWindow(this);

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::onClose, this);
	
	this->Layout();
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

void MainWindow::onShow(wxShowEvent& event)
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