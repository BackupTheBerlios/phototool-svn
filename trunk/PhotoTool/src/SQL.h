
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

