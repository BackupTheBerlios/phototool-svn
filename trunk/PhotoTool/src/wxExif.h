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

#ifndef _WX_EXIF_H_
#define _WX_EXIF_H_

#include <wx/wx.h>
#include <wx/hashmap.h>
#include <libexif/exif-data.h>

WX_DECLARE_STRING_HASH_MAP(wxString, ContentHash);

class wxExif
{
public:
    wxExif() : m_data(NULL) { }
    wxExif(const wxString& file);
    ~wxExif();

    bool Ok() { return m_data != NULL; }

    ContentHash& GetContent() { return m_content; }

private:
    // No copy
    wxExif(const wxExif&) { }

    ExifData *m_data;
    ContentHash m_content;
};

#endif

