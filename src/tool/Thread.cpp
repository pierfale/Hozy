#include "tool/Thread.hpp"

Thread::Thread() : _impl() {

}

void Thread::join(bool must_be_alive) {
    _impl.join(must_be_alive);
}

int Thread::id() {
    return _impl.id();
}

bool Thread::is_alive() {
    return _impl.is_alive();
}

void Thread::debug() {
    _impl.debug();
}

void Thread::debug_self(bool use_save_context) {
	THREAD_IMPLEMENTATION::debug_self(use_save_context);
}

int Thread::get_current_thread_id() {
	   return THREAD_IMPLEMENTATION::get_current_thread_id();
}

Thread* Thread::create_thread_from_this() {
    Thread* thread = new Thread();
    thread->_impl.create_thread_from_this();
    return thread;
}

void Thread::sleep(unsigned int ms) {
	THREAD_IMPLEMENTATION::sleep(ms);
}
