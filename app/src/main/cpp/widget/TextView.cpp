//
// Created by DZSB-000848 on 1/26/22.
//

#include "TextView.h"

#include <utility>
#include <base/native_log.h>

TextView::TextView() : View() {
    textPaint = new SkPaint();
    textPaint->setAntiAlias(true);
}

TextView::~TextView() {
    delete textPaint;
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

void TextView::measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec) {
    auto length = font.measureText(static_cast<const void *>(text.c_str()), strlen(text.c_str()),
                                   SkTextEncoding::kUTF8,
                                   &rect, textPaint);
    auto height = font.getSize();
    YGNodeStyleSetWidth(node, length);
    //todo 测量出来文字的高度感觉一直偏小
    YGNodeStyleSetHeight(node, rect.height() * 1.3f);
    //    ALOGD("TextView measure %f %f %f %f %f %f %f %f", length, height, YGNodeLayoutGetLeft(node),
//          YGNodeLayoutGetTop(node), YGNodeLayoutGetWidth(node), YGNodeLayoutGetHeight(node),
//          rect.width(), rect.height())
}

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
    canvas->drawString(text, skRect.left(), skRect.top() + rect.height(),
                       font, *textPaint);
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
}
