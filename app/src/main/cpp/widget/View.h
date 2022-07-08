//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_VIEW_H
#define SKIAUI_VIEW_H

#include <cstdint>
#include <yoga/Yoga.h>
#include <memory>
#include "array"
#include "memory"
#include "core/SkPaint.h"
#include "core/SkCanvas.h"
#include "core/SkRRect.h"
#include "LayoutParams.h"
#include "TouchEventDispatcher.h"
#include "IAnimator.h"

static int64_t VIEW_ID = 0;

class View {

public:

    View();

    virtual ~View();

    virtual const char *name() {
        return "view";
    }

    int64_t viewId;

    const char *parentName;

    int64_t parentId;

#pragma mark yoga 设置相关

    /**
     * 任何组件都可以复写，计算完宽高后必须调用setMeasuredDimension，包括ViewGroup及其子类
     * @param widthMeasureSpec
     * @param heightMeasureSpec
     */
    virtual void measure(int widthMeasureSpec, int heightMeasureSpec);

    /**
     * 作为View/TextView/ImageView 这种组件必须明确指出自己的宽高，ViewGroup根据子View的宽高和parent-ViewGroup的限制来设置自己的宽高
     * @param _measuredWidth
     * @param _measuredHeight
     */
    virtual void setMeasuredDimension(int _measuredWidth, int _measuredHeight);

    virtual void layout(int l, int t, int r, int b);

    virtual void draw(SkCanvas *canvas);

    virtual bool isViewGroup();

    void setConfig(YGConfigRef config);

    /**
     * 在AlignItems的基础上自定义每个子视图的对齐方式
     * @param align
     */
    virtual void setAlignSelf(YGAlign align);

    YGNodeRef node;

    YGConfigRef config;

protected:

    int width, height;

    int minWidth, minHeight;

protected:

    static int getDefaultSize(int minSize, int measureSpec);

#pragma mark LayoutParams相关
public:

    std::unique_ptr<LayoutParams> layoutParams;

    virtual void setLayoutParams(LayoutParams *layoutParams);

    virtual LayoutParams *getLayoutParams();

#pragma mark yoga 获取相关

public:

    virtual int getHeight();

    virtual int getWidth();

#pragma mark skia

    virtual void setBackgroundColor(SkColor color);

    virtual void setAntiAlias(bool antiAlias);

    virtual void setStyle(SkPaint::Style style);

    virtual void setStrokeWidth(SkScalar _width);

    virtual void setCornerRadius(int radius);

    virtual void setAlpha(float alpha);

    SkPaint *paint;

    std::array<int, 4> cornerRadius;

    int marginLeft, marginTop, marginRight, marginBottom;

protected:
    SkIRect skRect;

    SkIRect skRectWithBorder;

public:
    //todo 后续才支持的
    virtual void setPadding(std::array<int, 4> paddings);

    virtual void setPadding(int padding);

    virtual void setSizePercent(float widthPercent, float heightPercent);

    virtual void setWidthAuto();

    virtual void setHeightAuto();

#pragma mark TouchEvent

public:

    virtual bool onInterceptTouchEvent(TouchEvent *touchEvent);

    virtual bool onTouchEvent(TouchEvent *touchEvent);

    virtual void requestDisallowInterceptTouchEvent(bool disallowIntercept);

    virtual void setCustomTouchEventDispatcher(TouchEventDispatcher *touchEventDispatcher);

protected:

    std::unique_ptr<TouchEventDispatcher> touchEventDispatcher;

#pragma mark moving

protected:

    float translateX;
    float translateY;

#pragma mark Animator

protected:

    std::unique_ptr<IAnimator> animator;

    virtual void handleAnimation();

protected:

    bool isDirty;

};

#endif //SKIAUI_VIEW_H
