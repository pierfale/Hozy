#ifdef WIN32

#include "os/win32/ThreadImpl_win32.hpp"

ThreadImpl_win32::ThreadImpl_win32() {

}

void ThreadImpl_win32::join() {
    WaitForSingleObject(_thread, INFINITE);
}

int ThreadImpl_win32::id() {
    return (int)_id;
}

int ThreadImpl_win32::get_current_thread_id() {
    return (int)GetCurrentThreadId();
}

#endif
