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

#ifndef PHOTOEVENT_H
#define PHOTOEVENT_H

#include "Record.h"

// PhotoEvent

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(EVT_PHOTO_SELECTED_EVENT,  9003)
    DECLARE_EVENT_TYPE(EVT_PHOTOS_SELECTED_EVENT, 9004)
END_DECLARE_EVENT_TYPES()

#define EVT_PHOTO(type, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        type, wxID_ANY, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) \
            wxStaticCastEvent(PhotoEventFunction, &fn), \
        NULL \
    ),

#define EVT_PHOTO_SELECTED(fn)  EVT_PHOTO(EVT_PHOTO_SELECTED, fn)
#define EVT_PHOTOS_SELECTED(fn) EVT_PHOTO(EVT_PHOTOS_SELECTED_EVENT, fn)

class PhotoEvent : public wxNotifyEvent
{
public:
    PhotoEvent(wxEventType type) : wxNotifyEvent(type) { }
    PhotoEvent(const PhotoEvent& pevt);

    ACCESSOR(Photos, m_photos, PhotoArray)
    ACCESSOR(Photo, m_photo, Photo)

    bool HasPhotos() const { return m_photos.Count() > 0; }
    bool HasPhoto() const { return m_photo.Ok(); }

    wxEvent *Clone() const { return new PhotoEvent(*this); }

private:
    PhotoArray m_photos;
    Photo m_photo;
};

typedef void (wxEvtHandler::*PhotoEventFunction)(PhotoEvent&);

// PhotoDropEvent

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(EVT_PHOTO_DROP_EVENT, 10000)
END_DECLARE_EVENT_TYPES()

#define EVT_PHOTO_DROP(fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        EVT_PHOTO_DROP_EVENT, wxID_ANY, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) \
            wxStaticCastEvent(PhotoDropEventFunction, &fn), \
        (wxObject *) NULL \
    ),


class PhotoDropEvent : public wxNotifyEvent
{
public:
    PhotoDropEvent(const Photo& photo, const wxPoint& point)
        : wxNotifyEvent(EVT_PHOTO_DROP_EVENT), 
          m_photo(photo), m_point(point) { }

    ACCESSOR(Photo, m_photo, Photo)
    ACCESSOR(Point, m_point, wxPoint)

    wxEvent *Clone() const { return new PhotoDropEvent(m_photo, m_point); }

private:
    Photo m_photo;
    wxPoint m_point;
};

typedef void (wxEvtHandler::*PhotoDropEventFunction)(PhotoDropEvent&);

#endif

