#pragma once
#include "pch.h"
#include "main.h"
#include <wx/dataview.h>
#include <wx/spinctrl.h>

class ItemDialogBase : public wxDialog
{
private:

protected:
    // window content
    wxCheckBox* itemIsFreeCheckbox;
    wxCheckBox* useFiltersCheckbox;
    wxButton* resetButton;
    wxStaticText* itemCategoryLabel;
    wxChoice* itemCategoryChoice;
    wxStaticText* m_staticText16;
    wxChoice* skillFilterChoice;
    wxStaticText* m_staticText15;
    wxTextCtrl* m_textCtrl15;
    wxStaticText* m_staticText17;
    wxChoice* m_choice5;
    wxCheckBox* m_checkBox27;
    wxCheckBox* m_checkBox28;
    wxCheckBox* m_checkBox30;
    wxDataViewListCtrl* itemTable;
    wxDataViewColumn* numberCol;
    wxDataViewColumn* nameCol;
    wxDataViewColumn* categoryCol;
    wxDataViewColumn* typeCol;
    wxDataViewColumn* modCol;
    wxDataViewColumn* materialCol;
    wxDataViewColumn* extraCol;
    wxDataViewColumn* imageCol;
    wxStaticText* m_staticText30;
    wxSlider* itemCountLabel;
    wxRadioButton* noEnchantmentRadio;
    wxRadioButton* standardEnchantmentRadio;
    wxStaticText* m_staticText18;
    wxChoice* standardEnchantmentTypeChoice;
    wxRadioButton* specialEnchantmentRadio;
    wxStaticText* m_staticText181;
    wxChoice* specialEnchantmentTypeChoice;
    wxStaticText* m_staticText26;
    wxTextCtrl* standardEnchantmentPowerText;
    wxRadioButton* randomEnchantmentRadio;
    wxStaticText* chanceLabel;
    wxSlider* randomEnchantmentChanceSlider;
    wxStaticText* m_staticText31;
    wxSlider* m_slider9;
    wxCheckBox* identifiedCheckbox;
    wxCheckBox* brokenCheckbox;
    wxCheckBox* stolenCheckbox;
    wxCheckBox* hardenedCheckbox;
    wxStaticText* labelTmpEnchantmentType;
    wxChoice* choiceTmpEnchantment;
    wxStaticText* labelDays;
    wxSpinCtrl* valueDays;
    wxStaticText* labelHours;
    wxSpinCtrl* valueHours;
    wxStaticText* labelMinutes;
    wxSpinCtrl* valueMinutes;
    wxStaticText* m_staticText14;
    wxCheckBox* wandChargesManualAmountCheckbox;
    wxCheckBox* wandChargesVaryWithStrengthCheckbox;
    wxStaticText* m_staticText151;
    wxSlider* lowMaxChargesSizer;
    wxStaticText* m_staticText161;
    wxSlider* highMaxChargesSizer;
    wxStaticText* m_staticText171;
    wxSlider* chargesPercentageSizer;

    // sizers
    wxBoxSizer* mainSizer;
    wxStaticBoxSizer* enchantmentsSizer;
    wxGridBagSizer* enchantmentsInnerSizer;

public:

    ItemDialogBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create item"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(791, 794), long style = wxDEFAULT_DIALOG_STYLE);

    void createWandSettings();

    void createEnchantmentsStaticBox();

	void createItemFilters();

    ~ItemDialogBase();

};

