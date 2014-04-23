#include "tool/error/Exception.hpp"
#include "tool/Thread.hpp"

Exception::Exception(const std::string& file, const std::string& function, int line, int error_code) throw() : _file(file), _function(function), _line(line), _error_code(error_code), _os_error_code(0), _args(), _message()  {
    _message = "[Error] "+get_error_message(static_cast<ErrorCode>(_error_code))+"\n"+_file+" in "+_function+" at line "+ct::to_string(_line)+ " in thread "+ct::to_string(Thread::get_current_thread_id());
}

Exception::Exception(const std::string& file, const std::string& function, int line, int error_code, int os_error_code) throw() : _file(file), _function(function), _line(line), _error_code(error_code), _os_error_code(os_error_code), _args(), _message() {
    _message = "[Error] "+get_error_message(static_cast<ErrorCode>(_error_code))+" | Os error : "+os_message(_os_error_code)+"\n"+_file+" in "+_function+" at line "+ct::to_string(_line)+ " in thread "+ct::to_string(Thread::get_current_thread_id());
}

Exception::Exception(const std::string& file, const std::string& function, int line, int error_code, std::string args) throw() : _file(file), _function(function), _line(line), _error_code(error_code), _os_error_code(0), _args(args), _message() {
    _message = "[Error] "+get_error_message(static_cast<ErrorCode>(_error_code))+" ("+_args+") "+"\n"+_file+" in "+_function+" at line "+ct::to_string(_line)+ " in thread "+ct::to_string(Thread::get_current_thread_id());
}

