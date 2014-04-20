#include "tool/log/LogFile.hpp"

LogFile::LogFile(std::string path) : AbstractLog(~0), _file() {
    _file.open(path.c_str(), std::ios::out | std::ios::trunc);
    if(!_file)
        std::cout << "Unable to open " << path << std::endl;
     _file << __DATE__ << " " << __TIME__ << std::endl;

}

LogFile::LogFile(std::string path, int type_accept) : AbstractLog(type_accept), _file() {
    _file.open(path.c_str(), std::ios::out | std::ios::trunc);
    if(!_file)
        std::cout << "Unable to open " << path << std::endl;
     _file << __DATE__ << " " << __TIME__ << std::endl;

}

LogFile::~LogFile() {
    _file.close();
}

void LogFile::send(std::string message) {
    if(_file) {
        _file << message;
    }
}

