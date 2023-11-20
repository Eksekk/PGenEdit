#pragma once
#include "main.h"

// this will be a window representing simple console. Inside, the user will be able to enter lua commands and see the output. Commands will use RTTR reflection system to actually work.
class DebugConsole : public wxFrame
{
    wxButton* runScriptButton;
    std::vector<std::string> history;
    int historyIndex = 0;
    // position of last character of the result of previous command in the text control
    int lastResultEnd = 0;

    void onEnter(wxCommandEvent& event);
    void onText(wxCommandEvent& event);
    void onChar(wxKeyEvent& event);
    void onSize(wxSizeEvent& event);
    void onClose(wxCloseEvent& event);

    // controls
    wxTextCtrl* textCtrl;
    wxBoxSizer* sizerMain;
public:
    DebugConsole(wxWindow* parent);
    ~DebugConsole();

    wxDECLARE_EVENT_TABLE();

    std::pair<std::string, bool> runLua(const std::string& str);
    void onClickRunScript(wxCommandEvent& event);

    void processCommand();

};

