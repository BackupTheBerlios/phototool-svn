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

#include "LookupList.h"
#include "Album.h"
#include "Library.h"
#include "Location.h"
#include "PhotoDropTarget.h"
#include "PhotoEvent.h"
#include "Config.h"

extern "C++" {
    wxImageList* LookupList::m_images = NULL;
};

static const int g_location = 0;
static const int g_album = 1;

BEGIN_EVENT_TABLE(LookupList, wxListCtrl)
    EVT_SIZE(LookupList::OnSize)
    
    EVT_LIST_ITEM_SELECTED(wxID_ANY, LookupList::OnSelect)
    EVT_LIST_ITEM_ACTIVATED(wxID_ANY, LookupList::OnEdit)

    EVT_PHOTO_DROP(LookupList::OnPhotoDrop)

    EVT_LIBRARY_ALBUM(LookupList::OnLibrary)
    EVT_LIBRARY_LOCATION(LookupList::OnLibrary)
END_EVENT_TABLE()

LookupList::LookupList(wxWindow *parent)
    : wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                 wxLC_REPORT | wxLC_NO_HEADER | wxLC_SINGLE_SEL)
{
    InsertColumn(0, wxEmptyString);

    if (!m_images) {
        m_images = new wxImageList();

#if 0
        #include "./icons/location.xpm"
        #include "./icons/album.xpm"

        m_images->Add(wxBitmap(location));
        m_images->Add(wxBitmap(album));
#endif

        wxString iconPath = Config::GetDataPath();
        iconPath << wxFILE_SEP_PATH << _T("icons") << wxFILE_SEP_PATH;
        wxBitmap bitmap;

        bitmap = wxImage(iconPath + _T("location.png"));
        m_images->Add(bitmap);

        bitmap = wxImage(iconPath + _T("album.png"));
        m_images->Add(bitmap);
    }

    SetImageList(m_images, wxIMAGE_LIST_SMALL);
    PopulateList();

    PhotoDropTarget::AddDropTarget(this);
    Library::Get()->AddHandler(this);
}

LookupList::~LookupList()
{
    Library::Get()->RemoveHandler(this);
}

void LookupList::PopulateList()
{
    // Get selected item
    int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    // Clear the list
    DeleteAllItems();

    wxListItem li;
    li.SetMask(wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA);
    li.SetColumn(0);
    li.SetId(0);

    // Albums
    li.SetImage(g_album);
    li.SetData((void*)&g_album);

    wxArrayString albums;
    Library::Get()->LookupAlbums(albums);
    for(size_t i = 0; i < albums.Count(); i++) {
        li.SetText(albums[i]);
        li.SetId(li.GetId() + 1);
        li.SetState(0);
        InsertItem(li);
    }

    // Locations
    li.SetImage(g_location);
    li.SetData((void*)&g_location);

    wxArrayString locations;
    Library::Get()->LookupLocations(locations);
    for(size_t i = 0; i < locations.Count(); i++) {
        li.SetText(locations[i]);
        li.SetId(li.GetId() + 1);
        li.SetState(0);
        InsertItem(li);
    }

    // Set selected item
    SetItemState(selected, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void LookupList::OnSize(wxSizeEvent& evt)
{
    // Adjust column width
    SetColumnWidth(0, evt.GetSize().GetWidth() - 20);
    evt.Skip();
}

void LookupList::OnSelect(wxListEvent& evt)
{
    wxString item = evt.GetText();
    int type = *(int*)evt.GetData();

    PhotoArray photos;
    if (type == g_album)
        Library::Get()->GetPhotosByAlbum(photos, item);
    else if (type == g_location)
        Library::Get()->GetPhotosByLocation(photos, item);

    // Send notification of updated photo list
    PhotoEvent pevt(EVT_PHOTOS_SELECTED_EVENT);
    pevt.SetPhotos(photos);
    GetEventHandler()->ProcessEvent(pevt);
}

void LookupList::OnEdit(wxListEvent& evt)
{
    wxString item = evt.GetText();
    int type = *(int*)evt.GetData();

    EditDialog *dlg = NULL;
    if (type == g_album)
        dlg = new AlbumDialog(this, item);
    else if (type == g_location)
        dlg = new LocationDialog(this, item);

    dlg->ShowModal();
}

void LookupList::OnPhotoDrop(PhotoDropEvent& evt)
{
    // Hit test list
    int flag;
    int n = HitTest(evt.GetPoint(), flag);

    if (n != wxNOT_FOUND && flag | wxLIST_HITTEST_ONITEM) {
        // An item was hit
        wxString item = GetItemText(n);
        int type = *(int*)GetItemData(n);

        Photo photo = evt.GetPhoto();

        if (type == g_album) {
            // Add the photo to the album
            Album album = Library::Get()->GetAlbum(item);
            if (album.Ok() && Library::Get()->Update(photo, album))
                return;
        } else if (type == g_location) {
            // Set the photo's location
            Location location = Library::Get()->GetLocation(item);

            photo.SetLocation(location);
            if (location.Ok() && Library::Get()->Update(photo))
                return;
        }
    }

    // Event not handled
    evt.Skip();
}

void LookupList::OnLibrary(LibraryEvent&)
{
    PopulateList();
}

