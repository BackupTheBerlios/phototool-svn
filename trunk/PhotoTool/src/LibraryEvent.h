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

#ifndef LIBRARYEVENT_H
#define LIBRARYEVENT_H

#include "Record.h"

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(EVT_LIBRARY_LOCATION_EVENT, 7000)
    DECLARE_EVENT_TYPE(EVT_LIBRARY_CAMERA_EVENT, 7001)
    DECLARE_EVENT_TYPE(EVT_LIBRARY_PHOTO_EVENT, 7002)
    DECLARE_EVENT_TYPE(EVT_LIBRARY_ALBUM_EVENT, 7003)
END_DECLARE_EVENT_TYPES()

#define EVT_LIBRARY(type, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        type, wxID_ANY, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) \
            wxStaticCastEvent(LibraryEventFunction, &fn), \
        NULL \
    ),

#define EVT_LIBRARY_LOCATION(fn)  EVT_LIBRARY(EVT_LIBRARY_LOCATION_EVENT, fn)
#define EVT_LIBRARY_ALBUM(fn) EVT_LIBRARY(EVT_LIBRARY_ALBUM_EVENT, fn)
#define EVT_LIBRARY_PHOTO(fn) EVT_LIBRARY(EVT_LIBRARY_PHOTO_EVENT, fn)
#define EVT_LIBRARY_CAMERA(fn) EVT_LIBRARY(EVT_LIBRARY_CAMERA_EVENT, fn)

// Library event accessor (GetType; casts m_record to appropriate type)
#define LE_ACCESSOR(evt, type) \
    type Get##type() { \
        if (GetEventType() == evt) \
            return *(static_cast<type *>(&m_record)); \
        return type(); \
    }

            //return *(dynamic_cast<type>(&m_record)); 
class LibraryEvent : public wxEvent
{
public:
    LibraryEvent(wxEventType type, const Record& record)
        : wxEvent(0, type), m_record(record) { }

    ACCESSOR(Record, m_record, Record)

    LE_ACCESSOR(EVT_LIBRARY_LOCATION_EVENT, Location)
    LE_ACCESSOR(EVT_LIBRARY_ALBUM_EVENT, Album)
    LE_ACCESSOR(EVT_LIBRARY_PHOTO_EVENT, Photo)
    LE_ACCESSOR(EVT_LIBRARY_CAMERA_EVENT, Camera)

    wxEvent *Clone() const 
    {
        return new LibraryEvent(GetEventType(), m_record);
    }

private:
    Record m_record;
};

typedef void (wxEvtHandler::*LibraryEventFunction)(LibraryEvent&);

#endif

