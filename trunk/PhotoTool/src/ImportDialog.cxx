
#include "ImportDialog.h"
#include "Util.h"
#include "Notify.h"
#include "Library.h"
#include "Config.h"

#include <wx/xrc/xmlres.h>
#include <wx/tokenzr.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/dir.h>

BEGIN_EVENT_TABLE(ImportDialog, InputDialog)
    EVT_BUTTON(XRCID("ImportFiles"), ImportDialog::OnAddFiles)
    EVT_BUTTON(XRCID("ImportDirectory"), ImportDialog::OnAddDirectory)
    EVT_BUTTON(XRCID("ImportRemove"), ImportDialog::OnRemoveFiles)
    EVT_CHECKBOX(XRCID("CopyFiles"), ImportDialog::OnCopyFiles)
END_EVENT_TABLE()

ImportDialog::ImportDialog(wxWindow *parent)
    : InputDialog(parent, _T("ImportPanel"), _T("Import Photos"))
{
    // Change OK button text to something more appropriate
    CTRL("OK", wxButton)->SetLabel(_T("Import..."));
}

void ImportDialog::OnAddFiles(wxCommandEvent&)
{
    wxFileDialog *dlg = new wxFileDialog(this, _T("Import Photos"), 
                                         wxEmptyString, wxEmptyString, 
                                         IMAGE_WILDCARD, wxOPEN | wxMULTIPLE);

    if (dlg->ShowModal() == wxID_OK) {
        wxString dir = dlg->GetDirectory();

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
    wxDirDialog *dlg = new wxDirDialog(this, _T("Import Photos"));

    if (dlg->ShowModal() == wxID_OK) {

        wxArrayString fileNames;

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
    CTRL("ImportList", wxListBox)->GetSelections(sel);

    for(size_t i = 0; i < sel.Count(); i++)
        m_importList.Remove(CTRL("ImportList", wxListBox)->GetString(sel[i]));

    TransferDataToWindow();
}

void ImportDialog::OnCopyFiles(wxCommandEvent&)
{
    // We can only remove files if copying is turned on
    bool canRemove = CTRL("CopyFiles", wxCheckBox)->IsChecked();
    CTRL("RemoveFiles", wxCheckBox)->Enable(canRemove);
}

bool ImportDialog::TransferDataToWindow()
{
    wxString location = Config::GetDefaultLocation();
    CTRL("DefaultLocation", wxChoice)->SetStringSelection(location);

    wxString camera = Config::GetDefaultCamera();
    CTRL("DefaultCamera", wxChoice)->SetStringSelection(camera);

    // Update the list of images to import
    CTRL("ImportList", wxListBox)->Set(m_importList);
    return true;
}

bool ImportDialog::TransferDataFromWindow()
{
    if (m_importList.Count() == 0) {
        Notify::Info(this, _T("Please add image files to import"));
        return false;
    }

    bool success = true,
         copy = CTRL("CopyFiles", wxCheckBox)->IsChecked(),
         remove = CTRL("RemoveFiles", wxCheckBox)->IsChecked();

    wxString def;

    // Record default location
    def = CTRL("DefaultLocation", wxChoice)->GetStringSelection();
    Config::SetDefaultLocation(def);
    Location location = Library::Get()->GetLocation(def);

    // Record default camera
    def = CTRL("DefaultCamera", wxChoice)->GetStringSelection();
    Config::SetDefaultCamera(def);
    Camera camera = Library::Get()->GetCamera(def);

    // Import path
    wxString importPath = Config::GetBasePath();
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

        if (copy) {
            photo.SetExternalFileName(wxEmptyString);

            if (!Library::Get()->Update(photo)) {
                Notify::Error(this, _T("Failed to insert into database"));
                return false;
            }

            // Copy the file into the import path
            wxString newPath;
            newPath << importPath << wxFILE_SEP_PATH 
                    << nextId << _T(".jpg");
            nextId++;

            wxCopyFile(fileName.GetFullPath(), newPath); 

            if (remove) {
                // Remove the existing file
                wxRemoveFile(fileName.GetFullPath());
            }

        } else {
            // Record the path
            photo.SetExternalFileName(fileName.GetFullPath());
        }

        // Put the photo in the library
        if (!Library::Get()->Update(photo)) {
            // TODO
            Notify::Error(this, _T("There was an error updating the database"));
            return false;
        }
    }

    return success;
}

