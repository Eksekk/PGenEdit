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
    sizerMain = new wxBoxSizer(wxVERTICAL);
    sizerMain->Add(textCtrl, wxSizerFlags(1).Border(wxALL, 5).Expand());
    sizerButtons = new wxBoxSizer(wxHORIZONTAL);
    static const wxSizerFlags buttonFlags = wxSizerFlags().Border(wxALL, 5);
    sizerMain->Add(sizerButtons, wxSizerFlags().Expand().Border(wxALL, 5));
    static const wxSize buttonSize(100, 30);
    // TODO: make buttons able to be stretched if text doesn't fit in provided size
    runScriptButton = new wxButton(this, wxID_ANY, "Run script");
    runScriptButton->SetSize(buttonSize);
    clearTextButton = new wxButton(this, wxID_ANY, "Clear text");
    clearTextButton->SetSize(buttonSize);
    clearHistoryButton = new wxButton(this, wxID_ANY, "Clear command history");
    clearHistoryButton->SetSize(buttonSize);
}

DebugConsole::~DebugConsole()
{
}

void DebugConsole::onEnter(wxCommandEvent& event)
{
    // when is OnEnter called?
    // when enter is pressed in the text control
    event.Skip();
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
    if (shouldGoThroughHistoryForwards && historyIndex < (int)history.size() - 1)
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
    event.Skip();
}

void DebugConsole::onClose(wxCloseEvent& event)
{
    event.Skip();
}

void DebugConsole::onClearText(wxCommandEvent& event)
{
    textCtrl->SetValue("");
    lastResultEnd = 0;
}

void DebugConsole::onClearHistory(wxCommandEvent& event)
{
    history.clear();
    historyIndex = 0;
}
