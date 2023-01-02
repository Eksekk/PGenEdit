#include "pch.h"
#include "Application.h"
#include "globals.h"
#include "MainWindow.h"

Application::Application()
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

    Bind(wxEVT_THREAD, &Application::OnShowWindow, this, CMD_SHOW_WINDOW);
    Bind(wxEVT_THREAD, &Application::OnTerminate, this, CMD_TERMINATE);
}

void Application::OnShowWindow(wxThreadEvent& event)
{
    mainWindow->Show(event.GetInt());
}

void Application::OnTerminate(wxThreadEvent& event)
{
    MessageBoxA(0, "OnTerminate()", "", 0);
    //mainWindow->Destroy();
    ExitMainLoop();
}

bool Application::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }
    //wxMessageBox("OnInit()");
    //MSGBOX("OnInit()");
    mainWindow = new MainWindow(nullptr);
    return true;
}

// we can't have WinMain() in a DLL and want to start the app ourselves
wxIMPLEMENT_APP_NO_MAIN(Application);