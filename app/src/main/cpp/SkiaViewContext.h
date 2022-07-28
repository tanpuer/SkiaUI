//
// Created by cw on 1/21/22.
//

#ifndef SKIAUI_SKIAVIEWCONTEXT_H
#define SKIAUI_SKIAVIEWCONTEXT_H

#include <memory>
#include <gl/HYEGLContext.h>
#include "android/native_window_jni.h"
#include "TouchEvent.h"

class SkiaViewContext {

public:

    SkiaViewContext(ANativeWindow *nativeWindow);

    ~SkiaViewContext();

    void sizeChanged(int width, int height);

    void doFrame(long time);

    void dispatchTouchEvent(TouchEvent *touchEvent);

    void setVelocity(float x, float y);

private:

    HYEGLContext *glContext;

};


#endif //SKIAUI_SKIAVIEWCONTEXT_H
