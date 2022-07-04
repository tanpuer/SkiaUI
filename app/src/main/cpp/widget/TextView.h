//
// Created by DZSB-000848 on 1/26/22.
//

#ifndef SKIAUI_TEXTVIEW_H
#define SKIAUI_TEXTVIEW_H


#include "View.h"
#include "string"
#include "core/SkFont.h"
#include "core/SkTextBlob.h"

class TextView : public View {

public:

    TextView();

    virtual ~TextView();

    void measure(int widthMeasureSpec, int heightMeasureSpec) override;

    virtual void draw(SkCanvas *canvas) override;

    const char * name() override;

#pragma mark TextView api

    virtual void setText(SkString text);

    virtual SkString getText();

    virtual void setTextColor(SkColor color);

    virtual void setTextSize(SkScalar textSize);

    SkPaint *textPaint;

    virtual void setAlpha(float alpha) override;

private:

    SkString text;

    SkFont font;

    SkRect textRect;

    sk_sp<SkTextBlob> textBlob;

};


#endif //SKIAUI_TEXTVIEW_H
