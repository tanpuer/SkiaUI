//
// Created by DZSB-000848 on 1/24/22.
//

#include <base/native_log.h>
#include <yoga/Utils.h>
#include "View.h"
#include "effects/SkCornerPathEffect.h"

View::View() : width(0), height(0), skRect(SkRect::MakeEmpty()), cornerRadius(),
               availableHeight(0.0), availableWidth(0.0) {
    viewId = VIEW_ID++;
    paint = new SkPaint();
    paint->setAntiAlias(true);
    node = YGNodeNew();
}

View::~View() {
    delete paint;
    if (node != nullptr) {
        YGNodeFree(node);
    }
}

#pragma mark yoga

void View::measure() {
    if (YGFloatsEqual(availableWidth, 0.0f) && YGFloatsEqual(availableHeight, 0.0f)) {
        ALOGE("view width and height is zero, skip measure")
        return;
    }
}

void View::layout() {
    skRect.setXYWH(YGNodeLayoutGetLeft(node), YGNodeLayoutGetTop(node),
                   YGNodeLayoutGetWidth(node), YGNodeLayoutGetHeight(node));
}

void View::draw(SkCanvas *canvas) {
    canvas->drawRect(skRect, *paint);
}

void View::invalidate() {
    //todo
}

void View::requestLayout() {
    //todo
}

void View::setMargins(std::array<float, 4> margins) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        ALOGE("YGNodeRef not initialized, pls check!")
        return;
    }
    YGNodeStyleSetMargin(node, YGEdgeLeft, margins[0]);
    YGNodeStyleSetMargin(node, YGEdgeTop, margins[1]);
    YGNodeStyleSetMargin(node, YGEdgeRight, margins[2]);
    YGNodeStyleSetMargin(node, YGEdgeBottom, margins[3]);
}

void View::setPadding(std::array<float, 4> paddings) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        ALOGE("YGNodeRef not initialized, pls check!")
        return;
    }
    YGNodeStyleSetPadding(node, YGEdgeLeft, paddings[0]);
    YGNodeStyleSetPadding(node, YGEdgeTop, paddings[1]);
    YGNodeStyleSetPadding(node, YGEdgeRight, paddings[2]);
    YGNodeStyleSetPadding(node, YGEdgeBottom, paddings[3]);
}

void View::setMargins(float margin) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetMargin(node, YGEdgeAll, margin);
}

void View::setPadding(float padding) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetPadding(node, YGEdgeAll, padding);
}

void View::setSize(float _availableWidth, float _availableHeight) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    if (YGFloatsEqual(_availableWidth, this->availableWidth) &&
        YGFloatsEqual(_availableHeight, this->availableHeight)) {
        ALOGD("view is the same size, ignore")
        return;
    }
    this->availableWidth = _availableWidth;
    this->availableHeight = _availableHeight;
    YGNodeStyleSetWidth(node, availableWidth);
    YGNodeStyleSetHeight(node, availableHeight);
}

void View::setSizePercent(float widthPercent, float heightPercent) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetWidthPercent(node, widthPercent);
    YGNodeStyleSetHeightPercent(node, heightPercent);
}

void View::setWidthAuto() {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetWidthAuto(node);
}

void View::setHeightAuto() {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetHeightAuto(node);
}

void View::setAlignSelf(YGAlign align) {
    SkASSERT(node);
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetAlignSelf(node, align);
}

#pragma mark skia

void View::setBackgroundColor(SkColor color) {
    SkASSERT(paint);
    paint->setColor(color);
}

void View::setAntiAlias(bool antiAlias) {
    SkASSERT(paint);
    paint->setAntiAlias(antiAlias);
}

void View::setStyle(SkPaint::Style style) {
    SkASSERT(paint);
    paint->setStyle(style);
}

void View::setCornerRadius(float radius) {
    SkASSERT(paint);
    if (radius <= 0.0) {
        ALOGE("radius must > 0.0")
        return;
    }
    paint->setPathEffect(SkCornerPathEffect::Make(radius));
}

void View::setStrokeWidth(SkScalar _width) {
    SkASSERT(paint);
    if (_width < 0.0f) {
        ALOGE("width must > 0.0")
        return;
    }
    paint->setStrokeWidth(_width);
}

