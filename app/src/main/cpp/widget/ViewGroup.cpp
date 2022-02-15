//
// Created by DZSB-000848 on 1/24/22.
//

#include <yoga/Utils.h>
#include <base/native_log.h>
#include "ViewGroup.h"

ViewGroup::ViewGroup() : View(), maxChildWidth(0.0f), maxChildHeight(0.0f) {
    config = YGConfigNew();
    root = YGNodeNewWithConfig(config);
}

ViewGroup::~ViewGroup() {
    if (root == nullptr) {
        return;
    }
    for (auto view: children) {
        delete view;
    }
    YGConfigFree(config);
    YGNodeFree(root);
}

bool ViewGroup::addView(View *view, LayoutParams *layoutParams) {
    if (view == nullptr || view->node == nullptr) {
        ALOGE("add null view, pls check view!")
        return false;
    }
    auto childCount = YGNodeGetChildCount(root);
    YGNodeInsertChild(root, view->node, childCount);
    children.emplace_back(view);
    view->setLayoutParams(layoutParams);
    return true;
}

bool ViewGroup::removeView(View *view) {
    if (view == nullptr || view->node == nullptr) {
        ALOGE("remove null view, pls check view!")
        return false;
    }
    YGNodeRemoveChild(root, view->node);
    for (auto ite = children.begin(); ite < children.end(); ++ite) {
        if ((*ite)->viewId == view->viewId) {
            children.erase(ite);
            delete *ite;
            return true;
        }
    }
    return false;
}

void ViewGroup::removeAllViews() {
    if (root == nullptr) {
        ALOGE("remove null view, pls check view!")
        return;
    }
    YGNodeRemoveAllChildren(root);
    for (auto view: children) {
        delete view;
    }
}

void ViewGroup::measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec) {
    View::measure(widthMeasureSpec, heightMeasureSpec);
    for (auto &child: children) {
        measureChild(child, widthMeasureSpec, heightMeasureSpec);
    }
    YGNodeCalculateLayout(root, widthMeasureSpec->getSize(), heightMeasureSpec->getSize(),
                          YGDirectionLTR);
}

void ViewGroup::measureChild(View *child, MeasureSpec *parentWidthMeasureSpec,
                             MeasureSpec *parentHeightMeasureSpec) {
    auto lp = layoutParams.get();
    auto childWidthMeasureSpec = getChildMeasureSpec(parentWidthMeasureSpec,
                                                     lp->_marginLeft + lp->_marginLeft,
                                                     child->layoutParams->_width);
    auto childHeightMeasureSpec = getChildMeasureSpec(parentHeightMeasureSpec,
                                                      lp->_marginTop + lp->_marginBottom,
                                                      child->layoutParams->_height);
    child->measure(childWidthMeasureSpec, childHeightMeasureSpec);
}

MeasureSpec *ViewGroup::getChildMeasureSpec(MeasureSpec *parentMeasureSpec, float padding,
                                            float childDimension) {
    auto specMode = parentMeasureSpec->getMode();
    auto specSize = parentMeasureSpec->getSize();
    auto size = std::max(0.0f, specSize - padding);
    auto resultSize = .0f;
    auto resultMode = YGMeasureModeUndefined;
    switch (specMode) {
        // Parent has imposed an exact size on us
        case YGMeasureModeExactly: {
            if (childDimension >= 0) {
                resultSize = childDimension;
                resultMode = YGMeasureModeExactly;
            } else if (MeasureSpec::isMatchParent(childDimension)) {
                // Child wants to be our size. So be it.
                resultSize = size;
                resultMode = YGMeasureModeExactly;
            } else {
                // Child wants to determine its own size. It can't be
                // bigger than us.
                resultSize = size;
                resultMode = YGMeasureModeAtMost;
            }
            break;
        }
            // Parent has imposed a maximum size on us
        case YGMeasureModeAtMost: {
            if (childDimension >= 0) {
                // Child wants a specific size... so be it
                resultSize = childDimension;
                resultMode = YGMeasureModeExactly;
            } else if (MeasureSpec::isMatchParent(childDimension)) {
                // Child wants to be our size, but our size is not fixed.
                // Constrain child to not be bigger than us.
                resultSize = size;
                resultMode = YGMeasureModeAtMost;
            } else {
                // Child wants to determine its own size. It can't be
                // bigger than us.
                resultSize = size;
                resultMode = YGMeasureModeAtMost;
            }
            break;
        }

            // Parent asked to see how big we want to be
        case YGMeasureModeUndefined: {
            if (childDimension >= 0) {
                // Child wants a specific size... let him have it
                resultSize = childDimension;
                resultMode = YGMeasureModeExactly;
            } else if (MeasureSpec::isMatchParent(childDimension)) {
                // Child wants to be our size... find out how big it should be
                resultSize = size;
                resultMode = YGMeasureModeUndefined;
            } else {
                // Child wants to determine its own size.... find out how big it should be
                resultSize = size;
                resultMode = YGMeasureModeUndefined;
            }
            break;
        }
    }
    return MeasureSpec::makeMeasureSpec(resultSize, resultMode);
}

void ViewGroup::layout(float l, float t, float r, float b) {
    for (auto child: children) {
        auto left = YGNodeLayoutGetLeft(child->node);
        auto top = YGNodeLayoutGetTop(child->node);
        auto width = YGNodeLayoutGetWidth(child->node);
        auto height = YGNodeLayoutGetHeight(child->node);
        child->layout(left + l, top + t, left + width, top + height);
    }
}

void ViewGroup::draw(SkCanvas *canvas) {
    View::draw(canvas);
    for (auto child: children) {
        child->draw(canvas);
    }
}

void ViewGroup::setAlignItems(YGAlign align) {
    SkASSERT(root);
    if (root == nullptr) {
        return;
    }
    YGNodeStyleSetAlignItems(root, align);
}

void ViewGroup::setJustifyContent(YGJustify justify) {
    SkASSERT(root);
    if (root == nullptr) {
        return;
    }
    YGNodeStyleSetJustifyContent(root, justify);
}

void ViewGroup::setAlignContent(YGAlign align) {
    SkASSERT(root);
    if (root == nullptr) {
        return;
    }
    YGNodeStyleSetAlignContent(root, align);
}

void ViewGroup::setFlexWrap(YGWrap wrap) {
    SkASSERT(root);
    if (root == nullptr) {
        return;
    }
    YGNodeStyleSetFlexWrap(node, wrap);
}

void ViewGroup::setFlexDirection(YGFlexDirection direction) {
    SkASSERT(root);
    if (root == nullptr) {
        return;
    }
    YGNodeStyleSetFlexDirection(root, direction);
}

float ViewGroup::getWidth() {
    if (YGNodeStyleGetWidth(root).unit == YGUnitAuto) {
        return getMaxWidthInChildren();
    } else {
        //exactly todo percent
        return View::getWidth();
    }
}

float ViewGroup::getHeight() {
    if (YGNodeStyleGetHeight(root).unit == YGUnitAuto) {
        return getMaxHeightInChildren();
    } else {
        //exactly todo percent
        return View::getHeight();
    }
}

float ViewGroup::getMaxHeightInChildren() {
    float maxHeight = 0.0f;
    for (auto &child: children) {
        maxHeight = std::max(maxHeight, child->getHeight());
    }
    return maxHeight;
}

float ViewGroup::getMaxWidthInChildren() {
    float maxWidth = 0.0f;
    for (auto &child: children) {
        maxWidth = std::max(maxWidth, child->getWidth());
    }
    return maxWidth;
}

bool ViewGroup::isViewGroup() {
    return true;
}
