#include "pch.h"
#include "main.h"
#include "Utility.h"

// string functions

std::string stringToLower(const std::string& source)
{
	std::string out = source;
	for (char& c : out)
	{
		c = std::tolower(c);
	}
	return out;
}

std::vector<std::string> stringSplit(const std::string& text, const std::string& delimiter, bool ignoreCase)
{
    std::string useText = ignoreCase ? stringToLower(text) : text;
    std::string useDelimiter = ignoreCase ? stringToLower(delimiter) : delimiter;
    std::vector<std::string> strings;
    size_t pos = 0, foundPos;
    while ((foundPos = useText.find(useDelimiter, pos)) != std::string::npos)
    {
        strings.push_back(text.substr(pos, foundPos - pos));
        pos = foundPos + useDelimiter.size();
    }
    strings.push_back(text.substr(pos));
    return strings;
}

std::vector<std::string> stringSplit(const std::string& text, char delimiter, bool ignoreCase)
{
    std::string s;
    s.push_back(delimiter);
    return stringSplit(text, s, ignoreCase);
}

wxString stringRep(const wxString& str, int n)
{
    wxString ret = str;
    ret.reserve(str.size() * n);
    for (int i = 0; i < n - 1; ++i)
    {
        ret << str;
    }
    return ret;
}

wxString getTimeStr()
{
	auto endTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return wxString(std::ctime(&endTime));
}

// json functions
void jsonEnsureIsObject(Json& json)
{
    json = !json.is_object() ? Json::object() : json;
}

void jsonEnsureIsArray(Json& json)
{
    json = !json.is_array() ? Json::array() : json;
}

// wxWidgets functions
void redBlackGreenTextThreshold(wxWindow* win, int value, int threshold)
{
    if (value < threshold)
    {
        win->SetOwnForegroundColour(*wxRED);
    }
    else if (value > threshold)
    {
        win->SetOwnForegroundColour(*wxGREEN);
    }
    else
    {
        win->SetOwnForegroundColour(*wxBLACK);
    }
}

// misc functions
Bounds getBounds(int size)
{
	static const uint64_t
		u1_max = std::numeric_limits<uint8_t>::max(),
		u2_max = std::numeric_limits<uint16_t>::max(),
		u4_max = std::numeric_limits<uint32_t>::max();

	static const int64_t
		i1_min = std::numeric_limits<int8_t>::min(),
		i2_min = std::numeric_limits<int16_t>::min(),
		i4_min = std::numeric_limits<int32_t>::min(),
		i1_max = std::numeric_limits<int8_t>::max(),
		i2_max = std::numeric_limits<int16_t>::max(),
		i4_max = std::numeric_limits<int32_t>::max();

	int64_t low, high;

	bool uns = size > 0;
	switch (std::abs(size))
	{
	case 1:
	{
		low = uns ? 0 : i1_min;
		high = uns ? u1_max : i1_max;
		break;
	}
	case 2:
	{
		low = uns ? 0 : i2_min;
		high = uns ? u2_max : i2_max;
		break;
	}
	case 4:
	{
		low = uns ? 0 : i4_min;
		high = uns ? u4_max : i4_max;
		break;
	}
	case 8:
	{
		low = 0;
		high = u4_max;
		wxLogError("8-byte bounds are not implemented yet");
		wxLog::FlushActive();
		break;
	}
	default:
	{
		wxLogError("Unknown size (%d) in getBounds()", size);
		wxLog::FlushActive();
		return Bounds{ 0, 0 };
	}

	}
	return Bounds{ low, high };
}