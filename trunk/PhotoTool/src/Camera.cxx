
#include "Camera.h"
#include "Notify.h"

#include <wx/xrc/xmlres.h>

CameraListDialog::CameraListDialog(wxWindow *parent)
    : ListDialog(parent, _T("Cameras"))
{
}

bool CameraListDialog::TransferDataToWindow()
{
    wxArrayString items;
    Library::Get()->LookupCameras(items);
    SetItems(items);

    return true;
}

bool CameraListDialog::DoAdd()
{
    CameraDialog *dlg = new CameraDialog(this);
    return dlg->ShowModal() == wxID_OK;
}

bool CameraListDialog::DoEdit(const wxString& item)
{
    CameraDialog *dlg = new CameraDialog(this, item);
    return dlg->ShowModal() == wxID_OK;
}

bool CameraListDialog::DoRemove(const wxString& item)
{
    Camera camera = Library::Get()->GetCamera(item);
    return Library::Get()->Delete(camera);
}


CameraDialog::CameraDialog(wxWindow *parent, const wxString& name)
    : InputDialog(parent, _T("CameraPanel"), _T("Edit Camera"))
{
    if (name.Length() != 0) {
        m_camera = Library::Get()->GetCamera(name);
        TransferDataToWindow();
    }
}

bool CameraDialog::TransferDataFromWindow()
{
    if (CTRL("Manufacturer", wxComboBox)->GetValue().Length() == 0 ||
        CTRL("Model", wxTextCtrl)->GetValue().Length() == 0) {
        Notify::Info(this, _T("Enter a model and manufacturer for ") 
                     _T("this camera"));
        return false;
    }

    m_camera.SetManufacturer(CTRL("Manufacturer", wxComboBox)->GetValue());
    m_camera.SetModel(CTRL("Model", wxTextCtrl)->GetValue());

    double conv = 0;
    CTRL("MegaPixels", wxTextCtrl)->GetValue().ToDouble(&conv);
    m_camera.SetMegaPixels(conv);

    conv = 0;
    CTRL("Zoom", wxTextCtrl)->GetValue().ToDouble(&conv);
    m_camera.SetZoom(conv);

    return Library::Get()->Update(m_camera);
}

bool CameraDialog::TransferDataToWindow()
{
    CTRL("Manufacturer", wxComboBox)->SetValue(m_camera.GetManufacturer());
    CTRL("Model", wxTextCtrl)->SetValue(m_camera.GetModel());

    wxString conv;
    conv << m_camera.GetMegaPixels();
    CTRL("MegaPixels", wxTextCtrl)->SetValue(conv);

    conv.Clear();
    conv << m_camera.GetZoom();
    CTRL("Zoom", wxTextCtrl)->SetValue(conv);

    return true;
}

#define EDIT_CAMERAS _T("Edit cameras...")

IMPLEMENT_DYNAMIC_CLASS(CameraLookup, wxChoice)

BEGIN_EVENT_TABLE(CameraLookup, wxChoice)
    EVT_WINDOW_CREATE(CameraLookup::OnCreate)
    EVT_CHOICE(wxID_ANY, CameraLookup::OnSelect)
END_EVENT_TABLE()

CameraLookup::CameraLookup(wxWindow *parent, wxWindowID id, 
                           const wxPoint &pos, const wxSize &size, long style,
                           const wxValidator& validator, const wxString &name)
    : wxChoice(parent, id, pos, size, wxArrayString(), style, validator, name)
{
    PopulateLookup();
}

void CameraLookup::OnCreate(wxWindowCreateEvent&)
{
    PopulateLookup();
}

void CameraLookup::OnSelect(wxCommandEvent&)
{
    wxString location = GetStringSelection();
    if (location.Cmp(EDIT_CAMERAS) == 0) {
        CameraListDialog *dlg = new CameraListDialog(this);
        dlg->ShowModal();

        PopulateLookup();
    }
}

void CameraLookup::PopulateLookup()
{
    // Populate lookup
    wxArrayString items;
    Library::Get()->LookupCameras(items);

    Clear();
    for(size_t i = 0; i < items.Count(); i++) 
        Append(items[i]);

    Append(EDIT_CAMERAS);
}

