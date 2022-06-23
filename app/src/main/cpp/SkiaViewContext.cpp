//
// Created by DZSB-000848 on 1/21/22.
//

#include "SkiaViewContext.h"

SkiaViewContext::SkiaViewContext(ANativeWindow *nativeWindow) {
    glContext = new HYEGLContext(HYAssetsHolder::get().javaVm);
    glContext->sendMessage(glContext->kMsgTempleInit);
    glContext->sendMessage(glContext->kMsgSurfaceOnCreate, nativeWindow);
}

SkiaViewContext::~SkiaViewContext() {
    if (glContext != nullptr) {
        glContext->sendMessage(glContext->kMsgSurfaceOnDestroy);
    }
}

void SkiaViewContext::sizeChanged(int width, int height) {
    if (glContext != nullptr) {
        glContext->sendMessage(glContext->kMsgSurfaceSizeChanged, width, height);
    }
}

void SkiaViewContext::doFrame(long time) {
    if (glContext != nullptr) {
        glContext->sendMessage(glContext->kMsgDoFrame, (void *) time);
    }
}

void SkiaViewContext::dispatchTouchEvent(TouchEvent *touchEvent) {
    if (glContext != nullptr) {
        glContext->sendMessage(glContext->kMsgTouchEvent, touchEvent);
    }
}
