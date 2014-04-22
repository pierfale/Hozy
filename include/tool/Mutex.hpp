#ifndef MUTEX_HPP
#define MUTEX_HPP

#ifdef WIN32
#include "os/win32/MutexImpl_win32.hpp"
#define MUTEX_IMPLEMENTATION MutexImpl_win32
#elif defined UNIX
#include "os/unix/MutexImpl_unix.hpp"
#define MUTEX_IMPLEMENTATION MutexImpl_unix
#else
#error "This Operating system is not suported"
#endif

class Mutex {

public:
	Mutex();
	void lock();
	void unlock();

private:
	MUTEX_IMPLEMENTATION _impl;

};

#endif
