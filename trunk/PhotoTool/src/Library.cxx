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

#include "Library.h"
#include "SQL.h"

#include <wx/filefn.h>
#include <wx/filename.h>

extern "C++" {
    Library* Library::m_instance = NULL;
}

Library::Library()
    : m_db(NULL)
{
}

Library::~Library()
{
    if (m_db) {
        m_db->Close();
        delete m_db;
        m_db = NULL;
    }
} 

Library* Library::Get() 
{
    if (!m_instance)
        m_instance = new Library();

    return m_instance;
}

bool Library::Load(const wxString& dir)
{
    // Ensure photo directory exists
    if (!wxDirExists(dir))
        wxMkdir(dir);

    bool newLibrary = true;
    wxString database = dir + wxFILE_SEP_PATH + _T("db");
    if (wxFileExists(database))
        newLibrary = false;

    if (m_db) {
        m_db->Close();
        delete m_db;
        m_db = NULL;
    }

    m_db = new wxSQLiteDatabase(database);

    if (newLibrary && m_db->Ok()) {
        wxSQLiteQuery query(*m_db);

        query.Execute(CREATE_CAMERA);
        query.Execute(CREATE_LOCATION);
        query.Execute(CREATE_ALBUM);
        query.Execute(CREATE_PHOTO_ALBUM);
        query.Execute(CREATE_PHOTO);
    }

    return m_db->Ok();
}

bool Library::Lookup(const wxString& sql, wxArrayString& items)
{
    // Clear the items array 
    items.Clear();

    wxSQLiteQueryResult query(*m_db);
    if (!query.Execute(sql)) 
        return false;

    // Grab the result
    for(int i = 0; i < query.NumRows(); i++)
        items.Add(query.Fields(i, 0).AsString());

    return true;
}

bool Library::LookupLocations(wxArrayString& items)
{
    return Lookup(_T("SELECT name FROM location ORDER BY name"), items);
}

Location Library::QueryLocation(const wxString& sql)
{
    wxSQLiteQueryResult query(*m_db);

    if (!query.Execute(sql) || query.NumRows() != 1)
        return Location();

    Location location;
    location.SetId(query.Fields(0, 0).AsLong());
    location.SetName(query.Fields(0, 1).AsString());
    location.SetDescription(query.Fields(0, 2).AsString());

    return location;
}

Location Library::GetLocation(const wxString& name)
{
    wxString sql;
    sql << _T("SELECT * FROM location WHERE name LIKE ") << Pad(name);
    return QueryLocation(sql);
}

Location Library::GetLocation(int id)
{
    wxString sql;
    sql << _T("SELECT * FROM location WHERE location_id = ") << id;
    return QueryLocation(sql);
}

bool Library::Update(Location& location)
{
    wxSQLiteQuery query(*m_db);
    wxString sql;

    if (location.GetId() < 0) {
        sql << _T("INSERT INTO location VALUES(NULL, ") 
            << Pad(location.GetName()) << _T(", ") 
            << Pad(location.GetDescription()) << _T(")");
    } else {
        sql << _T("UPDATE location SET name = ") << Pad(location.GetName())
            << _T(", description = ") << Pad(location.GetDescription())
            << _T(" WHERE location_id = ") << location.GetId();
    }

    bool result = query.Execute(sql);
    if (result) Notify(location);
    return result;
}

bool Library::Delete(Location& location)
{
    if (location.GetId() < 0)
        return true;

    wxSQLiteQuery query(*m_db);
    wxString sql;

    sql << _T("DELETE FROM location WHERE location_id = ")
        << location.GetId();

    bool result = query.Execute(sql);
    if (result) Notify(location);
    return result;
}

bool Library::LookupCameras(wxArrayString& items)
{
    return Lookup(_T("SELECT manufacturer || ' ' || model FROM camera"), 
                  items);
}

Camera Library::QueryCamera(const wxString& sql)
{
    wxSQLiteQueryResult query(*m_db);

    if (!query.Execute(sql) || query.NumRows() != 1)
        return Camera();

    Camera camera;
    camera.SetId(query.Fields(0, 0).AsLong());
    camera.SetModel(query.Fields(0, 1).AsString());
    camera.SetManufacturer(query.Fields(0, 2).AsString());
    camera.SetMegaPixels(query.Fields(0, 3).AsDouble());
    camera.SetZoom(query.Fields(0, 4).AsDouble());

    return camera;
}

Camera Library::GetCamera(const wxString& name)
{
    wxString sql;
    sql << _T("SELECT * FROM camera ")
        << _T("WHERE (manufacturer || ' ' || model) LIKE ") 
        << Pad(name);
    return QueryCamera(sql);
}

Camera Library::GetCamera(int id)
{
    wxString sql;
    sql << _T("SELECT * FROM camera WHERE camera_id = ") << id;
    return QueryCamera(sql);
}

bool Library::Update(Camera& camera)
{
    wxSQLiteQuery query(*m_db);
    wxString sql;

    if (camera.GetId() < 0) {
        sql << _T("INSERT INTO camera VALUES(NULL, ") 
            << Pad(camera.GetModel()) << _T(", ") 
            << Pad(camera.GetManufacturer()) << _T(", ") 
            << camera.GetMegaPixels() << _T(", ") 
            << camera.GetZoom() << _T(")");
    } else {
        sql << _T("UPDATE camera SET model = ") << Pad(camera.GetModel())
            << _T(", manufacturer = ") << Pad(camera.GetManufacturer())
            << _T(", megapixels = ") << camera.GetMegaPixels()
            << _T(", zoom = ") << camera.GetZoom()
            << _T(" WHERE camera_id = ") << camera.GetId();
    }

    bool result = query.Execute(sql);
    if (result) Notify(camera);
    return result;
}

bool Library::Delete(Camera& camera)
{
    if (camera.GetId() < 0)
        return true;

    wxSQLiteQuery query(*m_db);
    wxString sql;

    sql << _T("DELETE FROM camera WHERE camera_id = ")
        << camera.GetId();

    bool result = query.Execute(sql);
    if (result) Notify(camera);
    return result;
}

bool Library::LookupAlbums(wxArrayString& items)
{
    return Lookup(_T("SELECT name FROM album ORDER BY name"), items);
}

Album Library::QueryAlbum(const wxString& sql)
{
    wxSQLiteQueryResult query(*m_db);

    if (!query.Execute(sql) || query.NumRows() != 1)
        return Album();

    Album album;
    album.SetId(query.Fields(0, 0).AsLong());
    album.SetName(query.Fields(0, 1).AsString());
    album.SetDescription(query.Fields(0, 2).AsString());

    return album;
}

Album Library::GetAlbum(const wxString& name)
{
    wxString sql;
    sql << _T("SELECT * FROM album WHERE name LIKE ") << Pad(name);
    return QueryAlbum(sql);
}

Album Library::GetAlbum(int id)
{
    wxString sql;
    sql << _T("SELECT * FROM album WHERE album_id = ") << id;
    return QueryAlbum(sql);
}

bool Library::Update(Album& album)
{
    wxSQLiteQuery query(*m_db);
    wxString sql;

    if (album.GetId() < 0) {
        sql << _T("INSERT INTO album VALUES(NULL, ") 
            << Pad(album.GetName()) << _T(", ") 
            << Pad(album.GetDescription()) << _T(")");
    } else {
        sql << _T("UPDATE album SET name = ") << Pad(album.GetName())
            << _T(", description = ") << Pad(album.GetDescription())
            << _T(" WHERE album_id = ") << album.GetId();
    }

    bool result = query.Execute(sql);
    if (result) Notify(album);
    return result;
}

bool Library::Delete(Album& album)
{
    if (album.GetId() < 0)
        return true;

    wxSQLiteQuery query(*m_db);
    wxString sql;

    sql << _T("DELETE FROM album WHERE album_id = ")
        << album.GetId();

    bool result = query.Execute(sql);
    if (result) Notify(album);
    return result;
}

bool Library::QueryPhotos(const wxString& sql, PhotoArray& array)
{
    array.Clear();

    wxSQLiteQueryResult query(*m_db);
    if (!query.Execute(sql)) 
        return false;

    for(int i = 0; i < query.NumRows(); i++)
        array.Add(GetPhoto(query.Fields(i, 0).AsLong()));

    return true;
}

bool Library::GetPhotos(PhotoArray& array)
{
    return QueryPhotos(_T("SELECT photo_id FROM photo;"), array);
}

bool Library::GetPhotosByAlbum(PhotoArray& array, const wxString &album)
{
    wxString sql;

    sql << _T("SELECT photo_album.photo ") 
        << _T("FROM photo_album LEFT JOIN album LEFT JOIN photo ") 
        << _T("ON album = album_id AND photo_album.photo = photo_id ") 
        << _T("WHERE album.name LIKE ") << Pad(album) 
        << _T(" ORDER BY position, photo.taken");

    return QueryPhotos(sql, array);
}

bool Library::GetPhotosByLocation(PhotoArray& array, 
                                     const wxString &location)
{
    wxString sql;

    sql << _T("SELECT photo_id FROM photo LEFT JOIN location ")
        << _T("ON location = location_id ")
        << _T("WHERE location.name LIKE ") << Pad(location);

    return QueryPhotos(sql, array);
}

bool Library::GetPhotosByTaken(PhotoArray& array, const wxDateTime& from, 
                               const wxDateTime& to)
{
    wxString sql;

    sql << _T("SELECT photo_id FROM photo WHERE ")
        << _T("taken >= ") << from.GetTicks()
        << _T(" AND taken <= ") << to.GetTicks() 
        << _T(" ORDER BY taken;");

    return QueryPhotos(sql, array);
}

bool Library::GetDatesTaken(wxDateTimeArray& array, const wxDateTime& from, 
                            const wxDateTime& to)
{
    array.Clear();

    wxString sql;
    sql << _T("SELECT DISTINCT(taken) FROM photo ")
        << _T("WHERE taken >= ") << from.GetTicks() 
        << _T(" AND taken <= ") << to.GetTicks()
        << _T(" ORDER BY taken;");

    wxSQLiteQueryResult query(*m_db);
    if (!query.Execute(sql)) 
        return false;

    for(int i = 0; i < query.NumRows(); i++)
        array.Add(query.Fields(i, 0).AsLong());

    return true;
}

Photo Library::QueryPhoto(const wxString& sql)
{
    wxSQLiteQueryResult query(*m_db);

    if (!query.Execute(sql) || query.NumRows() != 1)
        return Photo();

    Photo photo;
    photo.SetId(query.Fields(0, 0).AsLong());
    photo.SetExternalFileName(query.Fields(0, 1).AsString());
    photo.SetName(query.Fields(0, 2).AsString());
    photo.SetDescription(query.Fields(0, 3).AsString());
    photo.SetTaken(query.Fields(0, 4).AsDate());
    photo.SetLocation(GetLocation(query.Fields(0, 5).AsLong()));
    photo.SetCamera(GetCamera(query.Fields(0, 6).AsLong()));

    return photo;
}

Photo Library::GetPhoto(const wxDateTime& taken)
{
    wxString sql;
    sql << _T("SELECT * FROM photo WHERE taken = ") << taken.GetTicks();

    Photo photo = QueryPhoto(sql);
    return photo;
}

Photo Library::GetPhoto(const wxString& fileName)
{
    wxString sql;
    sql << _T("SELECT * FROM photo WHERE file_name LIKE ") << Pad(fileName);

    // Check if photo is external
    Photo photo = QueryPhoto(sql);
    if (photo.Ok()) return photo;

    // Parse name into taken component
    wxDateTime taken;
    taken.ParseFormat(fileName.Right(23).c_str(), Photo::GetFileNameFormat());

    return GetPhoto(taken);
}

Photo Library::GetPhoto(int id)
{
    wxString sql;
    sql << _T("SELECT * FROM photo WHERE photo_id = ") << id;
    return QueryPhoto(sql);
}

bool Library::Update(Photo& photo)
{
    wxSQLiteQuery query(*m_db);
    wxString sql;

    if (photo.GetId() < 0) {
        sql << _T("INSERT INTO photo VALUES(NULL, ") 
            << Pad(photo.GetExternalFileName()) << _T(", ") 
            << Pad(photo.GetName()) << _T(", ") 
            << Pad(photo.GetDescription()) << _T(", ") 
            << photo.GetTaken().GetTicks() << _T(", ") 
            << photo.GetLocation().GetId() << _T(", ") 
            << photo.GetCamera().GetId() << _T(")");
    } else {
        sql << _T("UPDATE photo SET ")
            << _T("filename = ") << Pad(photo.GetExternalFileName())
            << _T(", name = ") << Pad(photo.GetName())
            << _T(", description = ") << Pad(photo.GetDescription())
            << _T(", taken = ") << photo.GetTaken().GetTicks()
            << _T(", location = ") << photo.GetLocation().GetId()
            << _T(", camera = ") << photo.GetCamera().GetId()
            << _T(" WHERE photo_id = ") << photo.GetId();
    }

    bool result = query.Execute(sql);

    if (result) {
        if (photo.GetId() < 0)
            photo.SetId(m_db->LastInsertRowId());

        Notify(photo);
    }

    return result;
}

bool Library::Delete(Photo& photo)
{
    if (photo.GetId() < 0)
        return true;

    wxSQLiteQuery query(*m_db);
    wxString sql;
    bool result = true;

    // Remove the photo
    sql << _T("DELETE FROM photo WHERE photo_id = ") << photo.GetId();
    result &= query.Execute(sql);

    // Remove stored file
    if (photo.GetExternalFileName().Length() == 0)
        wxRemoveFile(photo.GetFileName());
    // Remove thumbnail
    wxRemoveFile(photo.GetThumbFileName());

    // Remove photo albums
    sql.Clear();
    sql << _T("DELETE FROM photo_album WHERE photo = ") << photo.GetId();
    result &= query.Execute(sql);

    if (result) Notify(photo);
    return result;
}

bool Library::GetAlbums(const Photo& photo, wxArrayString& array)
{
    wxSQLiteQueryResult query(*m_db);
    wxString sql;

    array.Clear();

    sql << _T("SELECT album.name FROM album, photo_album ")
        << _T("WHERE album.album_id = photo_album.album ")
        << _T("      AND photo_album.photo = ")
        << photo.GetId();

    if (!query.Execute(sql)) 
        return false;

    for(int i = 0; i < query.NumRows(); i++)
        array.Add(query.Fields(i, 0).AsString());

    return true;
}

bool Library::Update(const Photo& photo, const wxArrayString& array,
                     const wxArrayInt& position)
{
    wxSQLiteQuery query(*m_db);
    wxString sql;
    bool result = true;

    // Delete existing photo albums 
    sql << _T("DELETE FROM photo_album WHERE photo = ")
        << photo.GetId();
    query.Execute(sql);

    // Add the (new/updated) photo albums 
    for(size_t i = 0; i < array.Count(); i++) {
        sql.Clear();
        sql << _T("INSERT INTO photo_album VALUES (NULL, ")
            << _T("(SELECT album_id FROM album WHERE name LIKE ")
            << Pad(array[i]) << _T("), ") << photo.GetId() << _T(", ");

        if (position.Count() == 0)
            sql << _T("-1");
        else 
            sql << position[i];

        sql << _T(");");

        result &= query.Execute(sql);
    }

    if (result) Notify(photo);
    return result;
}

bool Library::Update(const Photo& photo, const Album& album)
{
    wxSQLiteQuery query(*m_db);
    wxString sql;

    // Delete existing album entry
    sql << _T("DELETE FROM photo_album WHERE photo = ") << photo.GetId()
        << _T(" AND album_id = ") << album.GetId();
    query.Execute(sql);

    // Add the (new/updated) photo albums 
    sql.Clear();
    sql << _T("INSERT INTO photo_album VALUES (NULL, ")
        << album.GetId() << _T(", ") 
        << photo.GetId() << _T(", -1);");

    bool result = query.Execute(sql);
    if (result) Notify(photo);
    return result;
}

long Library::GetNextPhotoId()
{
    wxSQLiteQueryResult query(*m_db);
    wxString sql;

    sql << _T("SELECT max(photo_id) + 1 FROM photo;");

    if (!query.Execute(sql)) 
        return 1;

    return query.Fields(0, 0).AsLong();
}

void Library::AddHandler(wxWindow *handler)
{
    m_handlers.Append(handler);
}

bool Library::RemoveHandler(wxWindow *handler)
{
    return m_handlers.DeleteObject(handler);
}

void Library::Notify(const Album& album)
{ 
    LibraryEvent evt(EVT_LIBRARY_ALBUM_EVENT, album);
    NotifyHandlers(evt); 
}

void Library::Notify(const Photo& photo)
{ 
    LibraryEvent evt(EVT_LIBRARY_PHOTO_EVENT, photo);
    NotifyHandlers(evt); 
}

void Library::Notify(const Location& location)
{ 
    LibraryEvent evt(EVT_LIBRARY_LOCATION_EVENT, location);
    NotifyHandlers(evt); 
}

void Library::Notify(const Camera& camera)
{ 
    LibraryEvent evt(EVT_LIBRARY_CAMERA_EVENT, camera);
    NotifyHandlers(evt); 
}

void Library::NotifyHandlers(LibraryEvent& evt)
{
    for(wxWindowList::Node *n = m_handlers.GetFirst(); n; n = n->GetNext()) {
        wxWindow *handler = n->GetData();
        handler->GetEventHandler()->AddPendingEvent(evt);
    }
}

