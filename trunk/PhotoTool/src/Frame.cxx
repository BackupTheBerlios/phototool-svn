
#include "Frame.h"

#include "Location.h"
#include "Camera.h"
#include "Album.h"
#include "Notify.h"
#include "Config.h"

#include "AboutDialog.h"
#include "ImportDialog.h"
#include "PhotoDialog.h"
#include "SetupDialog.h"
#include "SlideShowDialog.h"

#include "TestPage.h" // TODO
#include "EditPage.h"
#include "LookupPage.h"
#include "ViewerPage.h"

#include <wx/xrc/xmlres.h>

#define LIST_PATH   0
#define VIEWER_PAGE 1

BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(XRCID("FileOpen"), Frame::OnFileOpen)
    EVT_MENU(XRCID("FileImport"), Frame::OnFileImport)
    EVT_MENU(XRCID("FileExit"), Frame::OnFileExit)

    EVT_MENU(XRCID("EditCameras"), Frame::OnEditCameras)
    EVT_MENU(XRCID("EditLocations"), Frame::OnEditLocations)
    EVT_MENU(XRCID("EditAlbums"), Frame::OnEditAlbums)
    EVT_MENU(XRCID("EditPreferences"), Frame::OnEditPreferences)

    EVT_MENU(XRCID("PhotoEdit"), Frame::OnPhotoEdit)
    EVT_MENU(XRCID("PhotoDelete"), Frame::OnPhotoDelete)
    EVT_MENU(XRCID("PhotoSlideShow"), Frame::OnPhotoSlideShow)

    EVT_MENU(XRCID("HelpAbout"), Frame::OnHelpAbout)

    EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, Frame::OnPageChanged)
END_EVENT_TABLE()

#define TOOL(icon, id, text, help) { \
        wxBitmap bitmap(_T("icons/") _T(icon) _T(".png")); \
        toolBar->AddTool(XRCID(id), _T(text), bitmap, wxNullBitmap, \
                         wxITEM_NORMAL, _T(help), _T(help)); \
        }

Frame::Frame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    // Set default position and size
    SetSize(Config::GetPosX(), Config::GetPosY(), 
            Config::GetSizeX(), Config::GetSizeY());

    // Initialize the menu bar
    SetMenuBar(wxXmlResource::Get()->LoadMenuBar(_T("MainMenu")));

    // Initialize the toolbar
    wxToolBar *toolBar = new wxToolBar(this, wxID_ANY, 
                                       wxDefaultPosition, wxDefaultSize, 
                                       /*wxTB_TEXT | */wxTB_FLAT);
    toolBar->SetMargins(3, 3);

    TOOL("import", "FileImport", "Import", "Import photos into database")
    toolBar->AddSeparator();
    TOOL("edit", "PhotoEdit", "Edit", "Edit selected photo")
    TOOL("delete", "PhotoDelete", "Delete", "Delete selected photo")
    TOOL("insert-image", "PhotoSlideShow", "Slide Show", "Start a slide show")
    toolBar->AddSeparator();
    TOOL("preferences", "EditPreferences", "Setup", 
         "Edit application preferences")
    TOOL("about", "HelpAbout", "About", "About this application")
    toolBar->AddSeparator();
    TOOL("exit", "FileExit", "Exit", "Exit this application")

    SetToolBar(toolBar);

    // Initialize the notebook display
#if defined(__WXMSW__)
    m_book = new wxNotebook(this); 
#else
    m_book = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                            wxNB_BOTTOM);
#endif

    m_book->AddPage(new LookupPage(m_book), _T("       Photos       "));
    m_book->AddPage(new ViewerPage(m_book), _T("        View        "));
    m_book->AddPage(new EditPage(m_book),   _T("        Edit        "));
    m_book->AddPage(new TestPage(m_book),   _T("        Test        "));

    CreateStatusBar(1);
    SetStatusText(_T("Welcome to ") + title, 0);
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
    } else {
        Notify::Info(this, _T("Select an item to edit"));
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
    } else {
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
