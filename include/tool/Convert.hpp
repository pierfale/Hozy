
#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <string>
#include <sstream>

class Ct {
public:

    static std::string to_string(int i) {
        std::stringstream s;
        s << i;
        return s.str();
    }

};

#endif
