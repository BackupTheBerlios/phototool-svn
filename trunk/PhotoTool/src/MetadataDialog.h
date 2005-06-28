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

#ifndef EXIFDIALOG_H
#define EXIFDIALOG_H

#include "InputDialog.h"
#include "Record.h"

class wxExifList;

class MetadataDialog : public InputDialog
{
public:
    MetadataDialog(wxWindow *parent, const Photo& photo);

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

private:
    Photo m_photo;

    wxExifList *m_list;

    DECLARE_EVENT_TABLE()
};

#endif

