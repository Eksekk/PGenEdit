#include "pch.h"
#include "EditorMainWindow.h"
#include <wx/statline.h>
#include "Enum_const.h"
#include "PlayerStructAccessor.h"
#include "EditorPlayerWindow.h"
#include "Profiler.h"

EditorMainWindow::EditorMainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	memset(playerButtons.data(), 0, playerButtons.size() * sizeof(std::decay_t<decltype(playerButtons[0])>));
	memset(playerWindows.data(), 0, playerWindows.size() * sizeof(std::decay_t<decltype(playerWindows[0])>));
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	setupMenusAndStatusBar();

	mainSizer = new wxBoxSizer(wxVERTICAL);

	mainPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	mainPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	mainPanel->SetScrollRate(35, 35);
	mainPanel->SetSizer(mainSizer);

	wxStaticBoxSizer* editPlayersSizer;
	editPlayersSizer = new wxStaticBoxSizer(new wxStaticBox(mainPanel, wxID_ANY, _("Edit players")), wxHORIZONTAL);

	auto names = playerAccessor->getPlayerNames();
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		playerButtons[i] = new wxButton(editPlayersSizer->GetStaticBox(), wxNewId(), names[i]);
		playerButtons[i]->SetMinSize(wxSize(100, 30));
		editPlayersSizer->Add(playerButtons[i], 0, wxALL, 5);
		playerButtons[i]->Bind(wxEVT_BUTTON, &EditorMainWindow::onPlayerButtonClick, this);
		playerButtonIds[i] = playerButtons[i]->GetId();

		//playerWindows[i] = new EditorPlayerWindow(/*this*/nullptr, i);
	}

	updateTimer = new wxTimer(this);
	Bind(wxEVT_TIMER, &EditorMainWindow::update, this);
	updateTimer->Start(250, wxTIMER_CONTINUOUS);

	mainSizer->Add(editPlayersSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticline31 = new wxStaticLine(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline31, 0, wxEXPAND | wxALL, 5);

	setupGlobalSettingsControls();

	m_staticline32 = new wxStaticLine(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline32, 0, wxEXPAND | wxALL, 5);

	setupOtherSettingsButtons();

	this->Layout();

	this->Centre(wxBOTH);

	Bind(wxEVT_CLOSE_WINDOW, &EditorMainWindow::onCloseWindow, this);
}

void EditorMainWindow::setupGlobalSettingsControls()
{
	wxBoxSizer* miscGlobalSettingsSizer;
	miscGlobalSettingsSizer = new wxBoxSizer(wxVERTICAL);

	miscGlobalSettingsLabel = new wxStaticText(mainPanel, wxID_ANY, _("Misc/global settings"));
	miscGlobalSettingsLabel->Wrap(-1);
	miscGlobalSettingsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	miscGlobalSettingsSizer->Add(miscGlobalSettingsLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	allowFindingEveryArtifactAgainButton = new wxButton(mainPanel, wxID_ANY, _("Allow finding every artifact again"));
	miscGlobalSettingsSizer->Add(allowFindingEveryArtifactAgainButton, 0, wxALL, 5);

	hireDismissPartyMembersButton = new wxButton(mainPanel, wxID_ANY, _("Hire/dismiss party members"));
	hireDismissPartyMembersButton->SetToolTip(_("Only for MM8"));

	miscGlobalSettingsSizer->Add(hireDismissPartyMembersButton, 0, wxALL, 5);


	mainSizer->Add(miscGlobalSettingsSizer, 1, wxEXPAND, 5);
}

void EditorMainWindow::setupOtherSettingsButtons()
{
	wxStaticBoxSizer* otherSettingsSizer;
	otherSettingsSizer = new wxStaticBoxSizer(new wxStaticBox(mainPanel, wxID_ANY, _("Other")), wxHORIZONTAL);

	mapSettingsButton = new wxButton(otherSettingsSizer->GetStaticBox(), wxID_ANY, _("Map settings"));
	mapSettingsButton->SetMinSize(wxSize(100, 30));

	otherSettingsSizer->Add(mapSettingsButton, 0, wxALL, 5);

	questSettingsButton = new wxButton(otherSettingsSizer->GetStaticBox(), wxID_ANY, _("Quest settings"));
	questSettingsButton->SetMinSize(wxSize(100, 30));

	otherSettingsSizer->Add(questSettingsButton, 0, wxALL, 5);

	npcSettingsButton = new wxButton(otherSettingsSizer->GetStaticBox(), wxID_ANY, _("NPC settings"));
	npcSettingsButton->SetMinSize(wxSize(100, 30));

	otherSettingsSizer->Add(npcSettingsButton, 0, wxALL, 5);

	houseSettingsButton = new wxButton(otherSettingsSizer->GetStaticBox(), wxID_ANY, _("House settings"));
	houseSettingsButton->SetMinSize(wxSize(100, 30));

	otherSettingsSizer->Add(houseSettingsButton, 0, wxALL, 5);


	mainSizer->Add(otherSettingsSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5);
}

void EditorMainWindow::setupMenusAndStatusBar()
{
	menuBar = new wxMenuBar(0);
	presetsMenu = new wxMenu();
	wxMenuItem* presetsStartingPartyMenuItem;
	presetsStartingPartyMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("Starting party")), wxEmptyString, wxITEM_NORMAL);
	presetsMenu->Append(presetsStartingPartyMenuItem);

	wxMenuItem* presetsMediumLevelPartyMenuItem;
	presetsMediumLevelPartyMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("Medium-level party")), wxEmptyString, wxITEM_NORMAL);
	presetsMenu->Append(presetsMediumLevelPartyMenuItem);

	wxMenuItem* presetsEndgamePartyMenuItem;
	presetsEndgamePartyMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("Endgame party")), wxEmptyString, wxITEM_NORMAL);
	presetsMenu->Append(presetsEndgamePartyMenuItem);

	wxMenuItem* presetsGodPartyMenuItem;
	presetsGodPartyMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("God party")), wxEmptyString, wxITEM_NORMAL);
	presetsMenu->Append(presetsGodPartyMenuItem);

	presetsMenu->AppendSeparator();

	wxMenuItem* presetsResetQuestProgressMenuItem;
	presetsResetQuestProgressMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("Reset quest progress")), wxEmptyString, wxITEM_NORMAL);
	presetsMenu->Append(presetsResetQuestProgressMenuItem);

	wxMenuItem* presetsResetNpcsMenuItem;
	presetsResetNpcsMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("Reset NPC state")), wxEmptyString, wxITEM_NORMAL);
	presetsMenu->Append(presetsResetNpcsMenuItem);

	wxMenuItem* presetsFullyResetGameStateMenuItem;
	presetsFullyResetGameStateMenuItem = new wxMenuItem(presetsMenu, wxID_ANY, wxString(_("Fully reset game state")), _("Starting party, quest progress, npcs, location, all maps respawned etc."), wxITEM_NORMAL);
	presetsMenu->Append(presetsFullyResetGameStateMenuItem);

	menuBar->Append(presetsMenu, _("Presets"));

	editMenu = new wxMenu();
	menuBar->Append(editMenu, _("Edit"));

	aboutMenu = new wxMenu();
	menuBar->Append(aboutMenu, _("About"));

	this->SetMenuBar(menuBar);

	statusBar = this->CreateStatusBar(1, wxSTB_ELLIPSIZE_END, wxID_ANY);
}

EditorPlayerWindow* EditorMainWindow::createPlayerWindow(int index)
{
	wxASSERT(index < MAX_PLAYERS);
	playerWindows[index] = new EditorPlayerWindow(this, index);
	return playerWindows[index];
}

void EditorMainWindow::destroyPlayerWindow(int index)
{
	wxASSERT(playerWindows[index]);
	playerWindows[index]->Destroy();
	playerWindows[index] = nullptr;
}

void EditorMainWindow::onPlayerButtonClick(wxCommandEvent& event)
{
	for (int i = 0; i < CURRENT_PARTY_SIZE; ++i)
	{
		if (event.GetId() == playerButtonIds[i])
		{
			if (!playerWindows[i])
			{
				Profiler profiler;
				profiler.start("Creating player window");
				playerWindows[i] = new EditorPlayerWindow(this, i);
				wxToolTip::Enable(true);
				profiler.end();
				//wxLogMessage(profiler.getDurationStr());
				wxLog::FlushActive();
			}
			playerWindows[i]->Show();
			return;
		}
	}
	wxFAIL_MSG(wxString::Format("Invalid player button index"));
}

void EditorMainWindow::update(wxTimerEvent& event)
{
	auto names = playerAccessor->getPlayerNames();
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		playerButtons[i]->SetLabel(names[i]);
		playerButtons[i]->Enable(i < CURRENT_PARTY_SIZE);
	}
}

void EditorMainWindow::onCloseWindow(wxCloseEvent& event)
{
	if (event.CanVeto())
	{
		event.Veto();
		Show(false);
		return;
	}
	Destroy();
}

EditorMainWindow::~EditorMainWindow()
{
	delete updateTimer;
}