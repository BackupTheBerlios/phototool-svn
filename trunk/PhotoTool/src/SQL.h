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

#define CREATE_PHOTO ( \
    _T("CREATE TABLE photo (                          ") \
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

#define CREATE_CAMERA ( \
    _T("CREATE TABLE camera (                         ") \
    _T("    camera_id INTEGER PRIMARY KEY NOT NULL,   ") \
    _T("                                              ") \
    _T("    model VARCHAR,                            ") \
    _T("    manufacturer VARCHAR,                     ") \
    _T("                                              ") \
    _T("    megapixels DECIMAL,                       ") \
    _T("    zoom DECIMAL                              ") \
    _T(");                                            "))

#define CREATE_ALBUM ( \
    _T("CREATE TABLE album (                          ") \
    _T("    album_id INTEGER PRIMARY KEY NOT NULL,    ") \
    _T("                                              ") \
    _T("    name VARCHAR NOT NULL UNIQUE,             ") \
    _T("    description VARCHAR                       ") \
    _T(");                                            "))

#define CREATE_PHOTO_ALBUM ( \
    _T("CREATE TABLE photo_album (                           ") \
    _T("    photo_album_id INTEGER PRIMARY KEY NOT NULL,     ") \
    _T("                                                     ") \
    _T("    album INTEGER NOT NULL,                          ") \
    _T("    photo INTEGER NOT NULL,                          ") \
    _T("    position INTEGER NOT NULL,                       ") \
    _T("                                                     ") \
    _T("    UNIQUE(album, photo)                             ") \
    _T(");                                                   "))

#define CREATE_LOCATION ( \
    _T("CREATE TABLE location (                       ") \
    _T("    location_id INTEGER PRIMARY KEY NOT NULL, ") \
    _T("                                              ") \
    _T("    name VARCHAR NOT NULL UNIQUE,             ") \
    _T("    description VARCHAR                       ") \
    _T(");                                            "))

#endif

