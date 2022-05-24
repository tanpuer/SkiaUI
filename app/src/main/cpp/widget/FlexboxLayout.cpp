//
// Created by cw on 2022/5/24.
//

#include "FlexboxLayout.h"

FlexboxLayout::FlexboxLayout() {


}

FlexboxLayout::~FlexboxLayout() {

}

void FlexboxLayout::setFlexDirection(YGFlexDirection direction) {
    assert(direction == YGFlexDirectionRow || direction == YGFlexDirectionColumn);
    this->_direction = direction;
    ViewGroup::setFlexDirection(direction);
}

void FlexboxLayout::layout(int l, int t, int r, int b) {
    if (_direction == YGFlexDirectionRow) {
        layoutHorizontal(l, t, r, b);
    } else {
        layoutVertical(l, t, r, b);
    }
}

void FlexboxLayout::layoutVertical(int l, int t, int r, int b) {
    auto tmpTop = layoutParams->_marginTop + t;
    for (auto &child: children) {
        auto left = static_cast<int>(YGNodeLayoutGetLeft(child->node));
        auto top = static_cast<int>(YGNodeLayoutGetTop(child->node));
        auto width = static_cast<int>(YGNodeLayoutGetWidth(child->node));
        auto height = static_cast<int>(YGNodeLayoutGetHeight(child->node));
        //todo 需要考虑padding
        tmpTop += child->layoutParams->_marginTop;
        child->layout(left + l, tmpTop, left + l + width, tmpTop + height);
        tmpTop += getHeight();
        tmpTop += child->layoutParams->_marginBottom;
    }
}

void FlexboxLayout::layoutHorizontal(int l, int t, int r, int b) {
    auto tmpLeft = layoutParams->_marginLeft + l;
    for (auto &child: children) {
        auto left = static_cast<int>(YGNodeLayoutGetLeft(child->node));
        auto top = static_cast<int>(YGNodeLayoutGetTop(child->node));
        auto width = static_cast<int>(YGNodeLayoutGetWidth(child->node));
        auto height = static_cast<int>(YGNodeLayoutGetHeight(child->node));
        //todo 需要考虑padding
        tmpLeft += child->layoutParams->_marginLeft;
        child->layout(tmpLeft, top + t, tmpLeft + width, top + t + height);
        tmpLeft += child->getWidth();
        tmpLeft += child->layoutParams->_marginRight;
    }
}
