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

wxString Photo::GetBaseName() const
{
    // <base path>/<year>/<month>/<day>/<hour>-<minute>-<second>
    wxString base;
    base << Config::GetBasePath() << wxFILE_SEP_PATH;

    // Year
    base << m_taken.Format(_T("%Y")) << wxFILE_SEP_PATH;
    if (!wxDirExists(base)) wxMkdir(base);

    // Month
    base << m_taken.Format(_T("%m")) << wxFILE_SEP_PATH;
    if (!wxDirExists(base)) wxMkdir(base);

    // Day
    base << m_taken.Format(_T("%d")) << wxFILE_SEP_PATH;
    if (!wxDirExists(base)) wxMkdir(base);

    // File name
    base << m_taken.Format(_T("%H-%M-%S"));
    return base;
}

wxString Photo::GetFileName() const
{
    if (m_file.Length() > 0 || GetId() < 0) {
        return m_file;
    } else {
        // TODO: Support other formats (format field in database)
        return GetBaseName() << _T(".jpg");
    }
}

wxString Photo::GetThumbFileName() const
{
    wxString thumbFile;

    if (m_file.Length() > 0 || GetId() < 0) {
        // TODO: Support thumbnails for external files
        return _T("");
    } else {
        thumbFile << GetBaseName() << _T(".thumb.jpg");
    }

    // If the thumbnail image doesn't exist, create it!
    if (!wxFileExists(thumbFile)) {
        // Open the image and scale it
        Image image(GetFileName());
        image.RescaleAspect(THUMB_WIDTH, THUMB_HEIGHT);

        // Save the thumbnail
        image.SaveFile(thumbFile, wxBITMAP_TYPE_JPEG);
    }

    return thumbFile;
}

wxBitmap Photo::GetBitmap() const
{
    return wxImage(GetThumbFileName());
}

