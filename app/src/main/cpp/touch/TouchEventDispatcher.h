//
// Created by cw on 2022/6/4.
//

#ifndef SKIAUI_TOUCHEVENTDISPATCHER_H
#define SKIAUI_TOUCHEVENTDISPATCHER_H

#include <View.h>
#include "TouchEvent.h"
#include "memory"

class TouchEventDispatcher {

public:

    TouchEventDispatcher();

    ~TouchEventDispatcher();

    virtual bool dispatchTouchEvent(TouchEvent *touchEvent);

    virtual bool onInterceptTouchEvent(TouchEvent *touchEvent);

    virtual bool onTouchEvent(TouchEvent *touchEvent);

    virtual void requestDisallowInterceptTouchEvent(bool disallowIntercept);

    virtual void setWeakView(View* view);

private:

    std::weak_ptr<View> weakRefView;

};


#endif //SKIAUI_TOUCHEVENTDISPATCHER_H
