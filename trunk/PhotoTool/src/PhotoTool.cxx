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

#include <wx/xrc/xmlres.h>

IMPLEMENT_APP(PhotoTool)

bool PhotoTool::OnInit()
{
    // Information about the application
    SetAppName(_T("PhotoTool"));
    SetVendorName(_T("Bryan Bulten"));

    // Initialize configuration options
    Config::Init();
    Config::GetBasePath();

    // Initialize image handlers
    wxInitAllImageHandlers();

    // Initialize XRC
    wxXmlResource *res = wxXmlResource::Get();
    res->InitAllHandlers();
    if (!res->Load(_T("../wxd/PhotoTool_wdr.xrc"))) {
        Notify::Error(NULL, _T("Error loading XRC resources.\nExiting."));
        return false;
    }

    // Initialize the default photo library
    Library::Get()->Load(Config::GetBasePath());

    // Create and show the main frame
    Frame *frame = new Frame(GetAppName());
    frame->Show(true);

    return true;
}

int PhotoTool::OnExit()
{
    Config::Close();
    return 0;
}

