#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#ifdef WIN32
#include <windows.h>
#elif defined UNIX
#include "string.h"
#endif

#include <string>
#include <exception>

#include "tool/error/ErrorCode.hpp"
#include "tool/error/ErrorMessage.hpp"

class Exception : public std::exception {

public:
    Exception(const std::string& file, const std::string& function, int line, int error_code) throw();

    Exception(const std::string& file, const std::string& function, int line, int error_code, int os_error_code) throw();

    Exception(const std::string& file, const std::string& function, int line, int error_code, std::string args) throw();

    virtual const char* what() const throw() {
        return _message.c_str();
    }

    int get_error_code() const {
        return _error_code;
    }

private:
    static std::string os_message(int os_error_code) {
#ifdef WIN32
		char *err;
		if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, os_error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &err, 0, NULL))
			return "";
		std::string msg(std::string(err)+" ("+ct::to_string(os_error_code)+")");
		LocalFree(err);
		return msg;
#elif defined UNIX
        return std::string(strerror(os_error_code))+" ("+ct::to_string(os_error_code)+")";
#endif
    }

    std::string _file;
    std::string _function;
    int _line;
    int _error_code;
    int _os_error_code;
    std::string _args;
    std::string _message;

};

#endif
