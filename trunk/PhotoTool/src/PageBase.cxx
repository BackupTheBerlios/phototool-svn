
#include "PageBase.h"

BEGIN_EVENT_TABLE(PageBase, wxPanel)
END_EVENT_TABLE()

PageBase::PageBase(wxNotebook *parent)
    : wxPanel(parent)
{
}

