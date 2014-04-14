#ifndef THREAD_IMPLEMENT_WIN32_HPP
#define THREAD_IMPLEMENT_WIN32_HPP

#ifdef WIN32

#include <windows.h>
#include <iostream>
#include <string>
#include "tool/error/ErrorManager.hpp"
#include "tool/log/Log.hpp"
#include "tool/Convert.hpp"

class ThreadImpl_win32 {

    friend class Thread;

public:
    ThreadImpl_win32();

    template<class Tclass>
    void create(void(Tclass::*function)(void*), Tclass* instance, void* argument) {
        MemberFunction<Tclass>* arg = new MemberFunction<Tclass>(function, instance, argument);

        _thread = CreateThread(NULL, 0, MemberFunction<Tclass>::run, arg, 0, &_id);

        if(_thread == NULL)
            fatal_error("Thread create error : "+Ct::to_string((int)GetLastError()));
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

    DWORD _id;
    HANDLE _thread;


};

#endif

#endif
