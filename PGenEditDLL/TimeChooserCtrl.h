#pragma once
#include "pch.h"
#include "main.h"
class wxSpinCtrl;

struct GameTime
{
    int64_t ticks;
    int minutes, hours, days, weeks, months, years;

    GameTime();
    static GameTime current();
    bool processTimeChanges();

    static const int TIME_TICKS_IN_MINUTE = 256, TIME_MINUTES_IN_HOUR = 60, TIME_HOURS_IN_DAY = 24;
    static const int TIME_DAYS_IN_WEEK = 7, TIME_WEEKS_IN_MONTH = 4, TIME_MONTHS_IN_YEAR = 12;
};

GameTime operator-(const GameTime& lhs, const GameTime& rhs);

class TimeChooserCtrl : public wxPanel
{
    wxStaticText* labelDays;
    wxSpinCtrl* valueDays;
    wxStaticText* labelHours;
    wxSpinCtrl* valueHours;
    wxStaticText* labelMinutes;
    wxSpinCtrl* valueMinutes;

public:
    TimeChooserCtrl(wxWindow* parent, int days = 0, int hours = 0, int minutes = 0);


    int64_t getTimeInYears();
    int64_t getTimeInMonths();
    int64_t getTimeInWeeks();
    int64_t getTimeInDays();
    int64_t getTimeInHours();
    int64_t getTimeInMinutes();
    int64_t getTimeInTicks();
};

