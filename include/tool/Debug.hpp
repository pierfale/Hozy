#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef WIN32
#include "os/win32/DebugImpl_win32.hpp"
#define DEBUG_IMPLEMENTATION DebugImpl_win32
#elif defined UNIX
#include "os/unix/DebugImp^l_unix.hpp"
#define DEBUG_IMPLEMENTATION DebugImpl_unix
#else
#error "This Operating system is unsuported"
#endif

#include <fstream>
#include "tool/Mutex.hpp"

class Debug {

public:
	static void genrate_core_dump();
	static std::string print_call_stack();

private:
	Debug();
	static Mutex _mutex;
	static std::ofstream _file;
};

#endif
