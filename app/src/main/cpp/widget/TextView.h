//
// Created by DZSB-000848 on 1/26/22.
//

#ifndef SKIAUI_TEXTVIEW_H
#define SKIAUI_TEXTVIEW_H


#include "View.h"
#include "string"
#include "core/SkFont.h"
#include "skparagraph/include/TextStyle.h"
#include "skparagraph/include/ParagraphBuilderImpl.h"
#include "skparagraph/include/ParagraphStyle.h"

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

    virtual void performLineBreak();

private:

    SkString text;

    SkFont font;

    SkRect textRect;

    SkString ellipsisStr;

    std::vector<SkString> textVector;

    std::unique_ptr<skia::textlayout::TextStyle> defaultStyle;

    skia::textlayout::ParagraphBuilderImpl *paragraphBuilder;

    sk_sp<skia::textlayout::FontCollection> fontCollection;

};


#endif //SKIAUI_TEXTVIEW_H
