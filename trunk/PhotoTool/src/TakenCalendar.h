
#ifndef TAKENCALENDAR_H
#define TAKENCALENDAR_H

#include <wx/wx.h>
#include <wx/calctrl.h>

class TakenCalendar : public wxCalendarCtrl
{
public:
    TakenCalendar(wxWindow *parent);

    void OnMonthChanged(wxCalendarEvent&);
    void OnDayChanged(wxCalendarEvent&);

private:
    DECLARE_EVENT_TABLE()
};

#endif

