
#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include "InputDialog.h"

class EditDialog : public InputDialog
{
public:
    EditDialog(wxWindow *parent, const wxString& title);

    wxString GetName();
    void SetName(const wxString& name);

    wxString GetDescription();
    void SetDescription(const wxString& description);
};

#endif

