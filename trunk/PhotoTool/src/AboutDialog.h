
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <wx/wx.h>

class AboutDialog : public wxDialog
{
public:
    AboutDialog(wxWindow *parent);

    void OnClose(wxCommandEvent&);

private:
    DECLARE_EVENT_TABLE()
};

#endif

