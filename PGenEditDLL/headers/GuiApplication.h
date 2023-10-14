#pragma once
#include "pch.h"
#include "main.h"
#include <wx/evtloop.h>

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
    wxTimer* idleEventTimer;
    wxGUIEventLoop* eventLoop;

    GuiApplication();
    virtual bool OnInit() override;
    virtual int OnExit() override;
    void enterLoop();
    void leaveLoop();
/*
private:
	void OnShowWindow(wxThreadEvent& event);
	void OnTerminate(wxThreadEvent& event);*/
};

wxDECLARE_APP(GuiApplication);