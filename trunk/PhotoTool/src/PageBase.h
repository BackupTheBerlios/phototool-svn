
#ifndef PAGEBASE_H
#define PAGEBASE_H

#include "Record.h"

#include <wx/wx.h>
#include <wx/notebook.h>

class PageBase : public wxPanel
{
public:
    PageBase(wxNotebook *parent);

    virtual void RefreshList() { }

    virtual Photo GetSelectedPhoto() { return Photo(); }
    virtual void SetSelectedPhoto(const Photo&) { }

private:
    DECLARE_EVENT_TABLE()
};

#endif

