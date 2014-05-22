#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <string>
#include <map>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include "tool/error/ErrorManager.hpp"

/*
template<int Tindex>
struct get_tuple_type {

	template<class Thead, class... Ttail>
	auto operator()(std::tuple<Thead, Ttail...> _tuple) -> decltype(std::get<Tindex>(_tuple)) {
		return std::get<Tindex>(_tuple);
	}
};
*/

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
/*

template<class Thead>
struct save_tuple_type<Thead> {

	static void tail() {

	}

};*/


struct get_parent_type {
	//static constexpr save_tuple_type<std::string> get(const char*){return save_tuple_type<std::string>();}

	static constexpr save_tuple_type<float, bool> get(const char*){return save_tuple_type<float, bool>();}
	static constexpr save_tuple_type<int> get(float){return save_tuple_type<int>();}

	//leaf
	//static void get(int){}

	template<class T>
	static void get(T) {}
};


template<int N>
struct get_tuple_type {
//decltype(get_tuple_type<N-1>::process(save_tuple_type<Ttail...>()))>
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

/*
template<class Thead>
struct get_tuple_type<Thead> {

	Thead operator()() {
		return Thead();
	}
};*/


template<class Torigin, class Ttarget>
class DataConvert {

public:

	static Ttarget convert(Torigin origin __attribute__((__unused__))) {
		std::cerr << "Error convert data (" << typeid(Torigin).name() << "to" << typeid(Ttarget).name() << std::endl;
		return Ttarget();
	}

	static bool allowed(Torigin origin __attribute__((__unused__))) {
		return false;
	}
};

template<>
int DataConvert<float, int>::convert(float origin);
template<>
bool DataConvert<float, int>::allowed(float origin);

template <class T, int N>
struct is_valid_type {

	template<bool b = true>
	static constexpr typename std::enable_if<b && !std::is_void<decltype(get_parent_type::get(T()))>::value, bool>::type check() {
		return !get_tuple_type<N>::is_end(get_parent_type::get(T()));
	}

	template<bool b = true>
	static constexpr typename std::enable_if<b && std::is_void<decltype(get_parent_type::get(T()))>::value, bool>::type check() {
		return false;
	}
};


template <class T>
class ConfigData {

public:

	virtual ~ConfigData();

	template<int N>
	static typename std::enable_if<is_valid_type<T, N>::check(), bool>::type
	_set(std::string key , T value) {
/*
		std::cout << get_tuple_type<0>::is_end(save_tuple_type<float, bool>()) << std::endl;
		std::cout << "1->" << typeid(get_tuple_type<0>::process(save_tuple_type<float, bool>())).name() << std::endl;
		std::cout << get_tuple_type<1>::is_end(save_tuple_type<float, bool>()) << std::endl;
		std::cout << "2->" << typeid(get_tuple_type<1>::process(save_tuple_type<float, bool>())).name() << std::endl;
		std::cout << get_tuple_type<2>::is_end(save_tuple_type<float, bool>()) << std::endl;
		std::cout << "3->" << typeid(get_tuple_type<2>::process(save_tuple_type<float, bool>())).name() << std::endl;
*/
		if(DataConvert<T, decltype(get_tuple_type<N>::process(get_parent_type::get(T())))>::allowed(value)) {
			ConfigData<decltype(get_tuple_type<N>::process(get_parent_type::get(T())))>::set(key, DataConvert<T, decltype(get_tuple_type<N>::process(get_parent_type::get(T())))>::convert(value));
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


	static bool set(std::string key, T value) {


		//ConfigData<decltype(get_tuple_type<1>::process(get_parent_type::get(T())/*save_tuple_type<bool, int>()*/))>::display();
//		std::result_of<get_parent_type(T)>::type;
	//	ConfigData<class std::result_of<class get_tuple_type<0>(class std::result_of<get_parent_type(T)>::type)> >::display();



		if(_set<0>(key, value))
			return true;
		else {
			auto it = _value.find(key);

			if(it != _value.end())
				it->second = value;
			else
				_value.insert(std::pair<std::string, T>(key, value));

			std::cout << key << " insert into " << typeid(T).name() << std::endl;
			return true;
		}



		//ConfigData<class std::result_of<get_parent_type(T)>::type>::set(key, DataConvert<T, class std::result_of<get_tuple_type(class std::result_of<get_parent_type(T)>::type)>::type>::convert(key, value));

		//get_tuple_type::get<class std::result_of<get_parent_type(T)>::type>(get_parent_type(value));
		//std::cout << typeid(class ).name() << std::endl;

	/*	if(!std::is_same<class std::result_of<get_parent_type(T)>::type, void>::value)
			Test::set<std::result_of<get_parent_type(T)>::type>(key, DataConvert<T, class std::result_of<get_parent_type(T)>::type>::convert(key, value));*/

		return false;
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

	static void display() {
		std::cout << std::is_same<int, T>::value << std::endl;
		std::cout << std::is_same<bool, T>::value << std::endl;
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

/*
 * int
 */
/*
template<>
template<>
bool ConfigData<int>::can_convert<float>(float origin, int* target);
template<>
void ConfigData<int>::set(std::string key, int value);
template<>
int ConfigData<int>::get(std::string key);
template<>
bool ConfigData<int>::has(std::string key);
template<>
std::vector<std::string> ConfigData<int>::get_key_set();*/
/*
 * float
 */
/*
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
template<>
std::vector<std::string> ConfigData<float>::get_key_set();*/
/*
 * std::string
 */
/*
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
template<>
std::vector<std::string> ConfigData<std::string>::get_key_set();

template<>
class ConfigData<long> {

};


template<class Torigin, class Ttarget>
class DataConvert {

	static Ttarget convert(Torigin) {

	}
};
*/
//bool fn_ref(int);
/*
struct get_parent_type {
	std::tuple<float> operator()(std::string){return std::tuple<float>();}
};

template<class T>
class Test {

public:
	static void set(std::string key, T value) {

		if(!std::is_same<class std::result_of<get_parent_type(T)>::type, void>::value)
			Test::set<std::result_of<get_parent_type(T)>::type>(key, DataConvert<T, class std::result_of<get_parent_type(T)>::type>::convert(key, value));
	}

};*/


#endif
