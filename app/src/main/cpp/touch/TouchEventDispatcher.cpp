//
// Created by cw on 2022/6/4.
//

#include "TouchEventDispatcher.h"
#include <yoga/Yoga.h>
#include "ViewGroup.h"

TouchEventDispatcher::TouchEventDispatcher(View *view) {
    this->view = view;
}

TouchEventDispatcher::~TouchEventDispatcher() = default;

bool TouchEventDispatcher::dispatchTouchEvent(TouchEvent *touchEvent) {
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return false;
    }
    if (onInterceptTouchEvent(touchEvent)) {
        return false;
    }
    switch (touchEvent->action) {
        case TouchEvent::ACTION_DOWN: {
            findTargetView();
            break;
        }
        case TouchEvent::ACTION_MOVE: {

            break;
        }
        case TouchEvent::ACTION_UP: {
            break;
        }
        case TouchEvent::ACTION_CANCEL : {
            break;
        }
        default: {
            break;
        }
    }
    return true;
}

bool TouchEventDispatcher::onInterceptTouchEvent(TouchEvent *touchEvent) {
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return false;
    }
    return false;
}

bool TouchEventDispatcher::onTouchEvent(TouchEvent *touchEvent) {
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return false;
    }
    return false;
}

void TouchEventDispatcher::requestDisallowInterceptTouchEvent(bool disallowIntercept) {

}

void TouchEventDispatcher::setWeakView(View *view) {

}

void TouchEventDispatcher::findTargetView() {
    auto targetView = weakTargetView.lock().get();
    if (targetView != nullptr) {
        ALOGE("findTargetView error: weakRefView is not null")
        clearTargetView();
    }
    if (view == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is null, pls check")
        return;
    }
    auto viewGroup = dynamic_cast<ViewGroup *>(view);
    if (viewGroup == nullptr) {
        ALOGE("dispatchTouchEvent weakRefView is not ViewGroup, pls check")
        return;
    }
    findTargetViewTraversal(viewGroup);
}

void TouchEventDispatcher::dispatchToTargetView(TouchEvent *touchEvent) {

}

void TouchEventDispatcher::clearTargetView() {
    weakTargetView.reset();
}

View *TouchEventDispatcher::findTargetViewTraversal(ViewGroup *viewGroup) {
    for (auto child:viewGroup->children) {
        if (dynamic_cast<ViewGroup *>(child) != nullptr) {
            return findTargetViewTraversal(dynamic_cast<ViewGroup *>(child));
        } else {
            //View
            auto left = YGNodeStyleGetPosition(child->node, YGEdgeLeft);
            auto top = YGNodeStyleGetPosition(child->node, YGEdgeTop);
            ALOGD("findTargetViewTraversal %s %d %d", child->name(), left, top)
        }
    }
    return nullptr;
}
