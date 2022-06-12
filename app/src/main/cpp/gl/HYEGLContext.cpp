//
// Created by cw on 2021/3/12.
//

#include "HYEGLContext.h"
#include "native_log.h"

HYEGLContext::HYEGLContext(JavaVM *javaVm) : Looper(javaVm) {
}

HYEGLContext::~HYEGLContext() {

}

void HYEGLContext::handleMessage(Looper::LooperMessage *msg) {
    switch (msg->what) {
        case kMsgTempleInit: {
            render = new HYEGLRender(env);
            break;
        }
        case kMsgTempleUnInit: {
            delete render;
            quit();
            break;
        }
        case kMsgSurfaceOnCreate: {
            render->OnSurfaceCreated(static_cast<ANativeWindow *>(msg->obj));
            break;
        }
        case kMsgSurfaceSizeChanged: {
            render->OnSurfaceChanged(msg->arg1, msg->arg2);
            break;
        }
        case kMsgDoFrame: {
            render->OnDoFrame(0L);
            break;
        }
        case kMsgSurfaceOnDestroy: {
            render->OnSurfaceDestroyed();
            break;
        }
        case kMsgTouchEvent: {
            render->DispatchTouchEvent(static_cast<TouchEvent *>(msg->obj));
            break;
        }
        default: {
            ALOGE("Unknown msg type, pls check %d", msg->what)
        }
    }
}

void HYEGLContext::pthreadExit() {
    Looper::pthreadExit();
}
