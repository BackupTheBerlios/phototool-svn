
#include "Record.h"
#include "Config.h"
#include "Image.h"

#include <wx/file.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(PhotoArray);

wxString Photo::GetFileName() const
{
    if (m_file.Length() > 0 || GetId() < 0) {
        return m_file;
    } else {
        wxString file;
        file << Config::GetBasePath() << wxFILE_SEP_PATH 
             << GetId() << _T(".jpg");
        return file;
    }
}

wxString Photo::GetThumbPath() const
{
    wxString thumbPath;
    thumbPath << Config::GetBasePath() << wxFILE_SEP_PATH 
              << _T("thumbs") << wxFILE_SEP_PATH
              << GetId() << _T(".jpg");

    // If the thumbnail image doesn't exist, create it!
    if (!wxFileExists(thumbPath)) {
        // Open the image and scale it
        Image image(GetFileName());
        image.RescaleAspect(THUMB_WIDTH, THUMB_HEIGHT);

        // Save the thumbnail
        image.SaveFile(thumbPath, wxBITMAP_TYPE_JPEG);
    }

    return thumbPath;
}

wxString Photo::GetBasePath() const
{
    wxString basePath;
    basePath << Config::GetBasePath() << wxFILE_SEP_PATH 
             << GetId();
    return basePath;
}

wxBitmap Photo::GetBitmap() const
{
    return wxImage(GetThumbPath());
}

