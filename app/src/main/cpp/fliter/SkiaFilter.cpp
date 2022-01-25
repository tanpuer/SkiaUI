//
// Created by DZSB-000848 on 1/21/22.
//

#include <GLES3/gl3.h>
#include <base/native_log.h>
#include <yoga/Yoga.h>
#include "SkiaFilter.h"
#include "core/SkGraphics.h"
#include "core/SkFont.h"

SkiaFilter::SkiaFilter() {
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
    SkASSERT(skCanvas);
    skCanvas->clear(SK_ColorWHITE);

    YGConfigRef config = YGConfigNew();
    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
    YGNodeStyleSetPadding(root, YGEdgeAll, 20);
    YGNodeStyleSetMargin(root, YGEdgeAll, 20);

    {
        YGNodeRef view = YGNodeNew();
        YGNodeStyleSetWidth(view, 300);
        YGNodeStyleSetHeight(view, 200);
        YGNodeStyleSetAlignSelf(view, YGAlignCenter);
        YGNodeStyleSetFlexGrow(view, 0);
        YGNodeInsertChild(root, view, 0);
        YGNodeCalculateLayout(root, f_width, f_height, YGDirectionLTR);
        SkRect rect = SkRect::MakeXYWH(YGNodeLayoutGetLeft(view), YGNodeLayoutGetTop(view),
                                       YGNodeLayoutGetWidth(view), YGNodeLayoutGetHeight(view));
        auto paint = SkPaint();
        paint.setColor(SK_ColorRED);
        paint.setStyle(SkPaint::kFill_Style);
        skCanvas->drawRect(rect, paint);
    }

    {
        YGNodeRef textView = YGNodeNew();
        YGNodeStyleSetWidth(textView, 200);
        YGNodeStyleSetHeight(textView, 100);
        YGNodeStyleSetMargin(textView, YGEdgeLeft, 100);
        YGNodeStyleSetAlignSelf(textView, YGAlignCenter);
        YGNodeInsertChild(root, textView, 1);
        YGNodeCalculateLayout(root, f_width, f_height, YGDirectionLTR);
        auto textPaint = SkPaint();
        textPaint.setColor(SK_ColorBLACK);
        const char *text = "123";
        SkFont font;
        font.setSize(60);
        skCanvas->drawString(text, YGNodeLayoutGetLeft(textView), YGNodeLayoutGetTop(textView),
                             font, textPaint);
    }


    skCanvas->flush();
}
