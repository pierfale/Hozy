#include "tool/ConfigData.hpp"

template<>
int DataConvert<float, int>::convert(float origin) {
	return static_cast<int>(origin);
}

template<>
float DataConvert<float, int>::reverse_convert(int origin) {
	return static_cast<float>(origin);
}

template<>
bool DataConvert<float, int>::allowed(float origin) {
	return (float)((int)origin) == origin;
}

template<>
float DataConvert<std::string, float>::convert(std::string origin) {
	float tmp;
	std::stringstream ss(origin);
	ss >> tmp;
	return tmp;

}

template<>
std::string DataConvert<std::string, float>::reverse_convert(float origin) {
	std::stringstream ss;
	ss << origin;
	return ss.str();
}

template<>
bool DataConvert<std::string, float>::allowed(std::string origin) {
	float tmp;
	return (std::stringstream(origin) >> tmp);
}
