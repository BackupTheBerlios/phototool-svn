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

#include "Album.h"
#include "Notify.h"

AlbumListDialog::AlbumListDialog(wxWindow *parent)
    : ListDialog(parent, _T("Albums"))
{
}

bool AlbumListDialog::TransferDataToWindow()
{
    wxArrayString items;
    Library::Get()->LookupAlbums(items);
    SetItems(items);

    return true;
}

bool AlbumListDialog::DoAdd()
{
    AlbumDialog *dlg = new AlbumDialog(this);
    return dlg->ShowModal() == wxID_OK;
}

bool AlbumListDialog::DoEdit(const wxString& item)
{
    AlbumDialog *dlg = new AlbumDialog(this, item);
    return dlg->ShowModal() == wxID_OK;
}

bool AlbumListDialog::DoRemove(const wxString& item)
{
    Album album = Library::Get()->GetAlbum(item);
    return Library::Get()->Delete(album);
}


AlbumDialog::AlbumDialog(wxWindow *parent, const wxString& name)
    : EditDialog(parent, _T("Edit Album"))
{
    if (name.Length() != 0) {
        m_album = Library::Get()->GetAlbum(name);
        TransferDataToWindow();
    }
}

bool AlbumDialog::TransferDataFromWindow()
{
    if (GetName().Length() == 0) {
        Notify::Info(this, _T("Enter a name for this album"));
        return false;
    }

    m_album.SetName(GetName());
    m_album.SetDescription(GetDescription());

    return Library::Get()->Update(m_album);
}

bool AlbumDialog::TransferDataToWindow()
{
    SetName(m_album.GetName());
    SetDescription(m_album.GetDescription());
    return true;
}

IMPLEMENT_DYNAMIC_CLASS(AlbumList, wxListBox)

BEGIN_EVENT_TABLE(AlbumList, wxListBox)
    EVT_WINDOW_CREATE(AlbumList::OnCreate)
END_EVENT_TABLE()

AlbumList::AlbumList(wxWindow *parent, wxWindowID id, 
                           const wxPoint &pos, const wxSize &size, 
                           long style, const wxValidator& validator,
                           const wxString &name)
    : wxListBox(parent, id, pos, size, wxArrayString(), style, validator, name)
{
}

void AlbumList::PopulateList()
{
    wxArrayString items;
    Library::Get()->LookupAlbums(items);

    Clear();
    for(size_t i = 0; i < items.Count(); i++)
        Append(items[i]);
}

void AlbumList::OnCreate(wxWindowCreateEvent&)
{
    PopulateList();
}

void AlbumList::GetSelections(wxArrayString &selection)
{
    wxArrayInt items; 
    wxListBox::GetSelections(items);

    selection.Clear();
    for(size_t i = 0; i < items.Count(); i++)
        selection.Add(GetString(items[i]));
}

void AlbumList::SetSelections(const wxArrayString &selection)
{
    for(size_t i = 0; i < selection.Count(); i++)
        SetStringSelection(selection[i]);
}


