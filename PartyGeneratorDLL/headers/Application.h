#pragma once
#include "pch.h"
#include "main.h"
#include "MainWindow.h"
class Application : public wxApp
{
public:
    Application();
    MainWindow* mainWindow = nullptr;

    virtual bool OnInit();

private:
    void OnShowWindow(wxThreadEvent& event);
    void OnTerminate(wxThreadEvent& event);
};

