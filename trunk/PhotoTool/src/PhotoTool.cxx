
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

