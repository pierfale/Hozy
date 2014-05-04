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
	static void set(std::string key, T value) {
		ConfigData<T>::set(key, value);
	}

	template <class T>
	static void set_if_not_exit(std::string key, T value) {
		if(!ConfigData<T>::has(key))
			ConfigData<T>::set(key, value);
	}
	template <class T>
	static T get(std::string key) {
		return ConfigData<T>::get(key);
	}

protected:
	Config();
	void load_config(const std::string& pathname);
	virtual void default_value() = 0;

private:
	void eval_line(const std::string& line, unsigned int line_n, const std::string& pathname);


};

/*
 * conver char* to string
 */

template <>
void Config::set<const char*>(std::string key, const char* value);
template <>
const char* Config::get<const char*>(std::string key);


/*
class ConfigStoreProto {

public:
	virtual ~ConfigStoreProto() {}
	virtual bool has(std::string key) = 0;

	template<class T>
	virtual T try_convert(std::string key) = 0;
};


class Config {

public:

	virtual ~Config();

	template<class T>
	static void set(std::string key, T value) {
		 for(unsigned int i = 0; i < _list_store.size(); i++) {
			 if(_list_store.has(key))
		 }
	}

	template<class T>
	static T get(std::string key) {
		for(unsigned int i = 0; i < _list_store.size(); i++) {
			if(_list_store.has(key)) {
				_list_store.try_convert<T>(key);
			}
		}
   }

	static void _add_store(ConfigStoreProto* store);

protected:
	Config();
	void load_config(const std::string& pathname);
	virtual void default_value() = 0;

private:
	void eval_line(const std::string& line, unsigned int line_n, const std::string& pathname);
	static std::vector<ConfigStoreProto*> _list_store;

};

template<class T>
class ConfigStore : public ConfigStoreProto {

public:

	ConfigStore() : _value() {
		Config::_add_store(this);
	}

	static T& get(std::string key) {
		auto it = _instance->_value.find(key);

		if(it == _instance->_value.end())
			throw_error_args(E_CONFIG_NOT_FOUND, key+" ("+typeid(T).name()+")")
		else
			return it->second;
	}

	static void set(std::string key, T value) {
		_instance->_value.insert(std::pair<std::string, T>(key, value));
	}

	virtual bool has(std::string key) {
		return _instance->_value.find(key) != _instance->_value.end();
	}

private:
	static ConfigStore<T>* _instance;
	std::map<std::string, T> _value;


};

template<class T>
ConfigStore<T>* ConfigStore<T>::_instance(new ConfigStore<T>());


template<class T1, class T2>
class ConfigValueConvert {

public:
	static bool can_convert() { return false; }

};

template<>
class ConfigValueConvert<int, float> {

public:
	static bool can_convert() { return true; }
	static float convert(int t) {
		return (float)t;
	}
};
*/
#endif
