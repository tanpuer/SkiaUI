//
// Created by templechen on 2019/3/15.
//

#include <pthread.h>
#include "Looper.h"
#include "native_log.h"

Looper::Looper() {
    this->jvm = nullptr;
    initThread();
}

Looper::Looper(JavaVM *jvm) {
    this->jvm = jvm;
    initThread();
}

void Looper::initThread() {
    head = nullptr;
    sem_init(&headdataavailable, 0, 0);
    sem_init(&headwriteprotect, 0, 1);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&worker_thread, &attr, trampoline, this);
    running = true;
}

Looper::~Looper() {
    if (running) {
        quit();
    }
}

void Looper::sendMessage(int what) {
    sendMessage(what, 0, 0, nullptr);
}

void Looper::sendMessage(int what, void *obj) {
    sendMessage(what, 0, 0, obj);
}

void Looper::sendMessage(int what, int arg1, int arg2) {
    sendMessage(what, arg1, arg2, nullptr);
}

void Looper::sendMessage(int what, int arg1, int arg2, void *obj) {
    auto *msg = new LooperMessage();
    msg->what = what;
    msg->arg1 = arg1;
    msg->arg2 = arg2;
    msg->obj = obj;
    msg->quit = false;
    addMessage(msg);
}

void Looper::quit() {
    auto *msg = new LooperMessage();
    msg->what = quitMessage;
    msg->arg1 = 0;
    msg->arg2 = 0;
    msg->obj = nullptr;
    msg->quit = true;
    addMessage(msg);
    pthread_join(worker_thread, nullptr);
    sem_destroy(&headwriteprotect);
    sem_destroy(&headdataavailable);
    running = false;
}

void Looper::addMessage(Looper::LooperMessage *msg) {
    sem_wait(&headwriteprotect);
    if (head == nullptr) {
        head = msg;
    } else {
        LooperMessage *h = head;
        while (h->next != nullptr) {
            h = h->next;
        }
        h->next = msg;
    }
    sem_post(&headwriteprotect);
    sem_post(&headdataavailable);
}

void *Looper::trampoline(void *p) {
    Looper *looper = static_cast<Looper *>(p);
    if (looper->jvm != nullptr) {
        int res = looper->jvm->AttachCurrentThread(&(looper->env), nullptr);
        if (res == JNI_OK) {
            ALOGD("AttachCurrentThread success")
        } else {
            ALOGD("AttachCurrentThread fail")
        }
    }
    looper->loop();
    looper->pthreadExit();
    ALOGD("pthread exit");
    return nullptr;
}

void Looper::loop() {
    while (true) {
        sem_wait(&headdataavailable);
        sem_wait(&headwriteprotect);
        LooperMessage *msg = head;
        if (msg == nullptr) {
            sem_post(&headwriteprotect);
            continue;
        }
        head = msg->next;
        sem_post(&headwriteprotect);
        if (msg->quit) {
            delete msg;
            break;
        }
        handleMessage(msg);
        delete msg;
    }
}

void Looper::handleMessage(Looper::LooperMessage *msg) {

}

void Looper::pthreadExit() {
    if (jvm != nullptr) {
        int res = jvm->DetachCurrentThread();
        if (res == JNI_OK) {
            ALOGD("DetachCurrentThread success")
        } else {
            ALOGD("DetachCurrentThread fail")
        }
        env = nullptr;
    }
    delete this;
}
