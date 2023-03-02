#include "pch.h"
#include "EditorSkillValueChooser.h"
#include "Enum_const.h"
#include "Utility.h"

extern int MAX_SKILL_LEVEL;

const std::unordered_map<int, Mastery> EditorSkillValueChooser::masteryToIdMap{ {0,  MASTERY_NONE}, {1, MASTERY_NOVICE},
    {2, MASTERY_EXPERT}, {3, MASTERY_MASTER}, {4, MASTERY_GM } };

const std::unordered_map<Mastery, int> EditorSkillValueChooser::idToMasteryMap = invertMap(EditorSkillValueChooser::masteryToIdMap);

const std::array<wxString, 5> EditorSkillValueChooser::masteryNames{ "None", "Novice", "Expert", "Master", "GM" };

EditorSkillValueChooser::EditorSkillValueChooser(wxWindow* parent, const wxString& labelText) : wxPanel(parent)
{
    wxFlexGridSizer* mainSizer = new wxFlexGridSizer(3, 0, 5);
    SetSizer(mainSizer);
    skillNameLabel = new wxStaticText(parent, wxID_ANY, labelText);
    mainSizer->Add(skillNameLabel, wxSizerFlags().Expand()); // expand to line up all instances of this class in skills panel
    skillLevel = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_SKILL_LEVEL, 0);
    mainSizer->Add(skillLevel);
    skillMastery = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxArrayString(5, masteryNames.data()));
    mainSizer->Add(skillMastery);
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
