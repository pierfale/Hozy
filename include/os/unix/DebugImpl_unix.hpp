#ifndef DEBUG_IMPLEMENT_UNIX_HPP
#define DEBUG_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <execinfo.h>
#include <ucontext.h>
#include <string>

#define STACK_MAX_SIZE 255


class DebugImpl_unix {

public:
    DebugImpl_unix();
    ~DebugImpl_unix();
    static void print_call_stack(std::ofstream& file, bool use_save_context);
    static void save_context();

private:
    static void* _save_stack[STACK_MAX_SIZE];
    static int _save_stack_size;

};

#endif
#endif
