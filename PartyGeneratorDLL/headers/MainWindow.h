#pragma once
#include "pch.h"
#include "main.h"
#include "ClassWindow.h"
#include <wx/statline.h>

class PlayerPanel;
class wxNotebook;
class GeneralPanel;
class DefaultPlayerPanel;

// TODO: swap player settings?
class MainWindow : public wxFrame
{
private:
	void onClose(wxCloseEvent& event);
	void onShow(wxShowEvent& event);
	void onKeyDown(wxKeyEvent& event);
	void onTimer(wxTimerEvent& event);
	void setupMenus();
	bool CanAcceptFocus() const;

protected:
	
public:
	static const int GENERAL_PANEL_PAGE = 0;
	static const int DEFAULT_PLAYER_PAGE = 1;
	static const int FIRST_PLAYER_PAGE = 2;

	wxPanel* mainPanel;
	wxBoxSizer* mainSizer;

	wxStatusBar* statusBar;
	wxMenuBar* menuBar;
	wxMenu* settingsMenu;
	wxMenu* editMenu;
	wxMenu* helpMenu;
	wxButton* loadButton;
	wxButton* saveButton;
	wxButton* clearButton;
	wxButton* randomizeButton;
	wxButton* copyButton;
	wxRadioButton* randomSeedRadio;
	wxRadioButton* specificSeedRadio;
	wxTextCtrl* specificSeedText;
	wxCheckBox* randomSeedInFileCheckbox;
	wxButton* generateButton;
	wxNotebook* tabs;

	GeneralPanel* generalPanel;
	DefaultPlayerPanel* defaultSettings;

	wxTimer* updateTabsTimer;

	wxBoxSizer* mm8PartialGenerationWarningSizer;

	wxStaticBitmap* warningBitmap;

	wxStaticText* warningText;

	static const wxString WARNING_FORMAT;

	MainWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Party generator"), const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(800, 700), long style = (wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL | wxWANTS_CHARS) & ~wxRESIZE_BORDER);

	~MainWindow();

	void update();
	void updateSettingsFromLinked();
	[[nodiscard]] std::vector<wxString> getPlayerNames();
};

