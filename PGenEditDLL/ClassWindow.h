#pragma once
#include "pch.h"
#include "main.h"
#include "ClassGenerationData.h"

class ClassInfoPanel;
class ClassSettingsTab;
class ClassGenerationData;

class ClassWindow : public wxFrame
{
private:

protected:


public:
	ClassInfoPanel* generalPanel;
	std::vector<ClassInfoPanel*> panels;
	wxBoxSizer* mainSizer, *classSizer, *topButtonSizer, *bottomButtonSizer;
	wxButton* closeButtonTop, *closeButtonBottom;
	wxScrolledWindow* mainPanel;
	ClassSettingsTab* parentTab;
	ClassGenerationData* linkedClassSettings;

	// TODO: five windows, where you can set various settings to use (item/resistance/all etc.)
	// copy from to, randomize, set to default, load, save
	// class managing one set of controls (settings chooser) for above five uses
	// copy from to choose settings and choose source&target

	// TODO: show jsoned settings (for manual copy) in window appearing when settings couldn't be saved to file

	ClassWindow(wxWindow* parent, const wxSize & size = wxSize(800, 600), long style = (wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) & ~wxRESIZE_BORDER);

	void createPanels(ClassGenerationSettings& generalClassSettings, std::unordered_map<int, ClassGenerationSettings>& classSettings);

	void updateSettingsFromLinked();
	~ClassWindow();

private:
	void OnCloseWindow(wxCloseEvent& event);
	void onCloseButtonClick(wxCommandEvent& event);
};

