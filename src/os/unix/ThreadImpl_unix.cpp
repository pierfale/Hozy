#ifdef UNIX

#include "os/unix/ThreadImpl_unix.hpp"

ThreadImpl_unix::ThreadImpl_unix() : _thread() {

}

void ThreadImpl_unix::join() {
    int err = pthread_join(_thread, NULL);
    if(err!= 0)
        throw_error_os(E_THREAD_JOIN_FAILED, err);
}

int ThreadImpl_unix::id() {
    return (unsigned int)_thread;
}

bool ThreadImpl_unix::is_alive() {
    return pthread_kill(_thread, 0) != ESRCH;
}

void ThreadImpl_unix::debug() {
    pthread_kill(_thread, SIGUSR1);
}

int ThreadImpl_unix::get_current_thread_id() {
    return (int)pthread_self();
}

void ThreadImpl_unix::create_thread_from_this() {
    _thread = pthread_self();
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

void ThreadImpl_unix::sig_usr1(int sig __attribute__((unused))) {
    debug_handler(false);
}

#endif
