//
// Created by ByteDance on 2022/8/5.
//

#include <core/SkPath.h>
#include "ProgressBar.h"
#include "effects/SkGradientShader.h"

ProgressBar::ProgressBar() : View(), progressRect(SkRect::MakeEmpty()) {
    paint->setStroke(true);
}

ProgressBar::~ProgressBar() = default;

void ProgressBar::setBarColor(SkColor color) {
    this->progressColor = color;
}

void ProgressBar::setGradientBarColor(SkColor colors[], int size) {
//    paint->setShader(SkGradientShader::MakeSweep(0, 0, colors, nullptr, size));
}

void ProgressBar::setBackgroundColor(SkColor color) {
    this->backgroundColor = color;
}

void ProgressBar::measure(int widthMeasureSpec, int heightMeasureSpec) {
    View::measure(widthMeasureSpec, heightMeasureSpec);
}

void ProgressBar::layout(int l, int t, int r, int b) {
    View::layout(l, t, r, b);
    auto diff = width * 0.2;
    progressRect.setLTRB(l + diff, t + diff, r - diff, b - diff);
}

void ProgressBar::draw(SkCanvas *canvas) {
    index += 3;
    if (index > 360) {
        index = 0;
    }
    if (backgroundColor != SK_ColorTRANSPARENT) {
        paint->setColor(backgroundColor);
        canvas->drawArc(progressRect, 0.0, 360, false, *paint);
    }
    paint->setColor(progressColor);
    canvas->drawArc(progressRect, 0.0, index, false, *paint);
}
