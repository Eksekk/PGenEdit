#include "pch.h"
#include "GameTime.h"
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

int64_t GameTime::getTicks() const
{
    return ticks;
}

void GameTime::setTicksExclusive(int64_t val)
{
    ticks = val;
    calculateValuesFromTicks();
}

void GameTime::setTicks(int64_t val)
{
    ticks = getFullTicks() + val;
    calculateValuesFromTicks();
}

int64_t GameTime::getYears() const
{
    return years;
}

void GameTime::setYears(int64_t val)
{
    int64_t change = val - years;
    ticks += change * TIME_TICKS_IN_YEAR;
    calculateValuesFromTicks();
}

double GameTime::getFullTimeInMinutes() const
{
    return (double)ticks / TIME_TICKS_IN_MINUTE;
}

double GameTime::getFullTimeInHours() const
{
    return (double)ticks / TIME_TICKS_IN_HOUR;
}

double GameTime::getFullTimeInDays() const
{
    return (double)ticks / TIME_TICKS_IN_DAY;
}

double GameTime::getFullTimeInWeeks() const
{
    return (double)ticks / TIME_TICKS_IN_WEEK;
}

double GameTime::getFullTimeInMonths() const
{
    return (double)ticks / TIME_TICKS_IN_MONTH;
}

double GameTime::getFullTimeInYears() const
{
    return (double)ticks / TIME_TICKS_IN_YEAR;
}

int64_t GameTime::getFullTicks() const
{
    std::initializer_list<std::pair<const int64_t&, int>> vals =
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

void GameTime::normalize()
{
    ticks = getFullTicks();
    calculateValuesFromTicks();
}

int64_t GameTime::getMonths() const
{
    return months;
}

void GameTime::setMonths(int64_t val)
{
    months = val;
    normalize();
}

int64_t GameTime::getWeeks() const
{
    return weeks;
}

void GameTime::setWeeks(int64_t val)
{
    weeks = val;
    normalize();
}

int64_t GameTime::getDays() const
{
    return days;
}

void GameTime::setDays(int64_t val)
{
    days = val;
    normalize();
}

int64_t GameTime::getHours() const
{
    return hours;
}

void GameTime::setHours(int64_t val)
{
    hours = val;
    normalize();
}

int64_t GameTime::getMinutes() const
{
    return minutes;
}

void GameTime::setMinutes(int64_t val)
{
    minutes = val;
    normalize();
}

GameTime::GameTime() : ticks(0), minutes(0), hours(0), days(0), weeks(0), months(0), years(0)
{

}

GameTime::GameTime(int64_t ticks)
{
    setTicksExclusive(ticks);
}

GameTime::GameTime(int64_t years, int64_t months, int64_t weeks, int64_t days, int64_t hours, int64_t minutes, int64_t ticks)
{
    this->years = years;
    this->months = months;
    this->weeks = weeks;
    this->days = days;
    this->hours = hours;
    this->minutes = minutes;
    this->ticks = ticks;

    normalize();
}

GameTime GameTime::current()
{
    int64_t ticks = gameAccessor->getTime();
    return GameTime(ticks);
}

GameTime& GameTime::operator-=(const GameTime& rhs)
{
    setTicksExclusive(getFullTicks() - rhs.getFullTicks());
    return *this;
}

GameTime& GameTime::operator+=(const GameTime& rhs)
{
    setTicksExclusive(getFullTicks() + rhs.getFullTicks());
    return *this;
}

GameTime operator-(const GameTime& lhs, const GameTime& rhs)
{
    return GameTime(lhs.getFullTicks() - rhs.getFullTicks());
}

GameTime operator+(const GameTime& lhs, const GameTime& rhs)
{
    return GameTime(lhs.getFullTicks() + rhs.getFullTicks());
}

bool operator==(const GameTime& lhs, const GameTime& rhs)
{
    return lhs.getFullTicks() == rhs.getFullTicks();
}

bool operator!=(const GameTime& lhs, const GameTime& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const GameTime& lhs, const GameTime& rhs)
{
    return lhs.getFullTicks() < rhs.getFullTicks();
}

bool operator>(const GameTime& lhs, const GameTime& rhs)
{
    return rhs < lhs;
}

bool operator<=(const GameTime& lhs, const GameTime& rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const GameTime& lhs, const GameTime& rhs)
{
    return !(lhs < rhs);
}

RTTR_REGISTRATION
{
    using namespace rttr;
registration::class_<GameTime>("GameTime")
.constructor<>()
.constructor<int64_t>()
.constructor<int64_t, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t>()
.constructor<const GameTime&>()
.constructor<GameTime&&>()

.property("ticks", &GameTime::getTicks, &GameTime::setTicks)
.property("years", &GameTime::getYears, &GameTime::setYears)
.property("months", &GameTime::getMonths, &GameTime::setMonths)
.property("weeks", &GameTime::getWeeks, &GameTime::setWeeks)
.property("days", &GameTime::getDays, &GameTime::setDays)
.property("hours", &GameTime::getHours, &GameTime::setHours)
.property("minutes", &GameTime::getMinutes, &GameTime::setMinutes)

.property_readonly("fullTimeInMinutes", &GameTime::getFullTimeInMinutes)
.property_readonly("fullTimeInHours", &GameTime::getFullTimeInHours)
.property_readonly("fullTimeInDays", &GameTime::getFullTimeInDays)
.property_readonly("fullTimeInWeeks", &GameTime::getFullTimeInWeeks)
.property_readonly("fullTimeInMonths", &GameTime::getFullTimeInMonths)
.property_readonly("fullTimeInYears", &GameTime::getFullTimeInYears)
.property_readonly("fullTicks", &GameTime::getFullTicks)

.method("getTicks", &GameTime::getTicks)
.method("getFullTicks", &GameTime::getFullTicks)
.method("getYears", &GameTime::getYears)
.method("getMonths", &GameTime::getMonths)
.method("getWeeks", &GameTime::getWeeks)
.method("getDays", &GameTime::getDays)
.method("getHours", &GameTime::getHours)
.method("getMinutes", &GameTime::getMinutes)

.method("setYears", &GameTime::setYears)
.method("setMonths", &GameTime::setMonths)
.method("setWeeks", &GameTime::setWeeks)
.method("setDays", &GameTime::setDays)
.method("setHours", &GameTime::setHours)
.method("setMinutes", &GameTime::setMinutes)
.method("setTicks", &GameTime::setTicks)
.method("setTicksExclusive", &GameTime::setTicksExclusive)

.method("getFullTimeInMinutes", &GameTime::getFullTimeInMinutes)
.method("getFullTimeInHours", &GameTime::getFullTimeInHours)
.method("getFullTimeInDays", &GameTime::getFullTimeInDays)
.method("getFullTimeInWeeks", &GameTime::getFullTimeInWeeks)
.method("getFullTimeInMonths", &GameTime::getFullTimeInMonths)
.method("getFullTimeInYears", &GameTime::getFullTimeInYears)

.method("current", &GameTime::current)
.method("normalize", &GameTime::normalize)
.method("operator-=", &GameTime::operator-=)
.method("operator+=", &GameTime::operator+=)
;

// globals or statics
        registration::method("operator-", select_overload<GameTime(const GameTime&, const GameTime&)>(&operator-))
        .method("operator+", select_overload<GameTime(const GameTime&, const GameTime&)>(&operator+))
        .method("operator==", select_overload<bool(const GameTime&, const GameTime&)>(&operator==))
        .method("operator!=", select_overload<bool(const GameTime&, const GameTime&)>(&operator!=))
        .method("operator<", select_overload<bool(const GameTime&, const GameTime&)>(&operator<))
        .method("operator>", select_overload<bool(const GameTime&, const GameTime&)>(&operator>))
        .method("operator<=", select_overload<bool(const GameTime&, const GameTime&)>(&operator<=))
        .method("operator>=", select_overload<bool(const GameTime&, const GameTime&)>(&operator>=))
.property_readonly("TIME_TICKS_IN_MINUTE", &GameTime::TIME_TICKS_IN_MINUTE)
.property_readonly("TIME_TICKS_IN_HOUR", &GameTime::TIME_TICKS_IN_HOUR)
.property_readonly("TIME_TICKS_IN_DAY", &GameTime::TIME_TICKS_IN_DAY)
.property_readonly("TIME_TICKS_IN_WEEK", &GameTime::TIME_TICKS_IN_WEEK)
.property_readonly("TIME_TICKS_IN_MONTH", &GameTime::TIME_TICKS_IN_MONTH)
.property_readonly("TIME_TICKS_IN_YEAR", &GameTime::TIME_TICKS_IN_YEAR)
.property_readonly("TIME_MINUTES_IN_HOUR", &GameTime::TIME_MINUTES_IN_HOUR)
.property_readonly("TIME_HOURS_IN_DAY", &GameTime::TIME_HOURS_IN_DAY)
.property_readonly("TIME_DAYS_IN_WEEK", &GameTime::TIME_DAYS_IN_WEEK)
.property_readonly("TIME_WEEKS_IN_MONTH", &GameTime::TIME_WEEKS_IN_MONTH)
.property_readonly("TIME_MONTHS_IN_YEAR", &GameTime::TIME_MONTHS_IN_YEAR)
        ;
}
