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
    ALOGD("~View ImageView")
}

void ImageView::setSource(const char *path) {
    auto data = SkData::MakeFromFileName(path);
    skImage = SkImage::MakeFromEncoded(data);
    if (skImage == nullptr) {
        ALOGE("skImage is null, pls check %s", path)
    }
}

void ImageView::measure(int widthMeasureSpec, int heightMeasureSpec) {
    if (skImage == nullptr) {
        YGNodeStyleSetWidth(node, 0);
        YGNodeStyleSetHeight(node, 0);
        return;
    }
    ALOGD("imageView size: %d %d", skImage->width(), skImage->height())
    setMeasuredDimension(skImage->width(), skImage->height());
}

void ImageView::draw(SkCanvas *canvas) {
    canvas->drawImage(skImage, skRect.left(), skRect.top(), SkSamplingOptions(), nullptr);
    View::draw(canvas);
}

void ImageView::layout(int l, int t, int r, int b) {
    ALOGD("imageView layout: %d %d %d %d", l, t, r, b)
    View::layout(l, t, r, b);
}

const char *ImageView::name() {
    return "ImageView";
}


