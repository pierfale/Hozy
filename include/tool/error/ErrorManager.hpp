#ifndef ERROR_MANAGER_HPP
#define ERROR_MANAGER_HPP

#include <iostream>
#include "tool/error/ErrorCode.hpp"
#include "tool/error/Exception.hpp"

#define error(msg) Log::lerr << "[Error] " << msg << std::endl << "in " << __FUNCTION__ << " at line " << __LINE__ << " : " << __FILE__ << std::endl;
#define fatal_error(msg) { error(msg) exit(EXIT_FAILURE); }
#define throw_error(code) throw Exception(__FILE__, __FUNCTION__, __LINE__, code);
#define throw_error_os(CODE_ERR,CODE_OS) {  int var_tmp = CODE_OS; throw Exception(__FILE__, __FUNCTION__, __LINE__, CODE_ERR, var_tmp); }


void print_stack_call();

#endif
