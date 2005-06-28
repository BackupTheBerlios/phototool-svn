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

#include "ImportDialog.h"
#include "Util.h"
#include "Notify.h"
#include "Library.h"
#include "Config.h"
#include "Location.h"
#include "Camera.h"

#include <wx/tokenzr.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/dir.h>

#define ID_ImportFilesButton        100
#define ID_ImportDirectoryButton    101
#define ID_ImportRemoveButton       102
#define ID_CopyFilesCheck           103

BEGIN_EVENT_TABLE(ImportDialog, InputDialog)
    EVT_BUTTON(ID_ImportFilesButton, ImportDialog::OnAddFiles)
    EVT_BUTTON(ID_ImportDirectoryButton, ImportDialog::OnAddDirectory)
    EVT_BUTTON(ID_ImportRemoveButton, ImportDialog::OnRemoveFiles)
    EVT_CHECKBOX(ID_CopyFilesCheck, ImportDialog::OnCopyFiles)
END_EVENT_TABLE()

ImportDialog::ImportDialog(wxWindow *parent)
    : InputDialog(parent, _T("Import Photos"))
{
    // TODO
    // Change OK button text to something more appropriate
    //CTRL("OK", wxButton)->SetLabel(_T("Import..."));
  
    m_location = new LocationLookup(this);
    m_camera = new CameraLookup(this);
    m_list = new wxListBox(this, -1, wxDefaultPosition, wxSize(150, 280));
    m_copy = new wxCheckBox(this, ID_CopyFilesCheck, 
                            _T("Copy files into PhotoTool directory"));
    m_remove = new wxCheckBox(this, -1, _T("Remove original files"));

    // Default configuration for imported photos
    wxFlexGridSizer *fsizer = new wxFlexGridSizer(2, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Location:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_location);
    fsizer->Add(new wxStaticText(this, -1, _T("Camera:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_camera);

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("Defaults"));
    wxStaticBoxSizer *defSizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    defSizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);

    // Import photos
    wxBoxSizer *actSizer = new wxBoxSizer(wxHORIZONTAL);
    actSizer->Add(new wxButton(this, ID_ImportFilesButton, 
                               _T("Add Files...")),
                  0, wxALL, 5);
    actSizer->Add(new wxButton(this, ID_ImportDirectoryButton, 
                               _T("Add Directory...")),
                  0, wxALL, 5);
    actSizer->Add(40, 10, 1, wxEXPAND);
    actSizer->Add(new wxButton(this, ID_ImportRemoveButton,
                               _T("Remove")),
                  0, wxALL, 5);

    sbox = new wxStaticBox(this, -1, _T("Photos"));
    wxStaticBoxSizer *importSizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    importSizer->Add(m_list, 1, wxEXPAND|wxALL, 5);
    importSizer->Add(actSizer, 0, wxEXPAND);

    // Configuration options
    sbox = new wxStaticBox(this, -1, _T("Options"));
    wxStaticBoxSizer *optSizer = new wxStaticBoxSizer(sbox, wxHORIZONTAL);
    optSizer->Add(m_copy, 0, wxALL, 5);
    optSizer->Add(m_remove, 0, wxALL, 5);

    // Group everything together
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(defSizer, 0, wxEXPAND|wxALL, 5);
    sizer->Add(importSizer, 0, wxEXPAND|wxALL, 5);
    sizer->Add(optSizer, 0, wxEXPAND|wxALL, 5);
    SetSizer(sizer);
    Fit();
}

void ImportDialog::OnAddFiles(wxCommandEvent&)
{
    wxFileDialog *dlg = new wxFileDialog(this, _T("Import Photos"), 
                                         Config::GetDefaultPath(), 
                                         wxEmptyString, IMAGE_WILDCARD, 
                                         wxOPEN | wxMULTIPLE);

    if (dlg->ShowModal() == wxID_OK) {
        wxString dir = dlg->GetDirectory();

        // Save default path
        Config::SetDefaultPath(dir);

        wxArrayString files; 
        dlg->GetFilenames(files);

        for(size_t i = 0; i < files.Count(); i++) {
            wxString fileName = dir + wxFILE_SEP_PATH + files[i];

            // Ensure each file exists (should never happen, but just in case)
            if (!wxFileExists(fileName)) {
                Notify::Error(this, fileName + _T(" does not exist."));
                continue;
            }

            m_importList.Add(fileName);
        }

        TransferDataToWindow();
    }
}

void ImportDialog::OnAddDirectory(wxCommandEvent&)
{
    wxDirDialog *dlg = new wxDirDialog(this, _T("Import Photos"), 
                                       Config::GetDefaultPath());

    if (dlg->ShowModal() == wxID_OK) {
        wxArrayString fileNames;

        // Save default path
        Config::SetDefaultPath(dlg->GetPath());

        // wxDir::GetAllFiles only supports simple filters, so we need to loop
        // though the list to get all the desired extensions.
        wxStringTokenizer tkz(IMAGE_FILES, _T(";"));
        while(tkz.HasMoreTokens()) {
            wxDir::GetAllFiles(dlg->GetPath(), &fileNames, tkz.GetNextToken(),
                               wxDIR_FILES);
        }

        if (fileNames.Count() == 0) {
            Notify::Error(this, _T("No image files were found in ") + 
                          dlg->GetPath() + _T("."));
            // Nothing to do
            return;
        }

        for(size_t i = 0; i < fileNames.Count(); i++)
            m_importList.Add(fileNames[i]);

        TransferDataToWindow();
    }
}

void ImportDialog::OnRemoveFiles(wxCommandEvent&)
{
    wxArrayInt sel;
    m_list->GetSelections(sel);

    for(size_t i = 0; i < sel.Count(); i++)
        m_importList.Remove(m_list->GetString(sel[i]));

    TransferDataToWindow();
}

void ImportDialog::OnCopyFiles(wxCommandEvent&)
{
    // We can only remove files if copying is turned on
    bool canRemove = m_copy->IsChecked();
    m_remove->Enable(canRemove);
}

bool ImportDialog::TransferDataToWindow()
{
    wxString location = Config::GetDefaultLocation();
    m_location->SetStringSelection(location);

    wxString camera = Config::GetDefaultCamera();
    m_camera->SetStringSelection(camera);

    // Update the list of photos to import
    m_list->Set(m_importList);
    return true;
}

bool ImportDialog::TransferDataFromWindow()
{
    if (m_importList.Count() == 0) {
        Notify::Info(this, _T("Please add image files to import"));
        return false;
    }

    bool success = true,
         copy = m_copy->IsChecked(),
         remove = m_remove->IsChecked();

    wxString def;

    // Record default location
    def = m_location->GetStringSelection();
    Config::SetDefaultLocation(def);
    Location location = Library::Get()->GetLocation(def);

    // Record default camera
    def = m_camera->GetStringSelection();
    Config::SetDefaultCamera(def);
    Camera camera = Library::Get()->GetCamera(def);

    // Import path
    long nextId = Library::Get()->GetNextPhotoId();

    for(size_t i = 0; i < m_importList.Count(); i++) {
        Photo photo;
        wxFileName fileName(m_importList[i]);

        // Time taken defaults to file modification time
        wxDateTime modified;
        fileName.GetTimes(NULL, &modified, NULL);
        photo.SetTaken(modified);

        // Default name
        photo.SetName(fileName.GetName());
        photo.SetDescription(wxEmptyString);

        // Camera and location
        photo.SetCamera(camera);
        photo.SetLocation(location);

        photo.SetExternalFileName(wxEmptyString);

        if (copy) {
            Library::Get()->Update(photo);

            // Copy the file into the import path
            wxCopyFile(fileName.GetFullPath(), photo.GetFileName()); 

            if (remove) {
                // Remove the existing file
                wxRemoveFile(fileName.GetFullPath());
            }
        } 
        else {
            // Record the path
            photo.SetExternalFileName(fileName.GetFullPath());
            Library::Get()->Update(photo);
        }

        wxSafeYield();
        nextId++;
    }

    return success;
}

