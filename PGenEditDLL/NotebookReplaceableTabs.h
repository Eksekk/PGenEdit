#pragma once
#include "main.h"
#include <wx/notebook.h>

class NotebookReplaceableTabs : public wxNotebook
{
public:
    // returns old panel
    wxWindow* replacePageAt(int index, wxWindow* replaceWith, const std::string& titlePlaceholder = "", const wxString& titleContent = "");
    NotebookReplaceableTabs(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(843, 479),
        long style = 0, const wxString& title = _(""));
private:
};

