
#include "PhotoDropTarget.h"
#include "PhotoEvent.h"
#include "Image.h"
#include "Library.h"

PhotoDataObject::PhotoDataObject(const Photo& photo)
    : wxFileDataObject()
{
    AddFile(photo.GetFileName());
}

PhotoDropTarget::PhotoDropTarget(wxWindow *owner)
    : wxFileDropTarget(), m_owner(owner)
{
}

bool PhotoDropTarget::OnDropFiles(wxCoord x, wxCoord y, 
                                  const wxArrayString& files)
{
    // We can only handle one file at a time!
    if (files.Count() != 1) 
        return false;

    Photo photo = Library::Get()->GetPhoto(files[0]);
    if (photo.Ok()) {
        PhotoDropEvent evt(photo, wxPoint(x, y));
        return m_owner->GetEventHandler()->ProcessEvent(evt);
    }

    return false;
}

void PhotoDropTarget::AddDropTarget(wxWindow *target)
{
    target->SetDropTarget(new PhotoDropTarget(target));
}

wxDragResult PhotoDropTarget::DoDragDrop(wxWindow *source, const Photo& photo)
{
    PhotoDataObject data(photo);

    // Create thumbnail for drag icon
    Image thumb(photo.GetThumbPath());
    thumb.RescaleAspect(64, 64);

    // Create the icon (wxCursor in Windows, wxIcon everywhere else)
#if defined (__WXMSW__)
    wxCursor icon(thumb);
#else
    wxIcon icon; 
    icon.CopyFromBitmap(thumb);
#endif

    // TODO: Use different icons for each parameter (change image to black and
    // white, etc.)

    // Create the drop source
    wxDropSource dropSource(source, icon, icon, icon);
    dropSource.SetData(data);

    return dropSource.DoDragDrop(true);
}

