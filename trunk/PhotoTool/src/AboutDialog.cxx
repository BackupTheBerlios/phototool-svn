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

