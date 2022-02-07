//
// Created by DZSB-000848 on 1/24/22.
//

#include <yoga/Utils.h>
#include <base/native_log.h>
#include "ViewGroup.h"

ViewGroup::ViewGroup() : View() {
    auto config = YGConfigNew();
    root = YGNodeNewWithConfig(config);
}

ViewGroup::~ViewGroup() = default;

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

void ViewGroup::measure() {
    //默认不支持rtl
    for (auto child: children) {
        child->measure();
    }
    YGNodeCalculateLayout(root, availableWidth, availableHeight, YGDirectionLTR);
}

void ViewGroup::layout() {
    for (auto child: children) {
        child->layout();
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
