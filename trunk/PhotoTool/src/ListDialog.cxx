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

#include "ListDialog.h"
#include "Notify.h"
#include "Util.h"

#define ID_AddButton    100
#define ID_EditButton   101
#define ID_RemoveButton 102
#define ID_CloseButton  103
#define ID_ItemList     104

BEGIN_EVENT_TABLE(ListDialog, wxDialog)
    EVT_BUTTON(ID_AddButton, ListDialog::OnAction)
    EVT_BUTTON(ID_EditButton, ListDialog::OnAction)
    EVT_BUTTON(ID_RemoveButton, ListDialog::OnAction)

    EVT_LISTBOX_DCLICK(ID_ItemList, ListDialog::OnAction)

    EVT_BUTTON(ID_CloseButton, ListDialog::OnClose)
END_EVENT_TABLE()

ListDialog::ListDialog(wxWindow *parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title)
{
    m_list = new wxListBox(this, ID_ItemList, wxDefaultPosition,
                           wxSize(-1, 200));

    // Add buttons to sizer
    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(new wxButton(this, ID_AddButton, _T("Add...")), 
                  0, wxALL, 5);
    btnSizer->Add(new wxButton(this, ID_EditButton, _T("Edit...")), 
                  0, wxALL, 5);
    btnSizer->Add(new wxButton(this, ID_RemoveButton, _T("Remove")), 
                  0, wxALL, 5);

    // Add list and buttons to static box
    wxStaticBox *sbox = new wxStaticBox(this, -1, GetTitle());
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(m_list, 1, wxEXPAND|wxALL, 5);
    ssizer->Add(btnSizer, 0, wxEXPAND);

    // Wrap it all up
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer, 1, wxEXPAND|wxALL, 5);
    sizer->Add(new wxButton(this, ID_CloseButton, _T("Close")), 
               0, wxALL|wxALIGN_RIGHT, 5);
    SetSizer(sizer);
    Fit();

    TransferDataToWindow();
}

void ListDialog::OnAction(wxCommandEvent& evt)
{
    bool refresh = false;

    if (ID_AddButton == evt.GetId()) {
        // Add a new item
        refresh = DoAdd();
    } 
    else if (ID_EditButton == evt.GetId() || ID_ItemList == evt.GetId()) {
        // Edit an existing item
        wxString sel = m_list->GetStringSelection();
        if (sel.Length() == 0)
            Notify::Error(this, _T("Select an item to edit"));
        else 
            refresh = DoEdit(sel);
    } 
    else if (ID_RemoveButton == evt.GetId()) {
        // Remove the selected item
        wxString sel = m_list->GetStringSelection();
        if (sel.Length() == 0)
            Notify::Error(this, _T("Select an item to remove"));
        else 
            refresh = DoRemove(sel);
    }

    // Refresh list contents
    if (refresh)
        TransferDataToWindow();
}

void ListDialog::OnClose(wxCommandEvent&)
{
    if (TransferDataFromWindow())
        EndModal(wxID_OK);
}

void ListDialog::SetItems(wxArrayString& items)
{
    m_list->Set(items);
}

