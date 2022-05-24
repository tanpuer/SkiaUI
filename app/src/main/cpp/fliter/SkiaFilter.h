//
// Created by DZSB-000848 on 1/21/22.
//

#ifndef SKIAUI_SKIAFILTER_H
#define SKIAUI_SKIAFILTER_H


#include "IFilter.h"
#include "gpu/gl/GrGLInterface.h"
#include "gpu/GrDirectContext.h"
#include "core/SkSurface.h"
#include "core/SkCanvas.h"

class SkiaFilter : IFilter {

public:

    SkiaFilter();

    ~SkiaFilter();

    virtual void setWindowSize(int width, int height) override;

    virtual void doFrame() override;

private:

    sk_sp<SkSurface> skiaSurface;

    sk_sp<GrDirectContext> skiaContext;

    SkCanvas *skCanvas;
};


#endif //SKIAUI_SKIAFILTER_H
