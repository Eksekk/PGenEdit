#pragma once
#include "pch.h"
#include "main.h"
#include "ItemDialogBase.h"

class CreateItemDialog : public ItemDialogBase
{
    // generator & create
    wxStaticText* labelItemCount;
    wxSlider* sliderItemCount;

public:
    // create & edit
    mm7::Item getNewItemModal();
    CreateItemDialog(wxWindow* parent);
};

