#include "pch.h"
#include "EditorSkillValueChooser.h"
#include "Enum_const.h"
#include "Utility.h"

extern int MAX_SKILL_LEVEL;

const std::unordered_map<int, Mastery> EditorSkillValueChooser::masteryToIdMap{ {0, MASTERY_NONE}, {1, MASTERY_NOVICE},
    {2, MASTERY_EXPERT}, {3, MASTERY_MASTER}, {4, MASTERY_GM } };

const std::unordered_map<Mastery, int> EditorSkillValueChooser::idToMasteryMap = invertMap(EditorSkillValueChooser::masteryToIdMap);

const std::array<wxString, 5> EditorSkillValueChooser::masteryNames{ "None", "Novice", "Expert", "Master", "GM" };

wxDEFINE_EVENT(SKILL_VALUE_CHANGE, wxCommandEvent);

EditorSkillValueChooser::EditorSkillValueChooser(wxWindow* parent, const wxString& labelText) : wxPanel(parent)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	SetSizer(mainSizer);
	wxBoxSizer* innerSizer = new wxBoxSizer(wxHORIZONTAL); // to allow sizer "border" to have color
    // NOTE my first attempt used panel inside current panel and didn't work (after showing layout wasn't recalculated), adding sizer works
	mainSizer->Add(innerSizer, wxSizerFlags(1).Expand().Border(wxALL, 5));
    skillNameLabel = new wxStaticText(this, wxID_ANY, labelText);
    innerSizer->Add(skillNameLabel, wxSizerFlags(1).CenterVertical().Border(wxRIGHT, 5)); // stretch to line up all instances of this class in skills panel
    skillLevel = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_SKILL_LEVEL, 0);
    skillLevel->Bind(wxEVT_SPINCTRL, &EditorSkillValueChooser::onValueChange, this);
    innerSizer->Add(skillLevel);
    static wxSize skillLevelMinSize{ 45, -1 };
    skillLevel->SetMinSize(skillLevelMinSize);
    if (MMVER > 6)
    {
		skillLevelBonusLabel = new wxStaticText(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_CENTER_HORIZONTAL);
		skillLevelBonusLabel->SetToolTip("Skill bonus, like from magic rings or followers");
		innerSizer->Add(skillLevelBonusLabel, wxSizerFlags().CenterVertical().Border(wxALL, 5));
        static wxSize textExtent;
        static bool set = false;
        if (!set) // text width calculation might be expensive, caching just in case
        {
            // and I'm just in case deferring calculation until first chooser creation, because wx won't be initialized yet
            // and text width is much more complex operation than setting two-member struct (skillLevelMinSize)
            textExtent = wxWindow::GetTextExtent("0000");
            set = true;
        }
        skillLevelBonusLabel->SetMinSize(textExtent); // align evenly, even if some bonuses are 0 and some +15
    }
    else
    {
        skillLevelBonusLabel = nullptr;
    }
    skillMastery = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, static_cast<int>(MAX_MASTERY) + 1, masteryNames.data());

	skillMastery->Bind(wxEVT_CHOICE, &EditorSkillValueChooser::onValueChange, this);
	innerSizer->Add(skillMastery);

    Bind(wxEVT_SHOW, &EditorSkillValueChooser::onShow, this);
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
    static const wxFont FONT_NORMAL, FONT_BOLD(-1, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    // FIRST SET COLOR, THEN LABEL, OTHERWISE COLOR MIGHT NOT BE CHANGED
	if (value > 0)
	{
		skillLevelBonusLabel->SetForegroundColour(*wxGREEN);
		skillLevelBonusLabel->SetLabel(wxString::Format("+%d", value));
		skillLevelBonusLabel->SetOwnFont(FONT_BOLD);
	}
	else if (value < 0)
	{
		skillLevelBonusLabel->SetForegroundColour(*wxRED);
		skillLevelBonusLabel->SetLabel(wxString::Format("%d", value));
		skillLevelBonusLabel->SetOwnFont(FONT_BOLD);
	}
	else
	{
		skillLevelBonusLabel->SetForegroundColour(*wxBLACK);
		skillLevelBonusLabel->SetLabel(wxString::Format("%d", value));
		skillLevelBonusLabel->SetOwnFont(FONT_NORMAL);
	}
}

void EditorSkillValueChooser::onValueChange(wxCommandEvent& event)
{
    // doing this roundabout way because couldn't get event object in skills panel and decided to do my own event category
    wxCommandEvent event2(SKILL_VALUE_CHANGE, GetId());
    event2.SetEventObject(this); // IMPORTANT !!!, event object is not set automatically
    ProcessWindowEvent(event2);
}

void EditorSkillValueChooser::setRowColor(const wxColour& colour)
{
    SetBackgroundColour(colour);
}

void EditorSkillValueChooser::onShow(wxShowEvent& event)
{
    if (!event.IsShown()) return;
    this->Layout();
    Layout();
    GetSizer()->Layout();
}
