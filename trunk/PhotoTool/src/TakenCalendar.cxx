/**
 * PhotoTool is an application for organizing and publishing a collection of
 * digital images. 
 *
 * Copyright (C) 2005  Bryan Bulten (bryan@bulten.ca)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

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

    // Send notification of updated photo list
    PhotoEvent pevt(EVT_PHOTOS_SELECTED_EVENT);
    pevt.SetPhotos(photos);
    GetEventHandler()->ProcessEvent(pevt);
}

