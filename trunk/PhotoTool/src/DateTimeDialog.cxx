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

#include "DateTimeDialog.h"
#include "Util.h"

#include <wx/xrc/xmlres.h>
#include <wx/calctrl.h>
#include <wx/spinctrl.h>

DateTimeDialog::DateTimeDialog(wxWindow *parent, wxDateTime& dateTime)
    : InputDialog(parent, _T("DateTimePanel"), _T("Date/Time")),
      m_dateTime(dateTime)
{
    TransferDataToWindow();
}

bool DateTimeDialog::TransferDataToWindow()
{
    CTRL("Calendar", wxCalendarCtrl)->SetDate(m_dateTime);
    CTRL("Hour", wxSpinCtrl)->SetValue(m_dateTime.GetHour());
    CTRL("Minute", wxSpinCtrl)->SetValue(m_dateTime.GetMinute());
    CTRL("Second", wxSpinCtrl)->SetValue(m_dateTime.GetSecond());

    return true;
}

bool DateTimeDialog::TransferDataFromWindow()
{
    m_dateTime = CTRL("Calendar", wxCalendarCtrl)->GetDate();
    m_dateTime.SetHour(CTRL("Hour", wxSpinCtrl)->GetValue());
    m_dateTime.SetMinute(CTRL("Minute", wxSpinCtrl)->GetValue());
    m_dateTime.SetSecond(CTRL("Second", wxSpinCtrl)->GetValue());

    return true;
}

