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

    virtual void setGradientBarColor(SkColor colors[], int size);

    virtual void setBackgroundColor(SkColor color) override;

    virtual void draw(SkCanvas *canvas) override;

    void measure(int widthMeasureSpec, int heightMeasureSpec) override;

    virtual void layout(int l, int t, int r, int b) override;

protected:

    SkRect progressRect;

private:

    int index;

    SkColor backgroundColor = SK_ColorTRANSPARENT;

    SkColor progressColor = SK_ColorTRANSPARENT;

};


#endif //SKIAUI_PROGRESSBAR_H
