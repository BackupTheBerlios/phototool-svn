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

#ifndef EDITPAGE_H
#define EDITPAGE_H

#include "PageBase.h"
#include "Image.h"

#include <wx/splitter.h>
#include <wx/scrolwin.h>

class EditPanel : public wxScrolledWindow
{
public:
    EditPanel(wxWindow *parent);

private:
};

class EditViewer : public wxScrolledWindow
{
public:
    EditViewer(wxWindow *parent);

    void OnDraw(wxDC& dc);
    void OnSize(wxSizeEvent& evt);

    void SetPhoto(const Photo& photo);
    Image& GetWorkingImage() { return m_working; }

    void RefreshDisplay();

private:
    Image m_working;
        
    Image m_display;
    wxPoint m_position;

    DECLARE_EVENT_TABLE()
};

class EditPage : public PageBase
{
public:
    EditPage(wxNotebook *parent);

    Photo GetSelectedPhoto() { return m_photo; }
    void SetSelectedPhoto(const Photo& photo);

    void OnGrayScale(wxCommandEvent&);

    void OnRGB(wxScrollEvent&);
    void OnHSL(wxScrollEvent&);

private:
    EditPanel *m_edit;
    EditViewer *m_viewer;

    wxSplitterWindow *m_split;

    Photo m_photo;

    DECLARE_EVENT_TABLE()
};

#endif

