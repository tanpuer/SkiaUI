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

    //todo test code

    LinearLayout _root;
    _root.setLayoutParams(LayoutParams::makeExactlyWidth(width));
    _root.setFlexWrap(YGWrapWrap);
    _root.setOrientation(LinearLayout::Orientation::HORIZONTAL);
    _root.setJustifyContent(YGJustifyCenter);
    _root.setAlignItems(YGAlignCenter);

    {
        auto view = new View();
        view->setBackgroundColor(SK_ColorRED);
        view->setStyle(SkPaint::kFill_Style);
        view->setCornerRadius(30);
        auto viewLayoutParams = LayoutParams::makeExactlyLayoutParams(300, 200);
        viewLayoutParams->setMargin({0, drawCount, 0, 0});
        _root.addView(view, viewLayoutParams);

        auto textView = new TextView();
        textView->setText(SkString("Hello World"));
        textView->setTextColor(SK_ColorBLACK);
        textView->setTextSize(60);
        textView->setBackgroundColor(SK_ColorRED);
        textView->setStyle(SkPaint::kStroke_Style);
//    textView->setAlignSelf(YGAlignFlexEnd);
        auto tvLayoutParams = LayoutParams::makeWrapContent(true, true);
        tvLayoutParams->setMargin(50);
        _root.addView(textView, tvLayoutParams);

        auto imageView = new ImageView();
        imageView->setSource("/sdcard/cowboy.png");
        imageView->setCornerRadius(30);
        imageView->setStyle(SkPaint::kStroke_Style);
        imageView->setBackgroundColor(SK_ColorRED);
        imageView->setStrokeWidth(10);
        _root.addView(imageView, LayoutParams::makeWrapContent(true, true));
    }

    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    _root.measure(rootWidthSpec, rootHeightSpec);
    _root.layout(0, 0, width, height);
    _root.draw(skCanvas);

    skCanvas->flush();
}
