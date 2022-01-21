//
// Created by DZSB-000848 on 1/21/22.
//

#ifndef SKIAUI_SKIAVIEWCONTEXT_H
#define SKIAUI_SKIAVIEWCONTEXT_H

#include <memory>
#include <gl/HYEGLContext.h>
#include "android/native_window_jni.h"

class SkiaViewContext {

public:

    SkiaViewContext(ANativeWindow *nativeWindow);

    ~SkiaViewContext();

    void sizeChanged(int width, int height);

    void doFrame();

private:

    HYEGLContext *glContext;

};


#endif //SKIAUI_SKIAVIEWCONTEXT_H
