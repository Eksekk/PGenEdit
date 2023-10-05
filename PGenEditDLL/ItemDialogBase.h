#pragma once
#include "pch.h"
#include "main.h"
#include <wx/dataview.h>

class ItemDialogBase;
class ItemTableViewModel : public wxDataViewModel
{
private:
    wxVector<wxVector<wxVariant>> data;
public:
    void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;

    bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;

    wxDataViewItem GetParent(const wxDataViewItem& item) const override;

    bool IsContainer(const wxDataViewItem& item) const override;

    unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;

    unsigned int GetColumnCount() const override;
    wxString GetColumnType(unsigned int col) const override;
    ItemDialogBase& dialog;

    std::unordered_map<int, int> classIdsToTableIndexes;
    ItemTableViewModel(ItemDialogBase& dialog);
};

class wxDataViewListCtrl;
class wxDataViewColumn;
class wxSpinCtrl;
class wxGridBagSizer;

// base class for "generate random item", "edit item" and "create item" dialog
class ItemDialogBase : public wxDialog
{
private:

protected:
    ItemTableViewModel* itemTableViewModel;
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
    wxCheckBox* checkboxFilterShowQuestLoreItems;
    wxCheckBox* checkboxFilterShowSpecialItems;
    wxCheckBox* checkboxFilterShowArtifactsRelics;
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
