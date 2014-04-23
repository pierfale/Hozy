#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef WIN32
#include "os/win32/Debug_win32.hpp"
#define DEBUG_IMPLEMENTATION Debug_win32
#elif defined UNIX
#include "os/unix/Debug_unix.hpp"
#define DEBUG_IMPLEMENTATION Debug_unix
#else
#error "This Operating system is unsuported"
#endif


class Debug {

public:
	static std::string backtrace();
	static void generate_core_dump(std::string pathname);

private:
	Debug();
};

#endif
