#pragma once
#include "main.h"

// this will be a window representing simple console. Inside, the user will be able to enter lua commands and see the output. Commands will use lua to interpret the script, and my custom functions callable in lua will use RTTR reflection system to actually work.
class DebugConsole : public wxFrame
{
    std::vector<std::string> history;
    int historyIndex = 0;
    // position of last character of the result of previous command in the text control
    int lastResultEnd = 0;

    // event handlers
    void onEnter(wxCommandEvent& event);
    void onText(wxCommandEvent& event);
    void onChar(wxKeyEvent& event);
    void onSize(wxSizeEvent& event);
    void onClose(wxCloseEvent& event);

    void onClearText(wxCommandEvent& event);
    void onClearHistory(wxCommandEvent& event);

    void onClickRunScript(wxCommandEvent& event);

    // controls
    wxButton* runScriptButton;
    wxButton* clearTextButton;
    wxButton* clearHistoryButton;

    wxTextCtrl* textCtrl;
    wxBoxSizer* sizerMain;
    wxBoxSizer* sizerButtons;
public:
    DebugConsole(wxWindow* parent);
    ~DebugConsole();

    // returns string with result and whether it was successful
    std::pair<std::string, bool> runLua(const std::string& str);

    void processCommand();

};

