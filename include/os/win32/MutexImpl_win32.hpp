#ifndef MUTEX_IMPLEMENT_WIN32_HPP
#define MUTEX_IMPLEMENT_WIN32_HPP

#ifdef WIN32

#include <windows.h>
#include "tool/error/ErrorManager.hpp"

class MutexImpl_win32 {

public:
    MutexImpl_win32();
    ~MutexImpl_win32();

    void lock();
    void unlock();
private:
    HANDLE _mutex;

};

#endif

#endif
