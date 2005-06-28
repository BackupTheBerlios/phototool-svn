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

#include "SlideShowDialog.h"
#include "SlideShowFrame.h"
#include "Library.h"
#include "Config.h"
#include "Notify.h"

#include <wx/spinctrl.h>

SlideShowDialog::SlideShowDialog(wxWindow *parent)
    : InputDialog(parent, _T("Start Slide Show"))
{
    // TODO
    // Change OK button text to something more appropriate
    //CTRL("OK", wxButton)->SetLabel(_T("Import..."));

    m_albums = new wxChoice(this, -1, wxDefaultPosition, wxSize(200, -1));
    m_transitionTime = new wxSpinCtrl(this, -1, wxEmptyString, 
                                      wxDefaultPosition, wxSize(50, -1));
    m_transitionTime->SetRange(0, 3600);

    wxBoxSizer *timeSizer = new wxBoxSizer(wxHORIZONTAL);
    timeSizer->Add(m_transitionTime, 0, wxRIGHT, 5);
    timeSizer->Add(new wxStaticText(this, -1, _T("seconds")));

    wxFlexGridSizer *fsizer = new wxFlexGridSizer(2, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Album:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_albums);
    fsizer->Add(new wxStaticText(this, -1, _T("Transition Time:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(timeSizer);

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("Options"));
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer);
    SetSizer(sizer);
    Fit();
}

bool SlideShowDialog::TransferDataFromWindow()
{
    Config::SetTransitionTime(m_transitionTime->GetValue());

    wxString album = m_albums->GetStringSelection();
    if (album.Length() == 0) {
        Notify::Info(this, _("Select an album to show"));
        return false;
    }

    PhotoArray photos;
    Library::Get()->GetPhotosByAlbum(photos, album);

    SlideShowFrame *frame = new SlideShowFrame(this);
    frame->Show(true);
    frame->StartSlideShow(photos, Config::GetTransitionTime());

    return true;
}

bool SlideShowDialog::TransferDataToWindow()
{
    m_transitionTime->SetValue(Config::GetTransitionTime());

    // Populate albums
    wxArrayString items;
    Library::Get()->LookupAlbums(items);

    m_albums->Clear();
    for(size_t i = 0; i < items.Count(); i++) 
        m_albums->Append(items[i]);

    return true;
}

