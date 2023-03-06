#pragma once
#include "pch.h"
#include "main.h"

class MainWindow;
class EditorMainWindow;
class ControlPanel;

class GuiApplication : public wxApp
{
public:
    MainWindow* mainWindow;
    EditorMainWindow* editorMainWindow;
    ControlPanel* controlPanel;
    using wxApp::DeletePendingObjects; // protected -> public

    GuiApplication();
    virtual bool OnInit();

/*
private:
	void OnShowWindow(wxThreadEvent& event);
	void OnTerminate(wxThreadEvent& event);*/
};

wxDECLARE_APP(GuiApplication);