
#include "InputDialog.h"

#include <wx/xrc/xmlres.h>

BEGIN_EVENT_TABLE(InputDialog, wxDialog)
    EVT_BUTTON(XRCID("OK"), InputDialog::OnOK)
    EVT_BUTTON(XRCID("Cancel"), InputDialog::OnCancel)
END_EVENT_TABLE()

InputDialog::InputDialog(wxWindow *parent, const wxString& panel, 
                         const wxString& title)
    : wxDialog(parent, wxID_ANY, title)
{
    wxXmlResource *res = wxXmlResource::Get();

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    // Editor panel
    wxPanel *p = res->LoadPanel(this, panel);
    sizer->Add(p);

    // Input panel (OK/Cancel buttons)
    p = res->LoadPanel(this, _T("InputPanel"));
    sizer->Add(p, 0, wxEXPAND);

    SetSizer(sizer);
    Fit();
}

void InputDialog::OnOK(wxCommandEvent&)
{
    if (TransferDataFromWindow())
        EndModal(wxID_OK);
}

void InputDialog::OnCancel(wxCommandEvent&)
{
    EndModal(wxID_CANCEL);
}

