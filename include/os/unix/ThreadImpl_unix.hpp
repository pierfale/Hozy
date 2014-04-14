#ifndef THREAD_IMPLEMENT_UNIX_HPP
#define THREAD_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <iostream>
#include "tool/Convert.hpp"
#include "tool/error/ErrorManager.hpp"
#include "tool/log/Log.hpp"

class ThreadImpl_unix {

public:
    ThreadImpl_unix();

    template<class Tclass>
    void create(void(Tclass::*function)(void*), Tclass* instance, void* argument) {
        MemberFunction<Tclass>* arg = new MemberFunction<Tclass>(function, instance, argument);

        if(pthread_create(&_id, NULL, MemberFunction<Tclass>::run, arg) != 0) {
            fatal_error("Thread create error : "+strerror(errno));
        }
    }

    void join();
    int id();
    static int get_current_thread_id();

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

    pthread_t _id;


};

#endif
#endif