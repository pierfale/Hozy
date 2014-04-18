#include "tool/log/AbstractLog.hpp"

AbstractLog::AbstractLog(int type_accept) : _type_accept(type_accept) {

}

AbstractLog::~AbstractLog() {

}

int AbstractLog::get_type_accept() {
    return _type_accept;
}
