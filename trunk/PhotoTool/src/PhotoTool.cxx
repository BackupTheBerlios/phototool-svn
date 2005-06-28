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

#include "PhotoTool.h"
#include "Frame.h"
#include "Library.h"
#include "Notify.h"
#include "Config.h"
#include "PluginManager.h"
#include "WorkerThread.h"

#include <wx/thread.h>


IMPLEMENT_APP(PhotoTool)

bool PhotoTool::OnInit()
{
    // Information about the application
    SetAppName(_T("PhotoTool"));
    SetVendorName(_T("Bryan Bulten"));

    // Initialize image handlers
    wxInitAllImageHandlers();

    // Check if application is already running
    wxString instName = _T(".") + GetAppName() + _T("-") + wxGetUserId();

    m_instance = new wxSingleInstanceChecker(instName);
    if (m_instance->IsAnotherRunning()) {
        Notify::Error(NULL, _T("PhotoTool is already running."));
        return false;
    }

    // Show the splash screen
    //ShowSplash();

    // Initialize configuration options
    Config::Init();
    Config::GetBasePath();

    // Initialize the default photo library
    Library::Get()->Load(Config::GetBasePath());

    // Load plugins
    PluginManager pm;
    pm.LoadPlugins(_T("../plugins/"));

    // Hide the splash screen
    //HideSplash();

    // Create and show the main frame
    Frame *frame = new Frame(GetAppName());
    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

int PhotoTool::OnExit()
{
    // Allow new instances to run
    delete m_instance;
    m_instance = NULL;

    Config::Close();

    return 0;
}

void PhotoTool::ShowSplash()
{
    wxString splashPath = Config::GetDataPath() + _T("splash.png");

    wxBitmap bmp;
    bmp.LoadFile(splashPath, wxBITMAP_TYPE_PNG);

    // Perminant splash, hide with HideSplash()
    m_splash = new wxSplashScreen(bmp, wxSPLASH_CENTRE_ON_SCREEN, 0, NULL, -1,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxNO_BORDER | wxSTAY_ON_TOP); 
    wxSafeYield();
}

void PhotoTool::HideSplash()
{
    if (m_splash != NULL) {
        m_splash->Close();
        m_splash->Destroy();
        m_splash = NULL;
    }
}

