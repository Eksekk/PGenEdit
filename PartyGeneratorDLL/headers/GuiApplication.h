#pragma once
#include "pch.h"
#include "main.h"
#include "MainWindow.h"
class GuiApplication : public wxApp
{
public:
    GuiApplication();
    MainWindow* mainWindow;

    virtual bool OnInit();

private:
    void OnShowWindow(wxThreadEvent& event);
    void OnTerminate(wxThreadEvent& event);
};

wxDECLARE_APP(GuiApplication);