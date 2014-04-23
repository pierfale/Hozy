#ifndef DEBUG_WIN32_HPP
#define DEBUG_WIN32_HPP

#include <string>

class Debug_win32 {

public:
	static std::string backtrace();

private:
	Debug_win32();
};

#endif
