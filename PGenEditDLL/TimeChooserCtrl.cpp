#include "pch.h"
#include "TimeChooserCtrl.h"
#include "wx/spinctrl.h"

void TimeChooserCtrl::updateValuesFromTime()
{
    valueTicks->SetValue(time.getTicks());
    valueMinutes->SetValue(time.getMinutes());
    valueHours->SetValue(time.getHours());
    valueDays->SetValue(time.getDays());
}

void TimeChooserCtrl::onDaysChange(wxCommandEvent& event)
{
    time.setDays(valueDays->GetValue());
}

void TimeChooserCtrl::onHoursChange(wxCommandEvent& event)
{
    time.setHours(valueHours->GetValue());
}

void TimeChooserCtrl::onMinutesChange(wxCommandEvent& event)
{
    time.setMinutes(valueMinutes->GetValue());
}

void TimeChooserCtrl::onTicksChange(wxCommandEvent& event)
{
    time.setTicks(valueTicks->GetValue());
}

TimeChooserCtrl::TimeChooserCtrl(wxWindow* parent) : wxPanel(parent)
{
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags valueFlags, labelFlags;
    valueFlags.Border(wxALL, 5);
    labelFlags.Border(wxALL, 5).CenterVertical();

    labelDays = new wxStaticText(this, wxID_ANY, _("Days:"), wxDefaultPosition, wxDefaultSize, 0);
    labelDays->Wrap(-1);
    mainSizer->Add(labelDays, labelFlags);

    valueDays = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
    mainSizer->Add(valueDays, valueFlags);

    labelHours = new wxStaticText(this, wxID_ANY, _("Hours:"), wxDefaultPosition, wxDefaultSize, 0);
    labelHours->Wrap(-1);
    mainSizer->Add(labelHours, labelFlags);

    valueHours = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
    mainSizer->Add(valueHours, valueFlags);

    labelMinutes = new wxStaticText(this, wxID_ANY, _("Minutes:"), wxDefaultPosition, wxDefaultSize, 0);
    labelMinutes->Wrap(-1);
    mainSizer->Add(labelMinutes, labelFlags);

    valueMinutes = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
    mainSizer->Add(valueMinutes, valueFlags);

    labelTicks = new wxStaticText(this, wxID_ANY, _("Ticks:"), wxDefaultPosition, wxDefaultSize, 0);
    labelTicks->Wrap(-1);
    mainSizer->Add(labelTicks, labelFlags);

    valueTicks = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
    mainSizer->Add(valueTicks, valueFlags);
}

GameTime TimeChooserCtrl::getTime()
{
    return time;
}

void TimeChooserCtrl::setTime(const GameTime& time)
{
    this->time = time;
    updateValuesFromTime();
}

int64_t TimeChooserCtrl::getYears()
{
    return time.getYears();
}

int64_t TimeChooserCtrl::getMonths()
{
    return time.getMonths();
}

int64_t TimeChooserCtrl::getWeeks()
{
    return time.getWeeks();
}

int64_t TimeChooserCtrl::getDays()
{
    return time.getDays();
}

int64_t TimeChooserCtrl::getHours()
{
    return time.getHours();
}

int64_t TimeChooserCtrl::getMinutes()
{
    return time.getMinutes();
}

int64_t TimeChooserCtrl::getTicks()
{
    return time.getTicks();
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
