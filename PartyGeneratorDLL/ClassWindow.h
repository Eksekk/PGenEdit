#pragma once
#include "pch.h"
#include "main.h"
#include "ClassGenerationData.h"

class ClassInfoPanel;

class ClassWindow : public wxFrame
{
private:

protected:


public:
	wxButton* resetButton;
	ClassInfoPanel* generalPanel;
	std::vector<ClassInfoPanel*> panels;
	wxBoxSizer* sizer;

	// TODO: five windows, where you can set various settings to use (item/resistance/all etc.)
	// copy from to, randomize, set to default, load, save
	// class managing one set of controls (settings chooser) for above five uses
	// copy from to choose settings and choose source&target

	// TODO: show jsoned settings (for manual copy) in window appearing when settings couldn't be saved to file

	ClassWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Classes"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(843, 479), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	void createPanels(ClassGenerationSettings& generalClassSettings, std::unordered_map<int, ClassGenerationSettings>& classSettings);

	~ClassWindow();

};

