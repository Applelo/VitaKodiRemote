#ifndef VITAKODIREMOTE_CONFIG_HH
#define VITAKODIREMOTE_CONFIG_HH


#include <string>

class Config {
private:
    std::string ip, username, password;
    int port;
public:
    Config();
    Config(const std::string &ip, const std::string &username, const std::string &password, int port);

    const std::string &getIp() const;

    const std::string &getUsername() const;

    const std::string &getPassword() const;

    int getPort() const;


};


#endif //VITAKODIREMOTE_CONFIG_HH
