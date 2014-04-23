#ifndef THREAD_IMPLEMENT_UNIX_HPP
#define THREAD_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <iostream>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "tool/Function.hpp"
#include "tool/Convert.hpp"
#include "tool/error/ErrorManager.hpp"
#include "tool/log/Log.hpp"

class ThreadImpl_unix {

public:
    ThreadImpl_unix();

    template<class Tclass, class Treturn, class... Targs>
    void create(const MemberFunction<Tclass, Treturn, Targs...>& function, Targs... arguments) {
        MemberFunction<Tclass, Treturn, Targs...>* handler = new MemberFunction<Tclass, Treturn, Targs...>(function);
        handler->save_parameter(arguments...);
        int err = pthread_create(&_thread, NULL, proxy_member<Tclass, Treturn, Targs...>, handler);

        if(err != 0)
            throw_error_os(E_THREAD_CREATE_FAILED, err);
    }

    void join();
    int id();
    bool is_alive();
    static int get_current_thread_id();
    static void sleep(unsigned int ms);

private:
    pthread_t _thread;

    template<class Tclass, class Treturn, class... Targs>
    static void* proxy_member(void* arg) {
        pthread_detach(pthread_self());
        MemberFunction<Tclass, Treturn, Targs...>* handler = (MemberFunction<Tclass, Treturn, Targs...>*)arg;
        try {
            MemberFunction<Tclass, Treturn, Targs...>::static_call_with_saved_args(*handler);
        }
        catch(Exception const& e) {
            Log::lerr << std::string(e.what()) << std::endl;
            delete handler;
            pthread_exit(nullptr);
        }
        delete handler;
        pthread_exit(nullptr);
    }



};

#endif
#endif
