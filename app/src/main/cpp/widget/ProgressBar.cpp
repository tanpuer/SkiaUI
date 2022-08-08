//
// Created by ByteDance on 2022/8/5.
//

#include <core/SkPath.h>
#include "ProgressBar.h"
#include "effects/SkGradientShader.h"

ProgressBar::ProgressBar()
        : View(), progressRect(SkRect::MakeEmpty()), autoMode(true), progress(0), index(0),
          type(ProgressBarType::CIRCLE) {
    paint->setStroke(true);
}

ProgressBar::~ProgressBar() = default;

void ProgressBar::setBarColor(SkColor color) {
    this->progressColor = color;
}

void ProgressBar::setGradientBarColor(SkColor colors[], int size) {
    //todo 滑动的时候centerX，centerY一直在变化，需要不停更新shader，因此gradient还是适合非滑动页面
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
    if (type == ProgressBarType::CIRCLE) {
        auto diff = width * 0.2;
        progressRect.setLTRB(l + diff, t + diff, r - diff, b - diff);
    } else if (type == ProgressBarType::LINEAR) {
        progressRect.setLTRB(l + marginLeft, t, r - marginRight, b);
    }
}

void ProgressBar::draw(SkCanvas *canvas) {
    if (type == ProgressBarType::CIRCLE) {
        if (autoMode) {
            index += 3;
            if (index > 360) {
                index = 0;
            }
        } else {
            index = progress * 360 / 100;
        }
        if (backgroundColor != SK_ColorTRANSPARENT) {
            paint->setColor(backgroundColor);
            canvas->drawArc(progressRect, 0.0, 360, false, *paint);
        }
        paint->setColor(progressColor);
        canvas->drawArc(progressRect, 0.0, index, false, *paint);
    } else if (type == ProgressBarType::LINEAR) {
        if (autoMode) {
            progress += 1;
            if (progress > 100) {
                progress = 0;
            }
        }
        paint->setStyle(SkPaint::kFill_Style);
        if (backgroundColor != SK_ColorTRANSPARENT) {
            paint->setColor(backgroundColor);
            canvas->drawRoundRect(progressRect, height / 2, height / 2, *paint);
        }
        paint->setColor(progressColor);
        progressRect.setLTRB(progressRect.left(), progressRect.top(),
                             progressRect.right() * progress / 100,
                             progressRect.bottom());
        canvas->drawRoundRect(progressRect, height / 2, height / 2, *paint);
        canvas->drawCircle(progressRect.right(), progressRect.centerY(), height, *paint);
    }
}

void ProgressBar::setProgress(int progress) {
    SkASSERT(progress <= 100 && progress >= 0);
    this->progress = progress;
    isDirty = true;
}

void ProgressBar::setAutoMode(bool autoMode) {
    this->autoMode = autoMode;
    isDirty = true;
}

void ProgressBar::setType(ProgressBar::ProgressBarType type) {
    this->type = type;
    isDirty = true;
}
