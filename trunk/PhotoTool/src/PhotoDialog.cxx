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

#include "PhotoDialog.h"
#include "Album.h"
#include "Camera.h"
#include "DateTime.h"
#include "Library.h"
#include "Location.h"

PhotoDialog::PhotoDialog(wxWindow *parent, const Photo& photo)
    : InputDialog(parent, _T("Photograph")),
      m_photo(photo)
{
    // Create controls
    m_location = new LocationLookup(this, -1, wxDefaultPosition, 
                                    wxSize(200, -1));

    m_dateTime = new DateTimeCtrl(this);
    m_camera = new CameraLookup(this, -1, wxDefaultPosition, 
                                wxSize(200, -1));
    m_name = new wxTextCtrl(this, -1);
    m_description = new wxTextCtrl(this, -1, wxEmptyString, 
                                   wxDefaultPosition, wxSize(300, 160), 
                                   wxTE_MULTILINE); 

    m_thumbnail = new wxStaticBitmap(this, -1, wxNullBitmap, 
                                     wxDefaultPosition, wxSize(133, 100));
    m_albums = new AlbumList(this, -1, wxDefaultPosition, 
                             wxSize(200, 110));

    // Photo information
    wxFlexGridSizer *fsizer = new wxFlexGridSizer(2, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Location:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_location);
    fsizer->Add(new wxStaticText(this, -1, _T("Date/Time:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_dateTime);
    fsizer->Add(new wxStaticText(this, -1, _T("Camera:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_camera);
    fsizer->Add(new wxStaticText(this, -1, _T("Name:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_name, 0, wxEXPAND);
    fsizer->Add(new wxStaticText(this, -1, _T("Description:")));
    fsizer->Add(m_description);

    wxStaticBox *left_sbox = new wxStaticBox(this, -1, _T("Photo Information"));
    wxStaticBoxSizer *left_ssizer = new wxStaticBoxSizer(left_sbox, wxVERTICAL);
    left_ssizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);
    
    // Album selection
    wxStaticBox *album_sbox = new wxStaticBox(this, -1, _T("Albums"));
    wxStaticBoxSizer *album_ssizer = new wxStaticBoxSizer(album_sbox, wxVERTICAL);
    album_ssizer->Add(m_albums, 1, wxEXPAND|wxALL, 5);

    // Albums and thumbnail preview
    wxBoxSizer *right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(m_thumbnail, 0, wxALL|wxALIGN_CENTER, 10);
    right_sizer->Add(album_ssizer, 1, wxEXPAND);

    // Group everything
    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(left_ssizer, 0, wxEXPAND|wxALL, 5);
    mainSizer->Add(right_sizer, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mainSizer);
    SetSizer(sizer);
    Fit();
}

bool PhotoDialog::TransferDataFromWindow()
{
    bool result = true;

    wxString location = m_location->GetStringSelection();
    m_photo.SetLocation(Library::Get()->GetLocation(location));

    wxString camera = m_camera->GetStringSelection();
    m_photo.SetCamera(Library::Get()->GetCamera(camera));

    m_photo.SetName(m_name->GetValue());
    m_photo.SetDescription(m_description->GetValue());

    wxDateTime taken = m_dateTime->GetValue();

    if (taken != m_photo.GetTaken() && m_photo.IsExternal()) {
        wxString oldThumbName = m_photo.GetThumbFileName();
        wxString oldFileName = m_photo.GetFileName();

        m_photo.SetTaken(taken);
        wxString thumbName = m_photo.GetThumbFileName();
        wxString fileName = m_photo.GetFileName();

        // Move file to new location
        wxRenameFile(oldThumbName, thumbName);
        wxRenameFile(oldFileName, fileName);
    } 
    else {
        m_photo.SetTaken(taken);
    }

    result &= Library::Get()->Update(m_photo);

    // Photo albums
    wxArrayString albums;
    m_albums->GetSelections(albums);
    result &= Library::Get()->Update(m_photo, albums);

    return result;
}

bool PhotoDialog::TransferDataToWindow()
{
    m_dateTime->SetValue(m_photo.GetTaken());

    m_name->SetValue(m_photo.GetName());
    m_description->SetValue(m_photo.GetDescription());

    // Thumbnail image
    m_thumbnail->SetBitmap(m_photo.GetBitmap());

    // Set camera
    wxString camera = m_photo.GetCamera().GetName();
    m_camera->SetStringSelection(camera);

    // Set location
    wxString location = m_photo.GetLocation().GetName();
    m_location->SetStringSelection(location);

    // Set selected albums
    wxArrayString selected;
    Library::Get()->GetAlbums(m_photo, selected);
    m_albums->SetSelections(selected);

    return true;
}

