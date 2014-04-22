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

int ThreadImpl_unix::get_current_thread_id() {
    return (int)pthread_self();
}

void ThreadImpl_unix::sleep(unsigned int ms) {
    if(usleep(ms) == -1) {
        throw_error(E_SLEEP_FAILED);
    }
}

#endif
