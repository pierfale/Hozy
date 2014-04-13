#ifndef THREAD_HPP
#define THREAD_HPP

#include "ThreadManager.hpp"

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
        ThreadManager::add(this);
    }

    void join() {
        impl.join();
    }

    int id() {
        return impl.id();
    }

    static int get_current_thread_id() {
           return impl.get_current_thread_id();
    }

private:
    static THREAD_IMPLEMENTATION impl;


};

#endif // THREAD_HPP
