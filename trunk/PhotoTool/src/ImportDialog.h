
#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "InputDialog.h"

class ImportDialog : public InputDialog
{
public:
    ImportDialog(wxWindow *parent);

    void OnAddFiles(wxCommandEvent&);
    void OnAddDirectory(wxCommandEvent&);
    void OnCopyFiles(wxCommandEvent&);
    void OnRemoveFiles(wxCommandEvent&);

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

private:
    wxArrayString m_importList;

    DECLARE_EVENT_TABLE()
};

#endif

