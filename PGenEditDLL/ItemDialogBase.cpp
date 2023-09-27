#include "pch.h"
#include "ItemDialogBase.h"
#include <wx/dataview.h>
#include <wx/spinctrl.h>
#include <wx/gbsizer.h>
#include "PlayerItem.h"
#include "ItemStructAccessor.h"
#include "GameData.h"

ItemDialogBase::ItemDialogBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    sizerMain = new wxBoxSizer(wxVERTICAL);

    checkboxItemIsFree = new wxCheckBox(this, wxID_ANY, _("Item is free"), wxDefaultPosition, wxDefaultSize, 0);
    checkboxItemIsFree->SetToolTip(_("If this is checked, guaranteed item won't decrease available \"item points\" pool (will essentially be free)"));

    sizerMain->Add(checkboxItemIsFree, 0, wxALL, 10);

    createItemFilters();

    wxStaticBoxSizer* sizerChooseItem;
    sizerChooseItem = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Choose item")), wxVERTICAL);

    itemTable = new wxDataViewListCtrl(sizerChooseItem->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    colNumber = itemTable->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, 50, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colName = itemTable->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colCategory = itemTable->AppendTextColumn(_("Category"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colType = itemTable->AppendTextColumn(_("Type"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colMod = itemTable->AppendTextColumn(_("Mod"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colMaterial = itemTable->AppendTextColumn(_("Material"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colExtra = itemTable->AppendTextColumn(_("Extra"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    colImage = itemTable->AppendIconTextColumn(_("Image"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);

    itemTableViewModel = new ItemTableViewModel(*this);
    itemTableViewModel->DecRef();
    itemTable->AssociateModel(itemTableViewModel);
    sizerChooseItem->Add(itemTable, 0, wxALL | wxEXPAND, 5);

    sizerMain->Add(sizerChooseItem, 1, wxEXPAND, 5);


    sizerMain->Add(0, 15, 0, wxEXPAND, 5);

    wxBoxSizer* sizerItemCount;
    sizerItemCount = new wxBoxSizer(wxHORIZONTAL);

    labelItemCount = new wxStaticText(this, wxID_ANY, _("Count:"), wxDefaultPosition, wxDefaultSize, 0);
    labelItemCount->Wrap(-1);
    sizerItemCount->Add(labelItemCount, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    sliderItemCount = new wxSlider(this, wxID_ANY, 1, 1, 20, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    sliderItemCount->SetMinSize(wxSize(300, -1));

    sizerItemCount->Add(sliderItemCount, 0, wxALL, 5);


    sizerMain->Add(sizerItemCount, 1, wxEXPAND, 5);

    createEnchantmentsStaticBox();

    sizerMain->Add(sizerEnchantments, 1, wxEXPAND, 5);


    sizerMain->Add(0, 5, 0, wxEXPAND, 5);

    createItemConditionTemporaryBonusPanel();


    sizerMain->Add(sizerTemporaryBonus, 1, wxEXPAND, 5);

    createWandSettings();

    sizerMain->Add(sizerWandSettings, 1, wxEXPAND, 5);


    this->SetSizer(sizerMain);
    this->Layout();

    this->Centre(wxBOTH);
}

void ItemDialogBase::createItemConditionTemporaryBonusPanel()
{
    sizerCondition = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Item condition")), wxHORIZONTAL);

    checkboxIdentified = new wxCheckBox(sizerCondition->GetStaticBox(), wxID_ANY, _("Identified"), wxDefaultPosition, wxDefaultSize, 0);
    checkboxIdentified->SetValue(true);
    sizerCondition->Add(checkboxIdentified, 0, wxALL, 5);

    checkboxBroken = new wxCheckBox(sizerCondition->GetStaticBox(), wxID_ANY, _("Broken"), wxDefaultPosition, wxDefaultSize, 0);
    sizerCondition->Add(checkboxBroken, 0, wxALL, 5);

    checkboxStolen = new wxCheckBox(sizerCondition->GetStaticBox(), wxID_ANY, _("Stolen (MM7)"), wxDefaultPosition, wxDefaultSize, 0);
    sizerCondition->Add(checkboxStolen, 0, wxALL, 5);

    checkboxHardened = new wxCheckBox(sizerCondition->GetStaticBox(), wxID_ANY, _("Hardened (MM7+)"), wxDefaultPosition, wxDefaultSize, 0);
    sizerCondition->Add(checkboxHardened, 0, wxALL, 5);


    sizerMain->Add(sizerCondition, 0, wxEXPAND, 5);


    sizerMain->Add(0, 5, 0, wxEXPAND, 5);

    sizerTemporaryBonus = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Temporary bonus")), wxHORIZONTAL);

    labelTmpEnchantmentType = new wxStaticText(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0);
    labelTmpEnchantmentType->Wrap(-1);
    sizerTemporaryBonus->Add(labelTmpEnchantmentType, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxArrayString choiceTmpEnchantmentChoices;
    choiceTmpEnchantment = new wxChoice(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceTmpEnchantmentChoices, 0);
    choiceTmpEnchantment->SetSelection(0);
    sizerTemporaryBonus->Add(choiceTmpEnchantment, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    sizerTemporaryBonus->Add(30, 0, 0, 0, 5);

    labelDays = new wxStaticText(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, _("Days:"), wxDefaultPosition, wxDefaultSize, 0);
    labelDays->Wrap(-1);
    sizerTemporaryBonus->Add(labelDays, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueDays = new wxSpinCtrl(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    sizerTemporaryBonus->Add(valueDays, 0, wxALL, 5);

    labelHours = new wxStaticText(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, _("Hours:"), wxDefaultPosition, wxDefaultSize, 0);
    labelHours->Wrap(-1);
    sizerTemporaryBonus->Add(labelHours, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueHours = new wxSpinCtrl(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    sizerTemporaryBonus->Add(valueHours, 0, wxALL, 5);

    labelMinutes = new wxStaticText(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, _("Minutes:"), wxDefaultPosition, wxDefaultSize, 0);
    labelMinutes->Wrap(-1);
    sizerTemporaryBonus->Add(labelMinutes, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueMinutes = new wxSpinCtrl(sizerTemporaryBonus->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    sizerTemporaryBonus->Add(valueMinutes, 0, wxALL, 5);
}

void ItemDialogBase::createWandSettings()
{
    sizerWandSettings = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Wand-specific settings")), wxVERTICAL);

    sizerMaxCharges = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer28;
    bSizer28 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText14 = new wxStaticText(sizerWandSettings->GetStaticBox(), wxID_ANY, _("Max charges:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText14->Wrap(-1);
    bSizer28->Add(m_staticText14, 0, wxALL, 5);

    checkboxWandChargesManualAmount = new wxCheckBox(sizerWandSettings->GetStaticBox(), wxID_ANY, _("Manual amount"), wxDefaultPosition, wxDefaultSize, 0);
    checkboxWandChargesManualAmount->SetToolTip(_("Enable to set your own amount. If disabled, game default will be generated."));

    bSizer28->Add(checkboxWandChargesManualAmount, 0, wxALL, 5);

    checkboxWandChargesVaryWithStrength = new wxCheckBox(sizerWandSettings->GetStaticBox(), wxID_ANY, _("Vary with strength"), wxDefaultPosition, wxDefaultSize, 0);
    checkboxWandChargesVaryWithStrength->SetValue(true);
    checkboxWandChargesVaryWithStrength->SetToolTip(_("If enabled, the stronger wand's spell is, the fewer charges (assumed input is for lowest-grade wands, that is about 35-45). Otherwise amount is exact, no matter what wand it is"));

    bSizer28->Add(checkboxWandChargesVaryWithStrength, 0, wxALL, 5);


    sizerMaxCharges->Add(bSizer28, 0, wxEXPAND, 5);

    wxBoxSizer* minSliderSizer;
    minSliderSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText151 = new wxStaticText(sizerWandSettings->GetStaticBox(), wxID_ANY, _("Min:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText151->Wrap(-1);
    minSliderSizer->Add(m_staticText151, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    sliderLowMaxCharges = new wxSlider(sizerWandSettings->GetStaticBox(), wxID_ANY, 50, 1, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    minSliderSizer->Add(sliderLowMaxCharges, 1, wxALL, 5);


    sizerMaxCharges->Add(minSliderSizer, 0, wxEXPAND, 5);

    wxBoxSizer* maxSliderSizer;
    maxSliderSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText161 = new wxStaticText(sizerWandSettings->GetStaticBox(), wxID_ANY, _("Max:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText161->Wrap(-1);
    maxSliderSizer->Add(m_staticText161, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    sliderHighMaxCharges = new wxSlider(sizerWandSettings->GetStaticBox(), wxID_ANY, 50, 1, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    maxSliderSizer->Add(sliderHighMaxCharges, 1, wxALL, 5);


    sizerMaxCharges->Add(maxSliderSizer, 0, wxEXPAND, 5);


    sizerWandSettings->Add(sizerMaxCharges, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer301;
    bSizer301 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText171 = new wxStaticText(sizerWandSettings->GetStaticBox(), wxID_ANY, _("Percentage of starting charges:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText171->Wrap(-1);
    bSizer301->Add(m_staticText171, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    sliderChargesPercentage = new wxSlider(sizerWandSettings->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    bSizer301->Add(sliderChargesPercentage, 1, wxALL, 5);


    sizerWandSettings->Add(bSizer301, 1, wxEXPAND, 5);
}
void ItemDialogBase::createEnchantmentsStaticBox()
{
    sizerEnchantments = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Enchantments")), wxVERTICAL);

    sizerEnchantmentsInner = new wxGridBagSizer(0, 0);
    sizerEnchantmentsInner->SetFlexibleDirection(wxBOTH);
    sizerEnchantmentsInner->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    radioNoEnchantment = new wxRadioButton(sizerEnchantments->GetStaticBox(), wxID_ANY, _("None"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radioNoEnchantment->SetValue(true);
    sizerEnchantmentsInner->Add(radioNoEnchantment, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

    radioStandardEnchantment = new wxRadioButton(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Standard"), wxDefaultPosition, wxDefaultSize, 0);
    sizerEnchantmentsInner->Add(radioStandardEnchantment, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* sizerStandardEnchantmentType;
    sizerStandardEnchantmentType = new wxBoxSizer(wxHORIZONTAL);

    labelStandardEnchantmentType = new wxStaticText(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0);
    labelStandardEnchantmentType->Wrap(-1);
    sizerStandardEnchantmentType->Add(labelStandardEnchantmentType, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxString standardEnchantmentTypeChoiceChoices[] = { _("Any"), _("of Might"), _("of Thought"), _("of Health"), _("of Fire Resistance") };
    int standardEnchantmentTypeChoiceNChoices = sizeof(standardEnchantmentTypeChoiceChoices) / sizeof(wxString);
    choiceStandardEnchantmentType = new wxChoice(sizerEnchantments->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, standardEnchantmentTypeChoiceNChoices, standardEnchantmentTypeChoiceChoices, 0);
    choiceStandardEnchantmentType->SetSelection(0);
    sizerStandardEnchantmentType->Add(choiceStandardEnchantmentType, 0, wxALL, 5);

    sizerEnchantmentsInner->Add(sizerStandardEnchantmentType, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND, 5);


    wxBoxSizer* sizerStandardEnchantmentPower;
    sizerStandardEnchantmentPower = new wxBoxSizer(wxHORIZONTAL);

    m_staticText26 = new wxStaticText(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Power:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText26->Wrap(-1);
    sizerStandardEnchantmentPower->Add(m_staticText26, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueStandardEnchantmentPower = new wxSpinCtrl(sizerEnchantments->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 25, 10);
    sizerStandardEnchantmentPower->Add(valueStandardEnchantmentPower, 0, wxALL, 5);


    sizerEnchantmentsInner->Add(sizerStandardEnchantmentPower, wxGBPosition(1, 3), wxGBSpan(1, 1), wxEXPAND, 5);

    radioSpecialEnchantment = new wxRadioButton(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Special"), wxDefaultPosition, wxDefaultSize, 0);
    sizerEnchantmentsInner->Add(radioSpecialEnchantment, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* sizerSpecialEnchantmentType;
    sizerSpecialEnchantmentType = new wxBoxSizer(wxHORIZONTAL);

    m_staticText181 = new wxStaticText(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText181->Wrap(-1);
    sizerSpecialEnchantmentType->Add(m_staticText181, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxString specialEnchantmentTypeChoiceChoices[] = { _("Any"), _("Warriors'"), _("of Life"), _("of Mana"), _("of the Dragon") };
    int specialEnchantmentTypeChoiceNChoices = sizeof(specialEnchantmentTypeChoiceChoices) / sizeof(wxString);
    choiceSpecialEnchantmentType = new wxChoice(sizerEnchantments->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, specialEnchantmentTypeChoiceNChoices, specialEnchantmentTypeChoiceChoices, 0);
    choiceSpecialEnchantmentType->SetSelection(0);
    sizerSpecialEnchantmentType->Add(choiceSpecialEnchantmentType, 1, wxALL, 5);


    sizerEnchantmentsInner->Add(sizerSpecialEnchantmentType, wxGBPosition(2, 1), wxGBSpan(1, 1), wxEXPAND, 5);

    randomEnchantmentRadio = new wxRadioButton(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Random"), wxDefaultPosition, wxDefaultSize, 0);
    sizerEnchantmentsInner->Add(randomEnchantmentRadio, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL, 5);

    wxBoxSizer* bSizer45;
    bSizer45 = new wxBoxSizer(wxHORIZONTAL);

    labelChance = new wxStaticText(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Chance:"), wxDefaultPosition, wxDefaultSize, 0);
    labelChance->Wrap(-1);
    bSizer45->Add(labelChance, 0, wxALL, 5);

    sliderRandomEnchantmentChance = new wxSlider(sizerEnchantments->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    bSizer45->Add(sliderRandomEnchantmentChance, 1, wxALL, 5);


    sizerEnchantmentsInner->Add(bSizer45, wxGBPosition(3, 1), wxGBSpan(1, 3), wxEXPAND, 5);

    wxBoxSizer* sizerRandomEnchantmentPower;
    sizerRandomEnchantmentPower = new wxBoxSizer(wxHORIZONTAL);

    m_staticText31 = new wxStaticText(sizerEnchantments->GetStaticBox(), wxID_ANY, _("Power:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText31->Wrap(-1);
    sizerRandomEnchantmentPower->Add(m_staticText31, 0, wxALL, 5);

    sliderRandomEnchantmentPower  = new wxSlider(sizerEnchantments->GetStaticBox(), wxID_ANY, 1, 1, 6, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS | wxSL_HORIZONTAL);
    sizerRandomEnchantmentPower->Add(sliderRandomEnchantmentPower , 0, wxALL | wxEXPAND, 5);


    sizerEnchantmentsInner->Add(sizerRandomEnchantmentPower, wxGBPosition(3, 4), wxGBSpan(1, 1), wxEXPAND, 5);


    sizerEnchantments->Add(sizerEnchantmentsInner, 1, wxEXPAND, 5);
}
void ItemDialogBase::createItemFilters()
{
    filtersSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Filter item list")), wxVERTICAL);

    filterButtonsSizer = new wxBoxSizer(wxHORIZONTAL);

    checkboxUseFilters = new wxCheckBox(filtersSizer->GetStaticBox(), wxID_ANY, _("Enable filters"), wxDefaultPosition, wxDefaultSize, 0);
    filterButtonsSizer->Add(checkboxUseFilters, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    buttonResetFilters = new wxButton(filtersSizer->GetStaticBox(), wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0);
    filterButtonsSizer->Add(buttonResetFilters, 0, wxALL, 5);


    filtersSizer->Add(filterButtonsSizer, 1, wxEXPAND, 5);

    panelFilters = new wxPanel(filtersSizer->GetStaticBox());
    wxBoxSizer* sizerFiltersPanel = new wxBoxSizer(wxVERTICAL);

    filtersSizer->Add(sizerFiltersPanel);

    wxBoxSizer* sizerItemFilterCategorySkill;
    sizerItemFilterCategorySkill = new wxBoxSizer(wxHORIZONTAL);

    labelItemCategory = new wxStaticText(panelFilters, wxID_ANY, _("Item category:"), wxDefaultPosition, wxDefaultSize, 0);
    labelItemCategory->Wrap(-1);
    sizerItemFilterCategorySkill->Add(labelItemCategory, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxString itemCategoryChoiceChoices[] = { _("Any"), _("Melee weapon"), _("Ranged weapon"), _("Armor"), _("Potion"), _("Scroll"), _("Book"), _("Jewelry"), _("Other") };
    int itemCategoryChoiceNChoices = sizeof(itemCategoryChoiceChoices) / sizeof(wxString);
    choiceItemCategory = new wxChoice(panelFilters, wxID_ANY, wxDefaultPosition, wxDefaultSize, itemCategoryChoiceNChoices, itemCategoryChoiceChoices, 0);
    choiceItemCategory->SetSelection(0);
    sizerItemFilterCategorySkill->Add(choiceItemCategory, 0, wxALL, 5);


    sizerItemFilterCategorySkill->Add(30, 0, 0, wxEXPAND, 5);

    m_staticText16 = new wxStaticText(panelFilters, wxID_ANY, _("Skill required to equip item:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText16->Wrap(-1);
    sizerItemFilterCategorySkill->Add(m_staticText16, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxString skillFilterChoiceChoices[] = { _("Any"), _("Other/no skill"), _("Club"), _("Sword"), _("Axe"), _("Blaster"), _("Fire magic"), _("Leather") };
    int skillFilterChoiceNChoices = sizeof(skillFilterChoiceChoices) / sizeof(wxString);
    choiceSkillFilter = new wxChoice(panelFilters, wxID_ANY, wxDefaultPosition, wxDefaultSize, skillFilterChoiceNChoices, skillFilterChoiceChoices, 0);
    choiceSkillFilter->SetSelection(0);
    sizerItemFilterCategorySkill->Add(choiceSkillFilter, 0, wxALL, 5);


    sizerFiltersPanel->Add(sizerItemFilterCategorySkill, 1, wxEXPAND, 5);

    wxBoxSizer* sizerFilterItemName;
    sizerFilterItemName = new wxBoxSizer(wxHORIZONTAL);

    m_staticText15 = new wxStaticText(panelFilters, wxID_ANY, _("Part of item's name (empty means any item):"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText15->Wrap(-1);
    sizerFilterItemName->Add(m_staticText15, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_textCtrl15 = new wxTextCtrl(panelFilters, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
#ifdef __WXGTK__
    if (!m_textCtrl15->HasFlag(wxTE_MULTILINE))
    {
        m_textCtrl15->SetMaxLength(30);
    }
#else
    m_textCtrl15->SetMaxLength(30);
#endif
    m_textCtrl15->SetMinSize(wxSize(250, -1));

    sizerFilterItemName->Add(m_textCtrl15, 0, wxALL, 5);


    sizerFiltersPanel->Add(sizerFilterItemName, 1, wxEXPAND, 5);

    wxBoxSizer* sizerFilterLowestRow;
    sizerFilterLowestRow = new wxBoxSizer(wxHORIZONTAL);

    m_staticText17 = new wxStaticText(panelFilters, wxID_ANY, _("Item type:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText17->Wrap(-1);
    sizerFilterLowestRow->Add(m_staticText17, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxString m_choice5Choices[] = { _("Any"), _("Leather"), _("Plate"), _("Weapon 1H"), _("Ring"), _("Boots") };
    int m_choice5NChoices = sizeof(m_choice5Choices) / sizeof(wxString);
    m_choice5 = new wxChoice(panelFilters, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice5NChoices, m_choice5Choices, 0);
    m_choice5->SetSelection(0);
    sizerFilterLowestRow->Add(m_choice5, 0, wxALL, 5);


    sizerFilterLowestRow->Add(30, 0, 0, wxEXPAND, 5);

    checkboxFilterShowQuestLoreItems = new wxCheckBox(panelFilters, wxID_ANY, _("Show quest/lore items"), wxDefaultPosition, wxDefaultSize, 0);
    sizerFilterLowestRow->Add(checkboxFilterShowQuestLoreItems, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    checkboxFilterShowSpecialItems = new wxCheckBox(panelFilters, wxID_ANY, _("Show special items"), wxDefaultPosition, wxDefaultSize, 0);
    sizerFilterLowestRow->Add(checkboxFilterShowSpecialItems, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    checkboxFilterShowArtifactsRelics = new wxCheckBox(panelFilters, wxID_ANY, _("Show artifacts/relics"), wxDefaultPosition, wxDefaultSize, 0);
    sizerFilterLowestRow->Add(checkboxFilterShowArtifactsRelics, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    sizerFiltersPanel->Add(sizerFilterLowestRow, 1, wxEXPAND, 5);


    sizerMain->Add(filtersSizer, 0, wxEXPAND, 5);


    sizerMain->Add(0, 5, 0, wxEXPAND, 5);
}

void ItemDialogBase::reapplyFilters()
{

}
void ItemDialogBase::setControlsEnabledState()
{
    bool filtersEnabled = checkboxUseFilters->IsChecked();
    panelFilters->Enable(filtersEnabled);
}

ItemDialogBase::~ItemDialogBase()
{

}

void ItemDialogBase::setControlValuesFromItem(const mm7::Item& item)
{
    wxDataViewEvent event;
    //event.
}

mm7::Item ItemDialogBase::buildItemFromControlValues()
{
    // TODO: create "BuildItemInformation" struct, which would be filled here and passed to other method, to facilitate testing this other method?
    mm7::Item item;
    memset(&item, 0, sizeof mm7::Item);
    // TODO: number
    if (radioSpecialEnchantment->GetValue())
    {
        item.bonus2 = choiceSpecialEnchantmentType->GetSelection(); // FIXME: translation tables
    }
    else if (radioStandardEnchantment->GetValue())
    {
        item.bonus = choiceStandardEnchantmentType->GetSelection(); // FIXME: see above
        item.bonusStrength = valueStandardEnchantmentPower->GetValue();
    }

    if (checkboxWandChargesManualAmount->IsChecked())
    
    item.identified = checkboxIdentified->IsChecked();
    item.broken = checkboxBroken->IsChecked();
    if (MMVER >= 7)
    {
        item.hardened = checkboxHardened->IsChecked();
    }
    if (MMVER == 7)
    {
        item.stolen = checkboxStolen->IsChecked();
    }
    return item;
}

mm7::Item ItemDialogBase::getNewItemModal()
{
    ShowModal();
    return buildItemFromControlValues();
}

mm7::Item ItemDialogBase::editItemModal(const mm7::Item& item)
{
    setControlValuesFromItem(item);
    ShowModal();
    return buildItemFromControlValues();
}

void ItemTableViewModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const
{
    const PlayerItem* playerItem = reinterpret_cast<const PlayerItem*>(&item);
    switch (col)
    {
    case 0: // id
        variant = (long)playerItem->id;
        break;
    case 1: // name
        variant = playerItem->name;
        break;
    case 2: // category (skill name)
    {
        PlayerSkill* sk = playerItem->skill;
        if (sk)
        {
            variant = GameData::skills.at(sk->id).name;
        }
        else
        {
            variant = "None";
        }
        break;
    }
    case 3: // type
        variant = playerItem->getItemTypeName();
        break;
    case 4: // mod
        variant = ""; // TODO
        break;
    case 5: // material
        variant = (long)playerItem->forItemTxtDo([](auto itemTxt) { return itemTxt->material; });
        break;
    case 6: // extra
        variant = ""; // TODO
        break;
    case 7: // image
        variant << *playerItem->image; // bitmaps require "shift left" operator
        break;
    }
}

bool ItemTableViewModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col)
{
    return false;
}

wxDataViewItem ItemTableViewModel::GetParent(const wxDataViewItem& item) const
{
    return wxDataViewItem();
}

bool ItemTableViewModel::IsContainer(const wxDataViewItem& item) const
{
    return false;
}

unsigned int ItemTableViewModel::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
{
    //itemAccessor->for
    return 0;
}

unsigned int ItemTableViewModel::GetColumnCount() const
{
    // NOT NEEDED, is not called because of deprecation
    return 8;
}

wxString ItemTableViewModel::GetColumnType(unsigned int col) const
{
    // NOT NEEDED, is not called because of deprecation
    return wxString();
}

ItemTableViewModel::ItemTableViewModel(ItemDialogBase& dialog) : dialog(dialog)
{
}
