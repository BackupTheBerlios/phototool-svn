
#ifndef DATETIMEDIALOG_H
#define DATETIMEDIALOG_H

#include "InputDialog.h"
#include "Util.h"

class DateTimeDialog : public InputDialog
{
public:
    DateTimeDialog(wxWindow *parent, wxDateTime& dateTime);

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    ACCESSOR(DateTime, m_dateTime, wxDateTime)

private:
    wxDateTime m_dateTime;
};

#endif

