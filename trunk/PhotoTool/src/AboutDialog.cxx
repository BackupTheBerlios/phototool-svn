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

BEGIN_EVENT_TABLE(AboutDialog, wxDialog)
    EVT_BUTTON(wxID_OK, AboutDialog::OnClose)
END_EVENT_TABLE()

AboutDialog::AboutDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, _T("About PhotoTool"))
{
    // About PhotoTool
    wxStaticText *text = new wxStaticText(this, -1, 
            _T("PhotoTool is an application for organizing and \n")
            _T("documenting a digital photo collection.\n")
            _T("\n")
            _T("Copyright (C) 2004 Bryan Bulten (bryan@bulten.ca)")
        );

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("About PhotoTool"));
    wxStaticBoxSizer *about_ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    about_ssizer->Add(text, 0, wxEXPAND|wxALL, 5);

    // License
    text = new wxStaticText(this, -1, 
            _T("This program is free software; you can redistribute\n")
            _T("it and/or modify it under the terms of the GNU\n")
            _T("General Public License as published by the Free\n")
            _T("Software Foundation; either version 2 of the License,\n")
            _T("or (at your option) any later version.")
        );

    sbox = new wxStaticBox(this, -1, _T("License"));
    wxStaticBoxSizer *license_ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    license_ssizer->Add(text, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(about_ssizer, 1, wxEXPAND|wxALL, 5);
    sizer->Add(license_ssizer, 1, wxEXPAND|wxALL, 5);
    sizer->Add(new wxButton(this, wxID_OK, _T("OK")), 
               0, wxALIGN_RIGHT|wxALL, 5);
    SetSizer(sizer);
    Fit();
}

void AboutDialog::OnClose(wxCommandEvent&)
{
    EndModal(wxID_OK);
}

