
#ifndef PHOTOEVENT_H
#define PHOTOEVENT_H

#include "Record.h"

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(EVT_PHOTO_EVENT, 8000)
    DECLARE_EVENT_TYPE(EVT_PHOTO_DROP_EVENT, 8001)
END_DECLARE_EVENT_TYPES()

#define EVT_PHOTO(fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        EVT_PHOTO_EVENT, wxID_ANY, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) \
            wxStaticCastEvent(PhotoEventFunction, &fn), \
        NULL \
    ),

#define EVT_PHOTO_DROP(fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        EVT_PHOTO_DROP_EVENT, wxID_ANY, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) \
            wxStaticCastEvent(PhotoDropEventFunction, &fn), \
        (wxObject *) NULL \
    ),

class PhotoEvent : public wxEvent
{
public:
    PhotoEvent(const PhotoArray& photos = PhotoArray())
        : wxEvent(0, EVT_PHOTO_EVENT), m_photos(photos) { }

    ACCESSOR(Photos, m_photos, PhotoArray);

    wxEvent *Clone() const { return new PhotoEvent(m_photos); }

private:
    PhotoArray m_photos;
};

class PhotoDropEvent : public wxEvent
{
public:
    PhotoDropEvent(const Photo& photo, const wxPoint& point)
        : wxEvent(0, EVT_PHOTO_DROP_EVENT), m_photo(photo), m_point(point) { }

    ACCESSOR(Photo, m_photo, Photo);
    ACCESSOR(Point, m_point, wxPoint);

    wxEvent *Clone() const { return new PhotoDropEvent(m_photo, m_point); }

private:
    Photo m_photo;
    wxPoint m_point;
};

typedef void (wxEvtHandler::*PhotoEventFunction)(PhotoEvent&);
typedef void (wxEvtHandler::*PhotoDropEventFunction)(PhotoDropEvent&);

#endif

