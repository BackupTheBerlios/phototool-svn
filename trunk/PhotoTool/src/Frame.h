
#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>

class ViewerPanel;
class PageBase;

class Frame : public wxFrame
{
public:
    Frame(const wxString& title);

    void OnFileOpen(wxCommandEvent&);
    void OnFileImport(wxCommandEvent&);
    void OnFileExit(wxCommandEvent&);

    void OnEditCameras(wxCommandEvent&);
    void OnEditLocations(wxCommandEvent&);
    void OnEditAlbums(wxCommandEvent&);
    void OnEditPreferences(wxCommandEvent&);

    void OnPhotoEdit(wxCommandEvent&);
    void OnPhotoDelete(wxCommandEvent&);
    void OnPhotoSlideShow(wxCommandEvent&);

    void OnHelpAbout(wxCommandEvent&);

    void OnPageChanged(wxNotebookEvent& evt);

private:
    wxNotebook *m_book;

    PageBase* GetCurrentPage();

    DECLARE_EVENT_TABLE()
};

#endif

