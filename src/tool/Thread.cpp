#include "tool/Thread.hpp"

Thread::Thread() {

}

void Thread::join() {
	impl.join();
}

int Thread::id() {
	return impl.id();
}

bool Thread::is_alive() {
	return impl.is_alive();
}

int Thread::get_current_thread_id() {
	   return THREAD_IMPLEMENTATION::get_current_thread_id();
}

void Thread::sleep(unsigned int ms) {
	THREAD_IMPLEMENTATION::sleep(ms);
}
