#include "pch.h"
#include "EditItemDialog.h"

std::optional<mm7::Item> EditItemDialog::getEditedItemModal(mm7::Item& item)
{
    setControlValuesFromItem(item);
    if (static_cast<ShowModalReturn>(ShowModal()) == ShowModalReturn::OK)
    {
        return buildItemFromControlValues();
    }
    else
    {
        return std::nullopt;
    }
}

EditItemDialog::EditItemDialog(wxWindow* parent) : ItemDialogBase(parent)
{
}
