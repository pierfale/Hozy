#ifndef ERROR_MANAGER_HPP
#define ERROR_MANAGER_HPP

#include <iostream>

#define error(msg) Log::lerr << "[Error] " << msg << std::endl << "in " << __FUNCTION__ << " at line " << __LINE__ << " : " << __FILE__ << std::endl;
#define fatal_error(msg) { error(msg) exit(EXIT_FAILURE); }

void print_stack_call();

#endif
