
#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <wx/wx.h>

class ListDialog : public wxDialog
{
public:
    ListDialog(wxWindow *parent, const wxString& title);

    void OnAction(wxCommandEvent&);
    void OnClose(wxCommandEvent&);

    void SetItems(wxArrayString& items);

protected:
    virtual bool DoAdd() = 0;
    virtual bool DoEdit(const wxString& item) = 0;
    virtual bool DoRemove(const wxString& item) = 0;

private:
    DECLARE_EVENT_TABLE()

    wxListBox *m_list;
};

#endif

