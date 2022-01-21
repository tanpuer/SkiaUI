//
// Created by cw on 2021/3/12.
//

#ifndef HYEDITOR_TEMPLEEGLCONTEXT_H
#define HYEDITOR_TEMPLEEGLCONTEXT_H


#include <Looper.h>
#include "HYEGLRender.h"

class HYEGLContext : public Looper {

public:
    enum TempleMsg {
        kMsgTempleInit,
        kMsgTempleUnInit,
        kMsgSurfaceOnCreate,
        kMsgSurfaceSizeChanged,
        kMsgSurfaceOnDestroy,
        kMsgDoFrame
    };

public:

    HYEGLContext(JavaVM *javaVm);

    ~HYEGLContext() override;

    void handleMessage(LooperMessage *msg) override;

    void pthreadExit() override;

private:

    HYEGLRender *render;

};


#endif //HYEDITOR_TEMPLEEGLCONTEXT_H
