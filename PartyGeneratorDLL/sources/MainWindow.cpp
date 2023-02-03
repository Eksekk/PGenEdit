#include "pch.h"
#include "main.h"
#include "MainWindow.h"
#include "GuiApplication.h"
#include "Generator.h"
#include "PlayerPanel.h"
#include "ClassWindow.h"
#include <wx/notebook.h>
#include "Player.h"
#include "Generator.h"
#include "GeneralPanel.h"
#include "DefaultPlayerPanel.h"
#include <wx/artprov.h>

///////////////////////////////////////////////////////////////////////////

extern int MAX_PLAYERS;
extern int MMVER;
extern Generator* generator;

const wxString MainWindow::WARNING_FORMAT = "Warning: your party count is %d. Only %d leftmost players' tabs will be generated, the rest is implicitly disabled.";

template<typename Player>
void MainWindow::update()
{
	auto names = getPlayerNames<Player>();
	
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		int pageId = FIRST_PLAYER_PAGE + i;
		tabs->SetPageText(pageId, names[i]);
		/*if (i < CURRENT_PARTY_SIZE)
		{
			tabs->GetPage(pageId)->Enable(true);
		}
		else
		{
			tabs->GetPage(pageId)->Enable(false);
		}*/
	}

	if (MMVER == 8 && CURRENT_PARTY_SIZE < 5)
	{
		warningText->SetLabel(wxString::Format(WARNING_FORMAT, CURRENT_PARTY_SIZE, CURRENT_PARTY_SIZE));
		for (auto& item : mm8PartialGenerationWarningSizer->GetChildren())
		{
			item->Show(true);
		}
	}
	else if (MMVER == 8)
	{
		for (auto& item : mm8PartialGenerationWarningSizer->GetChildren())
		{
			item->Show(false);
		}
	}
	//int sel = tabs->GetSelection();
	//if (sel >= FIRST_PLAYER_PAGE && sel >= FIRST_PLAYER_PAGE + CURRENT_PARTY_SIZE)
	//{
	//	tabs->SetSelection(FIRST_PLAYER_PAGE - 1 + CURRENT_PARTY_SIZE); // set to last enabled player
	//}
}

template<typename Player>
std::vector<wxString> MainWindow::getPlayerNames()
{
	std::vector<wxString> names;
	int i;
	for (i = 0; i < CURRENT_PARTY_SIZE; ++i)
	{
		names.push_back(reinterpret_cast<Player*>(generator->players[i])->name);
	}
	for (; i < MAX_PLAYERS; ++i)
	{
		names.push_back(wxString::Format("Player %d", i + 1));
	}
	
	return names;
}

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	assert(MAX_PLAYERS >= 4);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	mainPanel = new wxPanel(this);
	{
		statusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

		setupMenus();

		mainSizer = new wxBoxSizer(wxVERTICAL);

		mainPanel->SetSizer(mainSizer);

		// BUTTONS //

		wxBoxSizer* buttonsSizer;
		buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			loadButton = new wxButton(mainPanel, wxID_ANY, _("Load"), wxDefaultPosition, wxDefaultSize, 0);
			loadButton->SetToolTip(_("Load settings from file"));
			loadButton->SetMinSize(wxSize(-1, 30));

			buttonsSizer->Add(loadButton, 1, wxALL, 5);

			saveButton = new wxButton(mainPanel, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0);
			saveButton->SetToolTip(_("Save settings to file"));
			saveButton->SetMinSize(wxSize(-1, 30));

			buttonsSizer->Add(saveButton, 1, wxALL, 5);

			clearButton = new wxButton(mainPanel, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, 0);
			clearButton->SetToolTip(_("Set settings to their default values"));
			clearButton->SetMinSize(wxSize(-1, 30));

			buttonsSizer->Add(clearButton, 1, wxALL, 5);

			randomizeButton = new wxButton(mainPanel, wxID_ANY, _("Randomize"), wxDefaultPosition, wxDefaultSize, 0);
			randomizeButton->SetToolTip(_("Create random settings"));
			randomizeButton->SetMinSize(wxSize(-1, 30));

			buttonsSizer->Add(randomizeButton, 1, wxALL, 5);

			copyButton = new wxButton(mainPanel, wxID_ANY, _("Copy"), wxDefaultPosition, wxDefaultSize, 0);
			copyButton->SetToolTip(_("Copy settings or part of them from/to player"));
			copyButton->SetMinSize(wxSize(-1, 30));

			buttonsSizer->Add(copyButton, 1, wxALL, 5);
		}


		mainSizer->Add(buttonsSizer, 0, wxEXPAND, 5);

		// ~~BUTTONS~~ //

		// SEED //

		wxStaticBoxSizer* seedStaticBoxSizer;
		seedStaticBoxSizer = new wxStaticBoxSizer(new wxStaticBox(mainPanel, wxID_ANY, _("Seed")), wxHORIZONTAL);
		{
			randomSeedRadio = new wxRadioButton(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("Random"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
			seedStaticBoxSizer->Add(randomSeedRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

			specificSeedRadio = new wxRadioButton(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("Specific:"), wxDefaultPosition, wxDefaultSize, 0);
			seedStaticBoxSizer->Add(specificSeedRadio, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

			specificSeedText = new wxTextCtrl(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_NOHIDESEL);
			seedStaticBoxSizer->Add(specificSeedText, 0, wxALL, 5);

			randomSeedInFileCheckbox = new wxCheckBox(seedStaticBoxSizer->GetStaticBox(), wxID_ANY, _("Keep random seed in file"), wxDefaultPosition, wxDefaultSize, 0);
			randomSeedInFileCheckbox->SetToolTip(_("If set and seed to use is random, writes information about randomness to file (another user will get different seed), otherwise seed in file is exact"));

			seedStaticBoxSizer->Add(randomSeedInFileCheckbox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
		}

		mainSizer->Add(seedStaticBoxSizer, 0, wxLEFT, 5);

		// ~~SEED~~ //

		generateButton = new wxButton(mainPanel, wxID_ANY, _("Generate!"), wxDefaultPosition, wxDefaultSize, 0);
		generateButton->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
		generateButton->SetMinSize(wxSize(200, 50));

		mainSizer->Add(generateButton, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

		mm8PartialGenerationWarningSizer = new wxBoxSizer(wxHORIZONTAL);

		warningBitmap = new wxStaticBitmap(mainPanel, wxID_ANY, wxArtProvider::GetBitmap(wxART_WARNING, wxART_CMN_DIALOG), wxDefaultPosition, wxDefaultSize, 0);
		mm8PartialGenerationWarningSizer->Add(warningBitmap, 0, wxALL, 5);

		warningText = new wxStaticText(mainPanel, wxID_ANY, _("Warning: your party count is x. Only x leftmost tabs will be generated, the rest is implicitly disabled."), wxDefaultPosition, wxDefaultSize, 0);
		mm8PartialGenerationWarningSizer->Add(warningText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

		mainSizer->Add(mm8PartialGenerationWarningSizer, 0, wxEXPAND, 5);

		for (auto& item : mm8PartialGenerationWarningSizer->GetChildren())
		{
			item->Show(false);
		}

		tabs = new wxNotebook(mainPanel, wxID_ANY, pos, size, wxNB_TOP | wxNB_FIXEDWIDTH | wxCLIP_CHILDREN);
		mainSizer->Add(tabs, 1, wxEXPAND | wxALL, 5);
		generalPanel = new GeneralPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
		tabs->AddPage(generalPanel, _("General"), true);
		std::vector<wxString> playerNames;
		if (MMVER == 6)
		{
			//playerNames = getPlayerNames<mm6::Player>();
		}
		else if (MMVER == 7)
		{
			playerNames = getPlayerNames<mm7::Player>();
		}
		else if (MMVER == 8)
		{
			//playerNames = getPlayerNames<mm8::Player>();
		}

		defaultSettings = new DefaultPlayerPanel(tabs, &generator->defaultPlayerData);
		tabs->AddPage(defaultSettings, _("Default"), false);
		for (int i = 0; i < MAX_PLAYERS; ++i)
		{
			tabs->AddPage(new PlayerPanel(tabs, generator->playerData[i].get()), playerNames[i]);
		}

		updateTabsTimer = new wxTimer(this);
		Bind(wxEVT_TIMER, &MainWindow::onTimer, this); // TODO mm6-7 party size when reloading dll at runtime (currently hook launches only on map load)
		updateTabsTimer->Start(200, wxTIMER_CONTINUOUS);
	}

	this->Centre(wxBOTH);
	mainPanel->Layout();

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::onClose, this);
	Bind(wxEVT_KEY_DOWN, &MainWindow::onKeyDown, this);
	
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
	delete updateTabsTimer;
}

void MainWindow::onTimer(wxTimerEvent& event)
{
	if (MMVER == 6)
	{
		//update<mm6::Player>();
	}
	else if (MMVER == 7)
	{
		update<mm7::Player>();
	}
	else if (MMVER == 8)
	{
		//update<mm8::Player>();
	}
}

void MainWindow::onShow(wxShowEvent& event)
{
}

void MainWindow::onKeyDown(wxKeyEvent& event)
{
	event.Skip();
	if (event.GetKeyCode() == WXK_ESCAPE)
	{
		Show(false);
	}
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