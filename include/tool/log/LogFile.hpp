#ifndef LOG_FILE_H
#define LOG_FILE_H

#include <fstream>
#include <iostream>

#include "AbstractLog.hpp"

/// File output steam
/// Write the receive message into a file
class LogFile : public AbstractLog {

public:
    /// Create a file in specified path
    LogFile(std::string path);
    LogFile(std::string path, int level);
    ~LogFile();
    void send(std::string message);

private:

    /// File
    std::ofstream _file;

};
#endif // LOG_FILE_H
