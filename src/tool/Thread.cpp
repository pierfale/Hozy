#include "tool/Thread.hpp"

Thread::Thread() : _impl() {

}

void Thread::join() {
    _impl.join();
}

int Thread::id() {
    return _impl.id();
}

bool Thread::is_alive() {
    return _impl.is_alive();
}

int Thread::get_current_thread_id() {
	   return THREAD_IMPLEMENTATION::get_current_thread_id();
}

void Thread::sleep(unsigned int ms) {
	THREAD_IMPLEMENTATION::sleep(ms);
}
