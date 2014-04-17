#ifndef ERROR_MESSAGE_HPP
#define ERROR_MESSAGE_HPP

#include "tool/error/ErrorCode.hpp"
#include "tool/Convert.hpp"
#include <string>

std::string get_error_message(ErrorCode error_code);

#endif
