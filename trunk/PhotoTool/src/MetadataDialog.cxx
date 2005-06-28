
#include "MetadataDialog.h"
#include "wxExifList.h"

BEGIN_EVENT_TABLE(MetadataDialog, InputDialog)
END_EVENT_TABLE()

MetadataDialog::MetadataDialog(wxWindow *parent, const Photo& photo)
    : InputDialog(parent, _T("Photo Metadata")), 
      m_photo(photo)
{
    m_list = new wxExifList(this, -1, wxDefaultPosition, wxSize(500, 400));

    wxStaticBox *sbox = new wxStaticBox(this, -1, 
                                        _T("Metadata (exif) Information"));
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(m_list, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer, 0, wxEXPAND|wxALL, 5);
    SetSizer(sizer);
    Fit();
}

bool MetadataDialog::TransferDataFromWindow()
{
    return true;
}

bool MetadataDialog::TransferDataToWindow()
{
    m_list->SetFile(m_photo.GetFileName());

    return true;
}

