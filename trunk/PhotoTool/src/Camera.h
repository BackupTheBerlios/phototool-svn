
#ifndef CAMERA_H
#define CAMERA_H

#include "ListDialog.h"

class CameraListDialog : public ListDialog
{
public:
    CameraListDialog(wxWindow *parent);

    bool TransferDataToWindow();

protected:
    bool DoAdd();
    bool DoEdit(const wxString& item);
    bool DoRemove(const wxString& item);
};

#include "InputDialog.h"
#include "Library.h"

class CameraDialog : public InputDialog
{
public:
    CameraDialog(wxWindow *parent, const wxString& name = _T(""));

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

private:
    Camera m_camera;
};

class CameraLookup : public wxChoice
{
public:
    CameraLookup(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator& validator = wxDefaultValidator,
                 const wxString &name = wxT("cameraLookup"));
    ~CameraLookup() { }

    void PopulateLookup();

    void OnCreate(wxWindowCreateEvent&);
    void OnSelect(wxCommandEvent&);

private:
    DECLARE_DYNAMIC_CLASS(CameraLookup)
    DECLARE_EVENT_TABLE()
};

#endif

