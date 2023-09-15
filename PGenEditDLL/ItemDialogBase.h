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
    wxCheckBox* checkboxItemIsFree;
    wxCheckBox* checkboxUseFilters;
    wxButton* buttonResetFilters;
    wxStaticText* labelItemCategory;
    wxChoice* choiceItemCategory;
    wxStaticText* m_staticText16;
    wxChoice* choiceSkillFilter;
    wxStaticText* m_staticText15;
    wxTextCtrl* m_textCtrl15;
    wxStaticText* m_staticText17;
    wxChoice* m_choice5;
    wxCheckBox* m_checkBox27;
    wxCheckBox* m_checkBox28;
    wxCheckBox* m_checkBox30;
    wxDataViewListCtrl* itemTable;
    wxDataViewColumn* colNumber;
    wxDataViewColumn* colName;
    wxDataViewColumn* colCategory;
    wxDataViewColumn* colType;
    wxDataViewColumn* colMod;
    wxDataViewColumn* colMaterial;
    wxDataViewColumn* colExtra;
    wxDataViewColumn* colImage;
    wxStaticText* labelItemCount;
    wxSlider* sliderItemCount;
    wxRadioButton* radioNoEnchantment;
    wxRadioButton* radioStandardEnchantment;
    wxStaticText* m_staticText18;
    wxChoice* radioStandardEnchantmentType;
    wxRadioButton* radioSpecialEnchantment;
    wxStaticText* m_staticText181;
    wxChoice* choiceSpecialEnchantmentType;
    wxStaticText* m_staticText26;
    wxTextCtrl* textStandardEnchantmentPower;
    wxRadioButton* randomEnchantmentRadio;
    wxStaticText* labelChance;
    wxSlider* sliderRandomEnchantmentChance;
    wxStaticText* m_staticText31;
    wxSlider* m_slider9;
    wxCheckBox* checkboxIdentified;
    wxCheckBox* checkboxBroken;
    wxCheckBox* checkboxStolen;
    wxCheckBox* checkboxHardened;
    wxStaticText* labelTmpEnchantmentType;
    wxChoice* choiceTmpEnchantment;
    wxStaticText* labelDays;
    wxSpinCtrl* valueDays;
    wxStaticText* labelHours;
    wxSpinCtrl* valueHours;
    wxStaticText* labelMinutes;
    wxSpinCtrl* valueMinutes;
    wxStaticText* m_staticText14;
    wxCheckBox* checkboxWandChargesManualAmount;
    wxCheckBox* checkboxWandChargesVaryWithStrength;
    wxStaticText* m_staticText151;
    wxSlider* sizerLowMaxCharges;
    wxStaticText* m_staticText161;
    wxSlider* sizerHighMaxCharges;
    wxStaticText* m_staticText171;
    wxSlider* sizerChargesPercentage;

    // sizers
    wxBoxSizer* sizerMain;
    wxStaticBoxSizer* sizerEnchantments;
    wxGridBagSizer* sizerEnchantmentsInner;
    wxStaticBoxSizer* sizerWandSettings;
    wxBoxSizer* sizerMaxCharges;
    wxStaticBoxSizer* sizerCondition;
    wxStaticBoxSizer* sizerTemporaryBonus;
public:

    enum class Mode
    {
        CREATE,
        EDIT
    };
    Mode mode;

    ItemDialogBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create item"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(791, 794), long style = wxDEFAULT_DIALOG_STYLE);

    void createItemConditionTemporaryBonusPanel();

    void createWandSettings();

    void createEnchantmentsStaticBox();

	void createItemFilters();

    template<typename Item>
    mm7::Item getNewItemModal(const Item& item);

    ~ItemDialogBase();

};

template mm7::Item ItemDialogBase::getNewItemModal<mm6::Item>(const mm6::Item& item);
template mm7::Item ItemDialogBase::getNewItemModal<mm7::Item>(const mm7::Item& item);
template mm7::Item ItemDialogBase::getNewItemModal<mm8::Item>(const mm8::Item& item);
