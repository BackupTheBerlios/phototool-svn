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

