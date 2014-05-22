#include "tool/ConfigData.hpp"

template<>
int DataConvert<float, int>::convert(float origin) {
	return static_cast<int>(origin);
}

template<>
bool DataConvert<float, int>::allowed(float origin) {
	return (float)((int)origin) == origin;
}

/*
 *	int
 */

//Can concert float to int if number has 0 decimal
/*
template<>
template<>
bool ConfigData<int>::can_convert<float>(float origin, int* target) {
	if(origin == (float)static_cast<int>(origin)) {
		*target = static_cast<int>(origin);
		return true;
	}
	return false;
}


template <>
void ConfigData<int>::set(std::string key, int value) {
	auto it = _value.find(key);

	if(it != _value.end())
		it->second = value;
	else
		_value.insert(std::pair<std::string, int>(key, value));
}

template <>
int ConfigData<int>::get(std::string key) {
	auto it = _value.find(key);
	if(it != _value.end())
		return it->second;

	throw_error_args(E_CONFIG_NOT_FOUND, key);
}

template<>
bool ConfigData<int>::has(std::string key) {
	return _value.find(key) != _value.end();
}

template<>
std::vector<std::string> ConfigData<int>::get_key_set() {
	std::vector<std::string> set;

	for(auto it = _value.begin(); it != _value.end(); ++it)
		set.push_back(it->first);

	return set;
}
*/
/*
 * float
 */

//Can concert string to float if it's a number represented under a string
/*
template<>
template<>
bool ConfigData<float>::can_convert<std::string>(std::string origin, float* target) {
	std::stringstream ss(origin);
	if(ss >> (*target)) {
			return true;
	}
	return false;
}

template <>
void ConfigData<float>::set(std::string key, float value) {
	int convert;
	auto it = _value.find(key);

	if(it != _value.end())
		it->second = value;
	else if(ConfigData<int>::can_convert<float>(value, &convert)) {
		_remove(key, false);
		ConfigData<int>::set(key, convert);
	}
	else {
		ConfigData<int>::_remove(key, true);
		_value.insert(std::pair<std::string, float>(key, value));
	}
}


template <>
float ConfigData<float>::get(std::string key) {
	auto it = _value.find(key);
	if(it != _value.end())
		return it->second;

	if(ConfigData<int>::has(key))
		return static_cast<float>(ConfigData<int>::get(key));

	throw_error_args(E_CONFIG_NOT_FOUND, key);
}


template<>
bool ConfigData<float>::has(std::string key) {
	return _value.find(key) != _value.end() || ConfigData<int>::has(key);
}

template<>
void ConfigData<float>::_remove(std::string key, bool recursive) {
	auto it = _value.find(key);

	if(it != _value.end())
		_value.erase(it);

	if(recursive)
		ConfigData<int>::_remove(key, true);
}

template<>
std::vector<std::string> ConfigData<float>::get_key_set() {
	std::vector<std::string> set;

	for(auto it = _value.begin(); it != _value.end(); ++it)
		set.push_back(it->first);

	std::vector<std::string> set2 = ConfigData<int>::get_key_set();
	set.insert(set.end(), set2.begin(), set2.end());
	return set;
}
*/

/*
 * std::string
 */
/*
template<>
template<class T2>
bool ConfigData<std::string>::can_convert(T2 origin, std::string* target) {
	std::stringstream s;
	if(s << origin) {
		target->assign(s.str());
		return true;
	}
	return false;
}

template <>
void ConfigData<std::string>::set(std::string key, std::string value) {
	float convert;
	auto it = _value.find(key);

	if(it != _value.end())
		it->second = value;
	else if(ConfigData<float>::can_convert<std::string>(value, &convert)) {
		_remove(key, false);
		ConfigData<float>::set(key, convert);
	}
	else {
		ConfigData<float>::_remove(key, true);
		_value.insert(std::pair<std::string, std::string>(key, value));
	}
}

template <>
std::string ConfigData<std::string>::get(std::string key) {
	auto it = _value.find(key);
	if(it != _value.end())
		return it->second;

	if(ConfigData<float>::has(key))
		return ct::to_string(ConfigData<float>::get(key));

	throw_error_args(E_CONFIG_NOT_FOUND, key);
}


template<>
bool ConfigData<std::string>::has(std::string key) {
	std::cout << (_value.find(key) != _value.end()) << std::endl;
	return _value.find(key) != _value.end() || ConfigData<float>::has(key);
}

template<>
void ConfigData<std::string>::_remove(std::string key, bool recursive) {
	auto it = _value.find(key);

	if(it != _value.end())
		_value.erase(it);

	if(recursive)
		ConfigData<float>::_remove(key, true);
}


template<>
std::vector<std::string> ConfigData<std::string>::get_key_set() {
	std::vector<std::string> set;

	for(auto it = _value.begin(); it != _value.end(); ++it)
		set.push_back(it->first);

	std::vector<std::string> set2 = ConfigData<float>::get_key_set();
	set.insert(set.end(), set2.begin(), set2.end());
	return set;
}

*/
