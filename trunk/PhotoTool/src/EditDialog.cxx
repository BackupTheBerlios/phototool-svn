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

#include "EditDialog.h"
#include "Util.h"

EditDialog::EditDialog(wxWindow *parent, const wxString& title)
    : InputDialog(parent, title)
{
    m_name = new wxTextCtrl(this, -1, wxEmptyString, 
                            wxDefaultPosition, wxSize(80, -1));
    m_description = new wxTextCtrl(this, -1, wxEmptyString, 
                                   wxDefaultPosition, wxSize(300, 150),
                                   wxTE_MULTILINE);

    wxFlexGridSizer *fsizer = new wxFlexGridSizer(2, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Name:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_name, 0, wxEXPAND);
    fsizer->Add(new wxStaticText(this, -1, _T("Description:")));
    fsizer->Add(m_description);

    wxStaticBox *sbox = new wxStaticBox(this, -1, GetTitle());
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer, 0, wxEXPAND|wxALL, 5);
    SetSizer(sizer);
    Fit();
}

wxString EditDialog::GetName()
{
    return m_name->GetValue();
}

void EditDialog::SetName(const wxString& name)
{
    m_name->SetValue(name);
}

wxString EditDialog::GetDescription()
{
    return m_description->GetValue();
}

void EditDialog::SetDescription(const wxString& description)
{
    m_description->SetValue(description);
}

