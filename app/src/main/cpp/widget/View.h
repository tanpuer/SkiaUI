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

static int64_t VIEW_ID = 0;

class View {

public:

    View();

    virtual ~View();

    int64_t viewId;

#pragma mark yoga 设置相关

    virtual void
    measure(float _width, YGMeasureMode widthMode, float _height, YGMeasureMode heightMode);

    virtual void setMeasuredDimension(float _measuredWidth, float _measuredHeight);

    virtual void layout(float l, float t, float r, float b);

    virtual void draw(SkCanvas *canvas);

    virtual void setMargins(std::array<float, 4> margins);

    virtual void setMargins(float margin);

    virtual void setPadding(std::array<float, 4> paddings);

    virtual void setPadding(float padding);

    /**
     * 强制指定view的大小，同时mode会被设置成为exactly模式
     * @param _availableWidth
     * @param _availableHeight
     */
    virtual void setSize(float _availableWidth, float _availableHeight);

    /**
     * 设置百分比布局，同时mode会被设置成exactly模式
     * @param widthPercent
     * @param heightPercent
     */
    virtual void setSizePercent(float widthPercent, float heightPercent);

    virtual void setWidthAuto();

    virtual void setHeightAuto();

    virtual bool isViewGroup();

    virtual float setDefaultSize(float size, YGMeasureMode mode);

    /**
     * 在AlignItems的基础上自定义每个子视图的对齐方式
     * @param align
     */
    virtual void setAlignSelf(YGAlign align);

    YGNodeRef node;

protected:

    float width, height;

    YGMeasureMode widthMeasureMode, heightMeasureMode;

    float measuredWidth, measuredHeight;

    float minWidth, minHeight;

private:

    static float getDefaultSize(float _width, YGMeasureMode mode, float minSize);

#pragma mark yoga 获取相关

public:

    virtual float getHeight();

    virtual float getWidth();

    float marginLeft, marginTop, marginRight, marginBottom;

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

};

#endif //SKIAUI_VIEW_H
