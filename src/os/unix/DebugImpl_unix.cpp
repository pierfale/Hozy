#include "os/unix/DebugImpl_unix.hpp"
#include "tool/log/Log.hpp"
#include "tool/Thread.hpp"

Mutex DebugImpl_unix::_mutex;
std::ofstream DebugImpl_unix::_file("core_dump", std::ios::out | std::ios::trunc);

DebugImpl_unix::DebugImpl_unix() {

}

DebugImpl_unix::~DebugImpl_unix() {

}

std::string DebugImpl_unix::print_call_stack() {
    void* buffer[STACK_MAX_SIZE];

    int n =  backtrace(buffer, STACK_MAX_SIZE);

    char** str_c = backtrace_symbols(buffer,n);
    std::string str;

    for(int i=0; i<n; i++) {
        str += std::string(str_c[i])+"\n";
    }
    return str;

}

void DebugImpl_unix::genrate_core_dump() {
    _mutex.lock();

    if(_file) {
        Log::lout << "Generate core dump in " << "core_dump" << std::endl;
        _file << "Call Stack : Thread " << Thread::get_current_thread_id() << "\n" << std::endl;
        _file << print_call_stack() << std::endl;
        _file.flush();
    }
    else
        Log::lerr << "Can't generate core dump in " << "core_dump" << std::endl;
    std::cout << "OK =>" << std::endl << print_call_stack() << std::endl;
    _mutex.unlock();
}
