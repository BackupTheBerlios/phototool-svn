
#ifndef VIEWERPAGE_H
#define VIEWERPAGE_H

#include "PageBase.h"
#include "Record.h"

class ViewerPanel;

class ViewerPage : public PageBase
{
public:
    ViewerPage(wxNotebook *parent);

    Photo GetSelectedPhoto() { return m_photo; }
    void SetSelectedPhoto(const Photo& photo);

private:
    ViewerPanel *m_viewer;

    Photo m_photo;
};

#endif

