
#include "AboutDialog.h"

#include <wx/xrc/xmlres.h>

BEGIN_EVENT_TABLE(AboutDialog, wxDialog)
    EVT_BUTTON(XRCID("AboutClose"), AboutDialog::OnClose)
END_EVENT_TABLE()

AboutDialog::AboutDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, _T("About PhotoTool"))
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *p = wxXmlResource::Get()->LoadPanel(this, _T("AboutPanel"));
    sizer->Add(p, 0, wxEXPAND);

    SetSizer(sizer);
    Fit();
}

void AboutDialog::OnClose(wxCommandEvent&)
{
    Close();
}

