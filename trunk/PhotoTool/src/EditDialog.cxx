
#include "EditDialog.h"
#include "Util.h"

#include <wx/xrc/xmlres.h>

EditDialog::EditDialog(wxWindow *parent, const wxString& title)
    : InputDialog(parent, _T("EditPanel"), title)
{
}

wxString EditDialog::GetName()
{
    return CTRL("EditName", wxTextCtrl)->GetValue();
}

void EditDialog::SetName(const wxString& name)
{
    return CTRL("EditName", wxTextCtrl)->SetValue(name);
}

wxString EditDialog::GetDescription()
{
    return CTRL("EditDescription", wxTextCtrl)->GetValue();
}

void EditDialog::SetDescription(const wxString& description)
{
    CTRL("EditDescription", wxTextCtrl)->SetValue(description);
}

