
#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <wx/wx.h>

class InputDialog : public wxDialog
{
public:
    InputDialog(wxWindow *parent, const wxString& panel, 
                const wxString& title);

    void OnOK(wxCommandEvent&);
    void OnCancel(wxCommandEvent&);

private:
    DECLARE_EVENT_TABLE()
};

#endif

