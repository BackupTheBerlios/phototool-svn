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

