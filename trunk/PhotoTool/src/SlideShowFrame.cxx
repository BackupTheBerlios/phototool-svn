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

#include "SlideShowFrame.h"
#include "ViewerPanel.h"
#include "Image.h"
#include "Notify.h"

BEGIN_EVENT_TABLE(SlideShowFrame, wxFrame)
    EVT_KEY_UP(SlideShowFrame::OnKeyUp)

    EVT_TIMER(wxID_ANY, SlideShowFrame::OnTimer)
END_EVENT_TABLE()

SlideShowFrame::SlideShowFrame(wxWindow *parent)
    : wxFrame(parent, wxID_ANY, _T("Photo Viewer"))
{
    m_timer.SetOwner(this);
    m_viewer = new ViewerPanel(this);
}

void SlideShowFrame::StartSlideShow(const PhotoArray& photos, 
                                    int transitionTime)
{
    // Put us in fullscreen mode
    ShowFullScreen(true);
    m_viewer->SetFocus();
    wxSafeYield(this);

    // Reset parameters
    m_idx = -1;
    m_photos = photos;
    m_transitionTime = transitionTime;

    // Start timer
    m_timer.Stop();
    m_timer.Start(m_transitionTime * 1000);

    NextPhoto();
}

void SlideShowFrame::UpdatePhoto()
{
    int count = (int)m_photos.Count();
    if (m_timer.IsRunning()) {
        // Timer set, stop at the end of the show
        if (m_idx >= count) {
            m_timer.Stop();
            Close();
            return;
        } else if (m_idx < 0)
            m_idx = 0;
    } else {
        // No timer set, wrap index
        if (m_idx >= count)
            m_idx = 0;
        else if (m_idx < 0)
            m_idx = count - 1;
    }

    // Display current image, scaled to display size
    Image image(m_photos[m_idx].GetFileName());

    int displayWidth, displayHeight;
    wxDisplaySize(&displayWidth, &displayHeight);

    if (image.GetWidth() > displayWidth || image.GetHeight() > displayHeight)
        image.RescaleAspect(displayWidth, displayHeight);

    // Send image to the viewer
    m_viewer->SetPhoto(image);
    m_viewer->SetPosition(image.Centered(displayWidth, displayHeight));

    // Disable scrollbars
    m_viewer->SetScrollbars(1, 1, 1, 1);
    m_viewer->Refresh();
}

void SlideShowFrame::OnTimer(wxTimerEvent&)
{
    NextPhoto();
}

void SlideShowFrame::OnKeyUp(wxKeyEvent& evt)
{
    int key = evt.GetKeyCode();

    switch(key) {

    // End slide show
    case WXK_ESCAPE:
        m_timer.Stop();
        Close();
        break;

    // Next photo
    case WXK_RIGHT:
    case WXK_SPACE:
    case WXK_TAB:
        m_timer.Stop();
        NextPhoto();
        break;

    // Previous photo
    case WXK_LEFT:
    case WXK_BACK:
    case WXK_RETURN:
        m_timer.Stop();
        PreviousPhoto();
        break;
    }
}

