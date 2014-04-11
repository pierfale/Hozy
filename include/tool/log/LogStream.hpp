#ifndef LOG_STD_H
#define LOG_STD_H

#include <iostream>

#include "AbstractLog.hpp"

/// Standart output steam
/// Print the receive message into standart output (console by default)
class LogStream : public AbstractLog {

public:
    LogStream(std::ostream* stream);
    LogStream(std::ostream* stream, int level);
    void send(std::string message);

private:
    std::ostream* _stream;

};

#endif // LOG_STD_H
