
#include "LibraryView.h"
#include "Library.h"

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(LibraryViewArray);

LibraryView::LibraryView()
{
    Library::Get()->AddView(this);
}

LibraryView::~LibraryView()
{
    Library::Get()->RemoveView(this);
}

