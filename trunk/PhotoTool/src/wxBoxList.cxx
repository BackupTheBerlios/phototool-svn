
#include "wxBoxList.h"

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxBoxListItemArray);

BEGIN_EVENT_TABLE(wxBoxListItem, wxPanel)
    EVT_LEFT_UP(wxBoxListItem::OnLeftUp)
    EVT_LEFT_DCLICK(wxBoxListItem::OnLeftDClick)
END_EVENT_TABLE()

wxBoxListItem::wxBoxListItem(wxWindow *parent, wxWindowID id, 
                             const wxPoint& pos, const wxSize& size, 
                             const wxString& name)
    : wxPanel(parent, id, pos, size, 0, name)
{
    Select(false);
}

void wxBoxListItem::Select(bool select)
{
    // TODO: Have option to set this colour
    if (select)
        SetBackgroundColour(*wxBLUE);
    else 
        SetBackgroundColour(*wxWHITE);
}

void wxBoxListItem::OnLeftUp(wxMouseEvent&)
{
    wxBoxList *list = (wxBoxList*)GetParent();
    list->Select(list->GetIndex(this));

    wxCommandEvent evt(wxEVT_COMMAND_LISTBOX_SELECTED, GetId());
    evt.SetEventObject(this);
    GetEventHandler()->ProcessEvent(evt);
}

void wxBoxListItem::OnLeftDClick(wxMouseEvent&)
{
    wxCommandEvent evt(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, GetId());
    evt.SetEventObject(this);
    GetEventHandler()->ProcessEvent(evt);
}

void wxBoxListItem::AddChild(wxWindowBase *child)
{
    // Capture events sent to children
    child->SetEventHandler(this);

    wxPanel::AddChild(child);
}

BEGIN_EVENT_TABLE(wxBoxList, wxScrolledWindow)
    EVT_SIZE(wxBoxList::OnSize)
END_EVENT_TABLE()

wxBoxList::wxBoxList(wxWindow *parent, wxWindowID id, const wxPoint& pos, 
                     const wxSize& size, const wxString& name)
    : wxScrolledWindow(parent, id, pos, size, wxVSCROLL, name),
      m_boxSize(100, 100), m_boxMargins(3), m_selection(-1)
{
    SetBackgroundColour(*wxWHITE);
    SetScrollbars(1, 1, 1, 1);
}

void wxBoxList::Add(wxBoxListItem *item)
{
    m_items.Add(item);
    LayoutBoxItems();
}

wxBoxListItem *wxBoxList::Get(int n)
{
    if ((size_t)n < m_items.Count() && n != -1)
        return m_items[n];
    return NULL;
}

bool wxBoxList::Remove(wxBoxListItem *item)
{
    int n = GetIndex(item);
    if (n != -1) {
        RemoveAt(n);

        // Update layout
        LayoutBoxItems();
        return true;
    }

    return false;
}

bool wxBoxList::RemoveAt(int n)
{
    if ((size_t)n < m_items.Count()) {
        m_items[n]->Hide();
        m_items[n]->Destroy();
        m_items.RemoveAt(n);

        // Update layout
        LayoutBoxItems();
        return true;
    }

    return false;
}

void wxBoxList::Clear()
{
    for(size_t i = 0; i < m_items.Count(); i++) {
        m_items[i]->Hide();
        m_items[i]->Destroy();
    }
    m_items.Clear();
}

void wxBoxList::Select(int n, bool select)
{
    if ((size_t)n < m_items.Count() && n != -1) {
        // Deselect the previous item
        if ((size_t)m_selection < m_items.Count() && 
            m_selection != -1 && select)

            m_items[m_selection]->Select(false);

        m_selection = n;
        m_items[n]->Select(select);
    }
}

void wxBoxList::LayoutBoxItems()
{
    // Reset view
    SetScrollbars(1, 1, 1, 1);
  
    // Size required by each box
    int box_width = m_boxSize.GetWidth() + m_boxMargins, 
        box_height = m_boxSize.GetHeight() + m_boxMargins;

    // Window size
    int width, height;
    GetClientSize(&width, &height);
    if (width < box_width) width = box_width;

    // Position box items 
    for(size_t i = 0; i < m_items.Count(); i++) {
        int col = i % (width / box_width);
        int row = i / (width / box_width);

        m_items[i]->Move(col * box_width, row * box_height);
    }

    // Set the scroll bars
    int x = ((m_items.Count() % (width / box_width)) + 1) * box_width;
    int y = ((m_items.Count() / (width / box_width)) + 1) * box_height;

    SetVirtualSize(x, y);
    SetScrollRate(box_width, box_height);
}

void wxBoxList::OnSize(wxSizeEvent& evt) 
{ 
    LayoutBoxItems(); 
    evt.Skip();
}

int wxBoxList::GetIndex(wxBoxListItem *item)
{
    for(size_t i = 0; i < m_items.Count(); i++)
        if (m_items[i] == item)
            return (int)i;

    return -1;
}

