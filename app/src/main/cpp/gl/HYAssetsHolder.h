//
// Created by cw on 10/29/21.
//

#ifndef HYNDKPLAYER_HYASSETSHOLDER_H
#define HYNDKPLAYER_HYASSETSHOLDER_H

#endif //HYNDKPLAYER_HYASSETSHOLDER_H

#include "jni.h"

class HYAssetsHolder {

public:

    static HYAssetsHolder &get() {
        static HYAssetsHolder assetsHolder;
        return assetsHolder;
    }

    void setJVM(JavaVM *jvm) {
        this->javaVm = jvm;
    }

    void refJavaAssets(JNIEnv *env, jobject javaAssets) {
        this->javaAssets = javaAssets;
        javaAssetsRef = env->NewGlobalRef(javaAssets);
    }

    void unRefJavaAssets(JNIEnv *env) {
        env->DeleteGlobalRef(javaAssetsRef);
    }

    jobject getJavaAssets() {
        return javaAssetsRef;
    }

    JavaVM *javaVm;

private:

    HYAssetsHolder() {}

    HYAssetsHolder(const HYAssetsHolder &) = delete;

    HYAssetsHolder(const HYAssetsHolder &&) = delete;

    jobject javaAssets;

    jobject javaAssetsRef;

};