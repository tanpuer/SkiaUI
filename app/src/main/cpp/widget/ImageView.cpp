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

void
ImageView::measure(float _width, YGMeasureMode widthMode, float _height, YGMeasureMode heightMode) {
    if (skImage == nullptr) {
        YGNodeStyleSetWidth(node, 0);
        YGNodeStyleSetHeight(node, 0);
        return;
    }
    ALOGD("imageView size: %d %d", skImage->width(), skImage->height())
    YGNodeStyleSetWidth(node, static_cast<float >(skImage->width()));
    YGNodeStyleSetHeight(node, static_cast<float >(skImage->height()));
}

void ImageView::draw(SkCanvas *canvas) {
    canvas->drawImage(skImage, skRect.left(), skRect.top(), SkSamplingOptions(), nullptr);
    View::draw(canvas);
}


