//
// Created by DZSB-000848 on 1/26/22.
//

#include "TextView.h"

#include <utility>
#include <base/native_log.h>
#include "core/SkFont.h"

TextView::TextView() : View() {
    textPaint = new SkPaint();
    textPaint->setAntiAlias(true);
    textRect = SkRect::MakeEmpty();
    ellipsisStr = SkString('...');
    defaultStyle = std::make_unique<skia::textlayout::TextStyle>();
    fontCollection = sk_make_sp<skia::textlayout::FontCollection>();
    fontCollection->setDefaultFontManager(SkFontMgr::RefDefault());
}

TextView::~TextView() {
    delete textPaint;
//    ALOGD("~View TextView")
}

const char *TextView::name() {
    return "TextView";
}

void TextView::setText(SkString text) {
    this->text = std::move(text);
}

SkString TextView::getText() {
    return text;
}

void TextView::setTextColor(SkColor color) {
    SkASSERT(textPaint);
    textPaint->setColor(color);
    defaultStyle->setForegroundColor(*textPaint);
    defaultStyle->setBackgroundColor(*textPaint);
}

void TextView::setAlpha(float alpha) {
    View::setAlpha(alpha);
    textPaint->setAlphaf(alpha);
}

void TextView::measure(int widthMeasureSpec, int heightMeasureSpec) {
    if (text.isEmpty()) {
        setMeasuredDimension(0, 0);
        return;
    }
    auto length = font.measureText(static_cast<const void *>(text.c_str()), strlen(text.c_str()),
                                   SkTextEncoding::kUTF8,
                                   &textRect, textPaint);
    if (layoutParams->_widthMode == EXACTLY && layoutParams->_heightMode == EXACTLY) {
        auto ellipsisStrLength = font.measureText(static_cast<const void *>(ellipsisStr.c_str()), 3,
                                                  SkTextEncoding::kUTF8,
                                                  nullptr, textPaint);
        if (layoutParams->_width < length) {
            textVector.clear();
            //todo LineBreak
        }
        setMeasuredDimension(layoutParams->_width, layoutParams->_height);
        return;
    }
    setMeasuredDimension(static_cast<int>(length), static_cast<int>(font.getSpacing()));
}

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
    //y是基线的位置
    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
                           skRect.top() + textRect.height(), font, *textPaint);
    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
                           skRect.top() + textRect.height() * 2, font, *textPaint);

//    skia::textlayout::ParagraphStyle paraStyle;
//    paraStyle.setTextStyle(*defaultStyle);
//    delete paragraphBuilder;
//    paragraphBuilder = new skia::textlayout::ParagraphBuilderImpl(paraStyle, fontCollection);
//    paragraphBuilder->addText(text.c_str());
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
    defaultStyle->setFontSize(textSize);
}

void TextView::performLineBreak() {
    auto start = 0;

}
