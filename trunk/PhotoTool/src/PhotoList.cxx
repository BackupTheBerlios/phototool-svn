/**
 * PhotoTool is an application for organizing and publishing a collection of
 * digital images. 
 *
 * Copyright (C) 2005  Bryan Bulten (bryan@bulten.ca)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PhotoList.h"
#include "PhotoDialog.h"
#include "PhotoDropTarget.h"
#include "Notify.h"
#include "Util.h"

#include <wx/dnd.h>

BEGIN_EVENT_TABLE(PhotoList, wxHtmlListBox)
    EVT_MOTION(PhotoList::OnDragDrop)
    EVT_RIGHT_DOWN(PhotoList::OnPopup)
    EVT_LISTBOX_DCLICK(wxID_ANY, PhotoList::OnEdit)
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
    wxString thumbFile = photo.GetThumbFileName();
    thumbFile.Replace(_T(":"), _T("%3A"));
    html << _T("<td rowspan=2 width=140>") 
         << _T("<img src=\"") << thumbFile << _T("\" />")
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
    } 
    else {
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
#define ID_PhotoEdit        300
#define ID_PhotoMetadata    301
#define ID_PhotoDelete      302
#define ID_PhotoSlideShow   304

    wxMenu *menu = new wxMenu();
    menu->Append(ID_PhotoEdit, _T("&Edit..."),
                 _T("Edit the selected photo"));
    menu->Append(ID_PhotoMetadata, _T("&Metadata..."),
                 _T("View the selected photo's metadata (exif)"));
    menu->Append(ID_PhotoDelete, _T("&Delete"),
                 _T("Delete the selected photo"));
    menu->AppendSeparator();
    menu->Append(ID_PhotoSlideShow, _T("&Slide show..."),
                 _T("Start a slide show"));
    PopupMenu(menu);
}

void PhotoList::OnDragDrop(wxMouseEvent& evt)
{
    Photo photo = GetPhoto();

    if (evt.LeftIsDown() && photo.Ok())
        PhotoDropTarget::DoDragDrop(this, photo);

    evt.Skip();
}

