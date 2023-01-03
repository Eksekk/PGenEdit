#pragma once
#include "pch.h"
#include "main.h"
#include "ClassWindow.h"

class PlayerPanel;
class wxNotebook;

class MainWindow : public wxFrame
{
private:

protected:
	
public:

	void setupMenus();

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

	void onClose(wxCloseEvent& event);
};

