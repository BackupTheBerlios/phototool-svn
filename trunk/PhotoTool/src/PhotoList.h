
#ifndef PHOTOLIST_H
#define PHOTOLIST_H

#include "Library.h"

#include <wx/wx.h>
#include <wx/htmllbox.h>

class PhotoList : public wxHtmlListBox
{
public:
    PhotoList(wxWindow *parent);

    void OnEdit(wxCommandEvent&);

    void SetList(const PhotoArray& list);
    PhotoArray& GetList() { return m_photoList; }

    void OnPopup(wxMouseEvent&);
    void OnDragDrop(wxMouseEvent& evt);

    Photo GetPhoto();

protected:
    wxString OnGetItem(size_t n) const;

private:
    PhotoArray m_photoList;

    DECLARE_EVENT_TABLE()
};

#endif

