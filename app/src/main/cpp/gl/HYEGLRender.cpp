//
// Created by cw on 2021/3/12.
//

#include <native_log.h>
#include "HYEGLRender.h"

HYEGLRender::~HYEGLRender() {
    ALOGD("TempleEGLRender delete")
}

int HYEGLRender::CreateGLEnv(ANativeWindow *nativeWindow) {
    int result = mEGLCore->createGLEnv(nullptr, nativeWindow, 0, 0, false);
    return result;
}

void HYEGLRender::ReleaseGLEnv() {
    mEGLCore->releaseGLEnv();
}

void HYEGLRender::OnSurfaceCreated(ANativeWindow *nativeWindow) {
    ALOGD("OnSurfaceCreated")
    CreateGLEnv(nativeWindow);
    if (mEGLCore->getEGLDisplay() == EGL_NO_DISPLAY) {
        return;
    }
    mEGLCore->makeCurrent();
    initFilter();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void HYEGLRender::OnSurfaceChanged(int width, int height) {
    ALOGD("OnSurfaceChanged glViewport %d %d", width, height)
    if (mEGLCore->getEGLDisplay() == EGL_NO_DISPLAY) {
        return;
    }
    glViewport(0, 0, width, height);
    if (mFilter != nullptr) {
        mFilter->setWindowSize(width, height);
    }
}

void HYEGLRender::OnSurfaceDestroyed() {
    ReleaseGLEnv();
}

void HYEGLRender::OnDoFrame(long frameTimeNanos) {
    if (mFilter != nullptr) {
        mFilter->doFrame();
    }
    mEGLCore->swapBuffer();
}

void HYEGLRender::initFilter() {
    mFilter = std::make_unique<SkiaFilter>();
}

void HYEGLRender::DispatchTouchEvent(TouchEvent *touchEvent) {
    if (mFilter != nullptr) {

    }
    delete touchEvent;
}
