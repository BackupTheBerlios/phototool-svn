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

#ifndef SQL_H
#define SQL_H

#define CREATE_PHOTOS ( \
    _T("CREATE TABLE photos (                         ") \
    _T("    photo_id INTEGER PRIMARY KEY NOT NULL,    ") \
    _T("                                              ") \
    _T("    filename VARCHAR NOT NULL,                ") \
    _T("                                              ") \
    _T("    name VARCHAR,                             ") \
    _T("    description VARCHAR,                      ") \
    _T("    taken TIMESTAMP,                          ") \
    _T("                                              ") \
    _T("    location INTEGER NOT NULL,                ") \
    _T("    camera INTEGER NOT NULL                   ") \
    _T(");                                            "))

#define CREATE_CAMERAS ( \
    _T("CREATE TABLE cameras (                        ") \
    _T("    camera_id INTEGER PRIMARY KEY NOT NULL,   ") \
    _T("                                              ") \
    _T("    model VARCHAR,                            ") \
    _T("    manufacturer VARCHAR,                     ") \
    _T("                                              ") \
    _T("    megapixels DECIMAL,                       ") \
    _T("    zoom DECIMAL                              ") \
    _T(");                                            "))

#define CREATE_ALBUMS ( \
    _T("CREATE TABLE albums (                         ") \
    _T("    album_id INTEGER PRIMARY KEY NOT NULL,    ") \
    _T("                                              ") \
    _T("    name VARCHAR NOT NULL UNIQUE,             ") \
    _T("    description VARCHAR                       ") \
    _T(");                                            "))

#define CREATE_PHOTO_ALBUMS ( \
    _T("CREATE TABLE photo_albums (                          ") \
    _T("    photo_album_id INTEGER PRIMARY KEY NOT NULL,     ") \
    _T("                                                     ") \
    _T("    album INTEGER NOT NULL,                          ") \
    _T("    photo INTEGER NOT NULL,                          ") \
    _T("    position INTEGER NOT NULL,                       ") \
    _T("                                                     ") \
    _T("    UNIQUE(album, photo)                             ") \
    _T(");                                                   "))

#define CREATE_LOCATIONS ( \
    _T("CREATE TABLE locations (                       ") \
    _T("    location_id INTEGER PRIMARY KEY NOT NULL, ") \
    _T("                                              ") \
    _T("    name VARCHAR NOT NULL UNIQUE,             ") \
    _T("    description VARCHAR                       ") \
    _T(");                                            "))

#define CREATE_ALTERATIONS ( \
    _T("CREATE TABLE filters (                          ") \
    _T("    filter_id INTEGER PRIMARY KEY NOT NULL,     ") \
    _T("                                                ") \
    _T("    photo INTEGER NOT NULL,                     ") \
    _T("    name VARCHAR NOT NULL,                      ") \
    _T("    value VARCHAR                               ") \
    _T("    sequence INTEGER NOT NULL,                  ") \
    _T("                                                ") \
    _T("    UNIQUE(name, photo, sequence)               ") \
    _T(");                                              "))

#endif

