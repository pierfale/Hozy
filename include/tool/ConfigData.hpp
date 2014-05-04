#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <string>
#include <map>
#include "tool/error/ErrorManager.hpp"

template <class T>
class ConfigData {

public:

	virtual ~ConfigData();

	static void set(std::string key, T value) {

		auto it = _value.find(key);

		if(it != _value.end())
			it->second = value;
		else
			_value.insert(std::pair<std::string, T>(key, value));
	}

	static T get(std::string key) {
		auto it = _value.find(key);

		if(it != _value.end())
			return it->second;

		throw_error_args(E_CONFIG_NOT_FOUND, key);
	}

	static bool has(std::string key) {
		return _value.find(key) != _value.end();
	}

	static void _remove(std::string key, bool recursive __attribute__((__unused__))) {
		auto it = _value.find(key);

		if(it != _value.end())
			_value.erase(it);
	}

	template<class T2>
	static bool can_convert(T2 origin __attribute__((__unused__)), T* target) {
		return false;
	}

protected:
	ConfigData();


private:
	static std::map<std::string, T> _value;

};

/*
 * int
 */

template<>
template<>
bool ConfigData<int>::can_convert<float>(float origin, int* target);
template<>
void ConfigData<int>::set(std::string key, int value);
template<>
int ConfigData<int>::get(std::string key);
template<>
bool ConfigData<int>::has(std::string key);
/*
 * float
 */

template<>
template<>
bool ConfigData<float>::can_convert<std::string>(std::string origin, float* target);
template<>
void ConfigData<float>::set(std::string key, float value);
template<>
float ConfigData<float>::get(std::string key);
template<>
bool ConfigData<float>::has(std::string key);
template<>
void ConfigData<float>::_remove(std::string key, bool recursive);
/*
 * std::string
 */

template<>
template<class T2>
bool ConfigData<std::string>::can_convert(T2 origin, std::string* target);
template<>
void ConfigData<std::string>::set(std::string key, std::string value);
template<>
std::string ConfigData<std::string>::get(std::string key);
template<>
bool ConfigData<std::string>::has(std::string key);
template<>
void ConfigData<std::string>::_remove(std::string key, bool recursive);

template <class T>
std::map<std::string, T> ConfigData<T>::_value;


#endif
