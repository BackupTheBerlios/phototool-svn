
#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include "InputDialog.h"

class SetupDialog : public InputDialog
{
public:
    SetupDialog(wxWindow *parent);

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnBasePath(wxCommandEvent&);

private:
    DECLARE_EVENT_TABLE()
};

#endif

