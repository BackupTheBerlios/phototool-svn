
#ifndef LOOKUPPAGE_H
#define LOOKUPPAGE_H

#include "PageBase.h"
#include "PhotoEvent.h"

#include <wx/splitter.h>

class PhotoList;
class LookupList;
class TakenCalendar;

class LookupPage : public PageBase
{
public:
    LookupPage(wxNotebook *parent);
    ~LookupPage();

    void OnPhotos(PhotoEvent& evt);

    Photo GetSelectedPhoto();

private:
    wxSplitterWindow *m_split;

    LookupList *m_lookupList;
    TakenCalendar *m_calendar;

    PhotoList *m_photoList;

    DECLARE_EVENT_TABLE()
};

#endif

