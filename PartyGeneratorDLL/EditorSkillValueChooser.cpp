#include "pch.h"
#include "EditorSkillValueChooser.h"
#include "Enum_const.h"
#include "Utility.h"

extern int MAX_SKILL_LEVEL;

const std::unordered_map<int, Mastery> EditorSkillValueChooser::masteryToIdMap{ {0,  MASTERY_NONE}, {1, MASTERY_NOVICE},
    {2, MASTERY_EXPERT}, {3, MASTERY_MASTER}, {4, MASTERY_GM } };

const std::unordered_map<Mastery, int> EditorSkillValueChooser::idToMasteryMap = invertMap(EditorSkillValueChooser::masteryToIdMap);

const std::array<wxString, 5> EditorSkillValueChooser::masteryNames{ "None", "Novice", "Expert", "Master", "GM" };

wxDEFINE_EVENT(SKILL_VALUE_CHANGE, wxCommandEvent);

EditorSkillValueChooser::EditorSkillValueChooser(wxWindow* parent, const wxString& labelText) : wxPanel(parent)
{
    wxFlexGridSizer* mainSizer = new wxFlexGridSizer(MMVER == 6 ? 3 : 4, 0, 5);
    mainSizer->SetFlexibleDirection(wxBOTH);
    SetSizer(mainSizer);
    skillNameLabel = new wxStaticText(this, wxID_ANY, labelText);
    mainSizer->Add(skillNameLabel, wxSizerFlags().CenterVertical().Border(wxALL, 5)); // stretch to line up all instances of this class in skills panel
    // PROPORTION DOESN'T WORK IN FLEX SIZER
    // AddGrowableCol() works
    mainSizer->AddGrowableCol(0, 1);
    skillLevel = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_SKILL_LEVEL, 0);
    skillLevel->Bind(wxEVT_SPINCTRL, &EditorSkillValueChooser::onValueChange, this);
    mainSizer->Add(skillLevel, wxSizerFlags().Border(wxALL, 5));
    if (MMVER > 6)
    {
		skillLevelBonusLabel = new wxStaticText(this, wxID_ANY, "0");
		skillLevelBonusLabel->SetToolTip("Skill bonus, like from magic rings or followers");
		mainSizer->Add(skillLevelBonusLabel, wxSizerFlags().CenterVertical().Border(wxALL, 5));
    }
    else
    {
        skillLevelBonusLabel = nullptr;
    }
    skillMastery = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxArrayString(static_cast<int>(MAX_MASTERY) + 1, masteryNames.data()));

	skillMastery->Bind(wxEVT_CHOICE, &EditorSkillValueChooser::onValueChange, this);
    mainSizer->Add(skillMastery, wxSizerFlags().Border(wxALL, 5));
    Layout();
}

SkillValue EditorSkillValueChooser::getValue()
{
    return SkillValue{ skillLevel->GetValue(), masteryToIdMap.at(skillMastery->GetSelection()) };
}

int EditorSkillValueChooser::getLevel()
{
    return skillLevel->GetValue();
}

Mastery EditorSkillValueChooser::getMastery()
{
    return masteryToIdMap.at(skillMastery->GetSelection());
}

void EditorSkillValueChooser::setValue(const SkillValue& value)
{
    skillLevel->SetValue(value.level);
    skillMastery->SetSelection(idToMasteryMap.at(static_cast<Mastery>(value.mastery)));
}

void EditorSkillValueChooser::setValue(int value)
{
    setValue(splitSkill(value));
}

void EditorSkillValueChooser::setLevel(int level)
{
    skillLevel->SetValue(level);
}

void EditorSkillValueChooser::setMastery(Mastery mastery)
{
    skillMastery->SetSelection(idToMasteryMap.at(mastery));
}

void EditorSkillValueChooser::updateSkillBonus(int value)
{
    skillLevelBonusLabel->SetLabel(wxString::Format("%d", value));
    if (value > 0)
    {
        skillLevelBonusLabel->SetForegroundColour(*wxGREEN);
        skillLevelBonusLabel->SetLabel("+" + skillLevelBonusLabel->GetLabel());
    }
    else if (value < 0)
    {
        skillLevelBonusLabel->SetForegroundColour(*wxRED);
    }
    else
    {
        skillLevelBonusLabel->SetForegroundColour(*wxBLACK);
    }
}

void EditorSkillValueChooser::onValueChange(wxCommandEvent& event)
{
    // doing this roundabout way because couldn't get event object in skills panel and decided to do my own event category
    wxCommandEvent event2(SKILL_VALUE_CHANGE, GetId());
    event2.SetEventObject(this); // IMPORTANT !!!, event object is not set automatically
    ProcessWindowEvent(event2);
}