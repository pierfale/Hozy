#include "tool/log/LogFile.hpp"

LogFile::LogFile(std::string path) {
    _file.open(path.c_str(), std::ios::out | std::ios::trunc);
    if(!_file)
        std::cout << "Unable to open " << path << std::endl;
     _file << __DATE__ << " " << __TIME__ << std::endl;

}

LogFile::LogFile(std::string path, int level) {
    _file.open(path.c_str(), std::ios::out | std::ios::trunc);
    if(!_file)
        std::cout << "Unable to open " << path << std::endl;
     _file << __DATE__ << " " << __TIME__ << std::endl;
     _level = level;

}

LogFile::~LogFile() {
    _file.close();
}

void LogFile::send(std::string message) {
    if(_file) {
        _file << message;
    }
}

