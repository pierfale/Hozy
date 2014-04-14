#ifndef THREAD_HPP
#define THREAD_HPP

#include "ThreadManager.hpp"

#ifdef WIN32
#include "os/win32/ThreadImpl_win32.hpp"
#define THREAD_IMPLEMENTATION ThreadImpl_win32
#elif defined UNIX
#include "os/unix/ThreadImpl_unix.hpp"
#define THREAD_IMPLEMENTATION ThreadImpl_unix
#else
#error "This Operating system is unssuported"
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
    template<class Tclass>
    struct MemberFunction {
        MemberFunction(void(Tclass::*function)(void*), Tclass* instance, void* argument) : _function(function), _instance(instance), _argument(argument) {}
        void(Tclass::*_function)(void*);
        Tclass* _instance;
        void* _argument;
        static long unsigned int run(void* args) {
            MemberFunction<Tclass>* args_cast = (MemberFunction<Tclass>*)args;
            ((args_cast->_instance)->*(args_cast->_function))(args_cast->_argument);
            delete args_cast;
            return 0;
        }
    };

    static THREAD_IMPLEMENTATION impl;


};

#endif // THREAD_HPP
