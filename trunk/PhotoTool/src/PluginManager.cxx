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
#include "Notify.h"

#include <wx/dir.h>
#include <wx/dynload.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(PluginArray);

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
    // Cleanup
    while(m_plugins.Count() > 0) {
        PluginBase **plugin = m_plugins.Detach(0);
        delete *plugin;
    }
}

bool PluginManager::LoadPlugins(const wxString& path)
{
    wxArrayString pluginNames;
    int rc = -1;

    // Plugin extension is platform specific
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

    for(size_t i = 0; i < pluginNames.Count(); i++) {
        // Load the plugin
        wxPluginLibrary *lib = wxPluginManager::LoadLibrary(pluginNames[i]);

        if (lib->IsLoaded()) {
            // Get pointer to the plugin load function
            PluginLoadFunc plugin_load = 
                (PluginLoadFunc)lib->GetSymbol(_T("plugin_load"));

            if (plugin_load != NULL) {
                // Load the plugin instance
                PluginBase *plugin = plugin_load(); 
                m_plugins.Add(plugin);
            } else {
                // plugin_load was not defined (invalid plugin?)
                wxPrintf(_T("Could not load plugin: %s\n"), 
                         pluginNames[i].c_str());
            }
        }
    }

    return true;
}

