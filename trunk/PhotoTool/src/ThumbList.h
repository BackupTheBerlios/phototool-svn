
#ifndef THUMBLIST_H
#define THUMBLIST_H

#include "Library.h"
#include "wxBoxList.h"

class ThumbListItem : public wxBoxListItem
{
public:
    ThumbListItem(wxWindow *parent, const wxBitmap& bitmap);

private:
    wxStaticBitmap *m_thumb;

    DECLARE_EVENT_TABLE()
};

class ThumbList : public wxBoxList
{
public:
    ThumbList(wxWindow *parent);

    void SetList(const PhotoArray& list);
    PhotoArray& GetList() { return m_photoList; }

    Photo GetPhoto();

    void OnEdit(wxCommandEvent&);

private:
    PhotoArray m_photoList;

    DECLARE_EVENT_TABLE()
};

#endif

