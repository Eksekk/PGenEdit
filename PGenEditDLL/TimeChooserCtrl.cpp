#include "pch.h"
#include "TimeChooserCtrl.h"
#include "GameStructAccessor.h"

void GameTime::calculateValuesFromTicks()
{
    int64_t tmpTicks = ticks;
    std::initializer_list<std::pair<int64_t&, int>> vals =
    {
        {years, TIME_MONTHS_IN_YEAR},
        {months, TIME_WEEKS_IN_MONTH},
        {weeks, TIME_DAYS_IN_WEEK},
        {days, TIME_HOURS_IN_DAY},
        {hours, TIME_MINUTES_IN_HOUR},
        {minutes, TIME_TICKS_IN_MINUTE}
    };

    for (auto& [value, divisor] : vals)
    {
        value = tmpTicks / divisor;
        wxASSERT_MSG(value > 0, "Found negative time value"); // for now (negative values are used by game sometimes)
        tmpTicks %= divisor;
    }
}

inline int64_t GameTime::getTicks() const
{
    return ticks;
}

inline void GameTime::setTicks(int64_t val)
{
    ticks = val;
    calculateValuesFromTicks();
}

inline int64_t GameTime::getYears() const
{
    return years;
}

inline void GameTime::setYears(int64_t val)
{
    int64_t change = val - years;
    ticks += change * TIME_TICKS_IN_YEAR;
    calculateValuesFromTicks();
}

double GameTime::getFullTimeInMinutes()
{
    return (double)ticks / TIME_TICKS_IN_MINUTE;
}

double GameTime::getFullTimeInHours()
{
    return (double)ticks / TIME_TICKS_IN_HOUR;
}

double GameTime::getFullTimeInDays()
{
    return (double)ticks / TIME_TICKS_IN_DAY;
}

double GameTime::getFullTimeInWeeks()
{
    return (double)ticks / TIME_TICKS_IN_WEEK;
}

double GameTime::getFullTimeInMonths()
{
    return (double)ticks / TIME_TICKS_IN_MONTH;
}

double GameTime::getFullTimeInYears()
{
    return (double)ticks / TIME_TICKS_IN_YEAR;
}

int64_t GameTime::calcTicksFromFullTime()
{
    std::initializer_list<std::pair<int64_t&, int>> vals =
    {
        {minutes, TIME_TICKS_IN_MINUTE},
        {hours, TIME_MINUTES_IN_HOUR},
        {days, TIME_HOURS_IN_DAY},
        {weeks, TIME_DAYS_IN_WEEK},
        {months, TIME_WEEKS_IN_MONTH},
        {years, TIME_MONTHS_IN_YEAR},
    };

    int64_t newTicks = ticks % TIME_TICKS_IN_MINUTE; // only those free, that can't make up a minute
    int64_t currTickEquivalent = 1;
    for (auto& [value, multiplier] : vals)
    {
        currTickEquivalent *= multiplier;
        newTicks += currTickEquivalent * value;
    }
    return newTicks;
}

inline int64_t GameTime::getMonths() const
{
    return months;
}

inline void GameTime::setMonths(int64_t val)
{
    int64_t change = val - months;
    ticks += change * TIME_TICKS_IN_MONTH;
    calculateValuesFromTicks();
}

inline int64_t GameTime::getWeeks() const
{
    return weeks;
}

inline void GameTime::setWeeks(int64_t val)
{
    int64_t change = val - weeks;
    ticks += change * TIME_TICKS_IN_WEEK;
    calculateValuesFromTicks();
}

inline int64_t GameTime::getDays() const
{
    return days;
}

inline void GameTime::setDays(int64_t val)
{
    int64_t change = val - days;
    ticks += change * TIME_TICKS_IN_DAY;
    calculateValuesFromTicks();
}

inline int64_t GameTime::getHours() const
{
    return hours;
}

inline void GameTime::setHours(int64_t val)
{
    int64_t change = val - hours;
    ticks += change * TIME_TICKS_IN_HOUR;
    calculateValuesFromTicks();
}

inline int64_t GameTime::getMinutes() const
{
    return minutes;
}

inline void GameTime::setMinutes(int64_t val)
{
    int64_t change = val - minutes;
    ticks += change * TIME_TICKS_IN_MINUTE;
    calculateValuesFromTicks();
}

GameTime::GameTime() : ticks(0), minutes(0), hours(0), days(0), weeks(0), months(0), years(0)
{

}

GameTime GameTime::current()
{
    int64_t ticks = gameAccessor->getTime();
    GameTime time;
    time.setTicks(ticks);
    return time;
}

GameTime& GameTime::operator-=(const GameTime& rhs)
{
    setTicks(getTicks() - rhs.getTicks());
    return *this;
}

GameTime& GameTime::operator+=(const GameTime& rhs)
{
    setTicks(getTicks() + rhs.getTicks());
    return *this;
}

GameTime operator-(const GameTime& lhs, const GameTime& rhs)
{
    GameTime ret;
    ret.setTicks(lhs.getTicks() - rhs.getTicks());
    return ret;
}

GameTime operator+(const GameTime& lhs, const GameTime& rhs)
{
    GameTime ret;
    ret.setTicks(lhs.getTicks() + rhs.getTicks());
    return ret;
}

TimeChooserCtrl::TimeChooserCtrl(wxWindow* parent)
{
}

int64_t TimeChooserCtrl::getYears()
{
    return time.years;
}

int64_t TimeChooserCtrl::getMonths()
{
    return time.months;
}

int64_t TimeChooserCtrl::getWeeks()
{
    return time.weeks;
}

int64_t TimeChooserCtrl::getDays()
{
    return time.days;
}

int64_t TimeChooserCtrl::getHours()
{
    return time.hours;
}

int64_t TimeChooserCtrl::getMinutes()
{
    return time.minutes;
}

int64_t TimeChooserCtrl::getTicks()
{
    return time.ticks;
}

void TimeChooserCtrl::setYears(int64_t val)
{
    time.setYears(val);
}

void TimeChooserCtrl::setMonths(int64_t val)
{
    time.setMonths(val);
}

void TimeChooserCtrl::setWeeks(int64_t val)
{
    time.setYears(val);
}

void TimeChooserCtrl::setDays(int64_t val)
{
    time.setDays(val);
}

void TimeChooserCtrl::setHours(int64_t val)
{
    time.setHours(val);
}

void TimeChooserCtrl::setMinutes(int64_t val)
{
    time.setMinutes(val);
}

void TimeChooserCtrl::setTicks(int64_t val)
{
    time.setTicks(val);
}
