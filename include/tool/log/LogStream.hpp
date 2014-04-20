#ifndef LOG_STD_HPP
#define LOG_STD_HPP

#include <iostream>

#include "AbstractLog.hpp"

/// Standart output steam
/// Print the receive message into standart output (console by default)
class LogStream : public AbstractLog {

public:
    LogStream(std::ostream* stream);
    LogStream(std::ostream* stream, int type_accept);
    LogStream(const LogStream& origin);

    void send(std::string message);

    LogStream& operator=(const LogStream& origin);

private:
    std::ostream* _stream;

};

#endif // LOG_STD_H
