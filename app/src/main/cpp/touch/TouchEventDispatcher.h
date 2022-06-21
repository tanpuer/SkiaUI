//
// Created by cw on 2022/6/4.
//

#ifndef SKIAUI_TOUCHEVENTDISPATCHER_H
#define SKIAUI_TOUCHEVENTDISPATCHER_H

#include "TouchEvent.h"
#include "memory"

class View;

class ViewGroup;

class TouchEventDispatcher {

public:

    TouchEventDispatcher(View *view);

    ~TouchEventDispatcher();

    virtual bool dispatchTouchEvent(TouchEvent *touchEvent);

    virtual bool onInterceptTouchEvent(TouchEvent *touchEvent);

    virtual bool onTouchEvent(TouchEvent *touchEvent);

    virtual void requestDisallowInterceptTouchEvent(bool disallowIntercept);

    virtual void setWeakView(View *view);

private:

    void findTargetView();

    void dispatchToTargetView(TouchEvent *touchEvent);

    void clearTargetView();

    View *findTargetViewTraversal(ViewGroup *viewGroup);

private:

    View *view;

    std::weak_ptr<View> weakTargetView;

};


#endif //SKIAUI_TOUCHEVENTDISPATCHER_H
