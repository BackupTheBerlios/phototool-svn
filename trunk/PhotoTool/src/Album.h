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

#ifndef ALBUM_H
#define ALBUM_H

#include "ListDialog.h"

class AlbumListDialog : public ListDialog
{
public:
    AlbumListDialog(wxWindow *parent);

    bool TransferDataToWindow();

protected:
    bool DoAdd();
    bool DoEdit(const wxString& item);
    bool DoRemove(const wxString& item);
};

#include "EditDialog.h"
#include "Library.h"

class AlbumDialog : public EditDialog
{
public:
    AlbumDialog(wxWindow *parent, const wxString& name = _T(""));

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

private:
    Album m_album;
};

class AlbumList : public wxListBox
{
public:
    AlbumList(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator& validator = wxDefaultValidator,
                 const wxString &name = wxT("albumList"));
    ~AlbumList() { }

    void PopulateList();

    void GetSelections(wxArrayString &selection);
    void SetSelections(const wxArrayString &selection);

    void OnCreate(wxWindowCreateEvent&);

private:
    DECLARE_DYNAMIC_CLASS(AlbumList)
    DECLARE_EVENT_TABLE()
};

#endif

