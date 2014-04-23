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
	MutexImpl_win32(const MutexImpl_win32& origin);
	MutexImpl_win32& operator=(const MutexImpl_win32& origin);
    HANDLE _mutex;

};

#endif

#endif
