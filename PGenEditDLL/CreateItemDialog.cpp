#include "pch.h"
#include "CreateItemDialog.h"

mm7::Item CreateItemDialog::getNewItemModal()
{
    ShowModal();
    return buildItemFromControlValues();
}

CreateItemDialog::CreateItemDialog(wxWindow* parent) : ItemDialogBase(parent)
{
    sizerItemCount = new wxBoxSizer(wxHORIZONTAL);

    labelItemCount = new wxStaticText(this, wxID_ANY, _("Count:"), wxDefaultPosition, wxDefaultSize, 0);
    labelItemCount->Wrap(-1);
    sizerItemCount->Add(labelItemCount, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    sliderItemCount = new wxSlider(this, wxID_ANY, 1, 1, 20, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    sliderItemCount->SetMinSize(wxSize(300, -1));

    sizerItemCount->Add(sliderItemCount, 0, wxALL, 5);
    // CRASHES (when closing dialog)
    assert(insertBeforeWindow(sizerMain, sizerEnchantments, new wxSizerItem(sizerItemCount, wxSizerFlags(1).Border(wxALL, 5).Expand())));
    assert(insertBeforeWindow(sizerMain, sizerEnchantments, new wxSizerItem(0, 15, 0, wxEXPAND, 5)));

    Layout();
    SendSizeEvent();
}