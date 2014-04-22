#include "tool/Mutex.hpp"

Mutex::Mutex() : _impl() {

}

void Mutex::lock() {
	_impl.lock();
}

void Mutex::unlock() {
	_impl.unlock();
}
