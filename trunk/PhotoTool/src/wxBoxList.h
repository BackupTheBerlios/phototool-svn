
#ifndef _WX_BOXLIST_H_
#define _WX_BOXLIST_H_

#include <wx/wx.h>
#include <wx/scrolwin.h>

#define wxBoxListItemNameStr _T("wxBoxListItem")
#define wxBoxListNameStr _T("wxBoxList")

class wxBoxListItem : public wxPanel
{
public:
    wxBoxListItem(wxWindow *parent, wxWindowID id = wxID_ANY, 
                  const wxPoint& pos = wxDefaultPosition, 
                  const wxSize& size = wxDefaultSize, 
                  const wxString& name = wxBoxListItemNameStr);

    virtual void Select(bool select = true);

    virtual void AddChild(wxWindowBase *child);

private:
    void OnLeftUp(wxMouseEvent&);
    void OnLeftDClick(wxMouseEvent&);

    DECLARE_EVENT_TABLE()
};

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(wxBoxListItem*, wxBoxListItemArray);

class wxBoxList : public wxScrolledWindow
{
public:
    wxBoxList(wxWindow *parent, wxWindowID id = wxID_ANY, 
              const wxPoint& pos = wxDefaultPosition, 
              const wxSize& size = wxDefaultSize, 
              const wxString& name = wxBoxListNameStr);

    // Dimensions of each item in the list
    const wxSize& GetBoxSize() const { return m_boxSize; }
    void SetBoxSize(const wxSize& boxSize) { m_boxSize = boxSize; }

    // Item addition/removal
    void Add(wxBoxListItem *item);
    bool Remove(wxBoxListItem *item);
    bool RemoveAt(int n);
    void Clear();

    wxBoxListItem* Get(int n);
    int GetIndex(wxBoxListItem *item);

    // Selection
    void Select(int n, bool select = true);
    int GetSelection() { return m_selection; }
    bool IsSelected(int n) { return n == m_selection; }

    // Item margins
    void SetBoxMargins(size_t margins) { m_boxMargins = margins; }
    size_t GetBoxMargins() const { return m_boxMargins; }

protected:
    // Positions and resizes items
    virtual void LayoutBoxItems();

    void OnSize(wxSizeEvent& evt);

private:
    wxSize m_boxSize;
    size_t m_boxMargins;

    wxBoxListItemArray m_items;

    int m_selection;

    DECLARE_EVENT_TABLE()
};

#endif

