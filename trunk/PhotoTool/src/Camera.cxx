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

#include "Camera.h"
#include "Notify.h"

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
    : InputDialog(parent, _T("Edit Camera"))
{
    m_manufacturer = new wxComboBox(this, -1, wxEmptyString,
                                    wxDefaultPosition, wxSize(200, -1));
    m_model = new wxTextCtrl(this, -1);
    m_megapixels = new wxTextCtrl(this, -1, wxEmptyString, 
                                  wxDefaultPosition, wxSize(40, -1));
    m_zoom = new wxTextCtrl(this, -1, wxEmptyString, 
                            wxDefaultPosition, wxSize(40, -1));

    m_default = new wxCheckBox(this, -1, _T("Make default camera"));

    // Camera information
    wxFlexGridSizer *fsizer = new wxFlexGridSizer(2, 10, 10);
    fsizer->AddGrowableCol(1);
    fsizer->Add(new wxStaticText(this, -1, _T("Manufacturer:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_manufacturer);
    fsizer->Add(new wxStaticText(this, -1, _T("Model:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_model, 0, wxEXPAND);
    fsizer->Add(new wxStaticText(this, -1, _T("MegaPixels:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_megapixels);
    fsizer->Add(new wxStaticText(this, -1, _T("Zoom:")),
                0, wxALIGN_CENTER_VERTICAL);
    fsizer->Add(m_zoom);
    fsizer->Add(10, 10);
    fsizer->Add(m_default);

    wxStaticBox *sbox = new wxStaticBox(this, -1, _T("Camera Information"));
    wxStaticBoxSizer *ssizer = new wxStaticBoxSizer(sbox, wxVERTICAL);
    ssizer->Add(fsizer, 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ssizer, 0, wxEXPAND|wxALL, 5);
    SetSizer(sizer);
    Fit();

    if (name.Length() != 0) {
        m_camera = Library::Get()->GetCamera(name);
        TransferDataToWindow();
    }
}

bool CameraDialog::TransferDataFromWindow()
{
    if (m_manufacturer->GetValue().Length() == 0 ||
        m_model->GetValue().Length() == 0) {
        Notify::Info(this, _T("Enter a model and manufacturer for ") 
                     _T("this camera"));
        return false;
    }

    m_camera.SetManufacturer(m_manufacturer->GetValue());
    m_camera.SetModel(m_model->GetValue());

    double conv = 0;
    m_megapixels->GetValue().ToDouble(&conv);
    m_camera.SetMegaPixels(conv);

    conv = 0;
    m_zoom->GetValue().ToDouble(&conv);
    m_camera.SetZoom(conv);

    return Library::Get()->Update(m_camera);
}

bool CameraDialog::TransferDataToWindow()
{
    m_manufacturer->SetValue(m_camera.GetManufacturer());
    m_model->SetValue(m_camera.GetModel());

    wxString conv;
    conv << m_camera.GetMegaPixels();
    m_megapixels->SetValue(conv);

    conv.Clear();
    conv << m_camera.GetZoom();
    m_zoom->SetValue(conv);

    return true;
}

#define EDIT_CAMERAS _T("Edit cameras...")

IMPLEMENT_DYNAMIC_CLASS(CameraLookup, wxChoice)

BEGIN_EVENT_TABLE(CameraLookup, wxChoice)
    EVT_CHOICE(wxID_ANY, CameraLookup::OnSelect)
END_EVENT_TABLE()

CameraLookup::CameraLookup(wxWindow *parent, wxWindowID id, 
                           const wxPoint &pos, const wxSize &size, long style,
                           const wxValidator& validator, const wxString &name)
    : wxChoice(parent, id, pos, size, wxArrayString(), style, validator, name)
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

