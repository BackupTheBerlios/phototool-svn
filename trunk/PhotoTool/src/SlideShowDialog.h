
#ifndef SLIDESHOWDIALOG_H
#define SLIDESHOWDIALOG_H

#include "InputDialog.h"

class SlideShowDialog : public InputDialog
{
public:
    SlideShowDialog(wxWindow *parent);

    bool TransferDataFromWindow();
    bool TransferDataToWindow();
};

#endif

