
#include "ThumbList.h"
#include "PhotoDialog.h"

#define EDGE 4

BEGIN_EVENT_TABLE(ThumbListItem, wxBoxListItem)
END_EVENT_TABLE()

ThumbListItem::ThumbListItem(wxWindow *parent, const wxBitmap& bitmap)
    : wxBoxListItem(parent)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_thumb = new wxStaticBitmap(this, wxID_ANY, bitmap);
    sizer->Add(m_thumb, 0, wxALIGN_CENTRE | wxALL, EDGE);

    SetSizer(sizer);
    Fit();
}

BEGIN_EVENT_TABLE(ThumbList, wxBoxList)
    EVT_LISTBOX_DCLICK(wxID_ANY, ThumbList::OnEdit)

    EVT_SIZE(ThumbList::OnSize)
END_EVENT_TABLE()

ThumbList::ThumbList(wxWindow *parent)
    : wxBoxList(parent)
{

    SetBoxSize(wxSize(THUMB_WIDTH + (EDGE * 2), THUMB_HEIGHT + (EDGE * 2)));
    SetBoxMargins(1);

    // TODO
    PhotoArray photos;
    Library::Get()->GetPhotos(photos);
    SetList(photos);
}

void ThumbList::SetList(const PhotoArray& list)
{
    m_photoList = list;

    // Remove existing thumbs
    Clear();

    // Add the new thumbs
    for(size_t i = 0; i < m_photoList.Count(); i++)
        Add(new ThumbListItem(this, m_photoList[i].GetBitmap()));
}

Photo ThumbList::GetPhoto()
{
    int i = GetSelection();
    if (i >= 0 && (size_t)i < m_photoList.Count())
        return m_photoList[i];

    return Photo();
}

void ThumbList::OnEdit(wxCommandEvent&)
{
    Photo photo = GetPhoto();
    if (photo.Ok()) {
        PhotoDialog *dlg = new PhotoDialog(this, photo);
        dlg->ShowModal();
    }
}

