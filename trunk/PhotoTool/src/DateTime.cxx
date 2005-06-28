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

#include "DateTime.h"

DateTimeDialog::DateTimeDialog(wxWindow *parent, wxDateTime& dateTime)
    : InputDialog(parent, _T("Date/Time")),
      m_dateTime(dateTime)
{
    m_calendar = new wxCalendarCtrl(this, -1);
    m_hour = new wxSpinCtrl(this, -1, wxEmptyString, 
                            wxDefaultPosition, wxSize(40, -1));
    m_minute = new wxSpinCtrl(this, -1, wxEmptyString, 
                              wxDefaultPosition, wxSize(40, -1));
    m_second = new wxSpinCtrl(this, -1, wxEmptyString, 
                              wxDefaultPosition, wxSize(40, -1));

    m_hour->SetRange(0, 23);
    m_minute->SetRange(0, 59);
    m_second->SetRange(0, 59);

    wxBoxSizer *timeSizer = new wxBoxSizer(wxHORIZONTAL);
    timeSizer->Add(m_hour, 0, wxALL, 5);
    timeSizer->Add(m_minute, 0, wxALL, 5);
    timeSizer->Add(m_second, 0, wxALL, 5);

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("Date/Time"));
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(m_calendar, 0, wxALIGN_CENTER|wxALL, 5);
    ssizer->Add(timeSizer, 0, wxALIGN_CENTER|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer, 0, wxEXPAND|wxALL, 5);
    SetSizer(sizer);
    Fit();

    TransferDataToWindow();
}

bool DateTimeDialog::TransferDataToWindow()
{
    m_calendar->SetDate(m_dateTime);
    m_hour->SetValue(m_dateTime.GetHour());
    m_minute->SetValue(m_dateTime.GetMinute());
    m_second->SetValue(m_dateTime.GetSecond());

    return true;
}

bool DateTimeDialog::TransferDataFromWindow()
{
    m_dateTime = m_calendar->GetDate();
    m_dateTime.SetHour(m_hour->GetValue());
    m_dateTime.SetMinute(m_minute->GetValue());
    m_dateTime.SetSecond(m_second->GetValue());

    return true;
}

#include "DateTime.h"
#include "Util.h"

BEGIN_EVENT_TABLE(DateTimeCtrl, wxPanel)
    EVT_BUTTON(-1, DateTimeCtrl::OnDateTime)
END_EVENT_TABLE()

DateTimeCtrl::DateTimeCtrl(wxWindow* parent)
    : wxPanel(parent)
{
    m_text = new wxTextCtrl(this, -1, wxEmptyString, 
                            wxDefaultPosition, wxSize(220, -1));
    wxButton *btn = new wxButton(this, -1, _T("..."), 
                                 wxDefaultPosition, wxSize(25, -1));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_text, 1);
    sizer->Add(btn, 0, wxLEFT, 3);
    SetSizer(sizer);
    Fit();
}

void DateTimeCtrl::OnDateTime(wxCommandEvent&)
{
    wxDateTime taken;
    taken.ParseFormat(m_text->GetValue(), DATE_FORMAT);

    DateTimeDialog *dlg = new DateTimeDialog(this, taken);
    if (dlg->ShowModal() == wxID_OK) {
        wxString date = dlg->GetDateTime().Format(DATE_FORMAT);
        m_text->SetValue(date);
    }
}

wxDateTime DateTimeCtrl::GetValue() const
{
    wxDateTime dt;
    dt.ParseFormat(m_text->GetValue(), DATE_FORMAT);
    return dt;
}

void DateTimeCtrl::SetValue(const wxDateTime& dt)
{
    wxString date = dt.Format(DATE_FORMAT);
    m_text->SetValue(date);
}

