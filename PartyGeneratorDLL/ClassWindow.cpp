#include "pch.h"
#include "ClassWindow.h"
#include "ClassInfoPanel.h"
#include "GameData.h"

ClassWindow::ClassWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	sizer = new wxBoxSizer(wxVERTICAL);

	this->SetSizer(sizer);

	this->Centre(wxBOTH);
}

ClassWindow::~ClassWindow()
{
}

void ClassWindow::createPanels(ClassGenerationSettings& generalClassSettings, std::unordered_map<int, ClassGenerationSettings>& classSettings)
{
	assert(classSettings.size() > 0);
	generalPanel = new ClassInfoPanel(this, wxID_ANY);
	generalPanel->linkedClassSettings = &generalClassSettings;
	sizer->Add(generalPanel);
	sizer->Add(0, 20); // adds spacer

	for (auto& [id, clas] : GameData::classes)
	{
		if (clas.tier == 0)
		{
			ClassInfoPanel* panel = new ClassInfoPanel(this, wxID_ANY);
			auto f = classSettings.find(clas.id);
			assert(f != classSettings.end());
			panel->linkedClassSettings = &(f->second);
			sizer->Add(panel);
		}
	}

	this->Layout();
}