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

#include "SetupDialog.h"
#include "Util.h"
#include "Config.h"
#include "Notify.h"
#include "Library.h"

#define ID_BasePathButton 100

BEGIN_EVENT_TABLE(SetupDialog, InputDialog)
    EVT_BUTTON(ID_BasePathButton, SetupDialog::OnBasePath)
END_EVENT_TABLE()

SetupDialog::SetupDialog(wxWindow *parent)
    : InputDialog(parent, _T("Setup"))
{
    m_basePath = new wxTextCtrl(this, -1, wxEmptyString,
                                wxDefaultPosition, wxSize(180, -1));
    wxButton *btn = new wxButton(this, ID_BasePathButton, _T("..."), 
                                 wxDefaultPosition, wxSize(25, -1));

    wxFlexGridSizer *fsizer = new wxFlexGridSizer(3, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Photo Directory:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_basePath);
    fsizer->Add(btn);

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("Options"));
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer);
    SetSizer(sizer);
    Fit();

    TransferDataToWindow();
}

bool SetupDialog::TransferDataToWindow()
{
    m_basePath->SetValue(Config::GetBasePath());
    return true;
}

bool SetupDialog::TransferDataFromWindow()
{
    wxString basePath = m_basePath->GetValue();

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
    wxString basePath = m_basePath->GetValue();
    wxDirDialog *dlg = new wxDirDialog(this, _T("Photo Directory"), basePath);

    if (dlg->ShowModal() == wxID_OK) {
        m_basePath->SetValue(dlg->GetPath());
    }
}

