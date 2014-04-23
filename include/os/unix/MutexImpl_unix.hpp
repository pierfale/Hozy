#ifndef MUTEX_IMPLEMENT_UNIX_HPP
#define MUTEX_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <pthread.h>
#include "tool/error/ErrorManager.hpp"

class MutexImpl_unix {

public:
    MutexImpl_unix();
    ~MutexImpl_unix();

    void lock();
    void unlock();
private:
    pthread_mutex_t _mutex;

};

#endif

#endif
