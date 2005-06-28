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

#ifndef UTIL_H
#define UTIL_H

// Creates an accessor for a class property (GetVar, SetVar)
#define ACCESSOR(name, var, type) \
    type Get##name() const { return var; } \
    void Set##name(const type& val) { var = val; }

// Format for importing and exporting dates
#define DATE_FORMAT _T("%B %d, %Y %T")

// List of image extensions
#define IMAGE_FILES _T("*.jpg;*.bmp;*.png;*.gif")

// Image wildcard for wxFileDialog
#define IMAGE_WILDCARD ( \
    _T("Image Files|") IMAGE_FILES _T("|") \
    _T("All Files|*.*"))

#define THUMB_WIDTH 133
#define THUMB_HEIGHT 100

#endif

