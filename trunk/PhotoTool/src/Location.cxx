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

#include "Location.h"
#include "Notify.h"

LocationListDialog::LocationListDialog(wxWindow *parent)
    : ListDialog(parent, _T("Locations"))
{
}

bool LocationListDialog::TransferDataToWindow()
{
    wxArrayString items;
    Library::Get()->LookupLocations(items);
    SetItems(items);

    return true;
}

bool LocationListDialog::DoAdd()
{
    LocationDialog *dlg = new LocationDialog(this);
    return (dlg->ShowModal() == wxID_OK);
}

bool LocationListDialog::DoEdit(const wxString& item)
{
    LocationDialog *dlg = new LocationDialog(this, item);
    return (dlg->ShowModal() == wxID_OK);
}

bool LocationListDialog::DoRemove(const wxString& item)
{
    Location location = Library::Get()->GetLocation(item);
    return Library::Get()->Delete(location);
}


LocationDialog::LocationDialog(wxWindow *parent, const wxString &name)
    : EditDialog(parent, _T("Edit Location"))
{
    if (name.Length() != 0) {
        m_location = Library::Get()->GetLocation(name);
        TransferDataToWindow();
    }
}

bool LocationDialog::TransferDataFromWindow()
{
    if (GetName().Length() == 0) {
        Notify::Info(this, _T("Enter a name for this location"));
        return false;
    }

    m_location.SetName(GetName());
    m_location.SetDescription(GetDescription());

    return Library::Get()->Update(m_location);
}

bool LocationDialog::TransferDataToWindow()
{
    SetName(m_location.GetName());
    SetDescription(m_location.GetDescription());
    return true;
}

#define EDIT_LOCATIONS _T("Edit locations...")

IMPLEMENT_DYNAMIC_CLASS(LocationLookup, wxChoice)

BEGIN_EVENT_TABLE(LocationLookup, wxChoice)
    EVT_WINDOW_CREATE(LocationLookup::OnCreate)
    EVT_CHOICE(wxID_ANY, LocationLookup::OnSelect)
END_EVENT_TABLE()

LocationLookup::LocationLookup(wxWindow *parent, wxWindowID id, 
                               const wxPoint &pos, const wxSize &size, 
                               long style, const wxValidator& validator,
                               const wxString &name)
    : wxChoice(parent, id, pos, size, wxArrayString(), style, validator, name)
{
}

void LocationLookup::OnCreate(wxWindowCreateEvent&)
{
    PopulateLookup();
}

void LocationLookup::OnSelect(wxCommandEvent&)
{
    wxString location = GetStringSelection();
    if (location.Cmp(EDIT_LOCATIONS) == 0) {
        LocationListDialog *dlg = new LocationListDialog(this);
        dlg->ShowModal();

        PopulateLookup();
    }
}

void LocationLookup::PopulateLookup()
{
    // Populate lookup
    wxArrayString items;
    Library::Get()->LookupLocations(items);

    Clear();
    for(size_t i = 0; i < items.Count(); i++) 
        Append(items[i]);

    Append(EDIT_LOCATIONS);
}

