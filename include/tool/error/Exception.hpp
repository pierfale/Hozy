#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#ifdef WIN32

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
        return std::string("[Error] "+get_error_message(static_cast<ErrorCode>(_error_code))+(_os_error_code != 0 ? " | Os error : "+os_message(_os_error_code) : "")+"\n"+_file+" in "+_function+" at line "+ct::to_string(_line)).c_str();
    }

    int error_code() {
        return _error_code;
    }

private:
    static std::string os_message(int os_error_code) {
#ifdef WIN32
        return to_string(os_error_code);
#elif defined UNIX
        return strerror(os_error_code);
#endif
    }

    std::string _file;
    std::string _function;
    int _line;
    int _error_code;
    int _os_error_code;

};

#endif
