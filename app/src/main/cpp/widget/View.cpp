//
// Created by DZSB-000848 on 1/24/22.
//

#include <base/native_log.h>
#include <yoga/Utils.h>
#include "View.h"
#include "effects/SkCornerPathEffect.h"

View::View() : width(0.0), height(0.0), skRect(SkRect::MakeEmpty()), cornerRadius(),
               availableHeight(0.0), availableWidth(0.0), marginLeft(0.0), marginTop(0.0),
               marginRight(0.0), marginBottom(0.0), skRectWithBorder(SkRect::MakeEmpty()),
               widthMeasureMode(YGMeasureModeUndefined), heightMeasureMode(YGMeasureModeExactly) {
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

void View::measure(float _width, YGMeasureMode widthMode, float _height, YGMeasureMode heightMode) {
    this->availableWidth = _width;
    this->availableHeight = _height;
    if (widthMode == YGMeasureModeExactly && heightMode == YGMeasureModeExactly) {
        YGNodeStyleSetHeight(node, _width);
        YGNodeStyleSetWidth(node, _height);
        return;
    }
    //todo 类似于Android的measure方法，由parent的measureMode和自身的measureMode共同决定

}

void View::setMeasuredDimension(float _width, float _height) {

}

void View::layout(float l, float t, float r, float b) {
    skRect.setLTRB(l, t, r, b);
    width = r - l;
    height = b - t;
}

void View::draw(SkCanvas *canvas) {
    if (YGFloatsEqual(paint->getStrokeWidth(), 0.0f)) {
        canvas->drawRect(skRect, *paint);
    } else {
        //todo 如果有strokeWidth，就会有一半画在rect外面，简单考虑，默认全部都算内边框
        auto diff = (paint->getStrokeWidth()) / 2;
        skRectWithBorder.setLTRB(skRect.left() + diff, skRect.top() + diff, skRect.right() - diff,
                                 skRect.bottom() - diff);
        canvas->drawRect(skRectWithBorder, *paint);
    }
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
    marginLeft = margins[0];
    marginTop = margins[1];
    marginRight = margins[2];
    marginBottom = margins[3];
}


void View::setMargins(float margin) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetMargin(node, YGEdgeAll, margin);
    marginLeft = marginTop = marginRight = marginBottom = margin;
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

bool View::isViewGroup() {
    return false;
}

float View::setDefaultSize(float size, YGMeasureMode mode) {
    switch (mode) {
        case YGMeasureModeExactly: {
            return size;
        }
        case YGMeasureModeAtMost: {

        }
        case YGMeasureModeUndefined: {

        }
        default: {
            return size;
        }
    }
}

#pragma mark yoga 获取相关

float View::getHeight() {
//    ALOGD("view getHeight value is: %f", height)
    return height;
}

float View::getWidth() {
//    ALOGD("view getWidth value is: %f", width)
    return width;
}

float View::getMarginLeft() {
    return marginLeft;
}

float View::getMarginTop() {
    return marginTop;
}

float View::getMarginRight() {
    return marginRight;
}

float View::getMarginBottom() {
    return marginBottom;
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

