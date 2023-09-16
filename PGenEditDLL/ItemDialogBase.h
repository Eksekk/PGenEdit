#pragma once
#include "pch.h"
#include "main.h"

class wxDataViewListCtrl;
class wxDataViewColumn;
class wxSpinCtrl;
class wxGridBagSizer;

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
    wxStaticText* labelStandardEnchantmentType;
    wxChoice* choiceStandardEnchantmentType;
    wxRadioButton* radioSpecialEnchantment;
    wxStaticText* m_staticText181;
    wxChoice* choiceSpecialEnchantmentType;
    wxStaticText* m_staticText26;
    wxSpinCtrl* valueStandardEnchantmentPower;
    wxRadioButton* randomEnchantmentRadio;
    wxStaticText* labelChance;
    wxSlider* sliderRandomEnchantmentChance;
    wxStaticText* m_staticText31;
    wxSlider* sliderRandomEnchantmentPower ;
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
    wxSlider* sliderLowMaxCharges;
    wxStaticText* m_staticText161;
    wxSlider* sliderHighMaxCharges;
    wxStaticText* m_staticText171;
    wxSlider* sliderChargesPercentage;
    wxPanel* panelFilters; // will contain controls to disable/enable all of them with single method call

    // sizers
    wxBoxSizer* sizerMain;
    wxStaticBoxSizer* sizerEnchantments;
    wxGridBagSizer* sizerEnchantmentsInner;
    wxStaticBoxSizer* sizerWandSettings;
    wxBoxSizer* sizerMaxCharges;
    wxStaticBoxSizer* sizerCondition;
    wxStaticBoxSizer* sizerTemporaryBonus;
    wxStaticBoxSizer* filtersSizer;
    wxBoxSizer* filterButtonsSizer;

    void createItemConditionTemporaryBonusPanel();
    void createWandSettings();
    void createEnchantmentsStaticBox();
    void createItemFilters();
    void reapplyFilters();
    void setControlsEnabledState();
    void setControlValuesFromItem(const mm7::Item& item);
    mm7::Item buildItemFromControlValues();
public:

    enum class Mode
    {
        CREATE,
        EDIT
    };
    Mode mode;
    ItemDialogBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create item"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(791, 794), long style = wxDEFAULT_DIALOG_STYLE);

    mm7::Item getNewItemModal();
    mm7::Item editItemModal(const mm7::Item& item);

    ~ItemDialogBase();

};
