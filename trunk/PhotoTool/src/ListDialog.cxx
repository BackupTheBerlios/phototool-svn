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

#include <wx/xrc/xmlres.h>

BEGIN_EVENT_TABLE(ListDialog, wxDialog)
    EVT_BUTTON(XRCID("Add"), ListDialog::OnAction)
    EVT_BUTTON(XRCID("Edit"), ListDialog::OnAction)
    EVT_BUTTON(XRCID("Remove"), ListDialog::OnAction)

    EVT_LISTBOX_DCLICK(XRCID("List"), ListDialog::OnAction)

    EVT_BUTTON(XRCID("Close"), ListDialog::OnClose)
END_EVENT_TABLE()

ListDialog::ListDialog(wxWindow *parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title)
{
    wxXmlResource::Get()->LoadPanel(this, _T("ListPanel"));
    Fit();

    m_list = CTRL("List", wxListBox);

    TransferDataToWindow();
}

void ListDialog::OnAction(wxCommandEvent& evt)
{
    bool refresh = false;

    if (XRCID("Add") == evt.GetId()) {
        // Add a new item
        refresh = DoAdd();

    } else if (XRCID("Edit") == evt.GetId() || XRCID("List") == evt.GetId()) {
        // Edit an existing item
        wxString sel = m_list->GetStringSelection();
        if (sel.Length() == 0)
            Notify::Error(this, _T("Select an item to edit"));
        else 
            refresh = DoEdit(sel);

    } else if (XRCID("Remove") == evt.GetId()) {
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

