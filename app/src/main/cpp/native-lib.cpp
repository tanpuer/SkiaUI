#include <jni.h>
#include <base/native_log.h>
#include <iterator>
#include "SkiaViewContext.h"
#include "android/native_window_jni.h"

const char *HYSkiaEngine = "com/temple/skiaui/HYSkiaEngine";

extern "C" JNIEXPORT jlong JNICALL
native_SurfaceCreated(JNIEnv *env, jobject instance, jobject javaSurface) {
    ALOGD("native_SurfaceCreated")
    auto skiaContext = new SkiaViewContext(ANativeWindow_fromSurface(env, javaSurface));
    return reinterpret_cast<jlong>(skiaContext);
}

extern "C" JNIEXPORT void JNICALL
native_SurfaceChanged(JNIEnv *env, jobject instance, jlong nativePtr, jint width, jint height) {
    ALOGD("native_SurfaceChanged")
    auto skiaContext = reinterpret_cast<SkiaViewContext *>(nativePtr);
    if (skiaContext == nullptr) {
        ALOGE("native_SurfaceChanged reinterpret_cast error")
        return;
    }
    skiaContext->sizeChanged(width, height);
}

extern "C" JNIEXPORT void JNICALL
native_SurfaceDestroyed(JNIEnv *env, jobject instance, jlong nativePtr) {
    ALOGD("native_SurfaceDestroyed")
    auto skiaContext = reinterpret_cast<SkiaViewContext *>(nativePtr);
    if (skiaContext == nullptr) {
        ALOGE("native_SurfaceDestroyed reinterpret_cast error")
        return;
    }
    delete skiaContext;
}

extern "C" JNIEXPORT void JNICALL
native_SurfaceDoFrame(JNIEnv *env, jobject instance, jlong nativePtr, jlong time) {
    auto skiaContext = reinterpret_cast<SkiaViewContext *>(nativePtr);
    if (skiaContext == nullptr) {
        ALOGE("native_SurfaceDestroyed reinterpret_cast error")
        return;
    }
    skiaContext->doFrame(time);
}

extern "C" JNIEXPORT void JNICALL
native_TouchEvent(JNIEnv *env, jobject instance, jlong nativePtr, jint action, jfloat x, jfloat y) {
    auto skiaContext = reinterpret_cast<SkiaViewContext *>(nativePtr);
    if (skiaContext == nullptr) {
        ALOGE("native_TouchEvent reinterpret_cast error")
        return;
    }
    auto touchEvent = new TouchEvent(static_cast<TouchEvent::MotionEvent>(action), x, y);
    skiaContext->dispatchTouchEvent(touchEvent);
    ALOGD("native_TouchEvent %d %f %f", action, x, y)
}

extern "C" JNIEXPORT void JNICALL
native_SetVelocity(JNIEnv *env, jobject instance, jlong nativePtr, jfloat x, jfloat y) {
    auto skiaContext = reinterpret_cast<SkiaViewContext *>(nativePtr);
    if (skiaContext == nullptr) {
        ALOGE("native_TouchEvent reinterpret_cast error")
        return;
    }
    skiaContext->setVelocity(x, y);
    ALOGD("native_SetVelocity %f %f", x, y)
}

static JNINativeMethod g_RenderMethods[] = {
        {"nativeSurfaceCreated",   "(Landroid/view/Surface;)J", (void *) native_SurfaceCreated},
        {"nativeSurfaceChanged",   "(JII)V",                    (void *) native_SurfaceChanged},
        {"nativeSurfaceDestroyed", "(J)V",                      (void *) native_SurfaceDestroyed},
        {"nativeSurfaceDoFrame",   "(JJ)V",                     (void *) native_SurfaceDoFrame},
        {"nativeTouchEvent",       "(JIFF)Z",                   (void *) native_TouchEvent},
        {"nativeSetVelocity",      "(JFF)V",                    (void *) native_SetVelocity}
};

static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *nativeMethods,
                                 int methodNum) {
    ALOGD("RegisterNativeMethods start %s", className)
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr) {
        ALOGD("RegisterNativeMethods fail clazz == null")
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, nativeMethods, methodNum) < 0) {
        ALOGD("RegisterNativeMethods fail")
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static void UnRegisterNativeMethods(JNIEnv *env, const char *className) {
    ALOGD("UnRegisterNativeMethods start")
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr) {
        ALOGD("UnRegisterNativeMethods fail clazz == null")
    }
    env->UnregisterNatives(clazz);
}

extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p) {
    JNIEnv *env = nullptr;
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    RegisterNativeMethods(env, HYSkiaEngine, g_RenderMethods, std::size(g_RenderMethods));
    return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p) {
    ALOGD("JNI_OnUnload")
    JNIEnv *env = nullptr;
    if (jvm->GetEnv((void **) env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    HYAssetsHolder::get().setJVM(jvm);
    UnRegisterNativeMethods(env, HYSkiaEngine);
}