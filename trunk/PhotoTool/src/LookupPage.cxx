
#include "LookupPage.h"
#include "PhotoList.h"
#include "TakenCalendar.h"
#include "LookupList.h"
#include "Config.h"

BEGIN_EVENT_TABLE(LookupPage, PageBase)
    EVT_PHOTO(LookupPage::OnPhotos)
END_EVENT_TABLE()

LookupPage::LookupPage(wxNotebook *parent)
    : PageBase(parent)
{
    m_split = new wxSplitterWindow(this, wxID_ANY,  wxDefaultPosition, 
                                   wxSize(300, 300), 
                                   wxSP_3DSASH | wxSP_LIVE_UPDATE);

    // Lookup side panel (lookup list + photo calendar)
    wxPanel *p = new wxPanel(m_split);

    m_lookupList = new LookupList(p);
    m_calendar = new TakenCalendar(p);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_lookupList, 1, wxEXPAND);
    sizer->Add(m_calendar, 0, wxALL | wxALIGN_CENTER, 5);
    p->SetSizer(sizer);
    p->Fit();

    // Photo list
    m_photoList = new PhotoList(m_split);

    // Split the window 
    m_split->SplitVertically(p, m_photoList, Config::GetSplitPos());

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_split, 1, wxEXPAND);
    SetSizer(sizer);
    Fit();
}

LookupPage::~LookupPage()
{
    Config::SetSplitPos(m_split->GetSashPosition());
}

void LookupPage::OnPhotos(PhotoEvent& evt)
{
    m_photoList->SetList(evt.GetPhotos());
}

Photo LookupPage::GetSelectedPhoto()
{
    return m_photoList->GetPhoto();
}

