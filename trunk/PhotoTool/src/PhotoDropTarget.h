
#ifndef PHOTODROPTARGET_H
#define PHOTODROPTARGET_H

#include "Record.h"

#include <wx/dnd.h>

class PhotoDataObject : public wxFileDataObject
{
public:
    PhotoDataObject(const Photo& photo);
};

class PhotoDropTarget : public wxFileDropTarget
{
public:
    PhotoDropTarget(wxWindow *owner);

    bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& files);

    static void AddDropTarget(wxWindow *target);
    static wxDragResult DoDragDrop(wxWindow *source, const Photo& photo);

private: 
    wxWindow *m_owner;
};

#endif

