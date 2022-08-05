//
// Created by ByteDance on 2022/8/5.
//

#include <core/SkPath.h>
#include "ProgressBar.h"

ProgressBar::ProgressBar() {
    progressRect = SkRect::MakeEmpty();
}

ProgressBar::~ProgressBar() = default;

void ProgressBar::setBarColor(SkColor color) {
    paint->setColor(color);
}

void ProgressBar::setGradientBarColor(SkColor startColor, SkColor endColor) {

}

void ProgressBar::setBackgroundColor(SkColor color) {
    View::setBackgroundColor(color);
}

void ProgressBar::draw(SkCanvas *canvas) {
    SkPath path;
    path.addArc(progressRect, 0.0, 135.0);
    canvas->drawArc(progressRect, 0.0, 180.0, true, *paint);
    canvas->drawPath(path, *paint);
//    View::draw(canvas);
}

void ProgressBar::layout(int l, int t, int r, int b) {
    View::layout(l, t, r, b);
    progressRect.setLTRB(l, t, r, b);
}
