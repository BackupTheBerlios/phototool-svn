
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

