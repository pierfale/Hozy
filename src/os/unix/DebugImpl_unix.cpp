#include "os/unix/DebugImpl_unix.hpp"
#include "tool/log/Log.hpp"
#include "tool/Thread.hpp"

#ifdef UNIX

void* DebugImpl_unix::_save_stack[STACK_MAX_SIZE];
int DebugImpl_unix::_save_stack_size(0);

DebugImpl_unix::DebugImpl_unix() {

}

DebugImpl_unix::~DebugImpl_unix() {

}

void DebugImpl_unix::print_call_stack(std::ofstream& file, bool use_save_context) {

    file << "Thread : " << Thread::get_current_thread_id() << std::endl;

    void* buffer[STACK_MAX_SIZE];
    void** p_buffer;
    int size;

    if(use_save_context) {
        std::cout << Thread::get_current_thread_id() << " : USE!" << std::endl;
        p_buffer = _save_stack;
        size = _save_stack_size;
    }
    else {
        std::cout << Thread::get_current_thread_id() << " : NO USE!" << std::endl;
        p_buffer = buffer;
        size = backtrace(buffer, STACK_MAX_SIZE);
    }

    char** str_c = backtrace_symbols(p_buffer, size);

    for(int i=0; i<size; i++) {
        file << str_c[i] << std::endl;
    }
    file << std::endl;
    free(str_c);

}

void DebugImpl_unix::save_context() {
     _save_stack_size = backtrace(_save_stack, STACK_MAX_SIZE);
}

#endif
