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

#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "InputDialog.h"

class LocationLookup;
class CameraLookup;

class ImportDialog : public InputDialog
{
public:
    ImportDialog(wxWindow *parent);

    void OnAddFiles(wxCommandEvent&);
    void OnAddDirectory(wxCommandEvent&);
    void OnCopyFiles(wxCommandEvent&);
    void OnRemoveFiles(wxCommandEvent&);

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

private:
    wxArrayString m_importList;

    LocationLookup *m_location;
    CameraLookup *m_camera;
    wxListBox *m_list;
    wxCheckBox *m_copy, *m_remove;

    DECLARE_EVENT_TABLE()
};

#endif

