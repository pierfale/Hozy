#include "os/unix/DebugImpl_unix.hpp"
#include "tool/log/Log.hpp"
#include "tool/Thread.hpp"

#ifdef UNIX

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
		free(str_c[i]);
    }
	free(str_c)
    return str;

}

#endif
