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

#ifndef PHOTODIALOG_H
#define PHOTODIALOG_H

#include "InputDialog.h"
#include "Record.h"

class PhotoDialog : public InputDialog
{
public:
    PhotoDialog(wxWindow *parent, const Photo& photo = Photo());

    ACCESSOR(Photo, m_photo, Photo)

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

    void OnDateTime(wxCommandEvent&);

private:
    Photo m_photo;

    DECLARE_EVENT_TABLE()
};

#endif

