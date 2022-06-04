//
// Created by cw on 2022/5/24.
//

#include "FlexboxLayout.h"

FlexboxLayout::FlexboxLayout() {


}

FlexboxLayout::~FlexboxLayout() {

}

const char *FlexboxLayout::name() {
    return "FlexboxLayout";
}

void FlexboxLayout::setFlexDirection(YGFlexDirection direction) {
    assert(direction == YGFlexDirectionRow || direction == YGFlexDirectionColumn);
    this->_direction = direction;
    ViewGroup::setFlexDirection(direction);
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
        ALOGD("layoutVertical %s %d %d %d %d", child->name(), left, top, width, height)
        child->layout(left, top, left + width, top + height);
    }
}

void FlexboxLayout::layoutHorizontal(int l, int t, int r, int b) {
    for (auto &child: children) {
        auto left = static_cast<int>(YGNodeLayoutGetLeft(child->node));
        auto top = static_cast<int>(YGNodeLayoutGetTop(child->node));
        auto right = static_cast<int>(YGNodeLayoutGetRight(child->node));
        auto bottom = static_cast<int>(YGNodeLayoutGetBottom(child->node));
        auto width = static_cast<int>(YGNodeLayoutGetWidth(child->node));
        auto height = static_cast<int>(YGNodeLayoutGetHeight(child->node));
        //todo 处理ViewGroup嵌套
        ALOGD("layoutHorizontal %s %d %d %d %d %d %d ", child->name(), left, top, right, bottom,
              width, height)
        //todo 需要考虑padding
        child->layout(left, top, left + width, top + height);
    }
}
