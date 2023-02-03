#include "pch.h"
#include "AlignmentRadioBox.h"

const wxString AlignmentRadioBox::texts[4] = { "Any", "Neutral", "Light", "Dark" };
const std::map<Alignment, int> AlignmentRadioBox::alignmentIndexes = { {ALIGNMENT_ANY, 0}, {ALIGNMENT_NEUTRAL, 1}, {ALIGNMENT_LIGHT, 2}, {ALIGNMENT_DARK, 3} };

//generateWhatRadioBox = new wxRadioBox(levelPanel, wxID_ANY, _("Generate"), wxDefaultPosition, wxDefaultSize, generateWhatRadioBoxNChoices, generateWhatRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
AlignmentRadioBox::AlignmentRadioBox(wxWindow* parent, wxString&& label) : wxRadioBox(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, 4, texts, 0, wxRA_SPECIFY_COLS)
{
	IsValid(5);
	SetSelection(alignmentIndexes.at(ALIGNMENT_ANY));
}

AlignmentRadioBox::AlignmentRadioBox(wxWindow* parent, const wxString& label) : wxRadioBox(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, 4, texts, 0, wxRA_SPECIFY_COLS)
{
	SetSelection(alignmentIndexes.at(ALIGNMENT_ANY));
}

Alignment AlignmentRadioBox::getSelectedAlignment()
{
	int sel = GetSelection();
	assert(sel >= 0 && sel <= 3);
	return (Alignment)sel;
}

bool AlignmentRadioBox::setSelection(Alignment alignment)
{
	auto itr = alignmentIndexes.find(alignment);
	assert(itr != alignmentIndexes.end());
	SetSelection(itr->second);
	return true;
}

bool AlignmentRadioBox::setSelection(const wxString& str)
{
	for (int i = 0; i < 4; ++i)
	{
		if (str.CmpNoCase(texts[i]) == 0)
		{
			SetSelection(i);
			return true;
		}
	}
	assert(false);
	return false;
}
