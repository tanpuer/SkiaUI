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

static int64_t VIEW_ID = 0;

class View {

public:

    View();

    virtual ~View();

    int64_t viewId;

#pragma mark yoga

    virtual void measure();

    virtual void layout();

    virtual void draw(SkCanvas *canvas);

    virtual void invalidate();

    virtual void requestLayout();

    virtual void setMargins(std::array<float, 4> margins);

    virtual void setMargins(float margin);

    virtual void setPadding(std::array<float, 4> paddings);

    virtual void setPadding(float padding);

    virtual void setSize(float _availableWidth, float _availableHeight);

    virtual void setSizePercent(float widthPercent, float heightPercent);

    virtual void setWidthAuto();

    virtual void setHeightAuto();

    /**
     * 在AlignItems的基础上自定义每个子视图的对齐方式
     * @param align
     */
    virtual void setAlignSelf(YGAlign align);

    YGNodeRef node;

    int width, height;

    float availableWidth, availableHeight;

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

};

#endif //SKIAUI_VIEW_H
