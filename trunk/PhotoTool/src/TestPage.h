
#ifndef TESTPAGE_H
#define TESTPAGE_H

#include "PageBase.h"
#include "ThumbList.h"

class ThumbList;

class TestPage : public PageBase
{
public:
    TestPage(wxNotebook *parent);

    Photo GetSelectedPhoto();
    void SetSelectedPhoto(const Photo& photo);

private:
    ThumbList *m_list;
};

#endif

