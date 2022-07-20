//
// Created by DZSB-000848 on 1/26/22.
//

#include "TextView.h"

#include <utility>
#include <base/native_log.h>
#include "core/SkFont.h"
#include "math.h"

TextView::TextView() : View(), maxLine(0) {
    textPaint = new SkPaint();
    textPaint->setAntiAlias(true);
    textRect = SkRect::MakeEmpty();
    defaultStyle = std::make_unique<TextStyle>();
    fontCollection = sk_make_sp<FontCollection>();
    fontCollection->setDefaultFontManager(SkFontMgr::RefDefault());
}

TextView::~TextView() {
    delete textPaint;
}

const char *TextView::name() {
    return "TextView";
}

void TextView::setText(SkString text) {
    this->text = std::move(text);
    isDirty = true;
}

SkString TextView::getText() {
    return text;
}

void TextView::setTextColor(SkColor color) {
    SkASSERT(textPaint);
    textPaint->setColor(color);
    defaultStyle->setColor(color);
    isDirty = true;
}

void TextView::setAlpha(float alpha) {
    View::setAlpha(alpha);
    textPaint->setAlphaf(alpha);
    auto color = textPaint->getColor();
    defaultStyle->setColor(SkColorSetARGB(alpha * 255, SkColorGetR(color), SkColorGetG(color),
                                          SkColorGetB(color)));
    isDirty = true;
}

void TextView::measure(int widthMeasureSpec, int heightMeasureSpec) {
    if (text.isEmpty()) {
        setMeasuredDimension(0, 0);
        return;
    }
    if (isDirty) {
        isDirty = false;
        skia::textlayout::ParagraphStyle paraStyle;
        paraStyle.setTextStyle(*defaultStyle);
        paraStyle.setTextAlign(TextAlign::kCenter);
        if (maxLine > 0) {
            paraStyle.setEllipsis(u"\u2026");
            paraStyle.setMaxLines(maxLine);
        }
        paragraphBuilder = std::make_unique<ParagraphBuilderImpl>(paraStyle, fontCollection);
        paragraphBuilder->addText(text.c_str());
        paragraph = paragraphBuilder->Build();
        auto width = 0.0f;
        auto height = 0.0f;
        //为了方便计算大小，最好强制制定TextView的宽度，否则默认用maxIntrinsicWidth
        if (layoutParams->_widthMode == EXACTLY) {
            width = static_cast<float >(layoutParams->_width);
            paragraph->layout(width);
        } else {
            paragraph->layout(SK_ScalarInfinity);
            width = paragraph->getMaxIntrinsicWidth() + 1;
            paragraph->layout(width);
        }
        auto spacing = font.getSpacing();
        if (layoutParams->_heightMode == EXACTLY) {
            // Parent has told us how big to be. So be it.
            height = static_cast<float >(layoutParams->_height);
            if (paragraph->getHeight() > layoutParams->_height) {
                setMaxLines(floor(layoutParams->_height / spacing));
                //当发现文字高度大于textview高度，更新maxLine，重新走measure方法
                measure(widthMeasureSpec, heightMeasureSpec);
                return;
            }
        } else {
            height = paragraph->getHeight();
        }
        setMeasuredDimension(static_cast<int>(width), static_cast<int>(height));
    }
}

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
    //y是基线的位置
//    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
//                           skRect.top() + textRect.height(), font, *textPaint);
//    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
//                           skRect.top() + textRect.height() * 2, font, *textPaint);
    SkASSERT(paragraph);
    paragraph->paint(canvas, skRect.left(), skRect.top());
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
    defaultStyle->setFontSize(textSize);
    isDirty = true;
}

void TextView::setMaxLines(int maxLine) {
    assert(maxLine > 0);
    this->maxLine = maxLine;
    isDirty = true;
}
