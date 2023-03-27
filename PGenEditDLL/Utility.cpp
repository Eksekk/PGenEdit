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

wxString rep(const wxString& str, int n)
{
	wxString ret = str;
	for (int i = 0; i < n - 1; ++i)
	{
		ret << str;
	}
	return ret;
}

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
void Profiler::start(const std::string& action)
{
	this->action = action;
	profilingNow = true;
	profilingStart = std::chrono::steady_clock::now();
}

void Profiler::end()
{
	profilingEnd = std::chrono::steady_clock::now();
	profilingNow = false;
}

wxString Profiler::getDurationStr()
{
	std::chrono::nanoseconds nanos = profilingEnd - profilingStart;
	static const wxString formatStr = "[Profiler] Action \"%s\" took %lf seconds (%lld milliseconds)";
	double seconds = std::chrono::duration<double>(nanos).count();
	long long millis = std::chrono::duration_cast<std::chrono::milliseconds>(nanos).count();
	return wxString::Format(formatStr, action, seconds, millis);
}

void Profiler::startAggregate(const std::string& action)
{
	profilingNow = true;
	aggregateAction = action;
	aggregateTime = std::chrono::nanoseconds(0);
	aggregateMaxDuration = std::chrono::nanoseconds(0);
	aggregateCount = 0;
	aggregateMaxDurationIndex = 0;
}

void Profiler::endAggregate()
{
	profilingNow = false;
}

void Profiler::startAggregatePart()
{
	aggregateStart = std::chrono::steady_clock::now();
	++aggregateCount;
}

void Profiler::endAggregatePart()
{
	aggregateEnd = std::chrono::steady_clock::now();
	auto duration = aggregateEnd - aggregateStart;
	aggregateTime += duration;
	if (duration > aggregateMaxDuration)
	{
		aggregateMaxDuration = duration;
		aggregateMaxDurationIndex = aggregateCount - 1;
	}
}

wxString Profiler::getAggregateDurationStr()
{
	static const wxString formatStr = 
		"[Profiler] Performing %d actions \"%s\" took %lf seconds (%lld milliseconds)\n"
		"Average duration: %lf seconds, %lld milliseconds\n"
		"Highest duration was of action number #%d (%lf seconds, %lld milliseconds)";
	double secondsTotal = std::chrono::duration<double>(aggregateTime).count();
	long long millisTotal = std::chrono::duration_cast<std::chrono::milliseconds>(aggregateTime).count();
	double secondsAverage = std::chrono::duration<double>(aggregateTime / aggregateCount).count();
	long long millisAverage = std::chrono::duration_cast<std::chrono::milliseconds>(aggregateTime / aggregateCount).count();
	double secondsHighest = std::chrono::duration<double>(aggregateMaxDuration).count();
	long long millisHighest = std::chrono::duration_cast<std::chrono::milliseconds>(aggregateMaxDuration).count();
	return wxString::Format(formatStr,
		aggregateCount, aggregateAction, secondsTotal, millisTotal,
		secondsAverage, millisAverage,
		aggregateMaxDurationIndex, secondsHighest, millisHighest);
}

Profiler::Profiler() : aggregateCount(0), aggregateTime{0}, aggregateMaxDuration{0}, aggregateMaxDurationIndex(0), profilingNow(false)
{
	
}
