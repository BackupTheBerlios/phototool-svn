/**
 * PhotoTool is an application for organizing and publishing a collection of
 * digital images. 
 *
 * Copyright (C) 2005  Bryan Bulten (bryan@bulten.ca)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "LookupPage.h"
#include "PhotoList.h"
#include "TakenCalendar.h"
#include "LookupList.h"
#include "Config.h"

BEGIN_EVENT_TABLE(LookupPage, PageBase)
    EVT_PHOTOS_SELECTED(LookupPage::OnPhotos)
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
    if (evt.HasPhotos())
        m_photoList->SetList(evt.GetPhotos());
}

Photo LookupPage::GetSelectedPhoto()
{
    return m_photoList->GetPhoto();
}

