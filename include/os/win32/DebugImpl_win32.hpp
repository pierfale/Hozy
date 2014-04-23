#ifndef DEBUG_IMPLEMENT_WIN32_HPP
#define DEBUG_IMPLEMENT_WIN32_HPP

#include <string>
#include <cstring>
#include <windows.h>
#include <DbgHelp.h>

#define STACK_MAX_SIZE 255

class DebugImpl_win32 {

public:
	static std::string print_call_stack();

private:
	DebugImpl_win32();
};

#endif
