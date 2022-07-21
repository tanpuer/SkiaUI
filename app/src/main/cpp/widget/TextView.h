//
// Created by cw on 1/26/22.
//

#ifndef SKIAUI_TEXTVIEW_H
#define SKIAUI_TEXTVIEW_H


#include "View.h"
#include "string"
#include "core/SkFont.h"
#include "skparagraph/include/TextStyle.h"
#include "skparagraph/include/ParagraphBuilderImpl.h"
#include "skparagraph/include/ParagraphStyle.h"
#include "skparagraph/include/Paragraph.h"

using namespace skia::textlayout;

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

    virtual void setAlpha(float alpha) override;

    void setMaxLines(int maxLine);

    /**
     * 上/中/下 划线
     */
    void setDecoration(TextDecoration decoration);

    /**
     * 实线/虚线/波浪线/点
     */
    void setDecorationStyle(TextDecorationStyle style);

    void setDecorationColor(SkColor color);

    /**
     * decoration线条的粗度倍数
     */
    void setDecorationThicknessMultiplier(SkScalar m);

    /**
     * @param locale "en_US"
     */
    void setLocale(SkString locale);

    void addShadow(SkColor color, SkPoint offset, double blurSigma);

protected:

    SkString text;

    SkFont font;

    SkRect textRect;

    std::vector<SkString> textVector;

    std::unique_ptr<TextStyle> defaultStyle;

    std::unique_ptr<ParagraphBuilderImpl> paragraphBuilder;

    sk_sp<FontCollection> fontCollection;

    std::unique_ptr<Paragraph> paragraph;

    int maxLine;

    SkColor skColor;

};


#endif //SKIAUI_TEXTVIEW_H
