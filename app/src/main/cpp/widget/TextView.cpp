//
// Created by DZSB-000848 on 1/26/22.
//

#include "TextView.h"

#include <utility>

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

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
    canvas->drawString(text, YGNodeLayoutGetLeft(node), YGNodeLayoutGetTop(node), font, *textPaint);
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
}
