
#include "ViewerPage.h"
#include "ViewerPanel.h"

ViewerPage::ViewerPage(wxNotebook *parent)
    : PageBase(parent)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_viewer = new ViewerPanel(this);
    sizer->Add(m_viewer, 1, wxEXPAND);

    SetSizer(sizer);
    Fit();
}

void ViewerPage::SetSelectedPhoto(const Photo& photo)
{
    m_photo = photo;
    m_viewer->SetPhoto(photo);
}

