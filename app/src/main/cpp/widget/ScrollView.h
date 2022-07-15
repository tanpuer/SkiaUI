//
// Created by ByteDance on 2022/7/15.
//

#ifndef SKIAUI_SCROLLVIEW_H
#define SKIAUI_SCROLLVIEW_H


#include "ViewGroup.h"
#include "Scroller.h"

class ScrollView : public ViewGroup {

public:

    ScrollView();

    virtual ~ScrollView();

protected:

    Scroller *scroller;

};


#endif //SKIAUI_SCROLLVIEW_H
