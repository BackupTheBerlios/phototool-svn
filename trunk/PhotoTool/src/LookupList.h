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

#ifndef LOOKUPLIST_H
#define LOOKUPLIST_H

#include "PhotoEvent.h"
#include "LibraryEvent.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

class LookupList : public wxListCtrl
{
public:
    LookupList(wxWindow *parent);
    ~LookupList();

    void PopulateList();

    void OnSize(wxSizeEvent& evt);

    void OnSelect(wxListEvent& evt);
    void OnEdit(wxListEvent& evt);

    void OnPhotoDrop(PhotoDropEvent& evt);
    void OnLibrary(LibraryEvent&);

private:
    static wxImageList *m_images;

    DECLARE_EVENT_TABLE()
};

#endif

