#include "os/win32/MutexImpl_win32.hpp"

#ifdef WIN32

MutexImpl_win32::MutexImpl_win32() : _mutex() {
	if((_mutex = CreateMutex(NULL, FALSE, NULL)) == NULL) {
		throw_error_os(E_MUTEX_CREATE_FAILED , GetLastError());
	}
}

MutexImpl_win32::MutexImpl_win32(const MutexImpl_win32& origin __attribute__((unused))) : _mutex() {

}


MutexImpl_win32::~MutexImpl_win32() {
    if(CloseHandle(_mutex) == 0) {
        throw_error_os(E_MUTEX_DESTROY_FAILED , GetLastError());
    }
}

void MutexImpl_win32::lock() {
	if(WaitForSingleObject(_mutex, INFINITE) == WAIT_FAILED) {
		throw_error_os(E_MUTEX_LOCK_FAILED , GetLastError());
	}
}

void MutexImpl_win32::unlock() {
	if(ReleaseMutex(_mutex) == 0) {
		throw_error_os(E_MUTEX_UNLOCK_FAILED , GetLastError());
	}
}

MutexImpl_win32& MutexImpl_win32::operator=(const MutexImpl_win32& origin __attribute__((unused))) {
	return *this;
}

#endif
