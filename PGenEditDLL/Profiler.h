#pragma once
#include "pch.h"
#include "main.h"

class Profiler
{
    std::chrono::time_point<std::chrono::steady_clock> profilingStart;
    std::chrono::time_point<std::chrono::steady_clock> profilingEnd;
    std::string action;

    std::chrono::time_point<std::chrono::steady_clock> aggregateStart;
    std::chrono::time_point<std::chrono::steady_clock> aggregateEnd;
    std::chrono::nanoseconds aggregateTime;
    std::chrono::nanoseconds aggregateMaxDuration;
    int aggregateMaxDurationIndex;
    std::string aggregateAction;
    int aggregateCount;
public:
    bool profilingNow;
    void start(const std::string& action);
    void end();
    wxString getDurationStr();
    void startAggregate(const std::string& action);
    void endAggregate();
    void startAggregatePart();
    void endAggregatePart();
    wxString getAggregateDurationStr();
    void logResults();

    Profiler();
};