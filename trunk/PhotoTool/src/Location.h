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

#ifndef LOCATION_H
#define LOCATION_H

#include "ListDialog.h"

class LocationListDialog : public ListDialog
{
public:
    LocationListDialog(wxWindow *parent);

    bool TransferDataToWindow();

protected:
    bool DoAdd();
    bool DoEdit(const wxString& item);
    bool DoRemove(const wxString& item);
};

#include "EditDialog.h"
#include "Library.h"

class LocationDialog : public EditDialog
{
public:
    LocationDialog(wxWindow *parent, const wxString& name = _T(""));

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

private:
    Location m_location;
};

class LocationLookup : public wxChoice
{
public:
    LocationLookup(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
                   const wxPoint &pos = wxDefaultPosition,
                   const wxSize &size = wxDefaultSize, long style = 0,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString &name = wxT("locationLookup"));
    ~LocationLookup() { }

    void PopulateLookup();

    void OnSelect(wxCommandEvent&);

private:
    DECLARE_DYNAMIC_CLASS(LocationLookup)
    DECLARE_EVENT_TABLE()
};

#endif

