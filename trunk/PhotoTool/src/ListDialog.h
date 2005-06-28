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

#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <wx/wx.h>

class ListDialog : public wxDialog
{
public:
    ListDialog(wxWindow *parent, const wxString& title);

    void OnAction(wxCommandEvent&);
    void OnClose(wxCommandEvent&);

    void SetItems(wxArrayString& items);

protected:
    virtual bool DoAdd() = 0;
    virtual bool DoEdit(const wxString& item) = 0;
    virtual bool DoRemove(const wxString& item) = 0;

private:
    wxListBox *m_list;

    DECLARE_EVENT_TABLE()
};

#endif

