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

#include "Frame.h"

#include "Location.h"
#include "Camera.h"
#include "Album.h"
#include "Notify.h"
#include "Config.h"

#include "AboutDialog.h"
#include "ImportDialog.h"
#include "ExportDialog.h"
#include "MetadataDialog.h"
#include "PhotoDialog.h"
#include "SetupDialog.h"
#include "SlideShowDialog.h"

#include "TestPage.h" // TODO
#include "EditPage.h"
#include "LookupPage.h"
#include "ViewerPage.h"

#define ID_FileOpen         100
#define ID_FileImport       101
#define ID_FileExport       102
#define ID_FileExit         103

#define ID_EditCameras      200
#define ID_EditLocations    201
#define ID_EditAlbums       202
#define ID_EditPreferences  203

#define ID_PhotoEdit        300
#define ID_PhotoMetadata    301
#define ID_PhotoDelete      302
#define ID_PhotoSlideShow   304

#define ID_HelpAbout        400

BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(ID_FileOpen, Frame::OnFileOpen)
    EVT_MENU(ID_FileImport, Frame::OnFileImport)
    EVT_MENU(ID_FileExport, Frame::OnFileExport)
    EVT_MENU(ID_FileExit, Frame::OnFileExit)

    EVT_MENU(ID_EditCameras, Frame::OnEditCameras)
    EVT_MENU(ID_EditLocations, Frame::OnEditLocations)
    EVT_MENU(ID_EditAlbums, Frame::OnEditAlbums)
    EVT_MENU(ID_EditPreferences, Frame::OnEditPreferences)

    EVT_MENU(ID_PhotoEdit, Frame::OnPhotoEdit)
    EVT_MENU(ID_PhotoMetadata, Frame::OnPhotoMetadata)
    EVT_MENU(ID_PhotoDelete, Frame::OnPhotoDelete)
    EVT_MENU(ID_PhotoSlideShow, Frame::OnPhotoSlideShow)

    EVT_MENU(ID_HelpAbout, Frame::OnHelpAbout)

    EVT_NOTEBOOK_PAGE_CHANGED(-1, Frame::OnPageChanged)
END_EVENT_TABLE()

Frame::Frame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    // Set default position and size
    SetSize(Config::GetPosX(), Config::GetPosY(), 
            Config::GetSizeX(), Config::GetSizeY());

    // Initialize the menu bar
    InitMenu();

    // Initialize the toolbar
    InitToolBar();

    // Initialize the notebook display
#if defined(__WXMSW__)
    m_book = new wxNotebook(this); 
#else
    m_book = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                            wxNB_BOTTOM);
#endif

    m_book->AddPage(new LookupPage(m_book), _T("Photos"));
    m_book->AddPage(new ViewerPage(m_book), _T("View"));
    m_book->AddPage(new EditPage(m_book), _T("Edit"));
    m_book->AddPage(new TestPage(m_book), _T("Test"));

    CreateStatusBar(1);
    SetStatusText(_T("Welcome to ") + title, 0);
}

void Frame::InitMenu()
{
    wxMenuBar *menuBar = new wxMenuBar();
    wxMenu *menu;

    // File menu
    menu = new wxMenu();
    menu->Append(ID_FileOpen, _T("&Open...\tCtrl+O"), 
                 _T("Open a photo directory"));
    menu->Append(ID_FileImport, _T("Import Photos...\tCtrl+I"), 
                 _T("Import photos into the database"));
    menu->AppendSeparator();
    menu->Append(ID_FileExit, _T("E&xit\tCtrl+Shift+W"), 
                 _T("Exit this application"));
    menuBar->Append(menu, _T("&File"));

    // Edit menu
    menu = new wxMenu();
    menu->Append(ID_EditCameras, _T("C&ameras..."),
                 _T("Edit the list of cameras"));
    menu->Append(ID_EditAlbums, _T("&Albums..."),
                 _T("Edit the list of photo albums"));
    menu->Append(ID_EditLocations, _T("&Locations..."),
                 _T("Edit the list of photo locations"));
    menu->AppendSeparator();
    menu->Append(ID_EditPreferences, _T("&Preferences..."), 
                 _T("Edit application preferences"));
    menuBar->Append(menu, _T("&Edit"));

    // Photo menu
    menu = new wxMenu();
    menu->Append(ID_PhotoEdit, _T("&Edit...\tCtrl+E"), 
                 _T("Edit the selected photo"));
    menu->Append(ID_PhotoMetadata, _T("&Metadata...\tCtrl+M"), 
                 _T("View the selected photo's metadata (exif)"));
    menu->Append(ID_PhotoDelete, _T("&Delete\tCtrl+D"),
                 _T("Delete the selected photo"));
    menu->AppendSeparator();
    menu->Append(ID_PhotoSlideShow, _T("&Slide show...\tCtrl+S"),
                 _T("Start a slide show"));
    menuBar->Append(menu, _T("&Photo"));

    // Help menu
    menu = new wxMenu();
    menu->Append(ID_HelpAbout, _T("&About...\tF1"),
                 _T("About this application"));
    menuBar->Append(menu, _T("&Help"));

    SetMenuBar(menuBar);
}

#if 0
#define TOOL(icon, id, text, help) { \
            wxBitmap bitmap(icon); \
            toolBar->AddTool(id, _T(text), bitmap, wxNullBitmap, \
                             wxITEM_NORMAL, _T(help), _T(help)); \
        }
#endif

#define TOOL(icon, id, text, help) { \
            wxString iconFile = Config::GetDataPath(); \
            iconFile << _T("icons") << wxFILE_SEP_PATH << _T(icon); \
            wxBitmap bitmap = wxImage(iconFile); \
            toolBar->AddTool(id, _T(text), bitmap, wxNullBitmap, \
                             wxITEM_NORMAL, _T(help), _T(help)); \
        }


void Frame::InitToolBar()
{
    wxToolBar *toolBar = new wxToolBar(this, wxID_ANY, 
                                       wxDefaultPosition, wxDefaultSize, 
                                       wxTB_FLAT | wxTB_HORIZONTAL);
    toolBar->SetMargins(0, 0);

    TOOL("import.png", ID_FileImport, "Import", 
         "Import photos into database")
    TOOL("export.png", ID_FileExport, "Export", 
         "Export photos from the database")
    toolBar->AddSeparator();
    TOOL("edit.png", ID_PhotoEdit, "Edit", 
         "Edit selected photo")
    TOOL("adjust.png", ID_PhotoEdit, "Adjust", 
         "Adjust selected photo") // TODO
    TOOL("view.png", ID_PhotoEdit, "View", 
         "View selected photo") // TODO
    TOOL("delete.png", ID_PhotoDelete, "Delete", 
         "Delete selected photo")
    TOOL("slideshow.png", ID_PhotoSlideShow, "Slide Show", 
         "Start a slide show")
    toolBar->AddSeparator();
    TOOL("prefs.png", ID_EditPreferences, "Setup", 
         "Edit application preferences")
    TOOL("help.png", ID_HelpAbout, "About", 
         "About this application")

    SetToolBar(toolBar);
}

void Frame::OnFileOpen(wxCommandEvent&)
{
    wxDirDialog *dlg = new wxDirDialog(this, _T("Open Photo Directory"),
                                       Config::GetBasePath());

    if (dlg->ShowModal() == wxID_OK) {
        Library::Get()->Load(dlg->GetPath());
        GetCurrentPage()->RefreshList();
    }
}

void Frame::OnFileImport(wxCommandEvent&)
{
    ImportDialog *dlg = new ImportDialog(this);
    if (dlg->ShowModal() == wxID_OK) {
        GetCurrentPage()->RefreshList();
    }
}

void Frame::OnFileExport(wxCommandEvent&)
{
    ExportDialog *dlg = new ExportDialog(this);
    dlg->ShowModal();
}

void Frame::OnFileExit(wxCommandEvent&)
{
    Config::SetPosX(GetRect().GetX());
    Config::SetPosY(GetRect().GetY());
    Config::SetSizeX(GetRect().GetWidth());
    Config::SetSizeY(GetRect().GetHeight());

    Close();
}

void Frame::OnEditCameras(wxCommandEvent&)
{
    CameraListDialog *dlg = new CameraListDialog(this);
    dlg->ShowModal();
}

void Frame::OnEditLocations(wxCommandEvent&)
{
    LocationListDialog *dlg = new LocationListDialog(this);
    dlg->ShowModal();
}

void Frame::OnEditAlbums(wxCommandEvent&)
{
    AlbumListDialog *dlg = new AlbumListDialog(this);
    dlg->ShowModal();
}

void Frame::OnEditPreferences(wxCommandEvent&)
{
    SetupDialog *dlg = new SetupDialog(this);
    if (dlg->ShowModal() == wxID_OK) {
        GetCurrentPage()->RefreshList();
    }
}

void Frame::OnPhotoEdit(wxCommandEvent&)
{
    Photo photo = GetCurrentPage()->GetSelectedPhoto();

    if (photo.Ok()) {
        PhotoDialog *dlg = new PhotoDialog(this, photo);
        if (dlg->ShowModal() == wxID_OK)
            GetCurrentPage()->RefreshList();
    } 
    else {
        Notify::Info(this, _T("Select an item to edit"));
    }
}

void Frame::OnPhotoMetadata(wxCommandEvent&)
{
    Photo photo = GetCurrentPage()->GetSelectedPhoto();

    if (photo.Ok()) {
        MetadataDialog *dlg = new MetadataDialog(this, photo);
        dlg->ShowModal();
    } 
    else {
        Notify::Info(this, _T("Select an item to view"));
    }
}

void Frame::OnPhotoDelete(wxCommandEvent&)
{
    Photo photo = GetCurrentPage()->GetSelectedPhoto();

    if (photo.Ok()) {
        wxString msg = _T("Delete ") + photo.GetName() + _T("?");
        if (Notify::Ask(this, msg)) {
            Library::Get()->Delete(photo);
            GetCurrentPage()->RefreshList();
        }
    } 
    else {
        Notify::Info(this, _T("Select an item to delete"));
    }
}

void Frame::OnPhotoSlideShow(wxCommandEvent&)
{
    SlideShowDialog *dlg = new SlideShowDialog(this);
    dlg->ShowModal();
}

void Frame::OnHelpAbout(wxCommandEvent&)
{
    AboutDialog *dlg = new AboutDialog(this);
    dlg->ShowModal();
}

PageBase* Frame::GetCurrentPage()
{
    return (PageBase*)m_book->GetPage(m_book->GetSelection());
}

void Frame::OnPageChanged(wxNotebookEvent& evt)
{
    PageBase *oldPage = (PageBase*)m_book->GetPage(evt.GetOldSelection());
    PageBase *newPage = (PageBase*)m_book->GetPage(evt.GetSelection());

    if (oldPage != NULL && newPage != NULL)
        newPage->SetSelectedPhoto(oldPage->GetSelectedPhoto());
}

