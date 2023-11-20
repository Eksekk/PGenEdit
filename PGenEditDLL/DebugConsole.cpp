#include "pch.h"
#include "DebugConsole.h"
#include "LuaWrapper.h"

std::pair<std::string, bool> DebugConsole::runLua(const std::string& str)
{
    std::string result;
    bool success = true;
    int stack = luaWrapper.gettop();
    try
    {
        success = luaWrapper.dostring(str);
        if (!success)
        {
            result = luaWrapper.tostring(-1);
        }
    }
    catch (const std::exception& e)
    {
        result = e.what();
        success = false;
    }
    luaWrapper.settop(stack);

    return { result, success };
}

void DebugConsole::onClickRunScript(wxCommandEvent& event)
{
    processCommand();
}

void DebugConsole::processCommand()
{
    std::string cmd = textCtrl->GetValue().ToStdString().substr(lastResultEnd);
    if (!cmd.empty())
    {
        history.push_back(cmd);
        auto [result, success] = runLua(cmd);
        textCtrl->AppendText("\n------------------------------------------\n" + result);
        lastResultEnd = textCtrl->GetValue().size();
    }
}

DebugConsole::DebugConsole(wxWindow* parent) : wxFrame(parent, wxID_ANY, "Debug console", wxDefaultPosition, wxSize(800, 600))
{
    textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    runScriptButton = new wxButton(this, wxID_ANY, "Run script");
    runScriptButton->SetSize(wxSize(100, 30));
    sizerMain = new wxBoxSizer(wxVERTICAL);
    sizerMain->Add(textCtrl, wxSizerFlags(1).Border(wxALL, 5).Expand());
    sizerMain->Add(runScriptButton, wxSizerFlags(0).Border(wxALL, 5));
}

DebugConsole::~DebugConsole()
{
}

void DebugConsole::onEnter(wxCommandEvent& event)
{
    // when is OnEnter called?
    // when enter is pressed in the text control
    processCommand();
}

void DebugConsole::onText(wxCommandEvent& event)
{
    event.Skip();
    // ignore for now
}

void DebugConsole::onChar(wxKeyEvent& event)
{
    // alt + up arrow should go through history
    bool shouldGoThroughHistoryForwards = event.AltDown() && event.GetKeyCode() == WXK_UP;
    bool shouldGoThroughHistoryBackwards = event.AltDown() && event.GetKeyCode() == WXK_DOWN;
    if (shouldGoThroughHistoryForwards && historyIndex < history.size() - 1)
    {
        textCtrl->SetValue(textCtrl->GetValue().substr(lastResultEnd) + history[historyIndex]);
        historyIndex++;
    }
    else if (shouldGoThroughHistoryBackwards && historyIndex > 0)
    {
        textCtrl->SetValue(textCtrl->GetValue().substr(lastResultEnd) + history[historyIndex]);
        historyIndex--;
    }
    else
    {
        event.Skip();
    }
}

void DebugConsole::onSize(wxSizeEvent& event)
{
}

void DebugConsole::onClose(wxCloseEvent& event)
{
}
