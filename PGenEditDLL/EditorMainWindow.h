#pragma once
#include "pch.h"
#include "main.h"

class wxStaticLine;
class EditorPlayerWindow;
class EditorMainWindow : public wxFrame
{
private:

    wxBoxSizer* mainSizer;
    wxTimer* updateTimer;
protected:
    wxMenuBar* menuBar;
    wxMenu* presetsMenu;
    wxMenu* editMenu;
    wxMenu* aboutMenu;
    wxStatusBar* statusBar;
    wxScrolledWindow* mainPanel;
    std::array<wxButton*, 5> playerButtons;
    wxStaticLine* m_staticline31;
    wxStaticText* miscGlobalSettingsLabel;
    wxButton* allowFindingEveryArtifactAgainButton;
    wxButton* hireDismissPartyMembersButton;
    wxStaticLine* m_staticline32;
    wxButton* mapSettingsButton;
    wxButton* questSettingsButton;
    wxButton* npcSettingsButton;
    wxButton* houseSettingsButton;

public:
    std::array<int, 50> playerButtonIds;
    std::array<EditorPlayerWindow*, 50> playerWindows;
    EditorMainWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Game state editor"),
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(654, 504), long style = (wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) & ~wxRESIZE_BORDER);

    void onPlayerButtonClick(wxCommandEvent& event);
    void setupGlobalSettingsControls();

    void setupOtherSettingsButtons();

    void setupMenusAndStatusBar();

    EditorPlayerWindow* createPlayerWindow(int index);

    void destroyPlayerWindow(int index);
    void update(wxTimerEvent& event);
    void onCloseWindow(wxCloseEvent& event);
    ~EditorMainWindow();

    friend class GUI_tests;
};

