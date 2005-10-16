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

#include "ExportDialog.h"
#include "Library.h"
#include "Config.h"
#include "Notify.h"

#include <wx/textctrl.h>

#define ID_ExportPathButton 100

BEGIN_EVENT_TABLE(ExportDialog, InputDialog)
    EVT_BUTTON(ID_ExportPathButton, ExportDialog::OnPath)
END_EVENT_TABLE()

ExportDialog::ExportDialog(wxWindow *parent) 
    : InputDialog(parent, _T("Export Album"))
{
    m_albums = new wxChoice(this, -1, wxDefaultPosition, wxSize(200, -1));
    m_path = new wxTextCtrl(this, -1, wxEmptyString, 
                            wxDefaultPosition, wxSize(200, -1));

    wxButton *btn = new wxButton(this, ID_ExportPathButton, _T("..."),
                                 wxDefaultPosition, wxSize(25, -1));

    wxBoxSizer *pathSizer = new wxBoxSizer(wxHORIZONTAL);
    pathSizer->Add(m_path, 1);
    pathSizer->Add(btn, 0, wxLEFT, 3);

    wxFlexGridSizer *fsizer = new wxFlexGridSizer(2, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Album:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_albums);
    fsizer->Add(new wxStaticText(this, -1, _T("Path:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(pathSizer);

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("Options"));
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer);
    SetSizer(sizer);
    Fit();
}

void ExportDialog::OnPath(wxCommandEvent&)
{
    wxDirDialog *dlg = new wxDirDialog(this, _T("Export"), 
                                       Config::GetDefaultPath());

    if (dlg->ShowModal() == wxID_OK) {
        Config::SetExportPath(dlg->GetPath());
        m_path->SetValue(dlg->GetPath());
    }
}

bool ExportDialog::TransferDataFromWindow()
{
    Config::SetExportPath(m_path->GetValue());

    wxString album = m_albums->GetStringSelection();
    if (album.Length() == 0) {
        Notify::Info(this, _("Select an album to export"));
        return false;
    }

    return DoExport(album);
}

bool ExportDialog::TransferDataToWindow()
{
    m_path->SetValue(Config::GetExportPath());

    // Populate albums
    wxArrayString items;
    Library::Get()->LookupAlbums(items);

    m_albums->Clear();
    for(size_t i = 0; i < items.Count(); i++) 
        m_albums->Append(items[i]);

    return true;
}

// TODO: Move this to a seperate module
bool ExportDialog::DoExport(const wxString& album)
{
    // Path to export to
    wxString path = Config::GetExportPath();

    // Path where the images should be saved
    wxString images = path;
    images << wxFILE_SEP_PATH << _T("images") << wxFILE_SEP_PATH;

    // Ensure photo directory exists
    if (!wxDirExists(path))
        wxMkdir(path);
    if (!wxDirExists(images))
        wxMkdir(images);

    PhotoArray photos;
    Library::Get()->GetPhotosByAlbum(photos, album);

    for(size_t i = 0; i < photos.Count(); i++) {
        Image image(photos[i].GetFileName());

        // Rescale photo for on-line use
        if (image.GetWidth() > 640 || image.GetHeight() > 480)
            image.RescaleAspect(640, 480);

        // Save to images directory
        wxString imageFile = images;
        imageFile << i << _T(".jpg");
        image.SaveFile(imageFile);

        wxString thumbFile = images;
        thumbFile << i << _T(".thumb.jpg");
        wxCopyFile(photos[i].GetThumbFileName(), thumbFile, true);
    }

    // HTML document
    wxString exportFile = Config::GetDataPath();
    exportFile << _T("export") << wxFILE_SEP_PATH << _T("export.html");

    wxString destFile = path; 
    destFile << wxFILE_SEP_PATH << _T("index.html");
    wxCopyFile(exportFile, destFile, true);

    // Photos JavaScript
    wxString scriptFile = path;
    scriptFile << wxFILE_SEP_PATH << _T("export.js");
    wxFile out(scriptFile.c_str(), wxFile::write);

    out.Write(_T("function load_photos() {\n"));

    wxString photoArrayDecl;
    photoArrayDecl << _T("    photos = new Array(") 
                   << photos.Count() << _T(");\n\n");
    out.Write(photoArrayDecl);

    for (size_t i = 0; i < photos.Count(); i++) {
        wxString photoArrayEntry;
        photoArrayEntry << _T("    photos[") << i 
                        << _T("] = new Array(\"") << photos[i].GetName()
                        << _T("\", \"\");\n");
        out.Write(photoArrayEntry);
    }

    out.Write(_T("}\n"));
    out.Close();

    return true;
}

