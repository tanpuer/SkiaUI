//
// Created by ByteDance on 2022/8/5.
//

#ifndef SKIAUI_PROGRESSBAR_H
#define SKIAUI_PROGRESSBAR_H


#include "View.h"

class ProgressBar : public View {

public:

    ProgressBar();

    virtual ~ProgressBar();

#pragma mark progressbar api

    virtual void setBarColor(SkColor color);

    virtual void setGradientBarColor(SkColor startColor, SkColor endColor);

    virtual void setBackgroundColor(SkColor color) override;

    virtual void draw(SkCanvas *canvas) override;

    virtual void layout(int l, int t, int r, int b) override;

protected:

    SkRect progressRect;

};


#endif //SKIAUI_PROGRESSBAR_H
