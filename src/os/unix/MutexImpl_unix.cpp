#include "os/unix/MutexImpl_unix.hpp"

#ifdef UNIX

MutexImpl_unix::MutexImpl_unix() : _mutex() {
    pthread_mutex_init(&_mutex, NULL);
}

MutexImpl_unix::~MutexImpl_unix() {
    int err;
    if((err = pthread_mutex_destroy(&_mutex)) != 0) {
        throw_error_os(E_MUTEX_DESTROY_FAILED , err);
    }
}

void MutexImpl_unix::lock() {
    int err;
    if((err = pthread_mutex_lock(&_mutex)) != 0) {
        throw_error_os(E_MUTEX_LOCK_FAILED , err);
    }
}

void MutexImpl_unix::unlock() {
    int err;
    if((err = pthread_mutex_unlock(&_mutex)) != 0) {
        throw_error_os(E_MUTEX_UNLOCK_FAILED , err);
    }
}


#endif
