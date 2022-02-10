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

bool ViewGroup::addView(View *view) {
    if (view == nullptr || view->node == nullptr) {
        ALOGE("add null view, pls check view!")
        return false;
    }
    auto childCount = YGNodeGetChildCount(root);
    YGNodeInsertChild(root, view->node, childCount);
    children.emplace_back(view);
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
    for (auto view: children) {
        delete view;
    }
    requestLayout();
}

void
ViewGroup::measure(float _width, YGMeasureMode widthMode, float _height, YGMeasureMode heightMode) {
    //默认不支持rtl
    for (auto child: children) {
        child->measure(_width, widthMode, _height, heightMode);
    }
    YGNodeCalculateLayout(root, availableWidth, availableHeight, YGDirectionLTR);
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
