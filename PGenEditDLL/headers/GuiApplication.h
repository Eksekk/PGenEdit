#pragma once
#include "main.h"

class MainWindow;
class EditorMainWindow;
class ControlPanel;
class wxGUIEventLoop;
class GuiApplication : public wxApp
{
public:
    MainWindow* mainWindow;
    EditorMainWindow* editorMainWindow;
    ControlPanel* controlPanel;
    using wxApp::DeletePendingObjects; // protected -> public
    wxTimer* idleEventTimer;
    wxGUIEventLoop* eventLoop;

    // create wxWidgets event handler, which handles all generated keypresses, but does nothing and calls "Skip()" to pass them to the default handler
    void onChar(wxKeyEvent& event);
    void onKeyDown(wxKeyEvent& event);
    void onKeyUp(wxKeyEvent& event);


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