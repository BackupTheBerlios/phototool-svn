
#include "PhotoList.h"
#include "PhotoDialog.h"
#include "PhotoDropTarget.h"
#include "Notify.h"
#include "Util.h"

#include <wx/xrc/xmlres.h>
#include <wx/dnd.h>

BEGIN_EVENT_TABLE(PhotoList, wxHtmlListBox)
    EVT_MOTION(PhotoList::OnDragDrop)

    EVT_LISTBOX_DCLICK(wxID_ANY, PhotoList::OnEdit)

    EVT_RIGHT_DOWN(PhotoList::OnPopup)
END_EVENT_TABLE()

PhotoList::PhotoList(wxWindow *parent)
    : wxHtmlListBox(parent)
{
    SetItemCount(0);
}

wxString PhotoList::OnGetItem(unsigned int n) const
{
    if (n >= m_photoList.Count())
        return wxString(_T("<b>Not found</b>"));

    Photo photo = m_photoList[n];

    wxString html;
    html << _T("<table border=0 width=\"100%\">") _T("<tr>");

    // Thumbnail
    wxString thumbPath = photo.GetThumbPath();
    thumbPath.Replace(_T(":"), _T("%3A"));
    html << _T("<td rowspan=2 width=140>") 
         << _T("<img src=\"") << thumbPath << _T("\" />")
         << _T("</td>");
         
    // Name
    html << _T("<td valign=\"top\">")  
         << _T("<b>") << photo.GetName() << _T("</b>") 
         << _T("</td>");
         
    // Date taken
    html << _T("<td valign=\"top\" align=\"right\">") 
         <<  _T("<b>") << photo.GetTaken().Format(DATE_FORMAT) << _T("</b>") 
         << _T("</td>");
         
    html << _T("</tr>") _T("<tr>");

    // Description
    wxString description = photo.GetDescription();
    description.Replace(_T("\n"), _T("<br />"));
    html << _T("<td colspan=2 valign=\"top\">")
         << description
         << _T("</td>");

    html << _T("</tr>") _T("</table>");

    return html;
}

void PhotoList::OnEdit(wxCommandEvent&)
{
    size_t id = GetSelection();
    if (id < m_photoList.Count()) {
        PhotoDialog *dlg = new PhotoDialog(this, m_photoList[id]);
        if (dlg->ShowModal() == wxID_OK) {
            m_photoList[id] = dlg->GetPhoto();
            Refresh();
        }
    } else {
        Notify::Info(this, _T("Select an item to edit"));
    }
}

void PhotoList::SetList(const PhotoArray& list)
{
    m_photoList = list;
    SetItemCount(m_photoList.Count());
    Refresh();
}

Photo PhotoList::GetPhoto()
{
    size_t id = GetSelection();
    if (id < m_photoList.Count()) {
        return m_photoList[id];
    }

    return Photo();
}

void PhotoList::OnPopup(wxMouseEvent&)
{
    POPUP_MENU("PopupMenu", "Photo");
}

void PhotoList::OnDragDrop(wxMouseEvent& evt)
{
    Photo photo = GetPhoto();

    if (evt.LeftIsDown() && photo.Ok())
        PhotoDropTarget::DoDragDrop(this, photo);

    evt.Skip();
}
