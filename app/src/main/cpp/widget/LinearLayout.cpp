//
// Created by DZSB-000848 on 1/26/22.
//

#include <base/native_log.h>
#include "LinearLayout.h"

LinearLayout::LinearLayout() : ViewGroup() {

}

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

void LinearLayout::measure() {
    ViewGroup::measure();
}

void LinearLayout::layout(float l, float t, float r, float b) {
    if (orientation == Orientation::HORIZONTAL) {
        ALOGD("LinearLayout layout horizontal %f %f %f %f", l, t, r, b)
        layoutHorizontal(l, t, r, b);
    } else {
        ALOGD("LinearLayout layout vertical %f %f %f %f", l, t, r, b)
        layoutVertical(l, t, r, b);
    }
}

void LinearLayout::layoutHorizontal(float l, float t, float r, float b) {
    auto tmpLeft = marginLeft + l;
    for (auto child: children) {
        auto left = YGNodeLayoutGetLeft(child->node);
        auto top = YGNodeLayoutGetTop(child->node);
        auto width = YGNodeLayoutGetWidth(child->node);
        auto height = YGNodeLayoutGetHeight(child->node);
        tmpLeft += child->marginLeft;
//        ALOGD("LinearLayout layout horizontal tmpLeft: %f %f", tmpLeft, width)
        child->layout(tmpLeft, top + t, tmpLeft + width, top + t + height);
        tmpLeft += width;
        tmpLeft += child->marginRight;
    }
}

void LinearLayout::layoutVertical(float l, float t, float r, float b) {
    auto tmpTop = marginTop + t;
    for (auto child: children) {
        auto left = YGNodeLayoutGetLeft(child->node);
        auto top = YGNodeLayoutGetTop(child->node);
        auto width = YGNodeLayoutGetWidth(child->node);
        auto height = YGNodeLayoutGetHeight(child->node);
        tmpTop += child->marginTop;
        child->layout(left + l, tmpTop, left + l + width, tmpTop + height);
//        ALOGD("LinearLayout layout vertical tmpTop: %f %f %f %f", tmpTop, height, getHeight(), child->marginTop)
        tmpTop += getHeight();
        tmpTop += marginBottom;
    }
}

LinearLayout::~LinearLayout() = default;
