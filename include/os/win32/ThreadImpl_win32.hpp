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
    void create(void(Tclass::*function)(), Tclass* instance) {
        MemberFunction<Tclass>* arg = new MemberFunction<Tclass>(function, instance);

        _thread = CreateThread(NULL, 0, MemberFunction<Tclass>::run, arg, 0, &_id);

        if(_thread == NULL)
            fatal_error("Thread create error : "+Ct::to_string((int)GetLastError()));
    }

    template<class Tclass, class Targs>
    void create(void(Tclass::*function)(Targs&), Tclass* instance, Targs& argument) {
        MemberFunctionArgs<Tclass, Targs>* arg = new MemberFunctionArgs<Tclass, Targs>(function, instance, argument);

        _thread = CreateThread(NULL, 0, MemberFunctionArgs<Tclass, Targs>::run, arg, 0, &_id);

        if(_thread == NULL)
            fatal_error("Thread create error : "+Ct::to_string((int)GetLastError()));
    }

    void join();
    int id();
    static int get_current_thread_id();

private:
    template<class Tclass>
    struct MemberFunction {
        MemberFunction(void(Tclass::*function)(), Tclass* instance) : _function(function), _instance(instance) {}
        void(Tclass::*_function)();
        Tclass* _instance;
        static long unsigned int run(void* args) {
            MemberFunction<Tclass>* args_cast = (MemberFunction<Tclass>*)args;
            ((args_cast->_instance)->*(args_cast->_function))();
            delete args_cast;
            return 0;
        }
    };

    template<class Tclass, class Targs>
    struct MemberFunctionArgs : MemberFunction<Tclass> {
        MemberFunctionArgs(void(Tclass::*function)(Targs&), Tclass* instance, Targs& argument) : MemberFunction<Tclass>(function, instance), _argument(argument) {}
        Targs& _argument;
        static long unsigned int run(void* args) {
            MemberFunctionArgs<Tclass, Targs>* args_cast = (MemberFunctionArgs<Tclass, Targs>*)args;
            ((args_cast->_instance)->*((void(Tclass::*)(Targs&))args_cast->_function))(args_cast->_argument);
            delete args_cast;
            return 0;
        }
    };

    DWORD _id;
    HANDLE _thread;


};

#endif

#endif
