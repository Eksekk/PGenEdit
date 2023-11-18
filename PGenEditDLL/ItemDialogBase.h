#pragma once
#include "main.h"
#include <wx/dataview.h>
#include "Utility.h"

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
    template<typename T>
    bool insertAfterBeforeWindow(wxSizer* sizer, const T* before, wxSizerItem* item, bool after)
    {
        const wxSizerItemList& list = sizer->GetChildren();
        for (size_t i = 0; i < sizer->GetItemCount(); ++i)
        {
            const T* ptr = nullptr;
            if constexpr (std::is_base_of_v<wxWindow, T>)
            {
                ptr = dynamic_cast<const T*>(list[i]->GetWindow());
            }
            else if constexpr (std::is_base_of_v<wxSizer, T>)
            {
                ptr = dynamic_cast<const T*>(list[i]->GetSizer());
            }
            else
            {
                COMPILE_TIME_CONSTEXPR_IF_ERROR();
            }

            // possible problems:
            // - parent not changed
            // - not inserted into destination sizer
            // - not detached from parent sizer
            // - no layout refresh
            
            // CHECK RETURN VALUE
            if (ptr && ptr == before) // found
            {
                wxWindow* destinationParent = sizer->GetContainingWindow();

                if (item->IsWindow())
                {
                    wxSizer* sizerContainingItem = item->GetWindow()->GetSizer();
                    if (sizerContainingItem)
                    {
                        sizerContainingItem->Detach(item->GetWindow());
                    }
                    wxASSERT(item->GetWindow()->Reparent(destinationParent));
                }
                else if (wxSizer* const itemAsSizer = item->GetSizer())
                {
                    // sizer might have containing window or be a child of another sizer
                    // need to detach it from parent sizers or from containing window
                    if (wxWindow* w = itemAsSizer->GetContainingWindow())
                    {
                        if (w->GetSizer() == itemAsSizer) // main sizer of parent window
                        {
                            w->SetSizer(nullptr, false);
                        }
                    }
                    
                    // need to take care to reparent every window that is reachable only through sizers (so child of reparented one won't be)
                    std::vector<wxSizer*> sizersToCheck{ itemAsSizer };
                    wxSizer* parentSizer = nullptr;
                    while (!sizersToCheck.empty())
                    {
                        wxSizer* sizer = sizersToCheck.back();
                        sizersToCheck.pop_back();
                        for (wxSizerItem* sizerItem : sizer->GetChildren())
                        {
                            if (sizerItem->IsSizer())
                            {
                                sizersToCheck.push_back(sizerItem->GetSizer());
                                if (sizerItem->GetSizer() == itemAsSizer)
                                {
                                    parentSizer = sizerItem->GetSizer();
                                }
                            }
                            else if (sizerItem->IsWindow())
                            {
                                wxASSERT(sizerItem->GetWindow()->Reparent(destinationParent));
                            }
                        }
                    }
                    if (parentSizer)
                    {
                        parentSizer->Detach(itemAsSizer);
                    }
                }
                int idx = i + (after ? 1 : 0);
                sizer->Insert(idx, item);
                return true;
            }
        }
        return false;
    }

protected:

    template<typename T>
    bool insertBeforeWindow(wxSizer* sizer, const T* before, wxSizerItem* item)
    {
        return insertAfterBeforeWindow(sizer, before, item, false);
    }

    template<typename T>
    bool insertAfterWindow(wxSizer* sizer, const T* before, wxSizerItem* item)
    {
        return insertAfterBeforeWindow(sizer, before, item, true);
    }

    // generator
    wxCheckBox* checkboxItemIsFree;
    wxCheckBox* checkboxWandChargesVaryWithStrength;
    wxStaticText* m_staticText151;
    wxSlider* sliderLowMaxCharges;
    wxStaticText* m_staticText161;
    wxSlider* sliderHighMaxCharges;

    // generator
    //wxStaticText* labelItemCount;
    //wxSlider* sliderItemCount;

    // create & edit
    mm7::Item editItemModal(const mm7::Item& item);

    ItemTableViewModel* itemTableViewModel;
    // window content
    wxScrolledWindow* panelMain;
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
    wxStaticBoxSizer* sizerFiltersMain;
    wxBoxSizer* filterButtonsSizer;

    virtual void createItemConditionTemporaryBonusPanel();
    virtual void createWandSettings();
    virtual void createEnchantmentsStaticBox();
    virtual void createItemFilters();
    virtual void reapplyFilters();
    virtual void setControlsEnabledState();
    virtual void setControlValuesFromItem(const mm7::Item& item);
    mm7::Item buildItemFromControlValues();

    void onClose(wxCloseEvent& event);
public:

    enum class Mode
    {
        CREATE,
        EDIT
    };
    Mode mode;
    ItemDialogBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create sizerItem"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(791, 794), long style = wxDEFAULT_DIALOG_STYLE);

    ~ItemDialogBase();

};
