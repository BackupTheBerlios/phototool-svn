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

#ifndef VIEWERFRAME_H
#define VIEWERFRAME_H

#include "Record.h"

#include <wx/wx.h>
#include <wx/timer.h>

class ViewerPanel;

class SlideShowFrame : public wxFrame
{
public:
    SlideShowFrame(wxWindow *parent);

    void StartSlideShow(const PhotoArray& photos, int transitionTime = 10);

    void NextPhoto() { m_idx++; UpdatePhoto(); }
    void PreviousPhoto() { m_idx--; UpdatePhoto(); }
    void UpdatePhoto();

    void OnTimer(wxTimerEvent&);
    void OnKeyUp(wxKeyEvent& evt);

private:
    PhotoArray m_photos;
    int m_idx;

    int m_transitionTime;
    wxTimer m_timer;

    ViewerPanel *m_viewer;

    DECLARE_EVENT_TABLE()
};

#endif

