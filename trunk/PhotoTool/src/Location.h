
#ifndef LOCATION_H
#define LOCATION_H

#include "ListDialog.h"

class LocationListDialog : public ListDialog
{
public:
    LocationListDialog(wxWindow *parent);

    bool TransferDataToWindow();

protected:
    bool DoAdd();
    bool DoEdit(const wxString& item);
    bool DoRemove(const wxString& item);
};

#include "EditDialog.h"
#include "Library.h"

class LocationDialog : public EditDialog
{
public:
    LocationDialog(wxWindow *parent, const wxString& name = _T(""));

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

private:
    Location m_location;
};

class LocationLookup : public wxChoice
{
public:
    LocationLookup(wxWindow *parent = NULL, wxWindowID id = wxID_ANY,
                   const wxPoint &pos = wxDefaultPosition,
                   const wxSize &size = wxDefaultSize, long style = 0,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString &name = wxT("locationLookup"));
    ~LocationLookup() { }

    void PopulateLookup();

    void OnCreate(wxWindowCreateEvent&);
    void OnSelect(wxCommandEvent&);

private:
    DECLARE_DYNAMIC_CLASS(LocationLookup)
    DECLARE_EVENT_TABLE()
};

#endif

