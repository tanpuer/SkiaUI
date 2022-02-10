//
// Created by DZSB-000848 on 1/26/22.
//

#ifndef SKIAUI_TEXTVIEW_H
#define SKIAUI_TEXTVIEW_H


#include "View.h"
#include "string"
#include "core/SkFont.h"

class TextView : public View {

public:

    TextView();

    virtual ~TextView();

    virtual void measure(float _width, YGMeasureMode widthMode, float _height,
                 YGMeasureMode heightMode) override;

    virtual void draw(SkCanvas *canvas) override;

#pragma mark TextView api

    virtual void setText(SkString text);

    virtual SkString getText();

    virtual void setTextColor(SkColor color);

    virtual void setTextSize(SkScalar textSize);

    SkPaint *textPaint;

private:

    SkString text;

    SkFont font;

    SkRect rect;

};


#endif //SKIAUI_TEXTVIEW_H
