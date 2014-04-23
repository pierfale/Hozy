#ifndef DEBUG_IMPLEMENT_UNIX_HPP
#define DEBUG_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <execinfo.h>
#include <string>
#include <fstream>

#include "tool/Mutex.hpp"

#define STACK_MAX_SIZE 255


class DebugImpl_unix {

public:
    DebugImpl_unix();
    ~DebugImpl_unix();
    static void genrate_core_dump();
    static std::string print_call_stack();

private:
    static Mutex _mutex;
    static std::ofstream _file;
};

#endif
#endif
