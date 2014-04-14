#ifdef UNIX

#include "os/unix/ThreadImpl_unix.hpp"

ThreadImpl_unix::ThreadImpl_unix() {

}

void ThreadImpl_unix::join() {
    pthread_join(_id, NULL);
}

int ThreadImpl_unix::id() {
    return (int)_id;
}

int ThreadImpl_unix::get_current_thread_id() {
    return (int)pthread_self();
}

#endif
