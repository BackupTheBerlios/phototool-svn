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

#ifndef RECORD_H
#define RECORD_H

#include "Util.h"

#include <wx/wx.h>

class Record 
{
public:
    Record() : m_id(-1) { }

    ACCESSOR(Id, m_id, int)

    bool Ok() const { return m_id >= 0; }

private:
    int m_id;
};

class Location : public Record
{
public:
    Location() : Record() { }

    ACCESSOR(Name, m_name, wxString)
    ACCESSOR(Description, m_description, wxString)

private:
    wxString m_name, m_description;
};

class Album : public Record
{
public:
    Album() : Record() { }

    ACCESSOR(Name, m_name, wxString)
    ACCESSOR(Description, m_description, wxString)

private:
    wxString m_name, m_description;
};

class Camera : public Record
{
public:
    Camera() : Record(), m_megapixels(3), m_zoom(10) { }

    wxString GetName() 
    { 
        return GetManufacturer() + _T(" ") + GetModel(); 
    }

    ACCESSOR(Manufacturer, m_manufacturer, wxString)
    ACCESSOR(Model, m_model, wxString)
    ACCESSOR(MegaPixels, m_megapixels, double)
    ACCESSOR(Zoom, m_zoom, double)

private:
    wxString m_manufacturer, m_model;
    double m_megapixels, m_zoom;
};

class Photo : public Record
{
public:
    Photo() : Record() { }

    wxString GetFileName() const;

    ACCESSOR(ExternalFileName, m_file, wxString)

    ACCESSOR(Name, m_name, wxString)
    ACCESSOR(Description, m_description, wxString)
    ACCESSOR(Taken, m_taken, wxDateTime)

    ACCESSOR(Location, m_location, Location)
    ACCESSOR(Camera, m_camera, Camera)

    wxString GetThumbFileName() const;
    wxString GetBaseName() const;
    wxBitmap GetBitmap() const;

    bool IsExternal() const { return m_file.Length() == 0; }

private:
    wxString m_file;

    wxString m_name, m_description;
    wxDateTime m_taken;

    Location m_location;
    Camera m_camera;
};

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(Photo, PhotoArray);

#endif

