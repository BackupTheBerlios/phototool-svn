
#ifndef NOTIFY_H
#define NOTIFY_H

#include <wx/wx.h>

class Notify 
{
public:
    static void Error(wxWindow *parent, const wxString& msg, 
                      const wxString& caption = _T("Error"));
    static void Info(wxWindow *parent, const wxString& msg,
                     const wxString& caption = _T("Information"));
    static bool Ask(wxWindow *parent, const wxString& msg,
                    const wxString& caption = _T("Confirmation"));

private:
    static int Message(wxWindow *parent, const wxString& msg,
                       const wxString& caption, int type);
};

#endif

