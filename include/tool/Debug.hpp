#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef WIN32
#include "os/win32/DebugImpl_win32.hpp"
#define DEBUG_IMPLEMENTATION DebugImpl_win32
#elif defined UNIX
#include "os/unix/DebugImpl_unix.hpp"
#define DEBUG_IMPLEMENTATION DebugImpl_unix
#else
#error "This Operating system is unsuported"
#endif

#include <fstream>
#include "tool/Mutex.hpp"
#include "tool/error/Exception.hpp"

class Debug {

public:

    static void init();
    static void set_exception(const Exception& e);
    static void print_call_stack(bool use_save_context = false);
    static void close();

    static void save_context();

private:
	Debug();
	static Mutex _mutex;
	static std::ofstream _file;
};

#endif
