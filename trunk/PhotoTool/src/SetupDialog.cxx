
#include "SetupDialog.h"
#include "Util.h"
#include "Config.h"
#include "Notify.h"
#include "Library.h"

#include <wx/xrc/xmlres.h>

BEGIN_EVENT_TABLE(SetupDialog, InputDialog)
    EVT_BUTTON(XRCID("BasePathButton"), SetupDialog::OnBasePath)
END_EVENT_TABLE()

SetupDialog::SetupDialog(wxWindow *parent)
    : InputDialog(parent, _T("SetupPanel"), _T("Setup"))
{
    TransferDataToWindow();
}

bool SetupDialog::TransferDataToWindow()
{
    CTRL("BasePath", wxTextCtrl)->SetValue(Config::GetBasePath());
    return true;
}

bool SetupDialog::TransferDataFromWindow()
{
    wxString basePath = CTRL("BasePath", wxTextCtrl)->GetValue();

    if (basePath.Length() == 0) {
        Notify::Error(this, _T("Please select a photo directory"));
        return false;
    }

    // Load the photo database
    Config::SetBasePath(basePath);
    Library::Get()->Load(Config::GetBasePath());

    return true;
}

void SetupDialog::OnBasePath(wxCommandEvent&)
{
    wxString basePath = CTRL("BasePath", wxTextCtrl)->GetValue();
    wxDirDialog *dlg = new wxDirDialog(this, _T("Photo Directory"), basePath);

    if (dlg->ShowModal() == wxID_OK) {
        CTRL("BasePath", wxTextCtrl)->SetValue(dlg->GetPath());
    }
}

