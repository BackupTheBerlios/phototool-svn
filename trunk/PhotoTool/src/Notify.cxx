
#include "Notify.h"

void Notify::Error(wxWindow *parent, const wxString& msg, 
                   const wxString& caption)
{
    Message(parent, msg, caption, wxICON_ERROR);
}

void Notify::Info(wxWindow *parent, const wxString& msg,
                  const wxString& caption)
{
    Message(parent, msg, caption, wxICON_INFORMATION);
}

bool Notify::Ask(wxWindow *parent, const wxString& msg, 
                 const wxString& caption)
{
    int result = Message(parent, msg, caption, wxICON_QUESTION | wxYES_NO);
    return result == wxID_YES;
}

int Notify::Message(wxWindow *parent, const wxString& msg,
                    const wxString& caption, int type)
{
    wxMessageDialog *dlg = new wxMessageDialog(parent, msg, caption, type);
    return dlg->ShowModal();
}

