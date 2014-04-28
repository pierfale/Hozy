#include "os/win32/DebugImpl_win32.hpp"
#include "tool/Convert.hpp"

#ifdef WIN32

CONTEXT DebugImpl_win32::_save_context;

DebugImpl_win32::DebugImpl_win32() {

}

void DebugImpl_win32::print_call_stack(std::ofstream& file, bool use_save_context) {
	print_call_stack(file, use_save_context, GetCurrentThread());
}

void DebugImpl_win32::print_call_stack(std::ofstream& file, bool use_save_context, HANDLE thread) {

	file << "Thread : " << GetThreadId(thread) << std::endl;

	if(use_save_context) {

	}

	const int max_name_size = 256;
	HANDLE process;
	CONTEXT context;
	PCONTEXT p_context;
	STACKFRAME64 stack;
	DWORD64 symbol_displacement = 0;
	DWORD line_displacement = 0;

	if(use_save_context) {
		p_context = &_save_context;
	}
	else {
		RtlCaptureContext(&context);
		p_context = &context;
	}


	memset(&stack, 0, sizeof(STACKFRAME64));

	process = GetCurrentProcess();

	#ifdef _M_IX86
		stack.AddrPC.Offset = p_context->Eip;
		stack.AddrStack.Offset = p_context->Esp;
		stack.AddrFrame.Offset = p_context->Ebp;
		DWORD machine_type = IMAGE_FILE_MACHINE_I386;
	#elif defined _M_X64
		stack.AddrPC.Offset = p_context->Rip;
		stack.AddrStack.Offset = p_context->Rsp;
		stack.AddrFrame.Offset = p_context->Rbp;
		DWORD machine_type = IMAGE_FILE_MACHINE_AMD64;
	#else
	#error "Machine not supported"
	#endif

	stack.AddrPC.Mode      = AddrModeFlat;
	stack.AddrStack.Mode   = AddrModeFlat;
	stack.AddrFrame.Mode   = AddrModeFlat;

	while(StackWalk64(machine_type, process, thread, &stack, p_context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
/*
		SYMBOL_INFO symbol;

		PSYMBOL_INFO p_symbol = &symbol;
		p_symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		p_symbol->MaxNameLen = max_name_size;*/

		ULONG64 buffer[(sizeof(SYMBOL_INFO)+max_name_size*sizeof(wchar_t)+sizeof(ULONG64)-1)/sizeof(ULONG64)];
		std::memset(buffer, 0, sizeof(buffer));
		PSYMBOL_INFO symbol = reinterpret_cast<PSYMBOL_INFO>(&buffer[0]);
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = max_name_size - 1;
		BOOL has_symbol = SymFromAddr(process, stack.AddrPC.Offset, &symbol_displacement, symbol);

		IMAGEHLP_LINE64  line;
		std::memset(&line, 0, sizeof(IMAGEHLP_LINE64));
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		BOOL has_line = SymGetLineFromAddr64(process, stack.AddrPC.Offset, &line_displacement, &line);

		if (has_symbol)
			file << std::string(symbol->Name) << " [0x" << stack.AddrPC.Offset << "+" << symbol_displacement << "]";
		else
			file << "(No symbol) [0x" << stack.AddrPC.Offset << "]";
		if (has_line) {
			file << " (" << ":" << line.LineNumber << ")";
		}

		file << std::endl;
	}
}

void DebugImpl_win32::save_context() {
	RtlCaptureContext(&_save_context);
}

#endif
