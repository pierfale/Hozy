#ifndef ABSTRACT_LOG_HPP
#define ABSTRACT_LOG_HPP

#include <string>

/// Abstract class which repesent an output stream
class AbstractLog {

public:
    /// Construct an output stream which treat message that have an higher level  than the parameter minLevel
    AbstractLog();

    virtual ~AbstractLog();

    /// Pure abstract method called when a standart stream is receive
    virtual void send(std::string message) = 0;

    /// return the level message which are treated
    int getLevel();

protected:
    int _level;
};

#endif // ABSTRACT_LOG_H
