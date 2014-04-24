#include "os/win32/DebugImpl_win32.hpp"
#include "tool/Convert.hpp"

#ifdef WIN32

DebugImpl_win32::DebugImpl_win32() {

}

std::string DebugImpl_win32::print_call_stack() {
	std::string str;
	/*void* stack[STACK_MAX_SIZE];
	SYMBOL_INFO* symbol;
	HANDLE process;
	unsigned short frames;

	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	frames = CaptureStackBackTrace(0, STACK_MAX_SIZE, stack, NULL);
	symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO)+256*sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	for(unsigned int i = 0; i<frames; i++) {
		SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
		str += ct::to_string((int)(frames-i-1))+" : "+symbol->Name+" = "+ct::to_string((void*)(symbol->Address))+"\n";
	}

	free(symbol);*/

	const int max_name_size = 256;
	HANDLE process;
	HANDLE thread;
	CONTEXT context;
	STACKFRAME64 stack;
	DWORD64 symbol_displacement = 0;
	DWORD line_displacement = 0;

	RtlCaptureContext(&context);
	memset(&stack, 0, sizeof(STACKFRAME64));

	process = GetCurrentProcess();
	thread = GetCurrentThread();

	#ifdef _M_IX86
		stack.AddrPC.Offset = context.Eip;
		stack.AddrStack.Offset = context.Esp;
		stack.AddrFrame.Offset = context.Ebp;
		DWORD machine_type = IMAGE_FILE_MACHINE_I386;
	#elif defined _M_X64
		stack.AddrPC.Offset = context.Rip;
		stack.AddrStack.Offset = context.Rsp;
		stack.AddrFrame.Offset = context.Rbp;
		DWORD machine_type = IMAGE_FILE_MACHINE_AMD64;
	#else
	#error "Machine not supported"
	#endif

	stack.AddrPC.Mode      = AddrModeFlat;
	stack.AddrStack.Mode   = AddrModeFlat;
	stack.AddrFrame.Mode   = AddrModeFlat;

	BOOL ret;
	do {
		ret = StackWalk64(machine_type, process, thread, &stack, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL);
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
			str += std::string(symbol->Name)+" [0x"+ct::to_string((void*)stack.AddrPC.Offset)+"+"+ct::to_string((int)symbol_displacement)+"]";
		else
			str += "(No symbol) [0x"+ct::to_string((void*)stack.AddrPC.Offset)+"]";

		if (has_line) {
			str += " ("+std::string(line.FileName)+":"+ct::to_string((int)line.LineNumber)+")";
		}
		str += "\n";


	} while(ret);

	return str;
}

#endif
