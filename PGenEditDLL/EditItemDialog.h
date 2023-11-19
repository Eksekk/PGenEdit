#pragma once
#include "main.h"
#include "ItemDialogBase.h"

class EditItemDialog : public ItemDialogBase
{
public:
    std::optional<mm7::Item> getEditedItemModal(mm7::Item& item);
    EditItemDialog(wxWindow* parent);
};

