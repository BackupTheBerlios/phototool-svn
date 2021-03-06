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

#ifndef CONFIG_H
#define CONFIG_H

#include <wx/config.h>

// PhotoTool configuration, generated by configure
#include "config.h"

#define CONFIG(name, key, type, val) \
    static type Get##name(const type& def = val) \
    { \
        type tmp; \
        wxConfig::Get()->Read(key, &tmp, def); \
        return tmp; \
    } \
    static void Set##name(const type& def) \
    { \
        wxConfig::Get()->Write(key, def); \
        wxConfig::Get()->Flush(true); \
    }

class Config
{
public:
    static void Init() 
    { 
        wxConfig::Get()->SetRecordDefaults(true); 
    }

    static void Close() { delete wxConfig::Set(NULL); }

    CONFIG(BasePath, _T("BasePath"), wxString, _T(""))

    // Frame size and position
    CONFIG(PosX, _T("PosX"), int, 100)
    CONFIG(PosY, _T("PosY"), int, 100)
    CONFIG(SizeX, _T("SizeX"), int, 500)
    CONFIG(SizeY, _T("SizeY"), int, 400)

    // Photo defaults
    CONFIG(DefaultCamera, _T("DefaultCamera"), wxString, _T(""))
    CONFIG(DefaultLocation, _T("DefaultLocation"), wxString, _T(""))

    // Tree  page
    CONFIG(SplitPos, _T("SplitPos"), int, 150)

    // Slide show defaults
    CONFIG(TransitionTime, _T("TransitionTime"), int, 10)

    // Default path for browsing for files and directories
    CONFIG(DefaultPath, _T("DefaultPath"), wxString, _T(""))

    // Default export export path
    CONFIG(ExportPath, _T("ExportPath"), wxString, _T(""))

    static wxString GetDatabasePath() 
    {
        return GetBasePath() + wxFILE_SEP_PATH + _T("db");
    }

    static wxString GetDataPath()
    {
        wxString dataPath;
        dataPath << PHOTOTOOL_PREFIX << wxFILE_SEP_PATH << _T("share") 
                 << wxFILE_SEP_PATH << _("phototool") << wxFILE_SEP_PATH;
        return dataPath;
    }
};

#endif

