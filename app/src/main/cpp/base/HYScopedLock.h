//
// Created by cw on 10/21/21.
//

#ifndef HYNDKPLAYER_HYSCOPEDLOCK_H
#define HYNDKPLAYER_HYSCOPEDLOCK_H

#include "pthread.h"

class HYSyncLock {

public:

    HYSyncLock() {
        pthread_mutexattr_init(&m_attr);
        pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &m_attr);
        pthread_cond_init(&m_cond, nullptr);
    }

    ~HYSyncLock() {
        pthread_mutex_destroy(&m_mutex);
        pthread_mutexattr_destroy(&m_attr);
        pthread_cond_destroy(&m_cond);
    }

    int Lock() {
        return pthread_mutex_lock(&m_mutex);
    }

    int UnLock() {
        return pthread_mutex_unlock(&m_mutex);
    }

    int Wait() {
        return pthread_cond_wait(&m_cond, &m_mutex);
    }

    int Signal() {
        return pthread_cond_signal(&m_cond);
    }

private:

    pthread_mutexattr_t m_attr;
    pthread_cond_t m_cond;
    pthread_mutex_t m_mutex;

};


class HYScopedLock {

public:

    HYScopedLock(HYSyncLock *lock) : m_pLock(lock) {
        performLock();
    }

    ~HYScopedLock() {
        if (m_pLock != nullptr) {
            m_pLock->UnLock();
        }
    }

    void Wait() {
        if (m_pLock != nullptr) {
            m_pLock->Wait();
        }
    }

    void Signal() {
        if (m_pLock != nullptr) {
            m_pLock->Signal();
        }
    }

private:

    HYSyncLock *m_pLock;

    void performLock() {
        if (m_pLock != nullptr) {
            m_pLock->Lock();
        }
    }

};


#endif //HYNDKPLAYER_HYSCOPEDLOCK_H
