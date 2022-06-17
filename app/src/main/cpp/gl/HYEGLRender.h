//
// Created by cw on 2021/3/12.
//

#ifndef HYEDITOR_TEMPLEEGLRENDER_H
#define HYEDITOR_TEMPLEEGLRENDER_H

#include <jni.h>
#include "memory"
#include "HYEGLCore.h"
#include "HYAssetsHolder.h"
#include "SkiaFilter.h"
#include "TouchEvent.h"

class HYEGLRender {

public:

    HYEGLRender(JNIEnv *env) {
        mEGLCore = std::make_unique<HYEGLCore>();
    }

    ~HYEGLRender();

    void OnSurfaceCreated(ANativeWindow *nativeWindow);

    void OnSurfaceChanged(int width, int height);

    void OnSurfaceDestroyed();

    void OnDoFrame(long frameTimeNanos);

    void DispatchTouchEvent(TouchEvent *touchEvent);

private:

    int CreateGLEnv(ANativeWindow *nativeWindow);

    void ReleaseGLEnv();

    std::unique_ptr<HYEGLCore> mEGLCore;

    void initFilter();

    std::unique_ptr<SkiaFilter> mFilter;

};


#endif //HYEDITOR_TEMPLEEGLRENDER_H
