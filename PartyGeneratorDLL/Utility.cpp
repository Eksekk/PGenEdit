#include "pch.h"
#include "main.h"
#include "Utility.h"

std::string tolowerStr(const std::string& source)
{
	std::string out = source;
	for (char& c : out)
	{
		c = std::tolower(c);
	}
	return out;
}

wxString getTimeStr()
{
	auto endTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return wxString(std::ctime(&endTime));
}

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

