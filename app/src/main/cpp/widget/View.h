//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_VIEW_H
#define SKIAUI_VIEW_H

#include <cstdint>
#include <yoga/Yoga.h>
#include "array"
#include "memory"
#include "core/SkPaint.h"
#include "core/SkCanvas.h"
#include "core/SkRRect.h"
#include "LayoutParams.h"

static int64_t VIEW_ID = 0;

class View {

public:

    View();

    virtual ~View();

    int64_t viewId;

#pragma mark yoga 设置相关

    /**
     * 任何组件都可以复写，计算完宽高后必须调用setMeasuredDimension，包括ViewGroup及其子类
     * @param widthMeasureSpec
     * @param heightMeasureSpec
     */
    virtual void measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec);

    virtual void setMeasuredDimension(float _measuredWidth, float _measuredHeight);

    virtual void layout(float l, float t, float r, float b);

    virtual void draw(SkCanvas *canvas);

    virtual bool isViewGroup();

    /**
     * 在AlignItems的基础上自定义每个子视图的对齐方式
     * @param align
     */
    virtual void setAlignSelf(YGAlign align);

    YGNodeRef node;

protected:

    float width, height;

    float minWidth, minHeight;

private:

    static float getDefaultSize(float minSize, MeasureSpec *measureSpec);

#pragma mark LayoutParams相关
public:

    std::unique_ptr<LayoutParams> layoutParams;

    virtual void setLayoutParams(LayoutParams *layoutParams);

    virtual LayoutParams *getLayoutParams();

#pragma mark yoga 获取相关

public:

    virtual float getHeight();

    virtual float getWidth();

#pragma mark skia

    virtual void setBackgroundColor(SkColor color);

    virtual void setAntiAlias(bool antiAlias);

    virtual void setStyle(SkPaint::Style style);

    virtual void setStrokeWidth(SkScalar _width);

    virtual void setCornerRadius(float radius);

    SkPaint *paint;

    std::array<int, 4> cornerRadius;

protected:
    SkRect skRect;

    SkRect skRectWithBorder;


public:
    //todo 后续才支持的
    virtual void setPadding(std::array<float, 4> paddings);

    virtual void setPadding(float padding);

    virtual void setSizePercent(float widthPercent, float heightPercent);

    virtual void setWidthAuto();

    virtual void setHeightAuto();

};

#endif //SKIAUI_VIEW_H
