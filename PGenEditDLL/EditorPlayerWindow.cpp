#include "pch.h"
#include "EditorPlayerWindow.h"
#include <wx/notebook.h>
#include "PlayerStructAccessor.h"
#include "EditorSkillsPanel.h"
#include "EditorMainWindow.h"
#include "GuiApplication.h"
#include <wx/evtloop.h>
#include "EditorStatisticsPanel.h"
#include "Asserter.h"
#include "SaveGameData.h"
#include "EditorItemsPanel.h"

const std::vector<std::pair<std::string, PlayerWindowPanelType>> EditorPlayerWindow::panelNamesWithIndexes =
{ {"Appearance", APPEARANCE_PANEL_INDEX}, { "Statistics", STATISTICS_PANEL_INDEX }, { "Skills", SKILLS_PANEL_INDEX },
    { "Spells", SPELLS_PANEL_INDEX }, { "Items", ITEMS_PANEL_INDEX }, { "Conditions/buffs", CONDITIONS_BUFFS_PANEL_INDEX }, { "Awards", AWARDS_PANEL_INDEX } };

int EditorPlayerWindow::getPanelIndexByType(PlayerWindowPanelType type)
{
	int i = 0;
    for (const auto& [str, enumIndex] : panelNamesWithIndexes)
    {
        if (enumIndex == type)
        {
            return i;
        }
		++i;
    }
    wxFAIL_MSG(wxString::Format("Couldn't get index of panel type %d", (int)type));
	return -1;
}

std::string EditorPlayerWindow::getPanelNameByType(PlayerWindowPanelType type)
{
	return panelNamesWithIndexes.at(getPanelIndexByType(type)).first;
}

int EditorPlayerWindow::setRosterIndex()
{
    throw std::logic_error("The method or operation is not implemented.");
}
void EditorPlayerWindow::setDefaultCustomSettings()
{
    throw std::logic_error("The method or operation is not implemented.");
}
bool EditorPlayerWindow::persist(Json& json) const
{
    throw std::logic_error("The method or operation is not implemented.");
}
bool EditorPlayerWindow::unpersist(const Json& json)
{
    throw std::logic_error("The method or operation is not implemented.");
}
std::string EditorPlayerWindow::getJsonPersistKey() const
{
	return "playerWindow";
}
void EditorPlayerWindow::updateFromPlayerData()
{
	wxFAIL; // shouldn't be called for now
}
EditorPlayerWindow::EditorPlayerWindow(wxWindow* parent, int playerIndex, int rosterIndex) : wxFrame(parent, wxID_ANY, "Edit " + playerAccessor->getNameOrDefault(playerIndex),
	wxDefaultPosition, wxSize(1100, 950), wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL), EditorPlayerPanel(playerIndex, rosterIndex), myIsBeingDestroyed(false), changingToPageIndex(0), changingPage(false)
{
	Asserter myasserter("Editor player window");
	Freeze();
	windowDisabler = nullptr;
	loop = nullptr;
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

	tabs = new wxNotebook(mainPanel, wxID_ANY);
	static const wxSize tabsImageSize = wxSize(50, 30);
    wxImageList* tabsImages = new wxImageList(tabsImageSize.GetWidth(), tabsImageSize.GetHeight());
    tabs->AssignImageList(tabsImages);
	// create placeholders, because combined panels hold too many controls and take too much time to create
	for (const auto& [str, requiredIndex] : panelNamesWithIndexes)
	{
		tabs->AddPage(new wxPanel(tabs), str);
		myassertf(tabs->GetPageCount() - 1 == requiredIndex, "Invalid index for panel '%s'", str);
	}

	mainSizer->Add(tabs, 1, wxEXPAND | wxALL, 5);
	tabs->Bind(wxEVT_BOOKCTRL_PAGE_CHANGED, &EditorPlayerWindow::onTabChange, this);

	mainPanel->SetSizer(mainSizer);
	mainPanel->Layout();
	mainSizer->Fit(mainPanel);

	this->Layout();
	this->Centre(wxBOTH);

	Bind(wxEVT_CLOSE_WINDOW, &EditorPlayerWindow::onCloseWindow, this);
	Bind(wxEVT_ACTIVATE, &EditorPlayerWindow::onActivate, this);
	Thaw();
	myasserter.flush();
}

void EditorPlayerWindow::showModal()
{
	Show();
	if (!windowDisabler)
	{
		windowDisabler = new wxWindowDisabler(this);
	}
	if (!loop)
	{
		loop = new wxEventLoop();
	}
	wxEventLoop::SetActive(loop);
	loop->Run();
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
	if (loop)
	{
		loop->Exit();
		wxEventLoop::SetActive(nullptr);
		delete windowDisabler;
		delete loop;
		loop = nullptr;
		windowDisabler = nullptr;
	}
	mainWindow->playerWindows[playerIndex] = nullptr;
	wxASSERT(Destroy());
	//wxGetApp().ProcessIdle(); // important because otherwise window won't ever be destroyed
	// (lack of "event loop", top level window destruction is done in idle events)
	
	// onWakeUpIdle() crashes process (no event loop!)
	//wxGetApp().ProcessPendingEvents();
	//wxGetApp().DeletePendingObjects();
	//CallAfter([] {wxGetApp().DeletePendingObjects(); });
}

bool EditorPlayerWindow::AcceptsFocus() const
{
	return true;
}

void EditorPlayerWindow::onActivate(wxActivateEvent& event)
{
	event.Skip();
	if (event.GetActive() && !IsBeingDeleted() && !myIsBeingDestroyed) // second and third condition important to prevent tests failed message triggering assert in accessor
	{
        EditorPlayerPanel* panel = dynamic_cast<EditorPlayerPanel*>(tabs->GetCurrentPage());
        if (panel)
        {
            panel->updateFromPlayerData();
			// TODO: persist on deactivate and unpersist on activate?
        }
	}
}
bool EditorPlayerWindow::Destroy()
{
	myIsBeingDestroyed = true;
	return wxFrame::Destroy();
}

void EditorPlayerWindow::onTabChange(wxBookCtrlEvent& event)
{
	// TODO!!!: RemovePage might allow to keep tab contents in memory, avoiding "a ton of controls" problem, since it's removed from the window?
	if (changingPage)
	{
		//event.Veto();
        event.Skip();
		return;
    }
    Freeze();
	changingPage = true;
	wxON_BLOCK_EXIT0([&] {changingPage = false; Thaw(); });
	// TODO: don't cast enum to int, use mapping table, more safety
	int oldSelInt = event.GetOldSelection(), newSelInt = tabs->GetSelection();//event.GetSelection();
	PlayerWindowPanelType oldSel = static_cast<PlayerWindowPanelType>(oldSelInt), newSel = static_cast<PlayerWindowPanelType>(newSelInt);

	if (newSel == oldSel)
	{
		wxLogInfo("[Editor player window] switch from panel %d to itself, skipping", oldSel);
		return;
	}

	EditorPlayerPanel* panel = dynamic_cast<EditorPlayerPanel*>(tabs->GetPage(oldSelInt));
	if (panel != nullptr) // can maybe be dummy?
    {
        saveGameData.saveEditorPlayerPanelData(*panel);
	}
    // replace old content page with dummy
    tabs->InsertPage(oldSelInt, new wxPanel(tabs), getPanelNameByType(oldSel));
	tabs->DeletePage(oldSelInt + 1);

	// replace dummy page with newly created one
	// 
	switch (newSel)
	{
	case SKILLS_PANEL_INDEX:
		tabs->InsertPage(newSelInt + 1, new EditorSkillsPanel(tabs, playerIndex, rosterIndex), getPanelNameByType(SKILLS_PANEL_INDEX));
		break;
	case APPEARANCE_PANEL_INDEX:
		tabs->InsertPage(newSelInt + 1, new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL), getPanelNameByType(APPEARANCE_PANEL_INDEX));
		break;
	case STATISTICS_PANEL_INDEX:
        tabs->InsertPage(newSelInt + 1, new EditorStatisticsPanel(tabs, playerIndex, rosterIndex), getPanelNameByType(STATISTICS_PANEL_INDEX));
        break;
	case SPELLS_PANEL_INDEX:
        tabs->InsertPage(newSelInt + 1, new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL), getPanelNameByType(SPELLS_PANEL_INDEX));
        break;
	case ITEMS_PANEL_INDEX:
        tabs->InsertPage(newSelInt + 1, new EditorItemsPanel(tabs, 14, 9, ItemRefPlayerInventory{.rosterIndex = rosterIndex}, {}, playerIndex, rosterIndex), getPanelNameByType(ITEMS_PANEL_INDEX));
        break;
	case CONDITIONS_BUFFS_PANEL_INDEX:
        tabs->InsertPage(newSelInt + 1, new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL), getPanelNameByType(CONDITIONS_BUFFS_PANEL_INDEX));
        break;
	case AWARDS_PANEL_INDEX:
        tabs->InsertPage(newSelInt + 1, new wxPanel(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL), getPanelNameByType(AWARDS_PANEL_INDEX));
        break;
	default:
		wxFAIL_MSG(wxString::Format("Unknown player panel type (%d)", (int)newSel));
		break;
    }
	try
	{

        tabs->DeletePage(newSelInt);
        tabs->ChangeSelection(newSelInt);
	}
	catch (const std::exception& ex)
	{
		wxLogError(ex.what());
		wxLog::FlushActive();
	}
    panel = dynamic_cast<EditorPlayerPanel*>(tabs->GetPage(newSelInt));
    if (panel) // TODO: remove condition when all panels are implemented (now they can be wxPanel as placeholder)
    {
        wxASSERT(panel != nullptr);
        saveGameData.loadEditorPlayerPanelData(*panel);
	}
}