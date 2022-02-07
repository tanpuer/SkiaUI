//
// Created by DZSB-000848 on 1/21/22.
//

#include <GLES3/gl3.h>
#include <base/native_log.h>
#include <yoga/Yoga.h>
#include <widget/ImageView.h>
#include "LinearLayout.h"
#include "TextView.h"
#include "SkiaFilter.h"
#include "core/SkGraphics.h"

SkiaFilter::SkiaFilter() : skCanvas(nullptr) {
    SkGraphics::Init();
}

SkiaFilter::~SkiaFilter() {
    if (skiaSurface != nullptr) {
        skiaSurface->unref();
    }
    if (skiaContext != nullptr) {
        skiaContext->unref();
    }
}

void SkiaFilter::setWindowSize(int width, int height) {
    this->width = width;
    this->height = height;
    this->f_width = static_cast<float >(width);
    this->f_height = static_cast<float >(height);
    auto backendInterface = GrGLMakeNativeInterface();
    skiaContext = GrDirectContext::MakeGL(backendInterface);
    SkASSERT(skiaContext);
    GLint buffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
    GLint stencil;
    glGetIntegerv(GL_STENCIL_BITS, &stencil);
    GLint samples;
    glGetIntegerv(GL_SAMPLES, &samples);
    auto maxSamples = skiaContext->maxSurfaceSampleCountForColorType(kRGBA_8888_SkColorType);
    if (samples > maxSamples)
        samples = maxSamples;
    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = buffer;
    fbInfo.fFormat = GL_RGBA8;
    auto _skRenderTarget = GrBackendRenderTarget(width, height, samples, stencil, fbInfo);
    skiaSurface = SkSurface::MakeFromBackendRenderTarget(
            skiaContext.get(),
            _skRenderTarget,
            kBottomLeft_GrSurfaceOrigin,
            kRGBA_8888_SkColorType,
            nullptr,
            nullptr);
    SkASSERT(skiaSurface);
    skCanvas = skiaSurface->getCanvas();
}

void SkiaFilter::doFrame() {
//    IFilter::doFrame();
    SkASSERT(skCanvas);
    skCanvas->clear(SK_ColorWHITE);

    LinearLayout root;
    root.setSize(f_width, f_height);
    root.setFlexDirection(YGFlexDirectionColumn);
    root.setAlignItems(YGAlignCenter);
    root.setJustifyContent(YGJustifyCenter);
    root.setFlexWrap(YGWrapWrap);
    auto view = new View();
    view->setBackgroundColor(SK_ColorRED);
    view->setStyle(SkPaint::kFill_Style);
    view->setSize(300, 200);
    view->setMargins({static_cast<float >(drawCount), 0, 0, 0});
    view->setCorner(30);
    root.addView(view);

    auto textView = new TextView();
    textView->setText(SkString("Hello World"));
    textView->setTextColor(SK_ColorBLACK);
    textView->setTextSize(60);
    textView->setMargins(50);
    textView->setBackgroundColor(SK_ColorRED);
    textView->setStyle(SkPaint::kStroke_Style);
//    textView->setAlignSelf(YGAlignFlexEnd);
    root.addView(textView);

    auto imageView = new ImageView();
    imageView->setSource("/sdcard/cowboy.png");
    imageView->setCorner(200);
    root.addView(imageView);

    root.measure();
    root.layout();
    root.draw(skCanvas);

    skCanvas->flush();
}
