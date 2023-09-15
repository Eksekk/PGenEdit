#include "pch.h"
#include "ItemDialogBase.h"
#include "wx/gbsizer.h"

ItemDialogBase::ItemDialogBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    mainSizer = new wxBoxSizer(wxVERTICAL);

    createItemFilters();


    wxStaticBoxSizer* chooseItemSizer;
    chooseItemSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Choose item")), wxVERTICAL);

    itemTable = new wxDataViewListCtrl(chooseItemSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    numberCol = itemTable->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, 50, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    nameCol = itemTable->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    categoryCol = itemTable->AppendTextColumn(_("Category"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    typeCol = itemTable->AppendTextColumn(_("Type"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    modCol = itemTable->AppendTextColumn(_("Mod"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    materialCol = itemTable->AppendTextColumn(_("Material"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    extraCol = itemTable->AppendTextColumn(_("Extra"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    imageCol = itemTable->AppendIconTextColumn(_("Image"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
    chooseItemSizer->Add(itemTable, 0, wxALL | wxEXPAND, 5);

    mainSizer->Add(chooseItemSizer, 1, wxEXPAND, 5);


    mainSizer->Add(0, 15, 0, wxEXPAND, 5);

    wxBoxSizer* bSizer44;
    bSizer44 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText30 = new wxStaticText(this, wxID_ANY, _("Count:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText30->Wrap(-1);
    bSizer44->Add(m_staticText30, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    itemCountLabel = new wxSlider(this, wxID_ANY, 1, 1, 20, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    itemCountLabel->SetMinSize(wxSize(300, -1));

    bSizer44->Add(itemCountLabel, 0, wxALL, 5);


    mainSizer->Add(bSizer44, 1, wxEXPAND, 5);

    createEnchantmentsStaticBox();

    mainSizer->Add(enchantmentsSizer, 1, wxEXPAND, 5);


    mainSizer->Add(0, 5, 0, wxEXPAND, 5);

    wxStaticBoxSizer* conditionSbSizer;
    conditionSbSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Item condition")), wxHORIZONTAL);

    identifiedCheckbox = new wxCheckBox(conditionSbSizer->GetStaticBox(), wxID_ANY, _("Identified"), wxDefaultPosition, wxDefaultSize, 0);
    identifiedCheckbox->SetValue(true);
    conditionSbSizer->Add(identifiedCheckbox, 0, wxALL, 5);

    brokenCheckbox = new wxCheckBox(conditionSbSizer->GetStaticBox(), wxID_ANY, _("Broken"), wxDefaultPosition, wxDefaultSize, 0);
    conditionSbSizer->Add(brokenCheckbox, 0, wxALL, 5);

    stolenCheckbox = new wxCheckBox(conditionSbSizer->GetStaticBox(), wxID_ANY, _("Stolen (MM7)"), wxDefaultPosition, wxDefaultSize, 0);
    conditionSbSizer->Add(stolenCheckbox, 0, wxALL, 5);

    hardenedCheckbox = new wxCheckBox(conditionSbSizer->GetStaticBox(), wxID_ANY, _("Hardened (MM7+)"), wxDefaultPosition, wxDefaultSize, 0);
    conditionSbSizer->Add(hardenedCheckbox, 0, wxALL, 5);


    mainSizer->Add(conditionSbSizer, 0, wxEXPAND, 5);


    mainSizer->Add(0, 5, 0, wxEXPAND, 5);

    wxStaticBoxSizer* temporaryBonusSizer;
    temporaryBonusSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Temporary bonus")), wxHORIZONTAL);

    labelTmpEnchantmentType = new wxStaticText(temporaryBonusSizer->GetStaticBox(), wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0);
    labelTmpEnchantmentType->Wrap(-1);
    temporaryBonusSizer->Add(labelTmpEnchantmentType, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxArrayString choiceTmpEnchantmentChoices;
    choiceTmpEnchantment = new wxChoice(temporaryBonusSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceTmpEnchantmentChoices, 0);
    choiceTmpEnchantment->SetSelection(0);
    temporaryBonusSizer->Add(choiceTmpEnchantment, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    temporaryBonusSizer->Add(30, 0, 0, 0, 5);

    labelDays = new wxStaticText(temporaryBonusSizer->GetStaticBox(), wxID_ANY, _("Days:"), wxDefaultPosition, wxDefaultSize, 0);
    labelDays->Wrap(-1);
    temporaryBonusSizer->Add(labelDays, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueDays = new wxSpinCtrl(temporaryBonusSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    temporaryBonusSizer->Add(valueDays, 0, wxALL, 5);

    labelHours = new wxStaticText(temporaryBonusSizer->GetStaticBox(), wxID_ANY, _("Hours:"), wxDefaultPosition, wxDefaultSize, 0);
    labelHours->Wrap(-1);
    temporaryBonusSizer->Add(labelHours, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueHours = new wxSpinCtrl(temporaryBonusSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    temporaryBonusSizer->Add(valueHours, 0, wxALL, 5);

    labelMinutes = new wxStaticText(temporaryBonusSizer->GetStaticBox(), wxID_ANY, _("Minutes:"), wxDefaultPosition, wxDefaultSize, 0);
    labelMinutes->Wrap(-1);
    temporaryBonusSizer->Add(labelMinutes, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    valueMinutes = new wxSpinCtrl(temporaryBonusSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    temporaryBonusSizer->Add(valueMinutes, 0, wxALL, 5);


    mainSizer->Add(temporaryBonusSizer, 1, wxEXPAND, 5);

    createWandSettings();

    mainSizer->Add(wandSettingsSizer, 1, wxEXPAND, 5);


    this->SetSizer(mainSizer);
    this->Layout();

    this->Centre(wxBOTH);
}

void ItemDialogBase::createWandSettings()
{
    wandSettingsSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Wand-specific settings")), wxVERTICAL);

    maxChargesSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer28;
    bSizer28 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText14 = new wxStaticText(wandSettingsSizer->GetStaticBox(), wxID_ANY, _("Max charges:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText14->Wrap(-1);
    bSizer28->Add(m_staticText14, 0, wxALL, 5);

    wandChargesManualAmountCheckbox = new wxCheckBox(wandSettingsSizer->GetStaticBox(), wxID_ANY, _("Manual amount"), wxDefaultPosition, wxDefaultSize, 0);
    wandChargesManualAmountCheckbox->SetToolTip(_("Enable to set your own amount. If disabled, game default will be generated."));

    bSizer28->Add(wandChargesManualAmountCheckbox, 0, wxALL, 5);

    wandChargesVaryWithStrengthCheckbox = new wxCheckBox(wandSettingsSizer->GetStaticBox(), wxID_ANY, _("Vary with strength"), wxDefaultPosition, wxDefaultSize, 0);
    wandChargesVaryWithStrengthCheckbox->SetValue(true);
    wandChargesVaryWithStrengthCheckbox->SetToolTip(_("If enabled, the stronger wand's spell is, the fewer charges (assumed input is for lowest-grade wands, that is about 35-45). Otherwise amount is exact, no matter what wand it is"));

    bSizer28->Add(wandChargesVaryWithStrengthCheckbox, 0, wxALL, 5);


    maxChargesSizer->Add(bSizer28, 0, wxEXPAND, 5);

    wxBoxSizer* minSliderSizer;
    minSliderSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText151 = new wxStaticText(wandSettingsSizer->GetStaticBox(), wxID_ANY, _("Min:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText151->Wrap(-1);
    minSliderSizer->Add(m_staticText151, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    lowMaxChargesSizer = new wxSlider(wandSettingsSizer->GetStaticBox(), wxID_ANY, 50, 1, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    minSliderSizer->Add(lowMaxChargesSizer, 1, wxALL, 5);


    maxChargesSizer->Add(minSliderSizer, 0, wxEXPAND, 5);

    wxBoxSizer* maxSliderSizer;
    maxSliderSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText161 = new wxStaticText(wandSettingsSizer->GetStaticBox(), wxID_ANY, _("Max:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText161->Wrap(-1);
    maxSliderSizer->Add(m_staticText161, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    highMaxChargesSizer = new wxSlider(wandSettingsSizer->GetStaticBox(), wxID_ANY, 50, 1, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    maxSliderSizer->Add(highMaxChargesSizer, 1, wxALL, 5);


    maxChargesSizer->Add(maxSliderSizer, 0, wxEXPAND, 5);


    wandSettingsSizer->Add(maxChargesSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer301;
    bSizer301 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText171 = new wxStaticText(wandSettingsSizer->GetStaticBox(), wxID_ANY, _("Percentage of starting charges:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText171->Wrap(-1);
    bSizer301->Add(m_staticText171, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    chargesPercentageSizer = new wxSlider(wandSettingsSizer->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    bSizer301->Add(chargesPercentageSizer, 1, wxALL, 5);


    wandSettingsSizer->Add(bSizer301, 1, wxEXPAND, 5);
}
void ItemDialogBase::createEnchantmentsStaticBox()
{
    enchantmentsSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Enchantments")), wxVERTICAL);

    enchantmentsInnerSizer = new wxGridBagSizer(0, 0);
    enchantmentsInnerSizer->SetFlexibleDirection(wxBOTH);
    enchantmentsInnerSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    noEnchantmentRadio = new wxRadioButton(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("None"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    noEnchantmentRadio->SetValue(true);
    enchantmentsInnerSizer->Add(noEnchantmentRadio, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

    standardEnchantmentRadio = new wxRadioButton(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Standard"), wxDefaultPosition, wxDefaultSize, 0);
    enchantmentsInnerSizer->Add(standardEnchantmentRadio, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* bSizer361;
    bSizer361 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText18 = new wxStaticText(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText18->Wrap(-1);
    bSizer361->Add(m_staticText18, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxString standardEnchantmentTypeChoiceChoices[] = { _("Any"), _("of Might"), _("of Thought"), _("of Health"), _("of Fire Resistance") };
    int standardEnchantmentTypeChoiceNChoices = sizeof(standardEnchantmentTypeChoiceChoices) / sizeof(wxString);
    standardEnchantmentTypeChoice = new wxChoice(enchantmentsSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, standardEnchantmentTypeChoiceNChoices, standardEnchantmentTypeChoiceChoices, 0);
    standardEnchantmentTypeChoice->SetSelection(0);
    bSizer361->Add(standardEnchantmentTypeChoice, 0, wxALL, 5);


    enchantmentsInnerSizer->Add(bSizer361, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND, 5);

    specialEnchantmentRadio = new wxRadioButton(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Special"), wxDefaultPosition, wxDefaultSize, 0);
    enchantmentsInnerSizer->Add(specialEnchantmentRadio, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* bSizer3611;
    bSizer3611 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText181 = new wxStaticText(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText181->Wrap(-1);
    bSizer3611->Add(m_staticText181, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxString specialEnchantmentTypeChoiceChoices[] = { _("Any"), _("Warriors'"), _("of Life"), _("of Mana"), _("of the Dragon") };
    int specialEnchantmentTypeChoiceNChoices = sizeof(specialEnchantmentTypeChoiceChoices) / sizeof(wxString);
    specialEnchantmentTypeChoice = new wxChoice(enchantmentsSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, specialEnchantmentTypeChoiceNChoices, specialEnchantmentTypeChoiceChoices, 0);
    specialEnchantmentTypeChoice->SetSelection(0);
    bSizer3611->Add(specialEnchantmentTypeChoice, 1, wxALL, 5);


    enchantmentsInnerSizer->Add(bSizer3611, wxGBPosition(2, 1), wxGBSpan(1, 1), wxEXPAND, 5);

    wxBoxSizer* bSizer40;
    bSizer40 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText26 = new wxStaticText(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Power:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText26->Wrap(-1);
    bSizer40->Add(m_staticText26, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    standardEnchantmentPowerText = new wxTextCtrl(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer40->Add(standardEnchantmentPowerText, 0, wxALL, 5);


    enchantmentsInnerSizer->Add(bSizer40, wxGBPosition(1, 3), wxGBSpan(1, 1), wxEXPAND, 5);

    randomEnchantmentRadio = new wxRadioButton(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Random"), wxDefaultPosition, wxDefaultSize, 0);
    enchantmentsInnerSizer->Add(randomEnchantmentRadio, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL, 5);

    wxBoxSizer* bSizer45;
    bSizer45 = new wxBoxSizer(wxHORIZONTAL);

    chanceLabel = new wxStaticText(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Chance:"), wxDefaultPosition, wxDefaultSize, 0);
    chanceLabel->Wrap(-1);
    bSizer45->Add(chanceLabel, 0, wxALL, 5);

    randomEnchantmentChanceSlider = new wxSlider(enchantmentsSizer->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
    bSizer45->Add(randomEnchantmentChanceSlider, 1, wxALL, 5);


    enchantmentsInnerSizer->Add(bSizer45, wxGBPosition(3, 1), wxGBSpan(1, 3), wxEXPAND, 5);

    wxBoxSizer* bSizer441;
    bSizer441 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText31 = new wxStaticText(enchantmentsSizer->GetStaticBox(), wxID_ANY, _("Power:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText31->Wrap(-1);
    bSizer441->Add(m_staticText31, 0, wxALL, 5);

    m_slider9 = new wxSlider(enchantmentsSizer->GetStaticBox(), wxID_ANY, 1, 1, 6, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS | wxSL_HORIZONTAL);
    bSizer441->Add(m_slider9, 0, wxALL | wxEXPAND, 5);


    enchantmentsInnerSizer->Add(bSizer441, wxGBPosition(3, 4), wxGBSpan(1, 1), wxEXPAND, 5);


    enchantmentsSizer->Add(enchantmentsInnerSizer, 1, wxEXPAND, 5);
}
void ItemDialogBase::createItemFilters()
{

    itemIsFreeCheckbox = new wxCheckBox(this, wxID_ANY, _("Item is free"), wxDefaultPosition, wxDefaultSize, 0);
    itemIsFreeCheckbox->SetToolTip(_("If this is checked, guaranteed item won't decrease available \"item points\" pool (will essentially be free)"));

    mainSizer->Add(itemIsFreeCheckbox, 0, wxALL, 10);

    wxStaticBoxSizer* filtersSizer;
    filtersSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Filter item list")), wxVERTICAL);

    wxBoxSizer* filterButtonsSizer;
    filterButtonsSizer = new wxBoxSizer(wxHORIZONTAL);

    useFiltersCheckbox = new wxCheckBox(filtersSizer->GetStaticBox(), wxID_ANY, _("Enable filters"), wxDefaultPosition, wxDefaultSize, 0);
    filterButtonsSizer->Add(useFiltersCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    resetButton = new wxButton(filtersSizer->GetStaticBox(), wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0);
    filterButtonsSizer->Add(resetButton, 0, wxALL, 5);


    filtersSizer->Add(filterButtonsSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer36;
    bSizer36 = new wxBoxSizer(wxHORIZONTAL);

    itemCategoryLabel = new wxStaticText(filtersSizer->GetStaticBox(), wxID_ANY, _("Item category:"), wxDefaultPosition, wxDefaultSize, 0);
    itemCategoryLabel->Wrap(-1);
    bSizer36->Add(itemCategoryLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxString itemCategoryChoiceChoices[] = { _("Any"), _("Melee weapon"), _("Ranged weapon"), _("Armor"), _("Potion"), _("Scroll"), _("Book"), _("Jewelry"), _("Other") };
    int itemCategoryChoiceNChoices = sizeof(itemCategoryChoiceChoices) / sizeof(wxString);
    itemCategoryChoice = new wxChoice(filtersSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, itemCategoryChoiceNChoices, itemCategoryChoiceChoices, 0);
    itemCategoryChoice->SetSelection(0);
    bSizer36->Add(itemCategoryChoice, 0, wxALL, 5);


    bSizer36->Add(30, 0, 0, wxEXPAND, 5);

    m_staticText16 = new wxStaticText(filtersSizer->GetStaticBox(), wxID_ANY, _("Skill required to equip item:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText16->Wrap(-1);
    bSizer36->Add(m_staticText16, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxString skillFilterChoiceChoices[] = { _("Any"), _("Other/no skill"), _("Club"), _("Sword"), _("Axe"), _("Blaster"), _("Fire magic"), _("Leather") };
    int skillFilterChoiceNChoices = sizeof(skillFilterChoiceChoices) / sizeof(wxString);
    skillFilterChoice = new wxChoice(filtersSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, skillFilterChoiceNChoices, skillFilterChoiceChoices, 0);
    skillFilterChoice->SetSelection(0);
    bSizer36->Add(skillFilterChoice, 0, wxALL, 5);


    filtersSizer->Add(bSizer36, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer38;
    bSizer38 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText15 = new wxStaticText(filtersSizer->GetStaticBox(), wxID_ANY, _("Part of item's name (empty means any item):"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText15->Wrap(-1);
    bSizer38->Add(m_staticText15, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_textCtrl15 = new wxTextCtrl(filtersSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
#ifdef __WXGTK__
    if (!m_textCtrl15->HasFlag(wxTE_MULTILINE))
    {
        m_textCtrl15->SetMaxLength(30);
    }
#else
    m_textCtrl15->SetMaxLength(30);
#endif
    m_textCtrl15->SetMinSize(wxSize(250, -1));

    bSizer38->Add(m_textCtrl15, 0, wxALL, 5);


    filtersSizer->Add(bSizer38, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer39;
    bSizer39 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText17 = new wxStaticText(filtersSizer->GetStaticBox(), wxID_ANY, _("Item type:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText17->Wrap(-1);
    bSizer39->Add(m_staticText17, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxString m_choice5Choices[] = { _("Any"), _("Leather"), _("Plate"), _("Weapon 1H"), _("Ring"), _("Boots") };
    int m_choice5NChoices = sizeof(m_choice5Choices) / sizeof(wxString);
    m_choice5 = new wxChoice(filtersSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice5NChoices, m_choice5Choices, 0);
    m_choice5->SetSelection(0);
    bSizer39->Add(m_choice5, 0, wxALL, 5);


    bSizer39->Add(30, 0, 0, wxEXPAND, 5);

    m_checkBox27 = new wxCheckBox(filtersSizer->GetStaticBox(), wxID_ANY, _("Show quest/lore items"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer39->Add(m_checkBox27, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    m_checkBox28 = new wxCheckBox(filtersSizer->GetStaticBox(), wxID_ANY, _("Show special items"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer39->Add(m_checkBox28, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    m_checkBox30 = new wxCheckBox(filtersSizer->GetStaticBox(), wxID_ANY, _("Show artifacts/relics"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer39->Add(m_checkBox30, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    filtersSizer->Add(bSizer39, 1, wxEXPAND, 5);


    mainSizer->Add(filtersSizer, 0, wxEXPAND, 5);


    mainSizer->Add(0, 5, 0, wxEXPAND, 5);
}
ItemDialogBase::~ItemDialogBase()
{
}