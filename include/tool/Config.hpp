#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <fstream>

#include "tool/error/ErrorManager.hpp"
#include "tool/ConfigData.hpp"

class Config {

public:
	virtual ~Config();

	template <class T>
	static void set(const std::string& key, T value) {
		ConfigData<T>::set(key, value);
	}

	template <class T>
	static void set_if_not_exist(const std::string& key, T value) {
		if(!ConfigData<T>::has(key))
			ConfigData<T>::set(key, value);
	}

	template <class T>
	static T get(const std::string& key) {
		return ConfigData<T>::get(key);
	}

	template <class T>
	static bool has(const std::string& key) {
		return ConfigData<T>::has(key);
	}

	template <class T>
	static void remove(const std::string& key) {
		return ConfigData<T>::remove(key);
	}


	static void save_config(const std::string& pathname);

protected:
	Config();
	void load_config(const std::string& pathname);
	virtual void default_value() = 0;

private:
	void eval_line(const std::string& line, unsigned int line_n, const std::string& pathname);
	static bool need_quote(const std::string& value);


};

/*
 * conver char* to string
 */
/*
template <>
void Config::set<const char*>(const std::string& key, const char* value);
template <>
void Config::set_if_not_exist<const char*>(const std::string& key, const char* value);
template <>
const char* Config::get<const char*>(const std::string& key);*/

#endif
