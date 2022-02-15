//
// Created by DZSB-000848 on 1/26/22.
//

#ifndef SKIAUI_IMAGEVIEW_H
#define SKIAUI_IMAGEVIEW_H


#include "View.h"

class ImageView : public View {

public:

    ImageView();

    virtual ~ImageView();

    void measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec) override;

    void layout(float l, float t, float r, float b) override;

    virtual void draw(SkCanvas *canvas) override;

#pragma mark ImageView api

    void setSource(const char *path);

    sk_sp<SkImage> skImage;

};


#endif //SKIAUI_IMAGEVIEW_H
