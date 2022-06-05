//
// Created by cw on 2022/6/4.
//

#include "TouchEventDispatcher.h"

TouchEventDispatcher::TouchEventDispatcher() {

}

TouchEventDispatcher::~TouchEventDispatcher() {

}

bool TouchEventDispatcher::dispatchTouchEvent() {
    return false;
}

bool TouchEventDispatcher::onInterceptTouchEvent() {
    return false;
}

bool TouchEventDispatcher::onTouchEvent() {
    return false;
}

void TouchEventDispatcher::requestDisallowInterceptTouchEvent(bool disallowIntercept) {

}
