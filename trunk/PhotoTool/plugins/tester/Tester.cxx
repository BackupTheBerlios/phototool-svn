
#include <phototool/PhotoTool.h>

class TesterPlugin : public PhotoEditPlugin
{
public:
    TesterPlugin() { wxPrintf(_T("TesterPlugin()\n")); }
    ~TesterPlugin() { wxPrintf(_T("~TesterPlugin()\n")); }

    wxString GetName() { return _T("Tester Plugin"); }
};

IMPLEMENT_PLUGIN(TesterPlugin)

