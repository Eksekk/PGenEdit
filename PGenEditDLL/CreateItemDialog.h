#pragma once
#include "main.h"
#include "ItemDialogBase.h"

class CreateItemDialog : public ItemDialogBase
{
    // generator & create
    wxStaticText* labelItemCount;
    wxSlider* sliderItemCount;
    wxBoxSizer* sizerItemCount;

public:
    // create & edit
    // returns whether item was successfully created (user didn't exit dialog with cancel etc.)
    std::optional<mm7::Item> getNewItemModal();
    CreateItemDialog(wxWindow* parent);
};

