#pragma once
#include "pch.h"
#include "main.h"
class wxSpinCtrl;

struct GameTime
{
    int64_t ticks, minutes, hours, days, weeks, months, years;

    void calculateValuesFromTicks();
public:

    int64_t getTicks() const;
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

    double getFullTimeInMinutes();
    double getFullTimeInHours();
    double getFullTimeInDays();
    double getFullTimeInWeeks();
    double getFullTimeInMonths();
    double getFullTimeInYears();

    int64_t calcTicksFromFullTime();

    GameTime();
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
};

GameTime operator-(const GameTime& lhs, const GameTime& rhs);
GameTime operator+(const GameTime& lhs, const GameTime& rhs);

class TimeChooserCtrl : public wxPanel
{
    wxStaticText* labelDays;
    wxSpinCtrl* valueDays;
    wxStaticText* labelHours;
    wxSpinCtrl* valueHours;
    wxStaticText* labelMinutes;
    wxSpinCtrl* valueMinutes;
    GameTime time;

public:
    TimeChooserCtrl(wxWindow* parent);


    int64_t getYears();
    int64_t getMonths();
    int64_t getWeeks();
    int64_t getDays();
    int64_t getHours();
    int64_t getMinutes();
    int64_t getTicks();

    void setYears(int64_t val);
    void setMonths(int64_t val);
    void setWeeks(int64_t val);
    void setDays(int64_t val);
    void setHours(int64_t val);
    void setMinutes(int64_t val);
    void setTicks(int64_t val);
};

