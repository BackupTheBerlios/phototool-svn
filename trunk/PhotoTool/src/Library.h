
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Record.h"

#include <wx/sqlite.h>

class Library 
{
public:
    static Library* Get();

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

    long GetNextPhotoId();

protected:
    bool Lookup(const wxString& query, wxArrayString& items);

    bool QueryPhotos(const wxString& sql, PhotoArray& array);
    Photo QueryPhoto(const wxString& sql);
    Photo GetPhoto(int id);

    Camera QueryCamera(const wxString& sql);
    Camera GetCamera(int id);

    Location QueryLocation(const wxString& sql);
    Location GetLocation(int id);

    Album QueryAlbum(const wxString& sql);
    Album GetAlbum(int id);

    wxSQLiteDatabase* m_db;

private:
    Library();
    ~Library();

    wxString Pad(const wxString& str) 
    {
        wxString tmp = str;
        tmp.Replace(_T("'"), _T("''"));
        return _T("'") + tmp + _T("'");
    }

    static Library* m_instance;
};

#endif

