
#ifndef ALBUM_H
#define ALBUM_H

#include "ListDialog.h"

class AlbumListDialog : public ListDialog
{
public:
    AlbumListDialog(wxWindow *parent);

    bool TransferDataToWindow();

protected:
    bool DoAdd();
    bool DoEdit(const wxString& item);
    bool DoRemove(const wxString& item);
};

#include "EditDialog.h"
#include "Library.h"

class AlbumDialog : public EditDialog
{
public:
    AlbumDialog(wxWindow *parent, const wxString& name = _T(""));

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

private:
    Album m_album;
};

class AlbumList : public wxListBox
{
public:
    AlbumList(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator& validator = wxDefaultValidator,
                 const wxString &name = wxT("albumList"));
    ~AlbumList() { }

    void PopulateList();

    void GetSelections(wxArrayString &selection);
    void SetSelections(const wxArrayString &selection);

    void OnCreate(wxWindowCreateEvent&);

private:
    DECLARE_DYNAMIC_CLASS(AlbumList)
    DECLARE_EVENT_TABLE()
};

#endif

