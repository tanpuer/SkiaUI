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

void TextView::measure() {
    //todo
    auto length = font.measureText(static_cast<const void *>(text.c_str()), strlen(text.c_str()),
                                   SkTextEncoding::kUTF8,
                                   nullptr);
    auto height = font.getSize();
    YGNodeStyleSetWidth(node, length);
    YGNodeStyleSetHeight(node, height);
//    ALOGD("TextView measure %f %f %f %f %f %f", length, height, YGNodeLayoutGetLeft(node),
//          YGNodeLayoutGetTop(node), YGNodeLayoutGetWidth(node), YGNodeLayoutGetHeight(node))
}

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
    canvas->drawString(text, YGNodeLayoutGetLeft(node),
                       YGNodeLayoutGetTop(node) + YGNodeLayoutGetHeight(node), font,
                       *textPaint);
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
}
