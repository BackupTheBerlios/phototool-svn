/**
 * PhotoTool is an application for organizing and publishing a collection of
 * digital images. 
 *
 * Copyright (C) 2005  Bryan Bulten (bryan@bulten.ca)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

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

