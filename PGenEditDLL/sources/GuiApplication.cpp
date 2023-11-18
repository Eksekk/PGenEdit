#include "pch.h"
#include "GuiApplication.h"
#include "globals.h"
#include "MainWindow.h"
#include "EditorMainWindow.h"
#include "ControlPanel.h"
#include "GameStructAccessor.h"
#include "wx/evtloop.h"

GuiApplication::GuiApplication() : eventLoop(nullptr), mainWindow(nullptr), editorMainWindow(nullptr), controlPanel(nullptr), idleEventTimer(nullptr)
{
    // Keep the wx "main" thread running even without windows. This greatly
    // simplifies threads handling, because we don't have to correctly
    // implement wx-thread restarting.
    //
    // Note that this only works if you don't explicitly call ExitMainLoop(),
    // except in reaction to wx_dll_cleanup()'s message. wx_dll_cleanup()
    // relies on the availability of wxApp instance and if the event loop
    // terminated, wxEntry() would return and wxApp instance would be
    // destroyed.
    //
    // Also note that this is efficient, because if there are no windows, the
    // thread will sleep waiting for a new event. We could safe some memory
    // by shutting the thread down when it's no longer needed, though.
	SetExitOnFrameDelete(false);
}

/*
void GuiApplication::OnShowWindow(wxThreadEvent& event)
{
    mainWindow->Show(event.GetInt());
}

void GuiApplication::OnTerminate(wxThreadEvent& event)
{
    MessageBoxA(0, "OnTerminate()", "", 0);
    //mainWindow->Destroy();
    ExitMainLoop();
}*/

bool GuiApplication::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }
    //wxMessageBox("OnInit()");
    //MSGBOX("OnInit()");
	//mainWindow = new MainWindow(nullptr);
    wxWindow* window = new wxWindow();
    window->SetHWND(gameAccessor->getWindowHandle()); // required for showModal() ???
    SetTopWindow(window);
    editorMainWindow = new EditorMainWindow(window);
    controlPanel = new ControlPanel(window);

    // GENERATE IDLE EVENTS
    // (they aren't generated automatically due to no event loop,
    // and are needed to safely delete windows (any other way to delete resulted in a crash))
    idleEventTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, [this](wxTimerEvent&) {this->ProcessIdle(); });
    idleEventTimer->Start(1000, wxTIMER_CONTINUOUS);
	wxToolTip::Enable(true);
    eventLoop = new wxGUIEventLoop;
    return true;
}

int GuiApplication::OnExit()
{
    delete idleEventTimer;
    return 0;
}

void GuiApplication::enterLoop()
{
    wxEventLoop::SetActive(eventLoop);
    eventLoop->Run();
}

void GuiApplication::leaveLoop()
{
    eventLoop->Exit();
    wxEventLoop::SetActive(nullptr);
}

wxIMPLEMENT_APP_NO_MAIN(GuiApplication);