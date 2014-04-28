#ifndef CONFIG_CLIENT_HPP
#define CONFIG_CLIENT_HPP

#include "tool/Config.hpp"
#include "tool/Singleton.hpp"

class ConfigClient : public Config, public Singleton<ConfigClient> {

    friend class Singleton<ConfigClient>;

public:
    virtual void initialize();
    virtual void destroy();

protected:


private:
    ConfigClient();

};

#endif
