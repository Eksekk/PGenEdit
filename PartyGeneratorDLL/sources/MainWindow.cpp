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
#include "GeneralPanel.h"

///////////////////////////////////////////////////////////////////////////

extern int MAX_PLAYERS;
extern int MMVER;
extern Generator* generator;

template<typename Player>
void MainWindow::updatePlayerNames(wxShowEvent& event)
{
	auto names = getPlayerNames<Player>();
	for (int i = FIRST_PLAYER_PAGE; i < tabs->GetPageCount(); ++i)
	{
		tabs->SetPageText(i, names[i - FIRST_PLAYER_PAGE]);
	}
}

template<typename Player>
std::vector<wxString> MainWindow::getPlayerNames()
{
	std::vector<wxString> names;
	if (generator->players) // setPlayerPointers() was called, TODO: zero out when exited to main menu etc.
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

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	// BUTTONS //

	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

	loadButton = new wxButton(this, wxID_ANY, _("Load"), wxDefaultPosition, wxDefaultSize, 0);
	loadButton->SetToolTip(_("Load settings from file"));
	loadButton->SetMinSize(wxSize(-1, 30));

	buttonsSizer->Add(loadButton, 1, wxALL, 5);

	saveButton = new wxButton(this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0);
	saveButton->SetToolTip(_("Save settings to file"));
	saveButton->SetMinSize(wxSize(-1, 30));

	buttonsSizer->Add(saveButton, 1, wxALL, 5);

	clearButton = new wxButton(this, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	clearButton->SetToolTip(_("Set settings to their default values"));
	clearButton->SetMinSize(wxSize(-1, 30));

	buttonsSizer->Add(clearButton, 1, wxALL, 5);

	randomizeButton = new wxButton(this, wxID_ANY, _("Randomize"), wxDefaultPosition, wxDefaultSize, 0);
	randomizeButton->SetToolTip(_("Create random settings"));
	randomizeButton->SetMinSize(wxSize(-1, 30));

	buttonsSizer->Add(randomizeButton, 1, wxALL, 5);

	copyButton = new wxButton(this, wxID_ANY, _("Copy"), wxDefaultPosition, wxDefaultSize, 0);
	copyButton->SetToolTip(_("Copy settings or part of them from/to player"));
	copyButton->SetMinSize(wxSize(-1, 30));

	buttonsSizer->Add(copyButton, 1, wxALL, 5);


	mainSizer->Add(buttonsSizer, 0, wxEXPAND, 5);

	// ~~BUTTONS~~ //
	
	// SEED //

	wxStaticBoxSizer* seedStaticBoxSizer;
	seedStaticBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Seed")), wxHORIZONTAL);

	randomSeedRadio = new wxRadioButton(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("Random"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	seedStaticBoxSizer->Add(randomSeedRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	specificSeedRadio = new wxRadioButton(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("Specific:"), wxDefaultPosition, wxDefaultSize, 0);
	seedStaticBoxSizer->Add(specificSeedRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	specificSeedText = new wxTextCtrl(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_NOHIDESEL);
	seedStaticBoxSizer->Add(specificSeedText, 0, wxALL, 5);

	randomSeedInFileCheckbox = new wxCheckBox(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("Keep random seed in file"), wxDefaultPosition, wxDefaultSize, 0);
	randomSeedInFileCheckbox->SetToolTip(_("If set and seed to use is random, writes information about randomness to file (another user will get different seed), otherwise seed in file is exact"));

	seedStaticBoxSizer->Add(randomSeedInFileCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	mainSizer->Add(seedStaticBoxSizer, 0, wxLEFT, 5);

	// ~~SEED~~ //

	generateButton = new wxButton(this, wxID_ANY, _("Generate!"), wxDefaultPosition, wxDefaultSize, 0);
	generateButton->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	generateButton->SetMinSize(wxSize(200, 50));

	mainSizer->Add(generateButton, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

	tabs = new wxNotebook(this, wxID_ANY, pos, size, wxNB_TOP | wxNB_FIXEDWIDTH);
	generalPanel = new GeneralPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxVSCROLL);
	tabs->AddPage(generalPanel, _("General"), true);
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

	defaultSettings = new PlayerPanel(tabs, &generator->defaultPlayerData);
	tabs->AddPage(defaultSettings, _("Default"), false);
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		tabs->AddPage(new PlayerPanel(tabs, &generator->playerData[i]), playerNames[i], i == 0);
	}

	mainSizer->Add(tabs, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(mainSizer);

	this->Centre(wxBOTH);

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