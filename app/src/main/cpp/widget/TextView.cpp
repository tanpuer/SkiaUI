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
    ALOGD("888888 %f %f %f %f", textRect.width(), textRect.height(), length, font.getSpacing())
    if (layoutParams->_widthMode == EXACTLY && layoutParams->_heightMode == EXACTLY) {
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
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
}