
#include "TestPage.h"

TestPage::TestPage(wxNotebook *parent)
    : PageBase(parent)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_list = new ThumbList(this);
    sizer->Add(m_list, 1, wxEXPAND);

    SetSizer(sizer);
    Fit();
}

Photo TestPage::GetSelectedPhoto()
{
    return m_list->GetPhoto();
}

void TestPage::SetSelectedPhoto(const Photo& photo)
{
    // TODO m_list->SetPhoto(photo)
}

