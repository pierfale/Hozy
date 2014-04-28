#ifndef DEBUG_IMPLEMENT_WIN32_HPP
#define DEBUG_IMPLEMENT_WIN32_HPP

#ifdef WIN32

#include <string>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <DbgHelp.h>

#define STACK_MAX_SIZE 255

class DebugImpl_win32 {

public:
	static void print_call_stack(std::ofstream& file, bool use_save_context);
	static void print_call_stack(std::ofstream& file, bool use_save_context, HANDLE thread);
	static void save_context();

private:
	DebugImpl_win32();

	struct Context {
		void* stack[STACK_MAX_SIZE];
	};

	static CONTEXT _save_context;
};

#endif

#endif
