#include "pch.h"
#include "AlignmentRadioBox.h"

const wxString AlignmentRadioBox::texts[4] = { "Any", "Neutral", "Light", "Dark" };
const std::map<Alignment, int> AlignmentRadioBox::alignmentIndexes = { {ALIGNMENT_ANY, 0}, {ALIGNMENT_NEUTRAL, 1}, {ALIGNMENT_LIGHT, 2}, {ALIGNMENT_DARK, 3} };

//generateWhatRadioBox = new wxRadioBox(levelPanel, wxID_ANY, _("Generate"), wxDefaultPosition, wxDefaultSize, generateWhatRadioBoxNChoices, generateWhatRadioBoxChoices, 1, wxRA_SPECIFY_ROWS);
AlignmentRadioBox::AlignmentRadioBox(wxWindow* parent, wxString&& label, bool useAny) : wxRadioBox(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, useAny ? 4 : 3, useAny ? texts : texts + 1, 0, wxRA_SPECIFY_COLS), useAny(useAny)
{
	SetSelection(alignmentIndexes.at(useAny ? ALIGNMENT_ANY : ALIGNMENT_NEUTRAL));
}

AlignmentRadioBox::AlignmentRadioBox(wxWindow* parent, const wxString& label, bool useAny) : wxRadioBox(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, useAny ? 4 : 3, useAny ? texts : texts + 1, 0, wxRA_SPECIFY_COLS), useAny(useAny)
{
	SetSelection(alignmentIndexes.at(useAny ? ALIGNMENT_ANY : ALIGNMENT_NEUTRAL));
}

Alignment AlignmentRadioBox::getSelectedAlignment()
{
	int sel = GetSelection();
	assert(sel >= 0 && sel <= (useAny ? 3 : 2));
	return (Alignment)(useAny ? sel : sel + 1);
}

bool AlignmentRadioBox::setSelection(Alignment alignment)
{
	auto itr = alignmentIndexes.find(alignment);
	assert(itr != alignmentIndexes.end());
	SetSelection(itr->second - (useAny ? 0 : 1));
	return true;
}

bool AlignmentRadioBox::setSelection(const wxString& str)
{
	for (int i = useAny ? 0 : 1; i < 4; ++i)
	{
		if (str.CmpNoCase(texts[i]) == 0)
		{
			SetSelection(useAny ? i : i - 1);
			return true;
		}
	}
	assert(false);
	return false;
}
