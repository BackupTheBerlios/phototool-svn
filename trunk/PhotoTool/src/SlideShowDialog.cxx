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

#include <wx/xrc/xmlres.h>
#include <wx/spinctrl.h>

SlideShowDialog::SlideShowDialog(wxWindow *parent)
    : InputDialog(parent, _T("SlideShowPanel"), _T("Start Slide Show"))
{
    // Change OK button text to something more appropriate
    CTRL("OK", wxButton)->SetLabel(_T("Start"));
}

bool SlideShowDialog::TransferDataFromWindow()
{
    Config::SetTransitionTime(CTRL("TransitionTime", wxSpinCtrl)->GetValue());

    wxString album = CTRL("Albums", wxChoice)->GetStringSelection();
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
    CTRL("TransitionTime", wxSpinCtrl)->SetValue(Config::GetTransitionTime());

    // Populate albums
    wxArrayString items;
    Library::Get()->LookupAlbums(items);

    CTRL("Albums", wxChoice)->Clear();
    for(size_t i = 0; i < items.Count(); i++) 
        CTRL("Albums", wxChoice)->Append(items[i]);

    return true;
}

