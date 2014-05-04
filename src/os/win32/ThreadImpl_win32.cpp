#ifdef WIN32

#include "os/win32/ThreadImpl_win32.hpp"

ThreadImpl_win32::ThreadImpl_win32() : _id(0), _thread() {

}

ThreadImpl_win32::ThreadImpl_win32(const ThreadImpl_win32& origin __attribute__((unused))) : ThreadImpl_win32() {

}


ThreadImpl_win32::~ThreadImpl_win32() {
	if(CloseHandle(_thread) == 0) {
        throw_error_os(E_THREAD_DESTROY_FAILED , GetLastError());
	}
}

void ThreadImpl_win32::join(bool must_be_alive __attribute__((unused))) {
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

void ThreadImpl_win32::create_thread_from_this() {
	_thread = GetCurrentThread();
	_id = GetCurrentThreadId();
}

void ThreadImpl_win32::debug() {
	DEBUG_IMPLEMENTATION::print_call_stack(Debug::get_file(), false, _thread);
	TerminateThread(_thread, 0);
}

void ThreadImpl_win32::debug_self(bool use_save_context) {
	 Debug::print_call_stack(use_save_context);
}

int ThreadImpl_win32::get_current_thread_id() {
    return (int)GetCurrentThreadId();
}

void ThreadImpl_win32::sleep(unsigned int ms) {
	Sleep(ms);
}

ThreadImpl_win32& ThreadImpl_win32::operator=(const ThreadImpl_win32& origin __attribute__((unused))) {
	return *this;
}

#endif
