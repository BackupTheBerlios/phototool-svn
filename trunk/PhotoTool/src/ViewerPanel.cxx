
#include "ViewerPanel.h"

BEGIN_EVENT_TABLE(ViewerPanel, wxScrolledWindow)
    EVT_LEFT_DOWN(ViewerPanel::OnLeftDown)
    EVT_LEFT_UP(ViewerPanel::OnLeftUp)
    EVT_MOTION(ViewerPanel::OnMotion)
END_EVENT_TABLE()

ViewerPanel::ViewerPanel(wxWindow *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxBLACK);
    SetForegroundColour(*wxBLACK);

    SetCursor(wxCURSOR_CROSS);

    SetScrollbars(1, 1, 1, 1);
}

void ViewerPanel::SetPhoto(const Photo& photo)
{
    if (photo.Ok()) {
        m_bitmap = wxImage(photo.GetFileName());

        SetScrollbars(1, 1, m_bitmap.GetWidth(), m_bitmap.GetHeight());
    } else {
        m_bitmap = wxBitmap();
    }

    Refresh();
}

void ViewerPanel::SetPhoto(const wxBitmap& bitmap)
{
    m_bitmap = bitmap;

    SetScrollbars(1, 1, m_bitmap.GetWidth(), m_bitmap.GetHeight());
    Refresh();
}

void ViewerPanel::OnDraw(wxDC& dc)
{
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();

    if (m_bitmap.Ok())
        dc.DrawBitmap(m_bitmap, m_position.x, m_position.y, true);
}

void ViewerPanel::OnLeftDown(wxMouseEvent& evt)
{
    if (!HasCapture()) {
        CaptureMouse();
        m_mouse = evt.GetPosition();
    }
}

void ViewerPanel::OnLeftUp(wxMouseEvent&)
{
    if (HasCapture())
        ReleaseMouse();
}

void ViewerPanel::OnMotion(wxMouseEvent& evt)
{
    if (HasCapture()) {
        wxPoint mouse = evt.GetPosition();

        // Adjust scroll position
        int x, y;
        GetViewStart(&x, &y);
        Scroll(x + (m_mouse.x - mouse.x), y + (m_mouse.y - mouse.y));

        m_mouse = mouse;
    }
}

