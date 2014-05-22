#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <string>
#include <map>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include "tool/error/ErrorManager.hpp"

template<class... Ttail>
struct save_tuple_type {

	static constexpr bool is_end() {
		return false;
	}

};

template<>
struct save_tuple_type<> {

	static constexpr bool is_end() {
		return true;
	}

};

template<class T>
struct get_parent_type {
	static void get() {}
};

template<>
struct get_parent_type<float> {
		static constexpr save_tuple_type<int> get() {return save_tuple_type<int>();}
};

template<>
struct get_parent_type<std::string> {
		static constexpr save_tuple_type<float, bool> get(){return save_tuple_type<float, bool>();}
};

template<>
struct get_parent_type<const char*> {
		static constexpr save_tuple_type<std::string> get(){return save_tuple_type<std::string>();}
};


template<int N>
struct get_tuple_type {
	template<class Head, class... Ttail>
	static auto process(save_tuple_type<Head, Ttail...>) -> decltype(get_tuple_type<N-1>::process(save_tuple_type<Ttail...>())) {
		return get_tuple_type<N-1>::process(save_tuple_type<Ttail...>());
	}

	template<class Head, class... Ttail>
	static constexpr bool is_end(save_tuple_type<Head, Ttail...>) {
		return get_tuple_type<N-1>::is_end(save_tuple_type<Ttail...>());
	}
};

template<>
struct get_tuple_type<0> {
	template<class Head, class... Ttail>
	static Head process(save_tuple_type<Head, Ttail...>) {
		return Head();
	}

	template<class... Ttail>
	static constexpr bool is_end(save_tuple_type<Ttail...>) {
		return save_tuple_type<Ttail...>::is_end();
	}
};

template<class Torigin, class Ttarget>
class DataConvert {

public:

	static Ttarget convert(Torigin origin __attribute__((__unused__))) {
		std::cerr << "Error convert data (" << typeid(Torigin).name() << "to" << typeid(Ttarget).name() << std::endl;
		return Ttarget();
	}

	static Torigin reverse_convert(Ttarget origin __attribute__((__unused__))) {
		std::cerr << "Error convert data (" << typeid(Ttarget).name() << "to" << typeid(Torigin).name() << std::endl;
		return Torigin();
	}


	static bool allowed(Torigin origin __attribute__((__unused__))) {
		return false;
	}
};

template<>
int DataConvert<float, int>::convert(float origin);
template<>
float DataConvert<float, int>::reverse_convert(int origin);
template<>
bool DataConvert<float, int>::allowed(float origin);

template<>
float DataConvert<std::string, float>::convert(std::string origin);
template<>
std::string DataConvert<std::string, float>::reverse_convert(float origin);
template<>
bool DataConvert<std::string, float>::allowed(std::string origin);

template <class T, int N>
struct is_valid_type {

	template<bool b = true>
	static constexpr typename std::enable_if<b && !std::is_void<decltype(get_parent_type<T>::get())>::value, bool>::type check() {
		return !get_tuple_type<N>::is_end(get_parent_type<T>::get());
	}

	template<bool b = true>
	static constexpr typename std::enable_if<b && std::is_void<decltype(get_parent_type<T>::get())>::value, bool>::type check() {
		return false;
	}
};


template <class T>
class ConfigData {

public:

	virtual ~ConfigData();

	/*
	 *	set
	 */
	template<int N>
	static typename std::enable_if<is_valid_type<T, N>::check(), bool>::type
	_set(std::string key , T value) {
		if(DataConvert<T, decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::allowed(value)) {
			ConfigData<decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::set(key, DataConvert<T, decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::convert(value));
			return true;
		}
		else
			return _set<N+1>(key, value);
	}

	template<int N>
	static typename std::enable_if<!is_valid_type<T, N>::check(), bool>::type
	_set(std::string key __attribute__((__unused__)), T value __attribute__((__unused__))) {
		return false;
	}

	/*
	 *	get
	 */

	template<int N>
	static typename std::enable_if<is_valid_type<T, N>::check(), T>::type
	_get(std::string key) {
		if(ConfigData<decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::has(key)) {
			return DataConvert<T, decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::reverse_convert(ConfigData<decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::get(key));
		}
		return _get<N+1>(key);
	}

	template<int N>
	static typename std::enable_if<!is_valid_type<T, N>::check(), T>::type
	_get(std::string key __attribute__((__unused__))) {
		return T();
	}

	/*
	 *	remove
	 */

	template<int N>
	static typename std::enable_if<is_valid_type<T, N>::check(), void>::type
	_remove(std::string key) {
		ConfigData<decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::remove(key);
		_remove<N+1>(key);
	}

	template<int N>
	static typename std::enable_if<!is_valid_type<T, N>::check(), void>::type
	_remove(std::string key __attribute__((__unused__))) {

	}

	/*
	 *	has
	 */

	template<int N>
	static typename std::enable_if<is_valid_type<T, N>::check(), bool>::type
	_has(std::string key) {
		return ConfigData<decltype(get_tuple_type<N>::process(get_parent_type<T>::get()))>::has(key) || _has<N+1>(key);
	}

	template<int N>
	static typename std::enable_if<!is_valid_type<T, N>::check(), bool>::type
	_has(std::string key __attribute__((__unused__))) {
		return false;
	}


	static bool set(std::string key, T value) {
		remove(key);
		return _set2(key, value);
	}

	static bool _set2(std::string key, T value) {
		if(_set<0>(key, value))
			return true;
		else {
			auto it = _value.find(key);

			if(it != _value.end())
				it->second = value;
			else
				_value.insert(std::pair<std::string, T>(key, value));

			return true;
		}
		return false;
	}

	static T get(std::string key) {
		if(!has(key))
			throw_error_args(E_CONFIG_NOT_FOUND, key);

		return _get2(key);
	}

	static T _get2(std::string key) {
		auto it = _value.find(key);

		if(it != _value.end())
			return it->second;

		return _get<0>(key);

	}

	static bool has(std::string key) {
		return _value.find(key) != _value.end() || _has<0>(key);
	}

	static void remove(std::string key) {
		auto it = _value.find(key);

		if(it != _value.end())
			_value.erase(it);
	}

	template<class T2>
	static bool can_convert(T2 origin __attribute__((__unused__)), T* target) {
		return false;
	}

	static std::vector<std::string> get_key_set() {
		std::vector<std::string> set;

		for(auto it = _value.begin(); it != _value.end(); ++it)
			set.push_back(it->first);

		return set;
	}

protected:
	ConfigData();


private:
	static std::map<std::string, T> _value;

};

template <class T>
std::map<std::string, T> ConfigData<T>::_value;

#endif
