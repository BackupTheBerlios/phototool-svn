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

#include "PluginManager.h"

#include <wx/dir.h>

PluginManager::PluginManager()
{
}

bool PluginManager::LoadPlugins(const wxString& path)
{
    wxArrayString pluginNames;
    int rc = -1;

#if defined(__WXMSW__)
    rc = wxDir::GetAllFiles(path, &pluginNames, _T("*.dll"));
#elif defined(__WXMAC__) || defined(__WXCOCOA__)
    rc = wxDir::GetAllFiles(path, &pluginNames, _T("*.dylib"));
#else
    rc = wxDir::GetAllFiles(path, &pluginNames, _T("*.so"));
#endif

    if (rc < 0) {
        wxPrintf(_T("Could not open plugin directory: %s\n"), path.c_str());
        return false;
    }

    if (pluginNames.Count() == 0) {
        wxPrintf(_T("No plugins found in %s\n"), path.c_str());
        return true;
    }

    wxDynamicLibrary lib;
    PluginTypeFunc plugin_type;

    for(size_t i = 0; i < pluginNames.Count(); i++) {
        wxPrintf(_T("%s: "), pluginNames[i].c_str());

        if (lib.Load(pluginNames[i])) {

            plugin_type = (PluginTypeFunc)lib.GetSymbol(_T("plugin_type"));

            if (plugin_type == NULL) {
                wxPrintf(_T("plugin_type not defined"), 
                         pluginNames[i].c_str());
            } else {
                int type = plugin_type();
                wxChar* typeName;

                if (type &  PHOTOTOOL_EDIT)
                    typeName = _T("edit");
                else if (type & PHOTOTOOL_SORT)
                    typeName = _T("sort");
                else if (type & PHOTOTOOL_VIEW)
                    typeName = _T("view");

                wxPrintf(_T("loaded successfully (%s plugin)"), 
                         typeName, type);
            }

        } else {
            wxPrintf(_T("error loading"));
        }

        wxPrintf(_T("\n"));
    }

    return true;
}

