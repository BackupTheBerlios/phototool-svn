
#ifndef VIEWERFRAME_H
#define VIEWERFRAME_H

#include "Record.h"

#include <wx/wx.h>
#include <wx/timer.h>

class ViewerPanel;

class SlideShowFrame : public wxFrame
{
public:
    SlideShowFrame(wxWindow *parent);

    void StartSlideShow(const PhotoArray& photos, int transitionTime = 10);

    void NextPhoto() { m_idx++; UpdatePhoto(); }
    void PreviousPhoto() { m_idx--; UpdatePhoto(); }
    void UpdatePhoto();

    void OnTimer(wxTimerEvent&);
    void OnKeyUp(wxKeyEvent& evt);

private:
    PhotoArray m_photos;
    int m_idx;

    int m_transitionTime;
    wxTimer m_timer;

    ViewerPanel *m_viewer;

    DECLARE_EVENT_TABLE()
};

#endif

