//
// Created by ByteDance on 2022/7/15.
//

#include <ScrollDispatcher.h>
#include "ScrollView.h"
#include "algorithm"

ScrollView::ScrollView() : xVelocity(0.0f), yVelocity(0.0f) {
    touchEventDispatcher = std::make_unique<ScrollDispatcher>(this);
}

ScrollView::~ScrollView() {

}

void ScrollView::measure(int widthMeasureSpec, int heightMeasureSpec) {
    for (auto &child: children) {
        measureChild(child, widthMeasureSpec, heightMeasureSpec);
    }
    auto width = 0;
    auto height = 0;
    if (_direction == YGFlexDirectionColumn) {
        if (layoutParams->_widthMode == EXACTLY) {
            width = layoutParams->_width;
        } else {
            width = getMaxWidthInChildren();
        }
        //竖向滑动必须制定高度
        assert(layoutParams->_heightMode == EXACTLY);
        height = layoutParams->_height;
    } else {
        if (layoutParams->_heightMode == EXACTLY) {
            height = layoutParams->_height;
        } else {
            height = getMaxHeightInChildren();
        }
        //横向滑动必须制定宽度
        assert(layoutParams->_widthMode == EXACTLY);
        width = layoutParams->_width;
    }
    ViewGroup::setMeasuredDimension(width, height);
    YGNodeCalculateLayout(node, YGNodeStyleGetWidth(node).value, YGNodeStyleGetHeight(node).value,
                          YGDirectionLTR);
}

void ScrollView::layout(int l, int t, int r, int b) {
    skRect.setLTRB(l, t, r, b);
    width = r - l;
    height = b - t;
    if (_direction == YGFlexDirectionRow) {
        layoutHorizontal(l + translateX, t, r, b);
    } else {
        layoutVertical(l, t + translateY, r, b);
    }
}

void ScrollView::updateTranslateY(float diffY) {
    translateY += diffY;
    //可滑动的上限和下限
    auto maxTranslate = height - getChildHeightSum();
    if (translateY <= maxTranslate) {
        translateY = maxTranslate;
    }
    if (translateY >= 0) {
        translateY = 0;
    }
    ALOGD("translateY update %f", translateY)
}

void ScrollView::setFlexWrap(YGWrap wrap) {
    assert(wrap == YGWrapNoWrap);
    FlexboxLayout::setFlexWrap(wrap);
}

void ScrollView::setFlexDirection(YGFlexDirection direction) {
    FlexboxLayout::setFlexDirection(direction);
}

void ScrollView::updateTranslateX(float diffX) {
    translateX += diffX;
    auto maxTranslate = width - getChildWidthSum();
    if (translateX <= maxTranslate) {
        translateX = maxTranslate;
    }
    if (translateX >= 0) {
        translateX = 0;
    }
}

bool ScrollView::addView(View *view, LayoutParams *layoutParams) {
    isDirty = true;
    return FlexboxLayout::addView(view, layoutParams);
}

bool ScrollView::removeView(View *view) {
    isDirty = true;
    return FlexboxLayout::removeView(view);
}

bool ScrollView::canScroll() {
    if (_direction == YGFlexDirectionRow) {
        return abs(translateX) < getChildWidthSum() - width;
    } else {
        return abs(translateY) < getChildHeightSum() - height;
    }
}

void ScrollView::setVelocity(float x, float y) {
    this->xVelocity = x;
    this->yVelocity = y;
    ALOGD("ScrollView setVelocity %f %f", x, y)
}
