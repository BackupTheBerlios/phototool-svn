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
#include "PhotoEditPlugin.h"
#include "Notify.h"

#include <wx/dir.h>

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
    // Clean-up loaded plugins
    for(size_t i = 0; i < m_plugins.Count(); i++) {
        m_plugins[i]->Unload();
        delete m_plugins[i];
        m_plugins[i] = NULL;
    }
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
        wxString msg;
        msg << _T("Could not open plugin directory: ") << path;
        Notify::Error(NULL, msg);

        return false;
    }

    wxDynamicLibrary lib;
    PluginTypeFunc plugin_type;
    PluginBase *plugin;

    for(size_t i = 0; i < pluginNames.Count(); i++) {
        if (!lib.Load(pluginNames[i])) continue;

        plugin_type = (PluginTypeFunc)lib.GetSymbol(_T("plugin_type"));
        if (plugin_type == NULL) {
            wxPrintf(_T("Could not load plugin: %s (plugin_type was")
                     _T("not defined)\n"), pluginNames[i].c_str());
            continue;
        } 

        int type = plugin_type();

        if (type &  PHOTOTOOL_EDIT) {
            plugin = new PhotoEditPlugin(pluginNames[i]);
        } else if (type & PHOTOTOOL_SORT) {
            // TODO
            continue;
        } else if (type & PHOTOTOOL_VIEW) {
            // TODO
            continue;
        } else if (type & PHOTOTOOL_EXPORT) {
            // TODO
            continue;
        } else {
            wxPrintf(_T("Unkown plugin type (%d): %s\n"), 
                     type, pluginNames[i].c_str());
            continue;
        }

        m_plugins.Add(plugin);
    }

    return true;
}

