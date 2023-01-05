#pragma once
#include "pch.h"
#include "main.h"
#include "ClassWindow.h"

class PlayerPanel;
class wxNotebook;

class MainWindow : public wxFrame
{
private:
	void onClose(wxCloseEvent& event);
	void onShow(wxShowEvent& event);
	void setupMenus();

protected:
	
public:

	

	wxStatusBar* statusBar;
	wxMenuBar* menuBar;
	wxMenu* settingsMenu;
	wxMenu* editMenu;
	wxMenu* helpMenu;

	std::vector<PlayerPanel*> playerPanels;
	ClassWindow* generalClassWindow;
	wxNotebook* tabs;

	MainWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Party generator"), const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MainWindow();

	template<typename Player>
	void updatePlayerNames(wxShowEvent& event);
	template<typename Player>
	std::vector<wxString> getPlayerNames();
};

