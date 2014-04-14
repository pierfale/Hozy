#ifdef UNIX

#include "os/unix/ThreadImpl_unix.hpp"

ThreadImpl_unix::ThreadImpl_unix() {

}

void ThreadImpl_unix::join() {
    pthread_join(_thread, NULL);
}

int ThreadImpl_unix::id() {
    return (unsigned int)_thread;
}

int ThreadImpl_unix::get_current_thread_id() {
    return (int)pthread_self();
}

#endif
