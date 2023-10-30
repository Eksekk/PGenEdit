#include "pch.h"
#include "NotebookReplaceableTabs.h"

wxWindow* NotebookReplaceableTabs::replacePageAt(int index, wxWindow* replaceWith, const std::string& titlePlaceholder, const wxString& titleContent)
{
    // TODO!!!: RemovePage might allow to keep tab contents in memory, avoiding "a ton of controls" problem, since it's removed from the window?
    //this->SetEvtHandlerEnabled(false);
    Freeze();
    wxON_BLOCK_EXIT0([&] {Thaw(); /*this->SetEvtHandlerEnabled(true);*/ });

    wxWindow* oldSelWindow = GetPage(index);
    // replace old content page with dummy
    InsertPage(index, new wxPanel(this), titlePlaceholder);
    DeletePage(index + 1);

    // replace dummy page with newly created one
    InsertPage(index + 1, replaceWith, titleContent);
    try
    {
        DeletePage(index);
    }
    catch (const std::exception& ex)
    {
        wxLogError(ex.what());
        wxLog::FlushActive();
    }
    return oldSelWindow;
}

NotebookReplaceableTabs::NotebookReplaceableTabs(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& title)
    : wxNotebook(parent, id, pos, size, style, title)
{
    
}