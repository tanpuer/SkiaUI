//
// Created by DZSB-000848 on 1/26/22.
//

#include <base/native_log.h>
#include "LinearLayout.h"

LinearLayout::LinearLayout() : ViewGroup() {
    YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
}

LinearLayout::~LinearLayout() = default;

bool LinearLayout::addView(View *view) {
    ViewGroup::addView(view);
    if (view == nullptr || view->node == nullptr) {
        ALOGE("add null view, pls check view!")
        return false;
    }
    auto childCount = YGNodeGetChildCount(root);
    YGNodeInsertChild(root, view->node, childCount);
    return true;
}

bool LinearLayout::removeView(View *view) {
    ViewGroup::removeView(view);
    if (view == nullptr || view->node == nullptr) {
        ALOGE("remove null view, pls check view!")
        return false;
    }
    YGNodeRemoveChild(root, view->node);
    return true;
}

void LinearLayout::setOrientation(YGFlexDirection orientation) {
    if (this->orientation == orientation) {
        return;
    }
    this->orientation = orientation;
    requestLayout();
}
