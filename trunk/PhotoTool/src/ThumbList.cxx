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

#include "ThumbList.h"
#include "PhotoDialog.h"

#define EDGE 4

BEGIN_EVENT_TABLE(ThumbListItem, wxBoxListItem)
END_EVENT_TABLE()

ThumbListItem::ThumbListItem(wxWindow *parent, const wxBitmap& bitmap)
    : wxBoxListItem(parent)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_thumb = new wxStaticBitmap(this, wxID_ANY, bitmap);
    sizer->Add(m_thumb, 0, wxALIGN_CENTRE | wxALL, EDGE);

    SetSizer(sizer);
    Fit();
}

BEGIN_EVENT_TABLE(ThumbList, wxBoxList)
    EVT_LISTBOX_DCLICK(wxID_ANY, ThumbList::OnEdit)

    EVT_SIZE(ThumbList::OnSize)
END_EVENT_TABLE()

ThumbList::ThumbList(wxWindow *parent)
    : wxBoxList(parent)
{

    SetBoxSize(wxSize(THUMB_WIDTH + (EDGE * 2), THUMB_HEIGHT + (EDGE * 2)));
    SetBoxMargins(1);

    // TODO
    PhotoArray photos;
    Library::Get()->GetPhotos(photos);
    SetList(photos);
}

void ThumbList::SetList(const PhotoArray& list)
{
    m_photoList = list;

    // Remove existing thumbs
    Clear();

    // Add the new thumbs
    for(size_t i = 0; i < m_photoList.Count(); i++)
        Add(new ThumbListItem(this, m_photoList[i].GetBitmap()));
}

Photo ThumbList::GetPhoto()
{
    int i = GetSelection();
    if (i >= 0 && (size_t)i < m_photoList.Count())
        return m_photoList[i];

    return Photo();
}

void ThumbList::OnEdit(wxCommandEvent&)
{
    Photo photo = GetPhoto();
    if (photo.Ok()) {
        PhotoDialog *dlg = new PhotoDialog(this, photo);
        dlg->ShowModal();
    }
}

