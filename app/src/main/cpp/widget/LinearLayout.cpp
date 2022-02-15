//
// Created by DZSB-000848 on 1/26/22.
//

#include <base/native_log.h>
#include "LinearLayout.h"

LinearLayout::LinearLayout() : ViewGroup() {

}

LinearLayout::~LinearLayout() = default;

void LinearLayout::setOrientation(LinearLayout::Orientation _orientation) {
    this->orientation = _orientation;
    if (orientation == Orientation::HORIZONTAL) {
        setFlexDirection(YGFlexDirectionRow);
    } else {
        setFlexDirection(YGFlexDirectionColumn);
    }
}

LinearLayout::Orientation LinearLayout::getOrientation() {
    return orientation;
}

void LinearLayout::measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec) {
    ViewGroup::measure(widthMeasureSpec, heightMeasureSpec);
    if (orientation == Orientation::VERTICAL) {
//        ALOGD("linearlayout vertical %d %f %f", YGNodeGetChildCount(root), YGNodeLayoutGetWidth(YGNodeGetChild(root, 0)), YGNodeLayoutGetHeight(YGNodeGetChild(root, 1)))
    } else {
        ALOGD("linearlayout horizontal %d %f %f %f %f", YGNodeGetChildCount(root),
              YGNodeLayoutGetHeight(YGNodeGetChild(root, 0)),
              YGNodeLayoutGetHeight(YGNodeGetChild(root, 1)),
              YGNodeLayoutGetHeight(YGNodeGetChild(root, 2)), getHeight())
//        YGNodeStyleSetHeight(root, getHeight());
    }
}

void LinearLayout::layout(float l, float t, float r, float b) {
    if (orientation == Orientation::HORIZONTAL) {
//        ALOGD("LinearLayout layout horizontal %f %f %f %f", l, t, r, b)
        layoutHorizontal(l, t, r, b);
    } else {
//        ALOGD("LinearLayout layout vertical %f %f %f %f", l, t, r, b)
        layoutVertical(l, t, r, b);
    }
}

void LinearLayout::layoutHorizontal(float l, float t, float r, float b) {
    auto tmpLeft = layoutParams->_marginLeft + l;
    for (auto child: children) {
        auto left = YGNodeLayoutGetLeft(child->node);
        auto top = YGNodeLayoutGetTop(child->node);
        auto width = YGNodeLayoutGetWidth(child->node);
        auto height = YGNodeLayoutGetHeight(child->node);
        tmpLeft += child->layoutParams->_marginLeft;
//        ALOGD("LinearLayout layout horizontal tmpLeft: %f %f", tmpLeft, width)
        child->layout(tmpLeft, top + t, tmpLeft + width, top + t + height);
        tmpLeft += getWidth();
        tmpLeft += child->layoutParams->_marginRight;
    }
}

void LinearLayout::layoutVertical(float l, float t, float r, float b) {
    auto tmpTop = layoutParams->_marginTop + t;
    for (auto child: children) {
        auto left = YGNodeLayoutGetLeft(child->node);
        auto top = YGNodeLayoutGetTop(child->node);
        auto width = YGNodeLayoutGetWidth(child->node);
        auto height = YGNodeLayoutGetHeight(child->node);
        tmpTop += child->layoutParams->_marginTop;
        child->layout(left + l, tmpTop, left + l + width, tmpTop + height);
        ALOGD("LinearLayout layout vertical tmpTop: %f %f %f %f", tmpTop, height, getHeight(),
              child->layoutParams->_marginTop)
        tmpTop += getHeight();
        tmpTop += child->layoutParams->_marginTop;
    }
}