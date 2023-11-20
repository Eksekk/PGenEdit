#pragma once
#include "main.h"
#include "GameTime.h"
class wxSpinCtrl;

wxDECLARE_EVENT(TIME_CTRL_TIME_CHANGE, wxCommandEvent);

class TimeChooserCtrl : public wxPanel
{
    wxStaticText* labelDays;
    wxSpinCtrl* valueDays;
    wxStaticText* labelHours;
    wxSpinCtrl* valueHours;
    wxStaticText* labelMinutes;
    wxSpinCtrl* valueMinutes;
    wxStaticText* labelTicks;
    wxSpinCtrl* valueTicks;
    wxBoxSizer* mainSizer;

    GameTime time;

    void updateValuesFromTime();
    void updateTimeFromValues();

    void onValuesChange(wxCommandEvent& event);

public:
    TimeChooserCtrl(wxWindow* parent);

    GameTime getTime();
    void setTime(const GameTime& time);

    int64_t getYears() const;
    int64_t getMonths() const;
    int64_t getWeeks() const;
    int64_t getDays() const;
    int64_t getHours() const;
    int64_t getMinutes() const;
    int64_t getTicks() const;

    void setYears(int64_t val);
    void setMonths(int64_t val);
    void setWeeks(int64_t val);
    void setDays(int64_t val);
    void setHours(int64_t val);
    void setMinutes(int64_t val);
    void setTicks(int64_t val);

    RTTR_REGISTRATION_FRIEND
};

