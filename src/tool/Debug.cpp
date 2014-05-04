#include "tool/Debug.hpp"
#include "tool/log/Log.hpp"
#include "tool/Thread.hpp"

Mutex Debug::_mutex;
std::ofstream Debug::_file;

void Debug::init() {
    _file.open("core_dump", std::ios::out | std::ios::trunc);

    if(!_file) {
        Log::lerr << "Can't generate core dump in " << "core_dump" << std::endl;
    }
}

void Debug::set_exception(const Exception& e) {
    _file << "Exception throw : \n" << e.what() << std::endl;
    _file << std::endl;
}

void Debug::close() {
    _file.close();
}

void Debug::print_call_stack(bool use_save_context) {
    DEBUG_IMPLEMENTATION::print_call_stack(_file, use_save_context);
}

void Debug::save_context() {
    DEBUG_IMPLEMENTATION::save_context();
}

std::ofstream& Debug::get_file() {
	return _file;
}
