
#ifndef EDITPAGE_H
#define EDITPAGE_H

#include "PageBase.h"

#include <wx/splitter.h>
#include <wx/scrolwin.h>

class EditPanel : public wxScrolledWindow
{
public:
    EditPanel(wxWindow *parent);

private:
};

class EditViewer : public wxScrolledWindow
{
public:
    EditViewer(wxWindow *parent);

private:
};

class EditPage : public PageBase
{
public:
    EditPage(wxNotebook *parent);

private:
    EditPanel *m_edit;
    EditViewer *m_viewer;
};

#endif

