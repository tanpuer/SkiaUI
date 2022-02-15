//
// Created by DZSB-000848 on 1/24/22.
//

#include <base/native_log.h>
#include <yoga/Utils.h>
#include "View.h"
#include "effects/SkCornerPathEffect.h"

View::View() : width(0.0), height(0.0), skRect(SkRect::MakeEmpty()), cornerRadius(),
               skRectWithBorder(SkRect::MakeEmpty()),
               minWidth(0), minHeight(0) {
    viewId = VIEW_ID++;
    paint = new SkPaint();
    paint->setAntiAlias(true);
    node = YGNodeNew();
    layoutParams = std::make_unique<LayoutParams>();
}

View::~View() {
    delete paint;
    if (node != nullptr) {
        YGNodeFree(node);
    }
}

#pragma mark yoga

void View::measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec) {
    //todo 目前每次都是forceLayout Android子类只能override onMeasure方法，精简处理
    setMeasuredDimension(getDefaultSize(minWidth, widthMeasureSpec),
                         getDefaultSize(minHeight, heightMeasureSpec));
}

void View::setMeasuredDimension(float _measuredWidth, float _measuredHeight) {
    YGNodeStyleSetWidth(node, _measuredWidth);
    YGNodeStyleSetHeight(node, _measuredHeight);
}

float View::getDefaultSize(float minSize, MeasureSpec *measureSpec) {
    float result = minSize;
    switch (measureSpec->getMode()) {
        case YGMeasureModeUndefined: {
            result = minSize;
            break;
        }
        case YGMeasureModeAtMost:
        case YGMeasureModeExactly: {
            result = measureSpec->getSize();
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

void View::layout(float l, float t, float r, float b) {
    //todo 默认设置boarder位置 Android layout默认啥都不做
    skRect.setLTRB(l, t, r, b);
    width = r - l;
    height = b - t;
}

void View::draw(SkCanvas *canvas) {
    //todo 默认画boarder，Android的onDraw默认啥都不做
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

#pragma mark yoga 获取相关

float View::getHeight() {
    return height;
}

float View::getWidth() {
    return width;
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

#pragma LayoutParams相关

void View::setLayoutParams(LayoutParams *_layoutParams) {
    layoutParams = std::unique_ptr<LayoutParams>(_layoutParams);
    YGNodeStyleSetMargin(node, YGEdgeLeft, layoutParams->_marginLeft);
    YGNodeStyleSetMargin(node, YGEdgeTop, layoutParams->_marginTop);
    YGNodeStyleSetMargin(node, YGEdgeRight, layoutParams->_marginRight);
    YGNodeStyleSetMargin(node, YGEdgeBottom, layoutParams->_marginBottom);
}

LayoutParams *View::getLayoutParams() {
    return layoutParams.get();
}

#pragma mark 后续才支持的

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

