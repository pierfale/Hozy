#ifdef WIN32

#include "os/win32/ThreadImpl_win32.hpp"

ThreadImpl_win32::ThreadImpl_win32() {

}

void ThreadImpl_win32::join() {
	if(WaitForSingleObject(_thread, INFINITE) == WAIT_FAILED) {
		throw_error_os(E_MUTEX_LOCK_FAILED , GetLastError());
	}
}

int ThreadImpl_win32::id() {
    return (int)_id;
}

bool ThreadImpl_win32::is_alive() {
	return WaitForSingleObject(_thread, 0) != WAIT_OBJECT_0;
}

int ThreadImpl_win32::get_current_thread_id() {
    return (int)GetCurrentThreadId();
}

void ThreadImpl_win32::sleep(unsigned int ms) {
	Sleep(ms);
}

#endif
