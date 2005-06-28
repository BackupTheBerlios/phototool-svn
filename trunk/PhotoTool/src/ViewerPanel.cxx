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

#include "ViewerPanel.h"

BEGIN_EVENT_TABLE(ViewerPanel, wxScrolledWindow)
    EVT_LEFT_DOWN(ViewerPanel::OnLeftDown)
    EVT_LEFT_UP(ViewerPanel::OnLeftUp)
    EVT_MOTION(ViewerPanel::OnMotion)
END_EVENT_TABLE()

ViewerPanel::ViewerPanel(wxWindow *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxBLACK);
    SetForegroundColour(*wxBLACK);

    SetCursor(wxCURSOR_CROSS);

    SetScrollbars(1, 1, 1, 1);
}

void ViewerPanel::SetPhoto(const Photo& photo)
{
    if (photo.Ok()) {
        m_bitmap = wxImage(photo.GetFileName());

        SetScrollbars(1, 1, m_bitmap.GetWidth(), m_bitmap.GetHeight());
    } 
    else {
        m_bitmap = wxBitmap();
    }

    Refresh();
}

void ViewerPanel::SetPhoto(const wxBitmap& bitmap)
{
    m_bitmap = bitmap;

    SetScrollbars(1, 1, m_bitmap.GetWidth(), m_bitmap.GetHeight());
    Refresh();
}

void ViewerPanel::OnDraw(wxDC& dc)
{
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();

    if (m_bitmap.Ok())
        dc.DrawBitmap(m_bitmap, m_position.x, m_position.y, true);
}

void ViewerPanel::OnLeftDown(wxMouseEvent& evt)
{
    if (!HasCapture()) {
        CaptureMouse();
        m_mouse = evt.GetPosition();
    }
}

void ViewerPanel::OnLeftUp(wxMouseEvent&)
{
    if (HasCapture())
        ReleaseMouse();
}

void ViewerPanel::OnMotion(wxMouseEvent& evt)
{
    if (HasCapture()) {
        wxPoint mouse = evt.GetPosition();

        // Adjust scroll position
        int x, y;
        GetViewStart(&x, &y);
        Scroll(x + (m_mouse.x - mouse.x), y + (m_mouse.y - mouse.y));

        m_mouse = mouse;
    }
}

