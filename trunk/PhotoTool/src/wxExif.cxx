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

#include "wxExif.h"

#include <wx/file.h>

#define BUFFER 1024

void wxExif_content_foreach_entry(ExifEntry *entry, void *data)
{
    wxExif *exif = (wxExif*)data;

    // Key
    wxString key(exif_tag_get_name(entry->tag), wxConvUTF8);

    // Value
    char buffer[BUFFER];
    exif_entry_get_value(entry, buffer, BUFFER);
    wxString value(buffer, wxConvUTF8);

    // Key => Value
    exif->GetContent()[key] = value;
}

void wxExif_content_foreach(ExifContent *content, void *data)
{
    exif_content_foreach_entry(content, &wxExif_content_foreach_entry, data);
}

wxExif::wxExif(const wxString& file)
    : m_data(NULL)
{
    m_data = exif_data_new_from_file(file.mb_str(wxConvUTF8));
    if (!m_data) return;

    // Dump data contents
    exif_data_foreach_content(m_data, &wxExif_content_foreach, (void*)this);
}

wxExif::~wxExif()
{
    if (m_data) {
        // FIXME: This is segfaulting for some reason....
        // Exif should have more documentation!
      
        // exif_data_free(m_data);
        m_data = NULL;
    }
}

