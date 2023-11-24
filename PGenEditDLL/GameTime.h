#pragma once
#include "main.h"
class GameTime
{
    int64_t ticks, minutes, hours, days, weeks, months, years;

    void calculateValuesFromTicks();
public:

    // returns ONLY ticks value, for full ticks use getFullTicks()
    int64_t getTicks() const;
    int64_t getFullTicks() const;
    // zeroes all values except ticks
    void setTicksExclusive(int64_t val);
    // changes ticks value and recalculates all other values
    void setTicks(int64_t val);
    int64_t getMinutes() const;
    void setMinutes(int64_t val);
    int64_t getHours() const;
    void setHours(int64_t val);
    int64_t getDays() const;
    void setDays(int64_t val);
    int64_t getWeeks() const;
    void setWeeks(int64_t val);
    int64_t getMonths() const;
    void setMonths(int64_t val);
    int64_t getYears() const;
    void setYears(int64_t val);

    // normalize values (for example 1 hour 70 minutes -> 2 hours 10 minutes)
    void normalize();

    double getFullTimeInMinutes() const;
    double getFullTimeInHours() const;
    double getFullTimeInDays() const;
    double getFullTimeInWeeks() const;
    double getFullTimeInMonths() const;
    double getFullTimeInYears() const;

    GameTime();
    GameTime(int64_t ticks);
    GameTime(int64_t years, int64_t months, int64_t weeks, int64_t days, int64_t hours, int64_t minutes, int64_t ticks);
    GameTime(const GameTime& time) = default;
    GameTime& operator=(const GameTime& time) = default;
    static GameTime current();

    static const int TIME_TICKS_IN_MINUTE = 256, TIME_MINUTES_IN_HOUR = 60, TIME_HOURS_IN_DAY = 24;
    static const int TIME_DAYS_IN_WEEK = 7, TIME_WEEKS_IN_MONTH = 4, TIME_MONTHS_IN_YEAR = 12;

    static const int TIME_TICKS_IN_HOUR = TIME_TICKS_IN_MINUTE * TIME_MINUTES_IN_HOUR;
    static const int TIME_TICKS_IN_DAY = TIME_TICKS_IN_HOUR * TIME_HOURS_IN_DAY;
    static const int TIME_TICKS_IN_WEEK = TIME_TICKS_IN_DAY * TIME_DAYS_IN_WEEK;
    static const int TIME_TICKS_IN_MONTH = TIME_TICKS_IN_WEEK * TIME_WEEKS_IN_MONTH;
    static const int TIME_TICKS_IN_YEAR = TIME_TICKS_IN_MONTH * TIME_MONTHS_IN_YEAR;

    GameTime& operator-=(const GameTime& rhs);
    GameTime& operator+=(const GameTime& rhs);
    friend GameTime operator-(const GameTime& lhs, const GameTime& rhs);
    friend GameTime operator+(const GameTime& lhs, const GameTime& rhs);
    // comparison operators
    friend bool operator==(const GameTime& lhs, const GameTime& rhs);
    friend bool operator!=(const GameTime& lhs, const GameTime& rhs);
    friend bool operator<(const GameTime& lhs, const GameTime& rhs);
    friend bool operator>(const GameTime& lhs, const GameTime& rhs);
    friend bool operator<=(const GameTime& lhs, const GameTime& rhs);
    friend bool operator>=(const GameTime& lhs, const GameTime& rhs);
};