#ifndef THREAD_HPP
#define THREAD_HPP

#ifdef WIN32
#include "os/win32/ThreadImpl_win32.hpp"
#define THREAD_IMPLEMENTATION ThreadImpl_win32
#endif

class Thread {

public:
    Thread() {

    }

    template<class Tclass>
    void create(void(Tclass::*function)(void*), Tclass* instance, void* argument) {
        impl.create(function, instance, argument);
    }

private:
    static THREAD_IMPLEMENTATION impl;


};

THREAD_IMPLEMENTATION Thread::impl;

#endif // THREAD_HPP
