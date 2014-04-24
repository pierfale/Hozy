
#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <string>
#include <sstream>

class ct {
public:

    static std::string to_string(int i) {
        std::stringstream s;
        s << i;
        return s.str();
    }

    static std::string to_string(unsigned int i) {
        std::stringstream s;
        s << i;
        return s.str();
    }

	static std::string to_string(void* i) {
		std::stringstream s;
		s << std::hex << i;
		return s.str();
	}

	static std::string to_hex_string(int i) {
		std::stringstream s;
		s << std::hex << i;
		return s.str();
	}

	static std::string to_hex_string(unsigned int i) {
		std::stringstream s;
		s << std::hex << i;
		return s.str();
	}


    static std::string uint64_to_hex_string(uint64_t i) {
        std::stringstream s;
        s << std::hex << i;
        return s.str();
    }
};

#endif
