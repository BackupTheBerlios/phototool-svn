
#include "PhotoDialog.h"
#include "Location.h"
#include "Camera.h"
#include "Album.h"
#include "DateTimeDialog.h"

#include <wx/xrc/xmlres.h>

BEGIN_EVENT_TABLE(PhotoDialog, InputDialog)
    EVT_BUTTON(XRCID("DateTimeButton"), PhotoDialog::OnDateTime)
END_EVENT_TABLE()

#define EDIT_LOCATIONS _T("Edit locations...")
#define EDIT_CAMERAS _T("Edit cameras...")

PhotoDialog::PhotoDialog(wxWindow *parent, Photo photo)
    : InputDialog(parent, _T("PhotoPanel"), _T("Photograph")),
      m_photo(photo)
{
}

bool PhotoDialog::TransferDataFromWindow()
{
    bool result = true;

    wxString location = CTRL("Location", wxChoice)->GetStringSelection();
    m_photo.SetLocation(Library::Get()->GetLocation(location));

    wxString camera = CTRL("Camera", wxChoice)->GetStringSelection();
    m_photo.SetCamera(Library::Get()->GetCamera(camera));

    m_photo.SetName(CTRL("Name", wxTextCtrl)->GetValue());
    m_photo.SetDescription(CTRL("Description", wxTextCtrl)->GetValue());

    wxDateTime taken;
    taken.ParseFormat(CTRL("DateTime", wxTextCtrl)->GetValue(), DATE_FORMAT);
    m_photo.SetTaken(taken);

    result &= Library::Get()->Update(m_photo);

    // Photo albums
    wxArrayString albums;
    CTRL("Albums", AlbumList)->GetSelections(albums);
    result &= Library::Get()->Update(m_photo, albums);

    return result;
}

bool PhotoDialog::TransferDataToWindow()
{
    wxString date = m_photo.GetTaken().Format(DATE_FORMAT);
    CTRL("DateTime", wxTextCtrl)->SetValue(date);

    CTRL("Name", wxTextCtrl)->SetValue(m_photo.GetName());
    CTRL("Description", wxTextCtrl)->SetValue(m_photo.GetDescription());

    // Thumbnail image
    CTRL("Thumbnail", wxStaticBitmap)->SetBitmap(m_photo.GetBitmap());

    // Set camera
    wxString camera = m_photo.GetCamera().GetName();
    CTRL("Camera", wxChoice)->SetStringSelection(camera);

    // Set location
    wxString location = m_photo.GetLocation().GetName();
    CTRL("Location", wxChoice)->SetStringSelection(location);

    // Set selected albums
    wxArrayString selected;
    Library::Get()->GetAlbums(m_photo, selected);
    CTRL("Albums", AlbumList)->SetSelections(selected);

    return true;
}

void PhotoDialog::OnDateTime(wxCommandEvent&)
{
    wxDateTime taken;
    taken.ParseFormat(CTRL("DateTime", wxTextCtrl)->GetValue(), DATE_FORMAT);

    DateTimeDialog *dlg = new DateTimeDialog(this, taken);
    if (dlg->ShowModal() == wxID_OK) {
        wxString date = dlg->GetDateTime().Format(DATE_FORMAT);
        CTRL("DateTime", wxTextCtrl)->SetValue(date);
    }
}

