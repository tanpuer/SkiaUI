//
// Created by DZSB-000848 on 1/26/22.
//

#include <base/native_log.h>
#include "ImageView.h"
#include "core/SkData.h"
#include "core/SkImage.h"

ImageView::ImageView() : View() {

}

ImageView::~ImageView() {

}

void ImageView::setSource(const char *path) {
    auto data = SkData::MakeFromFileName(path);
    assert(data);
    skImage = SkImage::MakeFromEncoded(data);
}

void ImageView::measure(MeasureSpec *widthMeasureSpec, MeasureSpec *heightMeasureSpec) {
    if (skImage == nullptr) {
        YGNodeStyleSetWidth(node, 0);
        YGNodeStyleSetHeight(node, 0);
        return;
    }
    ALOGD("imageView size: %d %d", skImage->width(), skImage->height())
    setMeasuredDimension(static_cast<float >(skImage->width()),
                         static_cast<float >(skImage->height()));
}

void ImageView::draw(SkCanvas *canvas) {
    canvas->drawImage(skImage, skRect.left(), skRect.top(), SkSamplingOptions(), nullptr);
    View::draw(canvas);
}

void ImageView::layout(float l, float t, float r, float b) {
    ALOGD("imageView layout: %f %f %f %f", l, t, r, b)
    View::layout(l, t, r, b);
}


