
#include "wxExifList.h"

IMPLEMENT_DYNAMIC_CLASS(wxExifList, wxListCtrl)

BEGIN_EVENT_TABLE(wxExifList, wxListCtrl)
    EVT_SIZE(wxExifList::OnSize)
    EVT_WINDOW_CREATE(wxExifList::OnCreate)
END_EVENT_TABLE()

wxExifList::wxExifList(wxWindow *parent, wxWindowID id, 
                       const wxPoint &pos, const wxSize &size, long style,
                       const wxValidator& validator, const wxString &name)
    : wxListCtrl(parent, id, pos, size, style, validator, name)
{
}

void wxExifList::SetFile(const wxString& file)
{
    m_data = wxExif(file);
    PopulateList();
}

void wxExifList::PopulateList()
{
    ClearAll();

    InsertColumn(0, _T("Tag"));
    InsertColumn(1, _T("Value"));

    if (m_data.Ok()) {
        ContentHash& hash = m_data.GetContent();

        // Populate key => value pairs
        long idx = -1;
        for(ContentHash::iterator i = hash.begin(); i != hash.end(); ++i) {
            idx = InsertItem(idx + 1, i->first);
            SetItem(idx, 1, i->second);
        }
    }

    // Force columns to be resized
    SetSize(GetSize());
}

void wxExifList::OnCreate(wxWindowCreateEvent&)
{
}

void wxExifList::OnSize(wxSizeEvent& evt)
{
    // Adjust column width
    SetColumnWidth(0, 170);
    SetColumnWidth(1, evt.GetSize().GetWidth() - 170 - 15);
    evt.Skip();
}

