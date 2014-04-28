#ifdef UNIX

#include "os/unix/ThreadImpl_unix.hpp"

std::map<pthread_t, unsigned int> ThreadImpl_unix::_thread_id;
unsigned int ThreadImpl_unix::_next_id(1);

ThreadImpl_unix::ThreadImpl_unix() : _thread() {

}

void ThreadImpl_unix::join(bool must_be_alive) {
    int err = pthread_join(_thread, NULL);
    if(err!= 0) {
        if(err != EINVAL || must_be_alive)
            throw_error_os(E_THREAD_JOIN_FAILED, err);
    }
}

int ThreadImpl_unix::id() {
    return _thread_id[_thread];
}

bool ThreadImpl_unix::is_alive() {
    return pthread_kill(_thread, 0) != ESRCH;
}

void ThreadImpl_unix::debug() {
    pthread_kill(_thread, SIGUSR1);
}

int ThreadImpl_unix::get_current_thread_id() {
    return _thread_id[pthread_self()];
}

void ThreadImpl_unix::create_thread_from_this() {
    _thread = pthread_self();
    _thread_id.insert(std::pair<pthread_t, unsigned int>(_thread, _next_id++));

    struct sigaction sa;
    sa.sa_handler = sig_usr_main;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
}

void ThreadImpl_unix::sleep(unsigned int ms) {
    if(usleep(ms) == -1) {
        if(errno != EINTR)
            throw_error_os(E_SLEEP_FAILED, errno);
    }
}

void ThreadImpl_unix::debug_handler(bool use_save_context) {
    Debug::print_call_stack(use_save_context);
}

void ThreadImpl_unix::sig_usr(int sig __attribute__((unused))) {
    debug_handler(false);
}

void ThreadImpl_unix::sig_usr_main(int sig __attribute__((unused))) {
    std::cout << "nop." << std::endl;
}

#endif
