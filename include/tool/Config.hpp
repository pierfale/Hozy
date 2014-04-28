#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>

class Config  {

public:

    template<class T>
    void set(std::string key, T value) {
        ConfigStore<T>::set(key, value);
    }

    template<class T>
    T get(std::string key) {
        return ConfigStore<T>::get(value);
    }

protected:
    Config();
    void load_config(std::string pathname);
    virtual void default_value() = 0;

};



template<class T>
class ConfigStore {

public:

    static T& get(std::string key) {
        auto it = _value.find(key);

        if(it == _value.end())
            throw_error(E_CONFIG_NOT_FOUND);
        else
            return it->second;
    }

    static void set(std::string key, T value) {
        _value.insert(std::pair<std::string, T>(key, value));
    }

private:
    static std::map<std::string, T> _value;

}

#endif
