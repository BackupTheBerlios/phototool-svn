
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

    wxString GetThumbPath() const;
    wxString GetBasePath() const;
    wxBitmap GetBitmap() const;

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

