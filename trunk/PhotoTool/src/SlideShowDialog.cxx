
#include "SlideShowDialog.h"
#include "SlideShowFrame.h"
#include "Library.h"
#include "Config.h"
#include "Notify.h"

#include <wx/xrc/xmlres.h>
#include <wx/spinctrl.h>

SlideShowDialog::SlideShowDialog(wxWindow *parent)
    : InputDialog(parent, _T("SlideShowPanel"), _T("Start Slide Show"))
{
    // Change OK button text to something more appropriate
    CTRL("OK", wxButton)->SetLabel(_T("Start"));
}

bool SlideShowDialog::TransferDataFromWindow()
{
    Config::SetTransitionTime(CTRL("TransitionTime", wxSpinCtrl)->GetValue());

    wxString album = CTRL("Albums", wxChoice)->GetStringSelection();
    if (album.Length() == 0) {
        Notify::Info(this, _("Select an album to show"));
        return false;
    }

    PhotoArray photos;
    Library::Get()->GetPhotosByAlbum(photos, album);

    SlideShowFrame *frame = new SlideShowFrame(this);
    frame->Show(true);
    frame->StartSlideShow(photos, Config::GetTransitionTime());

    return true;
}

bool SlideShowDialog::TransferDataToWindow()
{
    CTRL("TransitionTime", wxSpinCtrl)->SetValue(Config::GetTransitionTime());

    // Populate albums
    wxArrayString items;
    Library::Get()->LookupAlbums(items);

    CTRL("Albums", wxChoice)->Clear();
    for(size_t i = 0; i < items.Count(); i++) 
        CTRL("Albums", wxChoice)->Append(items[i]);

    return true;
}

