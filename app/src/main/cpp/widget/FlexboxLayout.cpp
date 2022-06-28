//
// Created by cw on 2022/5/24.
//

#include "FlexboxLayout.h"

FlexboxLayout::FlexboxLayout() {

}

FlexboxLayout::~FlexboxLayout() {
//    ALOGD("delete FlexboxLayout %lld", viewId)
}

const char *FlexboxLayout::name() {
    return "FlexboxLayout";
}

void FlexboxLayout::setFlexDirection(YGFlexDirection direction) {
    assert(direction == YGFlexDirectionRow || direction == YGFlexDirectionColumn);
    this->_direction = direction;
    ViewGroup::setFlexDirection(direction);
}


void FlexboxLayout::measure(int widthMeasureSpec, int heightMeasureSpec) {
    for (auto &child: children) {
        measureChild(child, widthMeasureSpec, heightMeasureSpec);
    }
    if (YGNodeStyleGetFlexDirection(node) == YGFlexDirectionRow) {
        if (layoutParams->_widthMode == EXACTLY) {
            YGNodeStyleSetWidth(node, layoutParams->_width);
        } else {
            YGNodeStyleSetWidth(node, getChildWidthSum());
        }
        if (layoutParams->_heightMode == EXACTLY) {
            YGNodeStyleSetHeight(node, layoutParams->_height);
        } else {
            YGNodeStyleSetHeight(node, getMaxHeightInChildren());
        }
    } else {
        if (layoutParams->_widthMode == EXACTLY) {
            YGNodeStyleSetWidth(node, layoutParams->_width);
        } else {
            YGNodeStyleSetWidth(node, getMaxWidthInChildren());
        }
        if (layoutParams->_heightMode == EXACTLY) {
            YGNodeStyleSetHeight(node, layoutParams->_height);
        } else {
            YGNodeStyleSetHeight(node, getChildHeightSum());
        }
    }
    ALOGD("YGNodeCalculateLayout %s %f %f", name(),
          YGNodeStyleGetWidth(node).value, YGNodeStyleGetHeight(node).value);
    YGNodeCalculateLayout(node, YGNodeStyleGetWidth(node).value, YGNodeStyleGetHeight(node).value,
                          YGDirectionLTR);
}

void FlexboxLayout::layout(int l, int t, int r, int b) {
    skRect.setLTRB(l, t, r, b);
    width = r - l;
    height = b - t;
    if (_direction == YGFlexDirectionRow) {
        layoutHorizontal(l, t, r, b);
    } else {
        layoutVertical(l, t, r, b);
    }
}

void FlexboxLayout::layoutVertical(int l, int t, int r, int b) {
    for (auto &child: children) {
        auto left = static_cast<int>(YGNodeLayoutGetLeft(child->node));
        auto top = static_cast<int>(YGNodeLayoutGetTop(child->node));
        auto width = static_cast<int>(YGNodeLayoutGetWidth(child->node));
        auto height = static_cast<int>(YGNodeLayoutGetHeight(child->node));
        //todo 需要考虑padding
        ALOGD("FlexboxLayout: layout vertical %s %d %d %d %d", child->name(), left, top, width,
              height)
        child->layout(left + l, top + t, left + l + width, top + t + height);
    }
}

void FlexboxLayout::layoutHorizontal(int l, int t, int r, int b) {
    auto tempLeft = l;
    for (auto &child: children) {
        auto left = static_cast<int>(YGNodeLayoutGetLeft(child->node));
        auto top = static_cast<int>(YGNodeLayoutGetTop(child->node));
        auto width = static_cast<int>(YGNodeLayoutGetWidth(child->node));
        auto height = static_cast<int>(YGNodeLayoutGetHeight(child->node));
        ALOGD("FlexboxLayout: layout horizontal %s %d %d %d %d", child->name(), left, top, width,
              height)
        //todo 需要考虑padding
        child->layout(left + l, top + t, left + l + width, top + t + height);
    }
}
