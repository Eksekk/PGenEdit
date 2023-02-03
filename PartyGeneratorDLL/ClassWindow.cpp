#include "pch.h"
#include "ClassWindow.h"
#include "ClassInfoPanel.h"
#include "GameData.h"
#include "ClassSettingsTab.h"

ClassWindow::ClassWindow(wxWindow* parent, const wxSize& size, long style) : wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, size, style)
{
	generalPanel = nullptr;
	parentTab = dynamic_cast<ClassSettingsTab*>(parent);
	wxASSERT_MSG(parentTab, wxString::Format("Class window for player %d doesn't have ClassSettingsTab as parent", linkedClassSettings->index));
	if (!parentTab) return;
	linkedClassSettings = parentTab->linkedClassSettings;
	if (linkedClassSettings->index == DEFAULT_SETTINGS_INDEX)
	{
		this->SetTitle("Default class settings");
	}
	else
	{
		this->SetTitle(wxString::Format("Class settings for player %d", linkedClassSettings->index + 1));
	}

	//this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	mainPanel = new wxScrolledWindow(this);
	mainPanel->SetScrollRate(30, 30);

	mainSizer = new wxBoxSizer(wxVERTICAL);
	mainPanel->SetSizer(mainSizer);

	topButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(topButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL);
	closeButtonTop = new wxButton(mainPanel, wxID_CLOSE, "Close");
	topButtonSizer->Add(closeButtonTop, 0, wxALIGN_BOTTOM | wxALL, 5);
	closeButtonTop->Bind(wxEVT_BUTTON, &ClassWindow::onCloseButtonClick, this);

	classSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(classSizer, 0, wxEXPAND | wxALL, 5);

	bottomButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(bottomButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL);
	closeButtonBottom = new wxButton(mainPanel, wxID_CLOSE, "Close");
	bottomButtonSizer->Add(closeButtonBottom, 0, wxALIGN_BOTTOM | wxALL, 5);
	closeButtonBottom->Bind(wxEVT_BUTTON, &ClassWindow::onCloseButtonClick, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &ClassWindow::OnCloseWindow, this);

	this->Centre(wxBOTH);
	mainPanel->Layout();
	mainSizer->Fit(mainPanel);
	this->Layout();
}

ClassWindow::~ClassWindow()
{
}

void ClassWindow::OnCloseWindow(wxCloseEvent& event)
{
	if (event.CanVeto())
	{
		event.Veto();
		Show(false);
	}
}

void ClassWindow::onCloseButtonClick(wxCommandEvent& event)
{
	Show(false);
}

void ClassWindow::createPanels(ClassGenerationSettings& generalClassSettings, std::unordered_map<int, ClassGenerationSettings>& classSettings)
{
	assert(classSettings.size() > 0);
	generalPanel = new ClassInfoPanel(mainPanel, &generalClassSettings);
	generalPanel->setClassName("Default settings");
	classSizer->Add(generalPanel, 0, wxEXPAND, 5);
	//sizer->Add(0, 20); // adds spacer

	for (auto& [id, clas] : GameData::classes)
	{
		if (clas.tier == 0)
		{
			auto f = classSettings.find(clas.id);
			assert(f != classSettings.end());
			ClassInfoPanel* panel = new ClassInfoPanel(mainPanel, &(f->second));
			panel->setClassName(clas.name);
			classSizer->Add(panel, 0, wxEXPAND, 5);
			panels.push_back(panel);
		}
	}
	wxStaticLine* line = new wxStaticLine(mainPanel);
	classSizer->Add(line, 0, wxALL | wxEXPAND, 5);

	classSizer->Layout();
	mainPanel->Layout();
	this->Layout();
	mainSizer->Fit(mainPanel);
}

void ClassWindow::updateSettingsFromLinked()
{
	generalPanel->updateSettingsFromLinked();
	for (auto& panel : panels)
	{
		panel->updateSettingsFromLinked();
	}
}