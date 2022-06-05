//
// Created by cw on 2022/6/4.
//

#ifndef SKIAUI_TOUCHEVENTDISPATCHER_H
#define SKIAUI_TOUCHEVENTDISPATCHER_H

#include "TouchEvent.h"

class TouchEventDispatcher {

    TouchEventDispatcher();

    ~TouchEventDispatcher();

    virtual bool dispatchTouchEvent();

    virtual bool onInterceptTouchEvent();

    virtual bool onTouchEvent();

    virtual void requestDisallowInterceptTouchEvent(bool disallowIntercept);

};


#endif //SKIAUI_TOUCHEVENTDISPATCHER_H
