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

#include "EditPage.h"

#include <wx/xrc/xmlres.h>

EditPanel::EditPanel(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                       wxVSCROLL | wxSUNKEN_BORDER)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *p = wxXmlResource::Get()->LoadPanel(this, _T("AdjustPanel"));
    sizer->Add(p);

    SetScrollbars(1, 1, 1, 1);
    SetSizer(sizer);
    FitInside();
}

BEGIN_EVENT_TABLE(EditViewer, wxScrolledWindow)
    EVT_SIZE(EditViewer::OnSize)
END_EVENT_TABLE()

EditViewer::EditViewer(wxWindow *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxWHITE);
}

void EditViewer::RefreshDisplay()
{
    if (m_working.Ok()) {
        int width, height;
        GetClientSize(&width, &height);

        // Rescale working image
        m_display = m_working.ScaleAspect(width, height);
        // Center on window
        m_position = m_display.Centered(width, height);

        Refresh();
    }
}

void EditViewer::SetPhoto(const Photo& photo)
{
    m_working = Image(photo.GetFileName());
    RefreshDisplay();
}

void EditViewer::OnDraw(wxDC& dc)
{
    // Clear background
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    // Draw image
    wxBitmap bitmap(m_display);
    if (bitmap.Ok())
        dc.DrawBitmap(bitmap, m_position.x, m_position.y, true);
}

void EditViewer::OnSize(wxSizeEvent& evt)
{
    RefreshDisplay();
    evt.Skip();
}

BEGIN_EVENT_TABLE(EditPage, PageBase)
    EVT_BUTTON(XRCID("GrayScale"), EditPage::OnGrayScale)
    //EVT_BUTTON(XRCID("Serpia"), EditPage::OnSerpia)
    //EVT_BUTTON(XRCID("EdgeDetect"), EditPage::OnEdgeDetect)

    //EVT_BUTTON(XRCID("Histogram"), EditPage::OnHistogram)
    //EVT_BUTTON(XRCID("Metadata"), EditPage::OnMetadata)

    EVT_COMMAND_SCROLL(XRCID("Hue"), EditPage::OnHSL)
    EVT_COMMAND_SCROLL(XRCID("Saturation"), EditPage::OnHSL)
    EVT_COMMAND_SCROLL(XRCID("Luminosity"), EditPage::OnHSL)

    EVT_COMMAND_SCROLL(XRCID("Red"), EditPage::OnRGB)
    EVT_COMMAND_SCROLL(XRCID("Blue"), EditPage::OnRGB)
    EVT_COMMAND_SCROLL(XRCID("Green"), EditPage::OnRGB)
END_EVENT_TABLE()

EditPage::EditPage(wxNotebook *parent)
    : PageBase(parent)
{
    m_split = new wxSplitterWindow(this, wxID_ANY,  wxDefaultPosition, 
                                   wxSize(300, 300), 
                                   wxSP_3DSASH | wxSP_LIVE_UPDATE);

    m_edit = new EditPanel(m_split);
    m_viewer = new EditViewer(m_split);

    m_split->SplitVertically(m_edit, m_viewer, 
                             m_edit->GetBestSize().GetWidth() + 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_split, 1, wxEXPAND);
    SetSizer(sizer);
    Fit();
}

void EditPage::SetSelectedPhoto(const Photo& photo)
{
    m_photo = photo;

    if (m_photo.Ok()) {
        m_viewer->SetPhoto(m_photo);
        // TODO m_edit->ResetControls();
    }
}

void EditPage::OnGrayScale(wxCommandEvent&)
{
    m_viewer->GetWorkingImage().ConvertToGrayScale();
    m_viewer->RefreshDisplay();
}

void EditPage::OnRGB(wxScrollEvent&)
{
    int r = CTRL("Red", wxSlider)->GetValue() - 100;
    int g = CTRL("Blue", wxSlider)->GetValue() - 100;
    int b = CTRL("Green", wxSlider)->GetValue() - 100;

    m_viewer->GetWorkingImage().AdjustRGB(r, g, b);
    m_viewer->RefreshDisplay();
}

void EditPage::OnHSL(wxScrollEvent&)
{
    int h = CTRL("Hue", wxSlider)->GetValue() - 100;
    int s = CTRL("Saturation", wxSlider)->GetValue() - 100;
    int l = CTRL("Luminosity", wxSlider)->GetValue() - 100;

    m_viewer->GetWorkingImage().AdjustHSL(h, s, l);
    m_viewer->RefreshDisplay();
}

