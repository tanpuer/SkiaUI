//
// Created by ByteDance on 2022/7/15.
//

#include "ScrollView.h"

ScrollView::ScrollView() {
    //暂时只测试竖向滑动的scrollView
    FlexboxLayout::setFlexDirection(YGFlexDirectionColumn);
}

ScrollView::~ScrollView() {

}

void ScrollView::measure(int widthMeasureSpec, int heightMeasureSpec) {
    for (auto &child: children) {
        measureChild(child, widthMeasureSpec, heightMeasureSpec);
    }
    auto width = 0;
    if (layoutParams->_widthMode == EXACTLY) {
        width = layoutParams->_width;
    } else {
        for (auto &child: children) {
            if (child->getWidth() > width) {
                width = child->getWidth();
            }
        }
    }
    auto height = 0;
    if (layoutParams->_heightMode == EXACTLY) {
        height = layoutParams->_height;
    } else {
        for (auto &child: children) {
            height += child->getHeight();
        }
    }
    ViewGroup::setMeasuredDimension(width, height);
    YGNodeCalculateLayout(node, YGNodeStyleGetWidth(node).value, YGNodeStyleGetHeight(node).value,
                          YGDirectionLTR);
}

void ScrollView::layout(int l, int t, int r, int b) {
    FlexboxLayout::layout(l, t, r, b);
}
