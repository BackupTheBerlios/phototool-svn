
#ifndef _WX_EXIFGRID_H_
#define _WX_EXIFGRID_H_

#include "wxExif.h"

#include <wx/listctrl.h>

class wxExifList : public wxListCtrl
{
public:
    wxExifList(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize, long style = 0,
               const wxValidator& validator = wxDefaultValidator,
               const wxString &name = wxT("exifList"));
    ~wxExifList() { }

    void SetFile(const wxString& file);

    void PopulateList();

    void OnCreate(wxWindowCreateEvent&);
    void OnSize(wxSizeEvent& evt);

private:
    wxExif m_data;

    DECLARE_DYNAMIC_CLASS(wxExifList)
    DECLARE_EVENT_TABLE()
};

#endif

