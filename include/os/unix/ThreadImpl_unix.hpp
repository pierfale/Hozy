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
#include "ThreadManager.hpp"

class ThreadImpl_unix {

public:
    ThreadImpl_unix();

    template<class Tclass, class Treturn, class... Targs>
    void create(const MemberFunction<Tclass, Treturn, Targs...>& function, Targs... arguments) {
        MemberFunction<Tclass, Treturn, Targs...>* handler = new MemberFunction<Tclass, Treturn, Targs...>(function);
        handler->save_parameter(arguments...);
        int err = pthread_create(&_thread, NULL, proxy_member<Tclass, Treturn, Targs...>, handler);
        _thread_id.insert(std::pair<pthread_t, unsigned int>(_thread, _next_id++));
        if(err != 0)
            throw_error_os(E_THREAD_CREATE_FAILED, err);
    }

    void join(bool must_be_alive);
    int id();
    bool is_alive();
    void create_thread_from_this();
    void debug();

    static int get_current_thread_id();
    static void sleep(unsigned int ms);

    static void debug_handler(bool use_save_context);

private:
    pthread_t _thread;



    template<class Tclass, class Treturn, class... Targs>
    static void* proxy_member(void* arg) {
        struct sigaction sa;
        sa.sa_handler = sig_usr;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        sigaction (SIGUSR1, &sa, NULL);

        MemberFunction<Tclass, Treturn, Targs...>* handler = (MemberFunction<Tclass, Treturn, Targs...>*)arg;
        try {
            MemberFunction<Tclass, Treturn, Targs...>::static_call_with_saved_args(*handler);
        }
        catch(Exception const& e) {
            Log::lerr << std::string(e.what()) << std::endl;
            delete handler;

            Debug::init();
            Debug::set_exception(e);
            ThreadManager::debug_all();
            pthread_exit(nullptr);

        }
        delete handler;
        pthread_exit(nullptr);
    }

    static void sig_usr(int sig);
    static void sig_usr_main(int sig);
    static std::map<pthread_t, unsigned int> _thread_id;
    static unsigned int _next_id;


};

#endif
#endif
