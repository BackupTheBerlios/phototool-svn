
#ifndef CONFIG_H
#define CONFIG_H

#include <wx/config.h>

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

    static wxString GetDatabasePath() 
    {
        return GetBasePath() + wxFILE_SEP_PATH + _T("db");
    }
};

#endif

