
#ifndef LOOKUPLIST_H
#define LOOKUPLIST_H

#include <wx/wx.h>
#include <wx/listctrl.h>

#include "PhotoEvent.h"

class LookupList : public wxListCtrl
{
public:
    LookupList(wxWindow *parent);

    void PopulateList();

    void OnSize(wxSizeEvent& evt);

    void OnSelect(wxListEvent& evt);
    void OnEdit(wxListEvent& evt);

    void OnPhotoDrop(PhotoDropEvent& evt);

private:
    static wxImageList *m_images;

    DECLARE_EVENT_TABLE()
};

#endif

