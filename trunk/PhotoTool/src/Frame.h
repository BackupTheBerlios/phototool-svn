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

#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>

class ViewerPanel;
class PageBase;

class Frame : public wxFrame
{
public:
    Frame(const wxString& title);

    void OnFileOpen(wxCommandEvent&);
    void OnFileImport(wxCommandEvent&);
    void OnFileExit(wxCommandEvent&);

    void OnEditCameras(wxCommandEvent&);
    void OnEditLocations(wxCommandEvent&);
    void OnEditAlbums(wxCommandEvent&);
    void OnEditPreferences(wxCommandEvent&);

    void OnPhotoEdit(wxCommandEvent&);
    void OnPhotoDelete(wxCommandEvent&);
    void OnPhotoSlideShow(wxCommandEvent&);

    void OnHelpAbout(wxCommandEvent&);

    void OnPageChanged(wxNotebookEvent& evt);

private:
    wxNotebook *m_book;

    PageBase* GetCurrentPage();

    DECLARE_EVENT_TABLE()
};

#endif

