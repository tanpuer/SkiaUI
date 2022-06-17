//
// Created by cw on 2022/6/4.
//

#include "TouchEventDispatcher.h"

TouchEventDispatcher::TouchEventDispatcher() = default;

TouchEventDispatcher::~TouchEventDispatcher() = default;

bool TouchEventDispatcher::dispatchTouchEvent(TouchEvent *touchEvent) {
    auto view = weakRefView.lock().get();
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return false;
    }
    if (onInterceptTouchEvent(touchEvent)) {
        return false;
    }
    if (view->isViewGroup()) {
    }
    return true;
}

bool TouchEventDispatcher::onInterceptTouchEvent(TouchEvent *touchEvent) {
    auto view = weakRefView.lock().get();
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return false;
    }
    return false;
}

bool TouchEventDispatcher::onTouchEvent(TouchEvent *touchEvent) {
    auto view = weakRefView.lock().get();
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return false;
    }
    return false;
}

void TouchEventDispatcher::requestDisallowInterceptTouchEvent(bool disallowIntercept) {

}

void TouchEventDispatcher::setWeakView(View *view) {
    weakRefView = std::shared_ptr<View>(view);
}
