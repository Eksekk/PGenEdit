#include "pch.h"
#include "TimeChooserCtrl.h"
#include "wx/spinctrl.h"

wxDEFINE_EVENT(TIME_CTRL_TIME_CHANGE, wxCommandEvent);

void TimeChooserCtrl::updateValuesFromTime()
{
    valueTicks->SetValue(time.getTicks());
    valueMinutes->SetValue(time.getMinutes());
    valueHours->SetValue(time.getHours());
    valueDays->SetValue(time.getDays());
}

void TimeChooserCtrl::updateTimeFromValues()
{
    time.setTicks(valueTicks->GetValue());
    time.setMinutes(valueMinutes->GetValue());
    time.setHours(valueHours->GetValue());
    time.setDays(valueDays->GetValue());
}

void TimeChooserCtrl::onValuesChange(wxCommandEvent& event)
{
    updateValuesFromTime();
}

TimeChooserCtrl::TimeChooserCtrl(wxWindow* parent) : wxPanel(parent)
{
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(mainSizer);
    wxSizerFlags valueFlags, labelFlags;
    valueFlags.Border(wxALL, 5);
    labelFlags.Border(wxALL, 5).CenterVertical();

    auto valueChangeHandler = [=](wxCommandEvent& event)
    {
        wxCommandEvent timeEvent(TIME_CTRL_TIME_CHANGE, GetId());
        timeEvent.SetEventObject(this);
        ProcessWindowEvent(timeEvent);
        updateTimeFromValues();
    };

    labelDays = new wxStaticText(this, wxID_ANY, _("Days:"), wxDefaultPosition, wxDefaultSize, 0);
    labelDays->Wrap(-1);
    mainSizer->Add(labelDays, labelFlags);

    valueDays = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0);
    valueDays->Bind(wxEVT_SPINCTRL, valueChangeHandler);
    mainSizer->Add(valueDays, valueFlags);

    labelHours = new wxStaticText(this, wxID_ANY, _("Hours:"), wxDefaultPosition, wxDefaultSize, 0);
    labelHours->Wrap(-1);
    mainSizer->Add(labelHours, labelFlags);

    valueHours = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0);
    valueHours->Bind(wxEVT_SPINCTRL, valueChangeHandler);
    mainSizer->Add(valueHours, valueFlags);

    labelMinutes = new wxStaticText(this, wxID_ANY, _("Minutes:"), wxDefaultPosition, wxDefaultSize, 0);
    labelMinutes->Wrap(-1);
    mainSizer->Add(labelMinutes, labelFlags);

    valueMinutes = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0);
    valueMinutes->Bind(wxEVT_SPINCTRL, valueChangeHandler);
    mainSizer->Add(valueMinutes, valueFlags);

    // TODO: int range (min-max arguments) is too small for tick count
    labelTicks = new wxStaticText(this, wxID_ANY, _("Ticks:"), wxDefaultPosition, wxDefaultSize, 0);
    labelTicks->Wrap(-1);
    mainSizer->Add(labelTicks, labelFlags);

    valueTicks = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0);
    valueTicks->Bind(wxEVT_SPINCTRL, valueChangeHandler);
    mainSizer->Add(valueTicks, valueFlags);

    Layout();
}

GameTime TimeChooserCtrl::getTime() const
{
    return time;
}

void TimeChooserCtrl::setTime(GameTime time)
{
    this->time = time;
    updateValuesFromTime();
}

int64_t TimeChooserCtrl::getYears() const
{
    return time.getYears();
}

int64_t TimeChooserCtrl::getMonths() const
{
    return time.getMonths();
}

int64_t TimeChooserCtrl::getWeeks() const
{
    return time.getWeeks();
}

int64_t TimeChooserCtrl::getDays() const
{
    return time.getDays();
}

int64_t TimeChooserCtrl::getHours() const
{
    return time.getHours();
}

int64_t TimeChooserCtrl::getMinutes() const
{
    return time.getMinutes();
}

int64_t TimeChooserCtrl::getTicks() const
{
    return time.getTicks();
}

int64_t TimeChooserCtrl::getTotalTicks() const
{
    return time.getTotalTicks();
}

void TimeChooserCtrl::setYears(int64_t val)
{
    time.setYears(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setMonths(int64_t val)
{
    time.setMonths(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setWeeks(int64_t val)
{
    time.setWeeks(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setDays(int64_t val)
{
    time.setDays(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setHours(int64_t val)
{
    time.setHours(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setMinutes(int64_t val)
{
    time.setMinutes(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setTicks(int64_t val)
{
    time.setTicks(val);
    updateValuesFromTime();
}

void TimeChooserCtrl::setTicksExclusive(int64_t val)
{
    time.setTicksExclusive(val);
    updateValuesFromTime();
}

RTTR_REGISTRATION
{

    // generate RTTR registration code for TimeChooserCtrl
    using namespace rttr;
    registration::class_<TimeChooserCtrl>("TimeChooserCtrl")
        .constructor<wxWindow*>()
        .property("time", &TimeChooserCtrl::getTime, &TimeChooserCtrl::setTime)
        .property("years", &TimeChooserCtrl::getYears, &TimeChooserCtrl::setYears)
        .property("months", &TimeChooserCtrl::getMonths, &TimeChooserCtrl::setMonths)
        .property("weeks", &TimeChooserCtrl::getWeeks, &TimeChooserCtrl::setWeeks)
        .property("days", &TimeChooserCtrl::getDays, &TimeChooserCtrl::setDays)
        .property("hours", &TimeChooserCtrl::getHours, &TimeChooserCtrl::setHours)
        .property("minutes", &TimeChooserCtrl::getMinutes, &TimeChooserCtrl::setMinutes)
        .property("ticks", &TimeChooserCtrl::getTicks, &TimeChooserCtrl::setTicks)
        .property("valueTicks", &TimeChooserCtrl::valueTicks, registration::private_access)
.property("valueMinutes", &TimeChooserCtrl::valueMinutes, registration::private_access)
.property("valueHours", &TimeChooserCtrl::valueHours, registration::private_access)
.property("valueDays", &TimeChooserCtrl::valueDays, registration::private_access)
.property("labelTicks", &TimeChooserCtrl::labelTicks, registration::private_access)
.property("labelMinutes", &TimeChooserCtrl::labelMinutes, registration::private_access)
.property("labelHours", &TimeChooserCtrl::labelHours, registration::private_access)
.property("labelDays", &TimeChooserCtrl::labelDays, registration::private_access)
        .method("getTime", &TimeChooserCtrl::getTime)
.method("setTime", &TimeChooserCtrl::setTime)
.method("getYears", &TimeChooserCtrl::getYears)
.method("getMonths", &TimeChooserCtrl::getMonths)
.method("getWeeks", &TimeChooserCtrl::getWeeks)
.method("getDays", &TimeChooserCtrl::getDays)
.method("getHours", &TimeChooserCtrl::getHours)
.method("getMinutes", &TimeChooserCtrl::getMinutes)
.method("getTicks", &TimeChooserCtrl::getTicks)
.method("setYears", &TimeChooserCtrl::setYears)
.method("setMonths", &TimeChooserCtrl::setMonths)
.method("setWeeks", &TimeChooserCtrl::setWeeks)
.method("setDays", &TimeChooserCtrl::setDays)
.method("setHours", &TimeChooserCtrl::setHours)
.method("setMinutes", &TimeChooserCtrl::setMinutes)
.method("setTicks", &TimeChooserCtrl::setTicks)
        .method("updateValuesFromTime", &TimeChooserCtrl::updateValuesFromTime, registration::private_access)
.method("updateTimeFromValues", &TimeChooserCtrl::updateTimeFromValues, registration::private_access)
        ;
}
