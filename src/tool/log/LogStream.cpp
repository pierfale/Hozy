#include "tool/log/LogStream.hpp"

LogStream::LogStream(std::ostream* stream) : _stream(stream) {
    _level = 0;
}

LogStream::LogStream(std::ostream* stream, int level) : _stream(stream) {
    _level = level;

}

void LogStream::send(std::string message) {
    *_stream << message;
}
