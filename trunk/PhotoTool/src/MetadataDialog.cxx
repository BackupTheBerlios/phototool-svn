
#include "MetadataDialog.h"
#include "wxExifList.h"

#include <wx/xrc/xmlres.h>

BEGIN_EVENT_TABLE(MetadataDialog, InputDialog)
END_EVENT_TABLE()

MetadataDialog::MetadataDialog(wxWindow *parent, const Photo& photo)
    : InputDialog(parent, _T("MetadataPanel"), _T("Photo Metadata")), 
      m_photo(photo)
{
}

bool MetadataDialog::TransferDataFromWindow()
{
    return true;
}

bool MetadataDialog::TransferDataToWindow()
{
    CTRL("MetadataList", wxExifList)->SetFile(m_photo.GetFileName());

    return true;
}

