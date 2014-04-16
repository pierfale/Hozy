#ifndef THREAD_IMPLEMENT_UNIX_HPP
#define THREAD_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <iostream>
#include <string.h>
#include <pthread.h>
#include "tool/Function.hpp"
#include "tool/Convert.hpp"
#include "tool/error/ErrorManager.hpp"
#include "tool/log/Log.hpp"

class ThreadImpl_unix {

public:
    ThreadImpl_unix();

    template<class Tclass, class Treturn = void, class... Targs>
    void create(const MemberFunction<Tclass, Treturn, Targs...>& function) {
        if(pthread_create(&_thread, NULL, unix_static_call<Tclass, Treturn, Targs...>, (void*)&function) != 0) {
            fatal_error("Thread create error : "+std::string(strerror(errno)))
        }

        /*

        MemberFunction<Tclass>* arg = new MemberFunction<Tclass>(function, instance);

        if(pthread_create(&_thread, NULL, MemberFunction<Tclass>::run, arg) != 0) {
            fatal_error("Thread create error : "+std::string(strerror(errno)))
        }*/
    }

    template<class Tclass, class Treturn, class... Targs>
    void create(const Function<Treturn, Targs...>& function) {
     /*   MemberFunction<Tclass>* arg = new MemberFunction<Tclass>(function, instance, argument);

        if(pthread_create(&_thread, NULL, MemberFunction<Tclass>::run, arg) != 0) {
            fatal_error("Thread create error : "+std::string(strerror(errno)))
        }*/
    }

    void join();
    int id();
    static int get_current_thread_id();

private:
    pthread_t _thread;

    template<class Tclass, class Treturn, class... Targs>
    static void* unix_static_call(void* arg) {
        MemberFunction<Tclass, Treturn, Targs...>* function = (MemberFunction<Tclass, Treturn, Targs...>*)arg;
        function->call();
        return NULL;
    }


};

#endif
#endif
