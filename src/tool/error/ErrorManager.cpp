#include "tool/error/ErrorManager.hpp"
#include "tool/Convert.hpp"

#ifdef WIN32

#include <windows.h>
#include <Dbghelp.h>

#define MAX_FRAME 255

void* get_rbp() {
    void* rbp = nullptr;
    asm("movq %rbp, -8(%rbp)");
    return rbp;
}

void print_stack_call() {
    /*void* stack[MAX_FRAME];
    USHORT size = CaptureStackBackTrace(0, MAX_FRAME, stack, NULL);

    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO)+256*sizeof(char), 1);
    symbol->MaxNameLen   = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    for(USHORT i=0; i<size; i++) {
       // SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
        std::cout << size-i-1 << std::endl;
    }*/

    void* rbp = get_rbp();

    while((rbp = *(void**)rbp) != nullptr) {
        std::cout << rbp << std::endl;
    }



}

#endif
