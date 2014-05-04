#include "tool/Config.hpp"
#include "tool/error/ErrorManager.hpp"


Config::Config() {

}

Config::~Config() {

}

template <class T>
static void set(std::string key, T value) {
	ConfigData<T>::set(key, value);
}

template <class T>
static T get(std::string key) {
	return ConfigData<T>::get(key);
}

template <>
void Config::set<const char*>(std::string key, const char* value) {
	Config::set<std::string>(key, std::string(value));
}

template <>
const char* Config::get<const char*>(std::string key) {
	return Config::get<std::string>(key).c_str();
}


void Config::load_config(const std::string& pathname) {

	std::ifstream file(pathname, std::ios::in);
    unsigned int line_n = 1;

    if(file) {
        std::string line;

        while(std::getline(file, line)) {
			eval_line(line, line_n, pathname);
            line_n++;
        }
    }
    else
        throw_error_args(E_FILE_NOT_FOUND, pathname);
}

void Config::eval_line(const std::string& line, unsigned int line_n, const std::string& pathname) {
    bool first_char = true;
    bool word = false;
    int n_word = 0;
    unsigned int word_begin;
    std::string key, value;

    for(unsigned int i = 0; i < line.size(); i++) {
        char c = line.at(i);
        if(c == '#' && first_char) {
            return;
        }

        if(c == '=') {

        }

        if(!isspace(c) && c != '=') {
            if(!word) {
                first_char = false;
                word_begin = i;
                word = true;
            }
        }
        else {
            if(word) {
                std::string str = line.substr(word_begin, i-word_begin);
                if(n_word == 0)
                    key = str;
                else if(n_word == 1) {
                    if(str != "=") {
                        throw_error_args(E_CONFIG_FILE_FORMAT, "expected '=' line "+ct::to_string(line_n)+" in file "+pathname);
                    }
                }
                else if(n_word == 3) {
                    if(str.at(0) == '"' || str.at(0) == '\'') {
						if(str.size() == 1 || str.at(str.size()-1) != str.at(0))
							throw_error_args(E_CONFIG_FILE_FORMAT, "expected '"+ct::to_string(str.at(0))+"' line "+ct::to_string(line_n)+" in file "+pathname);
                        value = str.substr(1, str.length()-2);
                    }
                    else
                        value = str;
                }
                else {
					if(str.at(0) != '#')
						throw_error_args(E_CONFIG_FILE_FORMAT, "Unexpected word \""+str+"\"");
                }

				//set_eval(key, value);

                n_word++;

                word = false;
            }
        }
	}
}
