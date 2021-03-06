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

#ifndef DATETIME_H
#define DATETIME_H

#include "InputDialog.h"
#include "Util.h"

#include <wx/calctrl.h>
#include <wx/spinctrl.h>

class DateTimeDialog : public InputDialog
{
public:
    DateTimeDialog(wxWindow *parent, wxDateTime& dateTime);

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    ACCESSOR(DateTime, m_dateTime, wxDateTime)

private:
    wxCalendarCtrl *m_calendar;
    wxSpinCtrl *m_hour, *m_minute, *m_second;

    wxDateTime m_dateTime;
};

class DateTimeCtrl : public wxPanel
{
public:
    DateTimeCtrl(wxWindow* parent);

    void OnDateTime(wxCommandEvent&);

    wxDateTime GetValue() const;
    void SetValue(const wxDateTime& dt);

private:
    wxTextCtrl *m_text;

private:
    DECLARE_EVENT_TABLE()
};

#endif

