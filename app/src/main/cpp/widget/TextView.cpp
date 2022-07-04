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
    textBlob = nullptr;
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
    textBlob = SkTextBlob::MakeFromText(this->text.c_str(), strlen(this->text.c_str()), font, SkTextEncoding::kUTF8);
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
    if (layoutParams->_widthMode == EXACTLY && layoutParams->_heightMode == EXACTLY) {
        setMeasuredDimension(layoutParams->_width, layoutParams->_height);
        return;
    }
    auto length = font.measureText(static_cast<const void *>(text.c_str()), strlen(text.c_str()),
                                   SkTextEncoding::kUTF8,
                                   &textRect, textPaint);
    auto height = font.getSize();
    YGNodeStyleSetWidth(node, length);
    //todo 测量出来文字的高度感觉一直偏小，暂时*1，3处理，找到正确的文字高度测量方式
    setMeasuredDimension(static_cast<int>(length), static_cast<int>(height * 1.3));
}

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
//    canvas->drawString(text, skRect.left(), skRect.top() + skRect.height(), font, *textPaint);
    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
                           skRect.top() + textRect.height(), font, *textPaint);
//    canvas->drawTextBlob(textBlob, skRect.left(), skRect.top(), *textPaint);
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
}