#include "tool/Debug.hpp"
#include "tool/log/Log.hpp"
#include "tool/Thread.hpp"

Mutex Debug::_mutex;
std::ofstream Debug::_file("core_dump", std::ios::out | std::ios::trunc);

void Debug::genrate_core_dump() {
	_mutex.lock();

	if(_file) {
		Log::lout << "Generate core dump in " << "core_dump" << std::endl;
		_file << "Call Stack : Thread " << Thread::get_current_thread_id() << "\n" << std::endl;
		_file << print_call_stack() << std::endl;
		_file.flush();
	}
	else
		Log::lerr << "Can't generate core dump in " << "core_dump" << std::endl;
	_mutex.unlock();
}

std::string Debug::print_call_stack() {
	return DEBUG_IMPLEMENTATION::print_call_stack();
}
