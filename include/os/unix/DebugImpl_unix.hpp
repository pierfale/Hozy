#ifndef DEBUG_IMPLEMENT_UNIX_HPP
#define DEBUG_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <execinfo.h>
#include <string>

#define STACK_MAX_SIZE 255


class DebugImpl_unix {

public:
    DebugImpl_unix();
    ~DebugImpl_unix();
    static std::string print_call_stack();

};

#endif
#endif
