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

// TODO
#include <wx/statline.h>
#include <wx/slider.h>

EditPanel::EditPanel(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                       wxVSCROLL | wxSUNKEN_BORDER)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    int flag = wxEXPAND | (wxALL ^ wxBOTTOM);
    int border = 5;

    sizer->Add(new wxButton(this, wxID_ANY, _T("Black and white")), 
               0, flag, border);
    sizer->Add(new wxButton(this, wxID_ANY, _T("Serpia")), 
               0, flag, border);
    sizer->Add(new wxButton(this, wxID_ANY, _T("Edge detect")), 
               0, flag, border);
    sizer->Add(new wxButton(this, wxID_ANY, _T("Histogram")), 
               0, flag, border);
    sizer->Add(new wxStaticText(this, wxID_ANY, _T("Brightness")), 
               0, flag, border);
    sizer->Add(new wxSlider(this, wxID_ANY, 50, 0, 100), 
               0, flag, border);
    sizer->Add(new wxStaticText(this, wxID_ANY, _T("Contrast")), 
               0, flag, border);
    sizer->Add(new wxSlider(this, wxID_ANY, 50, 0, 100), 
               0, flag, border);

    // Fix width of panel
    SetBestFittingSize(wxSize(140, -1));

    SetScrollbars(1, 1, 1, 1);
    SetSizer(sizer);
    FitInside();
}

EditViewer::EditViewer(wxWindow *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxWHITE);
}

EditPage::EditPage(wxNotebook *parent)
    : PageBase(parent)
{
    m_edit = new EditPanel(this);
    m_viewer = new EditViewer(this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_edit, 0, wxEXPAND);
    sizer->Add(m_viewer, 1, wxEXPAND);

    SetSizer(sizer);
    Fit();
}

