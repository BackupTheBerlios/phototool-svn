
#ifndef VIEWERPANEL_H
#define VIEWERPANEL_H

#include "Record.h"

#include <wx/wx.h>

class ViewerPanel : public wxScrolledWindow
{
public:
    ViewerPanel(wxWindow *parent);

    ACCESSOR(Position, m_position, wxPoint)

    void SetPhoto(const Photo& photo);
    void SetPhoto(const wxBitmap& bitmap);

    void OnDraw(wxDC& dc);

    void OnLeftDown(wxMouseEvent& evt);
    void OnLeftUp(wxMouseEvent&);
    void OnMotion(wxMouseEvent& evt);

private:
    wxBitmap m_bitmap;
    wxPoint m_position;
    
    wxPoint m_mouse;

    DECLARE_EVENT_TABLE()
};

#endif

