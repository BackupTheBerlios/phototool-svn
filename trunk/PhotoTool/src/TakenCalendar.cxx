
#include "TakenCalendar.h"
#include "Library.h"
#include "PhotoEvent.h"

BEGIN_EVENT_TABLE(TakenCalendar, wxCalendarCtrl)
    EVT_CALENDAR_YEAR(wxID_ANY, TakenCalendar::OnMonthChanged)
    EVT_CALENDAR_MONTH(wxID_ANY, TakenCalendar::OnMonthChanged)

    EVT_CALENDAR_DAY(wxID_ANY, TakenCalendar::OnDayChanged)
END_EVENT_TABLE()

TakenCalendar::TakenCalendar(wxWindow *parent)
    : wxCalendarCtrl(parent, wxID_ANY, wxDefaultDateTime, 
                     wxDefaultPosition, wxDefaultSize,
                     wxCAL_SHOW_HOLIDAYS | wxCAL_SEQUENTIAL_MONTH_SELECTION |
                     wxCAL_SHOW_SURROUNDING_WEEKS)
{
    wxCalendarEvent evt;
    OnMonthChanged(evt);
}

void TakenCalendar::OnMonthChanged(wxCalendarEvent&)
{
    wxDateTime from, to, date = GetDate();

    // Date range (for month)
    from.Set(1, date.GetMonth(), date.GetYear());
    to.Set(1, date.GetMonth(), date.GetYear());
    to.SetToLastMonthDay();

    wxDateTimeArray taken;
    Library::Get()->GetDatesTaken(taken, from, to);

    for(size_t i = from.GetDay(); i <= to.GetDay(); i++)
        ResetAttr(i);

    for(size_t i = 0; i < taken.Count(); i++) {
        wxCalendarDateAttr *attr = new wxCalendarDateAttr();

        attr->SetBorder(wxCAL_BORDER_SQUARE);
        attr->SetTextColour(*wxBLUE);
        attr->SetBorderColour(*wxBLUE);

        SetAttr(taken[i].GetDay(), attr);
    }
}

void TakenCalendar::OnDayChanged(wxCalendarEvent&)
{
    wxDateTime from, to, date = GetDate();

    // Date range (for selected date)
    from.Set(date.GetDay(), date.GetMonth(), date.GetYear());
    to = from + wxDateSpan::Day();

    PhotoArray photos;
    Library::Get()->GetPhotosByTaken(photos, from, to);

    // Notify page
    PhotoEvent pevt(photos);
    wxPostEvent(GetParent()->GetParent()->GetParent(), pevt);
}

