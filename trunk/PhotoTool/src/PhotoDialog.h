
#ifndef PHOTODIALOG_H
#define PHOTODIALOG_H

#include "InputDialog.h"
#include "Library.h"

class PhotoDialog : public InputDialog
{
public:
    PhotoDialog(wxWindow *parent, Photo photo = Photo());

    ACCESSOR(Photo, m_photo, Photo)

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

    void OnDateTime(wxCommandEvent&);

private:
    Photo m_photo;

    DECLARE_EVENT_TABLE()
};

#endif

