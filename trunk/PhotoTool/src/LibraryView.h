
#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "Record.h"

class LibraryView
{
public:
    LibraryView();
    virtual ~LibraryView();

    virtual void OnNotify(const Location&) { }
    virtual void OnNotify(const Album&) { }
    virtual void OnNotify(const Photo&) { }
    virtual void OnNotify() { }
};

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(LibraryView*, LibraryViewArray);

#endif

