//
// Created by cw on 1/24/22.
//

#include <base/native_log.h>
#include <yoga/Utils.h>
#include "View.h"
#include "effects/SkCornerPathEffect.h"

View::View() : width(0.0), height(0.0), skRect(SkIRect::MakeEmpty()), cornerRadius(),
               skRectWithBorder(SkIRect::MakeEmpty()),
               minWidth(0), minHeight(0),
               parentId(0),
               marginLeft(0), marginTop(0), marginRight(0), marginBottom(0),
               isDirty(false),
               widthPercent(0.0f), hwRatio(0.0f) {
    viewId = VIEW_ID++;
    paint = new SkPaint();
    paint->setAntiAlias(true);
    touchEventDispatcher = std::make_unique<TouchEventDispatcher>(this);
    animator = std::unique_ptr<IAnimator>(nullptr);
}

View::~View() {
    delete paint;
    if (node != nullptr) {
        YGNodeFree(node);
    }
}

#pragma mark yoga

/**
 * This is called to find out how big a view should be. The parent supplies constraint information in the width and height parameters.
The actual measurement work of a view is performed in onMeasure(int, int), called by this method. Therefore, only onMeasure(int, int) can and must be overridden by subclasses.
 * @param widthMeasureSpec
 * @param heightMeasureSpec
 */
void View::measure(int widthMeasureSpec, int heightMeasureSpec) {
    //todo 目前每次都是forceLayout Android子类只能override onMeasure方法，精简处理
    auto measuredWidth = getDefaultSize(minWidth, widthMeasureSpec);
    auto measuredHeight = getDefaultSize(minHeight, heightMeasureSpec);
    setMeasuredDimension(measuredWidth, measuredHeight);
//    ALOGD("setMeasuredDimension %s %d %d", name(), measuredWidth, measuredHeight)
}

void View::setMeasuredDimension(int _measuredWidth, int _measuredHeight) {
    width = _measuredWidth;
    height = _measuredHeight;
    YGNodeStyleSetWidth(node, _measuredWidth);
    YGNodeStyleSetHeight(node, _measuredHeight);
}

int View::getDefaultSize(int minSize, int measureSpec) {
    int result = minSize;
    switch (MeasureSpec::getMode(measureSpec)) {
        case UNSPECIFIED: {
            result = minSize;
            break;
        }
        case AT_MOST:
        case EXACTLY: {
            result = MeasureSpec::getSize(measureSpec);
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

void View::layout(int l, int t, int r, int b) {
    //todo 默认设置boarder位置 Android layout默认啥都不做
    skRect.setLTRB(l, t, r, b);
    width = r - l;
    height = b - t;
//    ALOGD("%s layout %d %d", name(), width, height)
}

void View::draw(SkCanvas *canvas) {
    //todo 默认画boarder，Android的onDraw默认啥都不做
    if (YGFloatsEqual(paint->getStrokeWidth(), 0.0f)) {
        canvas->drawIRect(skRect, *paint);
    } else {
        //todo 如果有strokeWidth，就会有一半画在rect外面，简单考虑，默认全部都算内边框
        auto diff = (paint->getStrokeWidth()) / 2;
        skRectWithBorder.setLTRB(skRect.left() + diff, skRect.top() + diff, skRect.right() - diff,
                                 skRect.bottom() - diff);
        //todo debug边框
        canvas->drawIRect(skRectWithBorder, *paint);
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

int View::getHeight() {
    return height;
}

int View::getWidth() {
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

void View::setCornerRadius(int radius) {
    SkASSERT(paint);
    if (radius <= 0) {
        ALOGE("radius must > 0")
        return;
    }
    paint->setPathEffect(SkCornerPathEffect::Make(static_cast<SkScalar>(radius)));
}

void View::setStrokeWidth(SkScalar _width) {
    SkASSERT(paint);
    if (_width < 0.0f) {
        ALOGE("width must > 0.0")
        return;
    }
    paint->setStrokeWidth(_width);
}

void View::setAlpha(float alpha) {
    SkASSERT(paint);
    paint->setAlphaf(alpha);
}

#pragma LayoutParams相关

void View::setLayoutParams(LayoutParams *_layoutParams) {
    this->marginLeft = _layoutParams->_marginLeft;
    this->marginTop = _layoutParams->_marginTop;
    this->marginRight = _layoutParams->_marginRight;
    this->marginBottom = _layoutParams->_marginBottom;
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

void View::setPadding(std::array<int, 4> paddings) {
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

void View::setPadding(int padding) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    YGNodeStyleSetPadding(node, YGEdgeAll, padding);
}

void View::setSizePercent(float widthPercent, float hwRatio) {
    YGAssert(node, "view is null, pls check");
    if (node == nullptr) {
        return;
    }
    this->widthPercent = widthPercent;
    this->hwRatio = hwRatio;
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

void View::setConfig(YGConfigRef config) {
    this->config = config;
    node = YGNodeNewWithConfig(config);
}

bool View::onInterceptTouchEvent(TouchEvent *touchEvent) {
    return touchEventDispatcher->onInterceptTouchEvent(touchEvent);
}

bool View::onTouchEvent(TouchEvent *touchEvent) {
    return touchEventDispatcher->onTouchEvent(touchEvent);
}

void View::requestDisallowInterceptTouchEvent(bool disallowIntercept) {
    touchEventDispatcher->requestDisallowInterceptTouchEvent(disallowIntercept);
}

void View::setCustomTouchEventDispatcher(TouchEventDispatcher *touchEventDispatcher) {
    ALOGD("setCustomTouchEventDispatcher")
    this->touchEventDispatcher = std::unique_ptr<TouchEventDispatcher>(touchEventDispatcher);
    this->touchEventDispatcher->setWeakView(this);
}

void View::handleAnimation() {
    if (animator != nullptr) {

    }
}

bool View::hasPercent() {
    return !YGFloatsEqual(0.0f, widthPercent) && YGFloatsEqual(0.0f, hwRatio);
}
