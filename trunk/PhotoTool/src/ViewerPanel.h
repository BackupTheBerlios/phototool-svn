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

#ifndef VIEWERPANEL_H
#define VIEWERPANEL_H

#include "Record.h"

#include <wx/wx.h>

class ViewerPanel : public wxScrolledWindow
{
public:
    ViewerPanel(wxWindow *parent);

    ACCESSOR(Position, m_position, wxPoint)

    void SetPhoto(const Photo& photo);
    void SetPhoto(const wxBitmap& bitmap);

    void OnDraw(wxDC& dc);

    void OnLeftDown(wxMouseEvent& evt);
    void OnLeftUp(wxMouseEvent&);
    void OnMotion(wxMouseEvent& evt);

private:
    wxBitmap m_bitmap;
    wxPoint m_position;
    
    wxPoint m_mouse;

    DECLARE_EVENT_TABLE()
};

#endif

