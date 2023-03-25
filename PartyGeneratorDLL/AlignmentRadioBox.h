#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
class AlignmentRadioBox : public wxRadioBox
{
public:
	static const wxString texts[4];
	static const std::map<Alignment, int> alignmentIndexes;

	AlignmentRadioBox(wxWindow* parent, wxString&& label, bool useAny = true);
	AlignmentRadioBox(wxWindow* parent, const wxString& label, bool useAny = true);

	Alignment getSelectedAlignment();
	bool setSelection(Alignment alignment);
	bool setSelection(const wxString& str);
	bool enableAlignment(Alignment alignment, bool enable = true);
	const bool useAny;
};