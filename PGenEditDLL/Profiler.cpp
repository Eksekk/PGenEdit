#include "pch.h"
#include "Profiler.h"

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

void Profiler::logResults()
{
    if (aggregateCount > 0)
    {
        if (profilingNow)
        {
            endAggregatePart();
            endAggregate();
        }
        wxLogMessage(getAggregateDurationStr());
    }
    else
    {
        if (profilingNow)
        {
            end();
        }
        wxLogMessage(getDurationStr());
    }
    wxLog::FlushActive();
}

Profiler::Profiler() : aggregateCount(0), aggregateTime{ 0 }, aggregateMaxDuration{ 0 }, aggregateMaxDurationIndex(0), profilingNow(false)
{

}
