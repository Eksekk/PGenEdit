#pragma once
#include "pch.h"
#include "main.h"
#include "ClassWindow.h"
#include <wx/statline.h>

class PlayerPanel;
class wxNotebook;
class GeneralPanel;

class MainWindow : public wxFrame
{
private:
	void onClose(wxCloseEvent& event);
	void onShow(wxShowEvent& event);
	void setupMenus();

protected:
	
public:

	static const int FIRST_PLAYER_PAGE = 2;
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
	ClassWindow* generalClassWindow;
	GeneralPanel* generalPanel;
	PlayerPanel* defaultSettings; // TODO: move to own class

	MainWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Party generator"), const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(800, 600), long style = (wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) & ~wxRESIZE_BORDER);

	~MainWindow();

	template<typename Player>
	void updatePlayerNames(wxShowEvent& event);
	template<typename Player>
	std::vector<wxString> getPlayerNames();
};

