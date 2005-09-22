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

#ifndef ALTERATIONS_H
#define ALTERATIONS_H

#include "Record.h"
#include "Image.h"

class Filter
{
public:
    Filter(const wxString &name, const wxString &value) 
        : m_name(name), m_value(value) { }

    ACCESSOR(Name, m_name, wxString)
    ACCESSOR(Value, m_value, wxString)

private:
    wxString m_name, m_value;
};

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(Filter, FiltersBase);

class Filters : public FiltersBase
{
public:
    Filters() : FiltersBase() { }

    ACCESSOR(Photo, m_photo, Photo)

    void Apply(Image &image);
    bool Undo();

private:
    Photo m_photo;
};

#endif
