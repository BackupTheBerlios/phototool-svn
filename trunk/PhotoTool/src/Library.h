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

#ifndef LIBRARY_H
#define LIBRARY_H

#include "Record.h"
#include "LibraryView.h"

#include <wx/sqlite.h>

class Library 
{
public:
    static Library* Get();

    // Load a database
    bool Load(const wxString& dir);

    // Camera management
    bool LookupCameras(wxArrayString& items);
    Camera GetCamera(const wxString& name);
    bool Update(Camera& camera);
    bool Delete(Camera& camera);

    // Location management
    bool LookupLocations(wxArrayString& items);
    Location GetLocation(const wxString& name);
    bool Update(Location& location);
    bool Delete(Location& location);

    // Album management
    bool LookupAlbums(wxArrayString& items);
    Album GetAlbum(const wxString& name);
    bool Update(Album& album);
    bool Delete(Album& album);

    // Photo management
    Photo GetPhoto(const wxString& fileName);
    bool Update(Photo& photo);
    bool Delete(Photo& photo);
    long GetNextPhotoId();

    // Photo lookup and searching
    bool GetPhotos(PhotoArray& array);
    bool GetPhotosByAlbum(PhotoArray& array, const wxString &album);
    bool GetPhotosByLocation(PhotoArray& array, const wxString &location);
    bool GetPhotosByTaken(PhotoArray& array, const wxDateTime& from, 
                          const wxDateTime& to);

    bool GetDatesTaken(wxDateTimeArray& array, 
                       const wxDateTime& from = wxDateTime((time_t)0),
                       const wxDateTime& to = wxDefaultDateTime);

    // Photo/Album management
    bool GetAlbums(const Photo& photo, wxArrayString& array);
    bool Update(const Photo& photo, const wxArrayString& array,
                const wxArrayInt& position = wxArrayInt());
    bool Update(const Photo& photo, const Album& album);

    // View management
    bool AddView(LibraryView *view);
    bool RemoveView(LibraryView *view);

protected:
    bool Lookup(const wxString& query, wxArrayString& items);

    // Photo querying
    bool QueryPhotos(const wxString& sql, PhotoArray& array);
    Photo QueryPhoto(const wxString& sql);
    Photo GetPhoto(int id);

    // Camera querying
    Camera QueryCamera(const wxString& sql);
    Camera GetCamera(int id);

    // Location querying
    Location QueryLocation(const wxString& sql);
    Location GetLocation(int id);

    // Album Querying
    Album QueryAlbum(const wxString& sql);
    Album GetAlbum(int id);

    // View notification
    void NotifyView(const Album& album);
    void NotifyView(const Photo& photo);
    void NotifyView(const Location& location);
    void NotifyView();

private:
    // The database
    wxSQLiteDatabase* m_db;

    // Library views
    LibraryViewArray m_views;

    wxString Pad(const wxString& str) 
    {
        wxString tmp = str;
        tmp.Replace(_T("'"), _T("''"));
        return _T("'") + tmp + _T("'");
    }

    Library();
    ~Library();

    static Library* m_instance;
};

#endif

