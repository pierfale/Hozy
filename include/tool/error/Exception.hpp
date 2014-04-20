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

class Exception : std::exception {

public:
    Exception(const std::string& file, const std::string& function, int line, int error_code) throw() : _file(file), _function(function), _line(line), _error_code(error_code), _os_error_code(0)  {

    }

    Exception(const std::string& file, const std::string& function, int line, int error_code, int os_error_code) throw() : _file(file), _function(function), _line(line), _error_code(error_code), _os_error_code(os_error_code) {

    }

    virtual const char* what() const throw() {
		/*std::cout << get_error_message(static_cast<ErrorCode>(_error_code)) <<  std::endl;
		std::cout << os_message(_os_error_code) <<  std::endl;*/

		return std::string("[Error] "+get_error_message(static_cast<ErrorCode>(_error_code))+(_os_error_code != 0 ? " | Os error : "+os_message(_os_error_code) : "")+"\n"+_file+" in "+_function+" at line "+ct::to_string(_line)).c_str();
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

};

#endif
