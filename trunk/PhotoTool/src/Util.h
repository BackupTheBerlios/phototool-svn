
#ifndef UTIL_H
#define UTIL_H

// Creates an accessor for a class property
#define ACCESSOR(name, var, type) \
    type Get##name() const { return var; } \
    void Set##name(const type& val) { var = val; }

// Quick access to XRC controls
#define CTRL(name, type) XRCCTRL(*this, name, type)

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

#define POPUP_MENU(menuBar, name) { \
        wxMenuBar *bar = wxXmlResource::Get()->LoadMenuBar(_T(menuBar)); \
        wxMenu *menu = bar->GetMenu(bar->FindMenu(_T(name))); \
        PopupMenu(menu); \
    }

#endif

