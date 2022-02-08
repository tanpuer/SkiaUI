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

    //todo test code

    LinearLayout _root;
    _root.setSize(f_width, f_height);
    _root.setFlexWrap(YGWrapWrap);
    _root.setOrientation(LinearLayout::Orientation::VERTICAL);
    _root.setJustifyContent(YGJustifyCenter);
    _root.setAlignItems(YGAlignCenter);

    {
        auto vp1 = new LinearLayout();
        vp1->setSize(f_width, 0);
        vp1->setHeightAuto();
        vp1->setFlexWrap(YGWrapWrap);
        vp1->setOrientation(LinearLayout::Orientation::HORIZONTAL);
        vp1->setJustifyContent(YGJustifyCenter);
        vp1->setAlignItems(YGAlignFlexStart);
        auto view = new View();
        view->setBackgroundColor(SK_ColorRED);
        view->setStyle(SkPaint::kFill_Style);
        view->setSize(300, 200);
        view->setMargins({static_cast<float >(drawCount), 0, 0, 0});
        view->setCornerRadius(30);
        vp1->addView(view);

        auto textView = new TextView();
        textView->setText(SkString("Hello World"));
        textView->setTextColor(SK_ColorBLACK);
        textView->setTextSize(60);
        textView->setMargins(50);
        textView->setBackgroundColor(SK_ColorRED);
        textView->setStyle(SkPaint::kStroke_Style);
//    textView->setAlignSelf(YGAlignFlexEnd);
        vp1->addView(textView);

        auto imageView = new ImageView();
        imageView->setSource("/sdcard/cowboy.png");
        imageView->setCornerRadius(30);
        imageView->setStyle(SkPaint::kStroke_Style);
        imageView->setBackgroundColor(SK_ColorRED);
        imageView->setStrokeWidth(10);
        vp1->addView(imageView);

        _root.addView(vp1);
    }

    {
        auto vp1 = new LinearLayout();
        vp1->setSize(f_width, 0);
        vp1->setHeightAuto();
        vp1->setFlexWrap(YGWrapWrap);
        vp1->setOrientation(LinearLayout::Orientation::HORIZONTAL);
        vp1->setJustifyContent(YGJustifyCenter);
        vp1->setAlignItems(YGAlignCenter);
        auto view = new View();
        view->setBackgroundColor(SK_ColorBLUE);
        view->setStyle(SkPaint::kFill_Style);
        view->setSize(300, 200);
        view->setMargins({static_cast<float >(drawCount), 0, 0, 0});
        view->setCornerRadius(30);
        vp1->addView(view);

        auto textView = new TextView();
        textView->setText(SkString("Hello World"));
        textView->setTextColor(SK_ColorBLACK);
        textView->setTextSize(60);
        textView->setMargins(50);
        textView->setBackgroundColor(SK_ColorBLUE);
        textView->setStyle(SkPaint::kStroke_Style);
//    textView->setAlignSelf(YGAlignFlexEnd);
        vp1->addView(textView);

        auto imageView = new ImageView();
        imageView->setSource("/sdcard/cowboy.png");
        imageView->setCornerRadius(30);
        imageView->setStyle(SkPaint::kStroke_Style);
        imageView->setBackgroundColor(SK_ColorBLUE);
        imageView->setStrokeWidth(10);
        vp1->addView(imageView);

        _root.addView(vp1);
    }

    _root.measure();
    _root.layout(0, 0, f_width, f_height);
    _root.draw(skCanvas);

    skCanvas->flush();
}
