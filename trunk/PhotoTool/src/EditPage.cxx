
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

